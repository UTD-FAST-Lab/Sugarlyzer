import argparse

p = argparse.ArgumentParser()
p.add_argument("output")
p.add_argument("files", nargs="*")
args = p.parse_args()

import json
from pathlib import Path

results = []
for fi in args.files:
    with open(fi, 'r') as f:
        from_file = json.load(f)
        for ff in from_file:
            ff['original_file'] = Path(fi).name
        results.extend(from_file)
    
results = sorted(results, key=lambda r: r['input_file'])
with open(args.output, 'w') as f:
    json.dump(results, f, indent=2)