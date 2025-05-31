#!/usr/bin/env python
import argparse
import sys
import json
from pathlib import Path

p = argparse.ArgumentParser()
p.add_argument("files", nargs="+")
args = p.parse_args()

results = []
for fi in args.files:
  with open(fi, 'r') as f:
    from_file = json.load(f)
    for ff in from_file:
      ff['original_file'] = Path(fi).name
    results.extend(from_file)

results = sorted(results, key=lambda r: r['input_file'])

try:
  print(json.dumps(results, indent=2))
except BrokenPipeError:
  sys.exit(-1)
