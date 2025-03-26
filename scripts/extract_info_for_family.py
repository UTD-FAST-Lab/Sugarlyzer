import argparse

p = argparse.ArgumentParser()
p.add_argument("family_results")
args = p.parse_args()

import json
import re

with open(args.family_results, 'r') as f:
    results = json.load(f)

for r in results:
    r['input_file'] = re.search("file (.*?):", r['err']).group(1)

with open(args.family_results + ".with_file", 'w') as f:
    json.dump(results, f, indent=2)