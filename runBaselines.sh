#!/bin/bash
if [ -z "$1" ]; then
  echo "Error: first parameter should be number of jobs."
  exit 1
fi

if [ -z "$2" ]; then
  echo "Warning: putting results in current directory."
  ROOT="."
else
  ROOT="$2"
fi

for t in clang infer phasar
do
  for p in toybox axtls busybox
  do
    dispatcher -t $t -p $p -r "$ROOT/$t.$p.baseline.json" --log "$ROOT/$t.$p.baseline.log" --jobs $1 --baselines
  done
done
