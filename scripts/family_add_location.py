#!/usr/bin/env python
import json
import re
import sys

results = json.loads(sys.stdin.read().strip())

for r in results:
    r['input_file'] = re.search(r"file (.*?):", r['err']).group(1)
    r['line_number'] = int(re.search(r"(\d+):\d+", r['err']).group(1).split(":")[0])

print(json.dumps(results, indent=2))