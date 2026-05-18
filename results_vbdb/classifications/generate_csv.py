import csv
import json
import os

with open("../ICST_2026/varbugs_classified.json", "r") as f:
  old_varbugs = json.load(f)

# Make it into a map
old_varbugs = {bug["id"]: bug for bug in old_varbugs}

with open("2.0_classifications.json", "r") as f:
  data = json.load(f)
with open("bug_reports.csv", "w", newline="") as f:
  writer = csv.DictWriter(f, fieldnames=["id", "classification", "reasoning", "old_classification"])
  for d in data:
    if "old_id" in d:
      d["old_classification"] = old_varbugs.get(d["old_id"], {}).get("classification", "N/A")
    # Only write the four fields
    writer.writerow({field: d.get(field, "N/A") for field in ["id", "classification", "reasoning", "old_classification"]})