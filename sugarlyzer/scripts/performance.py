import os
import re
import argparse
from collections import defaultdict

p = argparse.ArgumentParser(description="Run performance tests on Sugarlyzer")
p.add_argument("directory", help="Directory containing the performance test results")
args = p.parse_args()

TOOLS = {"clang", "infer"}
TARGETS = {"busybox", "axtls", "toybox"}
STRATEGIES = {"product", "transformation"}

times = defaultdict(lambda: defaultdict(list))

for trial in os.listdir(args.directory):
    trial_path = os.path.join(args.directory, trial)
    if not os.path.isdir(trial_path) or not trial.isdigit():
        continue
    for filename in os.listdir(trial_path):
        if not filename.endswith(".log"):
            continue
        stem = filename[:-4]
        parts = stem.split("_", 2)
        if len(parts) != 3:
            continue
        tool, target, strategy = parts
        if tool not in TOOLS or target not in TARGETS or strategy not in STRATEGIES:
            continue
        key = stem
        with open(os.path.join(trial_path, filename)) as f:
            for line in f:
                m = re.match(r"Analysis time:\s*([\d.]+)", line)
                if m:
                    times[key]["analysis"].append(float(m.group(1)))
                if strategy == "product":
                    m = re.match(r"Deduplication time:\s*([\d.]+)", line)
                    if m:
                        times[key]["deduplication"].append(float(m.group(1)))
                elif strategy == "transformation":
                    m = re.match(r"Build time:\s*([\d.]+)", line)
                    if m:
                        times[key]["desugaring"].append(float(m.group(1)))

METRIC_LABELS = {
    "analysis": "analysis time",
    "deduplication": "deduplication time",
    "desugaring": "desugaring time",
}

for tool in sorted(TOOLS):
    for target in sorted(TARGETS):
        for strategy in sorted(STRATEGIES):
            key = f"{tool}_{target}_{strategy}"
            if key not in times:
                continue
            metrics = ["analysis", "deduplication"] if strategy == "product" else ["analysis", "desugaring"]
            for metric in metrics:
                vals = times[key].get(metric, [])
                if vals:
                    avg = sum(vals) / len(vals)
                    print(f"Average {METRIC_LABELS[metric]} for {key}: {avg:.4f}")
                else:
                    print(f"Average {METRIC_LABELS[metric]} for {key}: N/A")
