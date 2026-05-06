import json
import os

with open("../ICST_2026/varbugs_classified.json", "r") as f:
    varbugs_classified = json.load(f)

i = 1
for v in varbugs_classified:
    if v['origin'] == 'family':
        v['classification'] = 'UNKNOWN'
        v['old_id'] = v['id']
        v['id'] = f'FAMILY_{i}'
        i += 1
        with open(f'./bug_reports/{v["id"]}.json', 'w') as f:
            json.dump(v, f, indent=2)
