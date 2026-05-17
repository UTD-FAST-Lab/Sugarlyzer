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


def avg(vals):
    return sum(vals) / len(vals) if vals else None


def cell(val):
    if val is None:
        return "-"
    return f"{{{val / 1000:.1f}}}"


TARGET_ORDER = ["axtls", "toybox", "busybox"]
TARGET_MACROS = {"axtls": r"\axtls", "toybox": r"\toybox", "busybox": r"\busybox"}
TOOL_MACROS = {"clang": r"\clang", "infer": r"\infer"}

print(r"\begin{tabular}{ll|rrrrrrrr}\hline")
print(r"  Program  & Tool   & \multicolumn{3}{c}{Product} & \multicolumn{3}{c}{Transformation} & \centercell{Family}                                                     \\")
print(r"           &        & \centercell{Analysis}       & \centercell{Deduplication}         & \centercell{Total} & \centercell{Desugaring} & \centercell{Analysis} & \centercell{Total} & \centercell{Analysis} \\ \hline")

for target in TARGET_ORDER:
    for i, tool in enumerate(["clang", "infer", "VAA"]):
        prog_label = TARGET_MACROS[target] if i == 0 else ""

        if tool == "VAA":
            print(f"  {prog_label:<8} & VAA    & -  & -  & -  & -  & -  & -  & - \\\\")
        else:
            prod_key = f"{tool}_{target}_product"
            trans_key = f"{tool}_{target}_transformation"

            prod_analysis    = avg(times[prod_key]["analysis"])
            prod_dedup       = avg(times[prod_key]["deduplication"])
            trans_desugaring = avg(times[trans_key]["desugaring"])
            trans_analysis   = avg(times[trans_key]["analysis"])

            prod_total  = (prod_analysis + prod_dedup) if (prod_analysis is not None and prod_dedup is not None) else None
            trans_total = (trans_desugaring + trans_analysis) if (trans_desugaring is not None and trans_analysis is not None) else None

            cols = [
                cell(prod_analysis),
                cell(prod_dedup),
                cell(prod_total),
                cell(trans_desugaring),
                cell(trans_analysis),
                cell(trans_total),
                "-",  # Family: always - for clang/infer
            ]
            print(f"  {prog_label:<8} & {TOOL_MACROS[tool]:<6} & {cols[0]:<28} & {cols[1]:<35} & {cols[2]:<24} & {cols[3]:<24} & {cols[4]:<21} & {cols[5]:<21} & {cols[6]:<21} \\\\")

    print(r"  \hline")

print(r"\end{tabular}")
