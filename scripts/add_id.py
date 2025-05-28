import argparse

p = argparse.ArgumentParser()
p.add_argument('input_file')
p.add_argument('analysis_type', choices=['family', 'product', 'transformation'])
args = p.parse_args()

import json

with open(args.input_file, 'r') as f:
    results = json.load(f)

id = 0
for r in results:
    r['id'] = f"{args.analysis_type.upper()}_{id}"
    id += 1

with open(args.input_file, 'w') as f:
    json.dump(results, f, indent=2)