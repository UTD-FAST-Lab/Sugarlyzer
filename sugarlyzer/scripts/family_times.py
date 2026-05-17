import re
import sys

pattern = re.compile(r'(\d+):(\d+\.\d+)')

def parse_seconds(m, s):
    return int(m) * 60 + float(s)

times = []
for path in (line.strip() for line in sys.stdin if line.strip()):
    try:
        with open(path) as f:
            content = f.read()
    except OSError as e:
        print(f"warning: {path}: {e}", file=sys.stderr)
        continue
    match = pattern.search(content)
    if match:
        times.append(parse_seconds(match.group(1), match.group(2)))
    else:
        print(f"warning: no runtime found in {path}", file=sys.stderr)

if times:
    print(f"{sum(times) / len(times):.2f}s  (n={len(times)})")
else:
    print("no runtimes found", file=sys.stderr)
    sys.exit(1)
