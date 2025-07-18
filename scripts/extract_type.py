#!/usr/bin/env python
import json
import sys

results = json.loads(sys.stdin.read().strip())

for r in results:
    print(r['taxonomy_type'])
