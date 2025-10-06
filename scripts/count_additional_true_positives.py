#!/usr/bin/env python
import argparse

p = argparse.ArgumentParser()
p.add_argument('--family', required=True)
p.add_argument('--product', required=True)
p.add_argument('--transformation', required=True)
p.add_argument('--vbdb_dir', required=True)
args = p.parse_args()

import json
import os
from pathlib import Path
from typing import Set, Tuple

with open(args.family, 'r') as f:
    # Assumes you have already used souschef.py to generate the JSON and then family_add_location.py to extract
    # fields from the JSON file.
    family = json.load(f)

with open(args.product, 'r') as f:
    product = json.load(f)

with open(args.transformation, 'r') as f:
    transformation = json.load(f)

print(f"Classified {len([*family, *transformation, *product])} bug reports.")

# Gather all of the initial true positives
tps = set()
for root, dirs, files in os.walk(args.vbdb_dir):
    for fi in files:
        if fi.endswith('.c') and '#' not in fi:
            tps.add((fi, "_ORIGINAL"))

assert len(tps) == 97, f"Expected 97 original true positives, found {len(tps)}"

additional_tps = set()
for report in [*family, *product, *transformation]:
    if report['classification'] == 'TP_NEW':
        additional_tps.add(((Path(report['input_file'])).name, report['taxonomy_type']))

print(f"Found {len(additional_tps)} additional true positives.")

import copy
base_stat = {"TP": 0, "FP": 0, "FN": 0, "ADJ_FN": 0}
warnings_stats = {
    "family": copy.deepcopy(base_stat),
    "transformation": copy.deepcopy(base_stat),
    "product": copy.deepcopy(base_stat)
}

# First, false negatives and true positives
all_tps: Set[Tuple[str, str]] = tps.union(additional_tps)
for tp in all_tps:
    for result, as_str in [(family, 'family'), (product, 'product'), (transformation, 'transformation')]:
        if tp[1] == "_ORIGINAL":
            if len([r for r in result if r['classification'] == 'TP' and 
                Path(r['input_file']).name == Path(tp[0]).name]) > 0:
                warnings_stats[as_str]['TP'] += 1
            else:
                warnings_stats[as_str]['FN'] += 1
        else:
            if len([r for r in result if r['classification'] == 'TP_NEW' and Path(r['input_file']).name == Path(tp[0]).name and tp[1] == r['taxonomy_type']]):
                warnings_stats[as_str]['TP'] += 1
            else:
                warnings_stats[as_str]['FN'] += 1

# Now, FPs
for result, as_str in [(family, 'family'), (product, 'product'), (transformation, 'transformation')]:
    fps = {(Path(r['input_file']).name, r['taxonomy_type']) for r in result if r['classification'] == 'FP'}
    warnings_stats[as_str]['FP'] = len(fps)


print(warnings_stats)

for origin, res in warnings_stats.items():
    recall = res['TP'] / (res['TP'] + res['FN'])
    precision = res['TP'] / (res['TP'] + res['FP'])
    print(f"{origin}: Recall={recall}, Precision={precision}")

