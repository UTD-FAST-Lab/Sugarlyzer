#!/usr/bin/env python
import json
import sys

rese = []
found = False
c = {}
for l in sys.stdin.readlines():
    l = l.lstrip().rstrip()
    if l.startswith("W [") or l.startswith('- W ['):
        found = True
        c['err'] = l
    elif found:
        found = False
        c['msg'] = l
        rese.append(c)
        c = {}
print(json.dumps(rese, indent=2))
