#!/usr/bin/env python
import json
import sys

results = json.loads(sys.stdin.read().strip())

for r in results:
    r['classification'] = ''

try:
  print(json.dumps(results, indent=2))
except BrokenPipeError:
  sys.exit(-1)