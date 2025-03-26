import argparse

p = argparse.ArgumentParser()
p.add_argument("results_file")
args = p.parse_args()

import json

with open(args.results_file, 'r') as f:
    results = json.load(f)

for r in results:
    r['classification'] = ''

with open(args.results_file + ".classified", 'w') as f:
    json.dump(results, f, indent=2)