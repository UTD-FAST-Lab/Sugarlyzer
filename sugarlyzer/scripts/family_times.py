import re
import sys

hms_pattern = re.compile(r'(\d+):(\d+):(\d+(?:\.\d+)?)')
ms_pattern = re.compile(r'(\d+):(\d+\.\d+)')

times = []
for path in (line.strip() for line in sys.stdin if line.strip()):
    try:
        with open(path) as f:
            content = f.read()
    except OSError as e:
        print(f"warning: {path}: {e}", file=sys.stderr)
        continue
    if m := hms_pattern.search(content):
        t = int(m.group(1)) * 3600 + int(m.group(2)) * 60 + float(m.group(3))
    elif m := ms_pattern.search(content):
        t = int(m.group(1)) * 60 + float(m.group(2))
    else:
        print(f"warning: no runtime found in {path}", file=sys.stderr)
        continue
    times.append(t)

if times:
    print(f"{sum(times) / len(times):.2f}s  (n={len(times)})")
else:
    print("no runtimes found", file=sys.stderr)
    sys.exit(1)
