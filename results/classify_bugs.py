#!/usr/bin/env python3
"""Classify bug reports using Claude API with vbdb source and HTML context."""

import json
import re
from html.parser import HTMLParser
from pathlib import Path

import anthropic

SCRIPT_DIR = Path(__file__).parent
ESEM_DIR = SCRIPT_DIR / "ESEM_26"
BUG_REPORTS_DIR = ESEM_DIR / "bug_reports"
VBDB_DIR = ESEM_DIR / "vbdb"
VBDB_HTML_DIR = ESEM_DIR / "vbdb.bitbucket.io"
OUTPUT_FILE = ESEM_DIR / "2.0_classifications.json"

MODEL = "claude-sonnet-4-6"

SYSTEM_PROMPT = """You are a research assistant classifying bug reports produced by Sugarlyzer, a variability-aware static analyzer for highly-configurable C programs.

## Background

Highly-configurable programs like BusyBox and the Linux kernel use #ifdef directives to include or exclude code depending on build-time configuration flags.

We are testing three strategies to find bugs using static analysis in highly-configurable systems.

You will be working with bug reports produced by static analysis tools.

Each bug report includes a **presence condition (PC)** — a boolean formula over configuration flags that describes when the reported alarm applies.

Your task: classify each report using the labels below.

## Classification Labels

- **TRUE**: Real bug present in the VarBugs Database (vbdb). PC is correctly constrained.
- **TRUE_NEW**: Real bug NOT in vbdb. PC is correctly constrained.
- **TRUE_OVER**: Real bug (in vbdb), but PC is over-constrained — too restrictive, misses configurations where the bug occurs.
- **TRUE_UNDER**: Real bug (in vbdb), but PC is under-constrained — too broad, includes configurations where the bug does NOT occur.
- **TRUE_NEW_OVER**: New real bug (not in vbdb), PC over-constrained.
- **TRUE_NEW_UNDER**: New real bug (not in vbdb), PC under-constrained.
- **FALSE**: False positive — not a real bug.

## Key Analysis Principles

**Only analyze the source code given.**
These bug reports are from excerpts of well-known programs. Only reason based on the snippet of source code given to you. For example, for a dead store report, only think about the code that is provided; do not infer that the variable is used elsewhere in the real code.

**Contradictory configurations → FALSE**
If a macro X is defined by #define when flag Y=T, then a PC saying X=F AND Y=T is contradictory (infeasible). Such alarms are false positives.

**Library macros make PCs over-constrained**
Macros like `_STDLIB_H`, `__need_malloc_and_calloc`, `__STRICT_ANSI__`, `__need___FILE`, `__USE_EXTERN_INLINES`, `OS2` are C library internals, not real feature flags. In real compilation, stdlib.h IS included (so `_STDLIB_H=T`). A PC requiring `!_STDLIB_H` or `!__need_malloc_and_calloc` restricts to non-real library states → typically over-constrained.

**Desugaring artifacts → FALSE (for TRANSFORMATION reports)**
TRANSFORMATION reports come from desugared code. Desugaring converts #ifdef blocks into separate if() blocks. This can produce spurious alarms:
- A variable declared in one if(FLAG) block may appear uninitialized in another if(FLAG) block, even though in real compilation both blocks always execute together.
- Struct/type renamings in the desugared file causing sizeof mismatches that don't exist in real code.
If the alarm only makes sense in the desugared model and would not exist when compiled normally, it is FALSE.

**Presence condition correctness**
Compare the PC to the actual code structure:
- Which #ifdef guards enclose the buggy code?
- Are the PC flags consistent with those guards?
- Does the PC include impossible flag combinations?
- Does the PC miss valid combinations where the bug still occurs?

**vbdb entry tells you if the bug is known**
If the source file has a vbdb entry and the alarm corresponds to the documented bug (same location, same type), classify TRUE (known bug). If it's a different bug at a different location/type not in vbdb, classify TRUE_NEW. If there is no vbdb entry, the bug is new.

**// ERROR comments mark known bug locations**
In the vbdb source files, lines marked `// ERROR` or `// (N) ERROR` indicate known bug locations from the vbdb database.

## Output Format

Respond with valid JSON only — no other text:
{"classification": "<LABEL>", "reasoning": "<2-5 sentence justification>"}"""


class HTMLTextExtractor(HTMLParser):
    def __init__(self):
        super().__init__()
        self._parts = []
        self._skip = False

    def handle_starttag(self, tag, _attrs):
        if tag in ("script", "style", "head"):
            self._skip = True

    def handle_endtag(self, tag):
        if tag in ("script", "style", "head"):
            self._skip = False

    def handle_data(self, data):
        if not self._skip:
            stripped = data.strip()
            if stripped:
                self._parts.append(stripped)

    def get_text(self):
        return "\n".join(self._parts)


def html_to_text(html):
    parser = HTMLTextExtractor()
    parser.feed(html)
    return parser.get_text()


def get_source_filename(report):
    if "input_file" in report:
        return Path(report["input_file"]).name
    if "originalFile" in report:
        return Path(report["originalFile"]).name
    if "originalAlarm" in report:
        loc = report["originalAlarm"].get("fileLocation", "")
        name = Path(loc).name
        # Strip .desugared suffix to get the original file
        name = name.replace(".desugared.c", ".c")
        return name
    return None


def get_source_code(source_filename):
    if not source_filename:
        return "(source file not found)"
    path = VBDB_DIR / source_filename
    if path.exists():
        return path.read_text()
    return f"(source file '{source_filename}' not found)"


def get_vbdb_content(source_filename):
    if not source_filename:
        return "(no vbdb entry)"
    stem = Path(source_filename).stem
    hash7 = stem[:7]
    for subdir in VBDB_HTML_DIR.iterdir():
        if not subdir.is_dir():
            continue
        html_path = subdir / f"{hash7}.html"
        if html_path.exists():
            return html_to_text(html_path.read_text())
    return "(no vbdb entry found for this file)"


def build_report_summary(report):
    summary = {"id": report.get("id"), "strategy": report.get("strategy", "family")}

    if "err" in report:
        # FAMILY report
        summary["error"] = report.get("err", "")
        summary["warning"] = report.get("msg", "")
        summary["taxonomy_type"] = report.get("taxonomy_type", "")
        summary["line_number"] = report.get("line_number")
        match = re.search(r'\[(.+?)\]', report.get("err", ""))
        if match:
            summary["presence_condition"] = match.group(1)
    else:
        # PRODUCT or TRANSFORMATION report
        alarm = report.get("originalAlarm", {})
        summary["alarm_type"] = alarm.get("alarmType")
        summary["description"] = alarm.get("description")
        summary["file"] = alarm.get("fileLocation")
        summary["line"] = alarm.get("line")
        if "sanitizedDescription" in report:
            summary["sanitized_description"] = report["sanitizedDescription"]
        if "lineInputFile" in report:
            summary["line_in_original_file"] = report["lineInputFile"]
        summary["presence_condition"] = report.get("presenceCondition", "")
        if "feasible" in report:
            summary["feasible"] = report["feasible"]

    return json.dumps(summary, indent=2)


def _call_api(client, user_content, thinking):
    kwargs = dict(
        model=MODEL,
        max_tokens=8000,
        thinking=thinking,
        system=[
            {
                "type": "text",
                "text": SYSTEM_PROMPT,
                "cache_control": {"type": "ephemeral"},
            }
        ],
        messages=[{"role": "user", "content": user_content}],
    )
    with client.messages.stream(**kwargs) as stream:
        return stream.get_final_message()


def _extract_response(message):
    """Return text block content, falling back to scanning thinking blocks for JSON."""
    text = next(
        (b.text for b in message.content if b.type == "text"),
        ""
    ).strip()
    if text:
        return text

    # Edge case: model put its answer inside the thinking block instead of text.
    # Scan for the expected JSON shape.
    for block in message.content:
        if block.type == "thinking":
            thinking_text = getattr(block, "thinking", "") or ""
            match = re.search(
                r'\{\s*"classification"\s*:.*?"reasoning"\s*:.*?\}',
                thinking_text,
                re.DOTALL,
            )
            if match:
                return match.group(0)

    return ""


def _parse_json(text):
    # Try a ```json ... ``` code fence first
    fence = re.search(r'```(?:json)?\s*(\{.*?\})\s*```', text, re.DOTALL)
    if fence:
        return json.loads(fence.group(1))

    # Fall back to finding a bare JSON object anywhere in the text
    obj = re.search(r'\{[^{}]*"classification"[^{}]*"reasoning"[^{}]*\}', text, re.DOTALL)
    if obj:
        return json.loads(obj.group(0))

    # Last resort: treat the whole text as JSON (original behaviour)
    return json.loads(text.strip())


def classify_report(client, report):
    source_filename = get_source_filename(report)
    source_code = get_source_code(source_filename)
    vbdb_content = get_vbdb_content(source_filename)
    report_summary = build_report_summary(report)

    user_content = f"""## Bug Report
{report_summary}

## Source File: {source_filename or "unknown"}
```c
{source_code}
```

## VarBugs Database Entry
{vbdb_content}

Classify this bug report."""

    # Attempt 1: adaptive thinking
    message = _call_api(client, user_content, thinking={"type": "adaptive"})
    text = _extract_response(message)

    # Attempt 2: thinking disabled — forces a plain text block every time
    if not text:
        block_types = [b.type for b in message.content]
        print(f"(no text block, blocks={block_types}, retrying without thinking)", end=" ", flush=True)
        message = _call_api(client, user_content, thinking={"type": "disabled"})
        text = _extract_response(message)

    if not text:
        raise ValueError(f"Empty response after retry. Blocks: {[b.type for b in message.content]}")

    return _parse_json(text)


def main():
    client = anthropic.Anthropic()

    # Load existing results for resume support
    results = {}
    if OUTPUT_FILE.exists():
        with open(OUTPUT_FILE) as f:
            existing = json.load(f)
        if isinstance(existing, list):
            results = {
                item["id"]: item
                for item in existing
                if item.get("classification") not in ("", "ERROR", None)
            }
        else:
            results = {
                k: v
                for k, v in existing.items()
                if v.get("classification") not in ("", "ERROR", None)
            }

    report_files = sorted(BUG_REPORTS_DIR.glob("*.json"))
    total = len(report_files)
    print(f"Found {total} bug reports. {len(results)} already classified.")

    for i, path in enumerate(report_files, 1):
        with open(path) as f:
            try:
                report = json.load(f)
            except json.JSONDecodeError:
                print(f"[{i}/{total}] {path.stem}: ERROR (invalid JSON)")
                continue

        report_id = report.get("id", path.stem)

        if report_id in results:
            print(f"[{i}/{total}] {report_id}: skipping ({results[report_id]['classification']})")
            continue

        print(f"[{i}/{total}] {report_id}: classifying...", end=" ", flush=True)
        try:
            result = classify_report(client, report)
            results[report_id] = {
                "id": report_id,
                "old_id": report.get("old_id"),
                "classification": result["classification"],
                "reasoning": result["reasoning"],
            }
            print(result["classification"])
        except Exception as e:
            print(f"ERROR: {e}")

            results[report_id] = {
                "id": report_id,
                "old_id": report.get("old_id"),
                "classification": "ERROR",
                "reasoning": str(e),
            }

        # Save after each report to support resuming
        try:
            output_list = sorted(results.values(), key=lambda x: x.get("id", ""))
            with open(OUTPUT_FILE, "w") as f:
                json.dump(output_list, f, indent=2)
        except Exception as save_err:
            print(f"  WARNING: could not save results: {save_err}")

    classified = sum(
        1 for v in results.values()
        if v.get("classification") not in ("ERROR", None)
    )
    print(f"\nDone. {classified}/{total} successfully classified.")
    print(f"Results written to {OUTPUT_FILE}")


if __name__ == "__main__":
    main()
