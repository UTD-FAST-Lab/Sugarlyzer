#!/usr/bin/env python
import json
import re
import sys

results = json.loads(sys.stdin.read().strip())

for r in results:
    r['input_file'] = re.search("file (.*?):", r['err']).group(1)
    r['line_number'] = re.search("(\d+):\d+").group(1)

print(json.dumps(results, indent=2))