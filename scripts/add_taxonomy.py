#!/usr/bin/env python
import argparse
import sys

p = argparse.ArgumentParser()
p.add_argument('analysis_type', choices=['family', 'product', 'transformation'])
args = p.parse_args()

import json
import taxonomy
import sys

results = json.loads(sys.stdin.read().strip())

for r in results:
  if args.analysis_type == 'family':
    r['taxonomy_type'] = taxonomy.get_warning_type(r['msg'], True)
  else:
    r['taxonomy_type'] = taxonomy.get_warning_type(r['message'], False)

try:
  print(json.dumps(results, indent=2))
except BrokenPipeError:
  sys.exit(-1)