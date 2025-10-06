#!/usr/bin/env python
import json
import sys
import argparse
import logging
logging.basicConfig(level=logging.INFO)

p = argparse.ArgumentParser()
p.add_argument("csv", help="The CSV that contains the classifications")
args = p.parse_args()

results = json.loads(sys.stdin.read().strip())

if args.csv is None:
    for r in results:
        r['classification'] = ''
else:
   # Read the CSV file and create a mapping from id to classification
   import csv
   classification_map = {}
   with open(args.csv, newline='') as csvfile:
       reader = csv.DictReader(csvfile)
       for row in reader:
           classification_map[row['ID']] = row['Final Classification']

   for r in results:
       if r['id'] in classification_map:
           r['classification'] = classification_map.get(r['id'], '')
       else:
           logging.info("CSV did not contain id for %s", r['id'])
           r['classification'] = ''

try:
  print(json.dumps(results, indent=2))
except BrokenPipeError:
  sys.exit(-1)