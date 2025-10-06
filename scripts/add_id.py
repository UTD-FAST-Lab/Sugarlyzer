#!/usr/bin/env python
import argparse

p = argparse.ArgumentParser()
p.add_argument('analysis_type', choices=['family', 'product', 'transformation'])
args = p.parse_args()

import json
import sys

results = json.loads(sys.stdin.read().strip())

id = 0
for r in results:
    r['id'] = f"{args.analysis_type.upper()}_{id}"
    id += 1

try:
  print(json.dumps(results, indent=2))
except BrokenPipeError:
  sys.exit(-1)