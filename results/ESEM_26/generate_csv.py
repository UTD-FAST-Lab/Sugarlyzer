import csv
import json
import os

with open("../ICST_2026/varbugs_classified.json", "r") as f:
  old_varbugs = json.load(f)

# Make it into a map
old_varbugs = {bug["id"]: bug for bug in old_varbugs}

for file in os.listdir("bug_reports"):
  if file.endswith(".json"):
    with open(os.path.join("bug_reports", file), "r") as f:
      try:
        data = json.load(f)
      except json.JSONDecodeError:
        print(f"Error decoding JSON from {file}")
        continue
    with open("bug_reports.csv", "a", newline="") as f:
      writer = csv.DictWriter(f, fieldnames=["id", "classification", "reasoning", "old_classification"])
      if "old_id" in data:
        data["old_classification"] = old_varbugs.get(data["old_id"], {}).get("classification", "N/A")
      # Only write the four fields
      writer.writerow({field: data.get(field, "N/A") for field in ["id", "classification", "reasoning", "old_classification"]})