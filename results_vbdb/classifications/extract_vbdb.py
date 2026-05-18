#!/usr/bin/env python3
"""Extract commit hash, bug type, and error line number from VBDB HTML files."""

import csv
import html
import re
import sys
from pathlib import Path


def extract_info(html_path: Path) -> dict:
    text = html_path.read_text(encoding="utf-8")

    # Commit hash: text content of the anchor inside "Bug fixed by commit"
    commit = ""
    commit_match = re.search(
        r"Bug fixed by commit\s*<a[^>]*>([^<]+)</a>", text
    )
    if commit_match:
        commit = commit_match.group(1).strip()

    # Bug type: second <td> in the row whose first <td> contains "Type"
    bug_type = ""
    type_match = re.search(
        r"<b>Type</b></td>\s*<td>\s*([^<]+?)\s*</td>", text
    )
    if type_match:
        bug_type = type_match.group(1).strip()

    # Error line number: count lines in the 'simple' tabcontent <pre> block
    error_line = ""
    simple_match = re.search(
        r"<div id='simple' class='tabcontent'><pre>(.*?)</pre></div>",
        text,
        re.DOTALL,
    )
    if simple_match:
        code_block = html.unescape(simple_match.group(1))
        lines = code_block.split("\n")
        for i, line in enumerate(lines, start=1):
            if "// ERROR" in line:
                error_line = str(i)
                break

    return {
        "file": html_path.name,
        "commit": commit,
        "type": bug_type,
        "error_line": error_line,
    }


def main():
    root = Path(__file__).parent / "vbdb.bitbucket.io"
    skip = {"index.html", "database.html"}

    html_files = sorted(
        p for p in root.rglob("*.html") if p.name not in skip
    )

    if not html_files:
        print("No HTML files found.", file=sys.stderr)
        sys.exit(1)

    output = Path(__file__).parent / "vbdb_extracted.csv"
    with output.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=["file", "commit", "type", "error_line"])
        writer.writeheader()
        for p in html_files:
            writer.writerow(extract_info(p))

    print(f"Wrote {len(html_files)} rows to {output}")


if __name__ == "__main__":
    main()
