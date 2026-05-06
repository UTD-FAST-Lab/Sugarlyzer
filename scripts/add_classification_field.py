#!/usr/bin/env python
import json
import sys
import argparse
import logging
logging.basicConfig(level=logging.INFO)

p = argparse.ArgumentParser()
p.add_argument("json", help="The JSON file that contains the classifications")
args = p.parse_args()

results = json.loads(sys.stdin.read().strip())

if args.json is None:
    for r in results:
        r['classification'] = ''
else:
   # Read the JSON file
    import json
    with open(args.json, 'r') as f:
        classification_data = json.load(f)
    for r in results:
        for c in classification_data:
            if all(k in r and k in c and r[k] == c[k] for k in c.keys() if k != 'classification'):
                r['classification'] = c['classification']

try:
  print(json.dumps(results, indent=2))
except BrokenPipeError:
  sys.exit(-1)