#!/bin/bash
if [ -z "$1" ]; then
  echo "Error: first parameter should be number of jobs."
  exit 1
fi

for t in clang infer phasar
do
  for p in toybox axtls busybox tosembusybox tosemopenssl tosemuclibc
  do
    dispatcher -t $t -p $p -r $t.$p.json --log $t.$p.log --jobs $1
  done
done
