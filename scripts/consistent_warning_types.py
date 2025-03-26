import argparse

p = argparse.ArgumentParser()
p.add_argument('input_file')
p.add_argument('analysis_type', choices=['family', 'product', 'transformation'])
args = p.parse_args()

import json
import taxonomy

with open(args.input_file, 'r') as f:
    results = json.load(f)

for r in results:
    if args.analysis_type == 'family':
        r['taxonomy_type'] = taxonomy.get_warning_type(r['msg'], True)
    else:
        r['taxonomy_type'] = taxonomy.get_warning_type(r['message'], False)

with open(args.input_file + '.with_taxonomy', 'w') as f:
    json.dump(results, f, indent=2)
