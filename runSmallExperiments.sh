#!/bin/bash
if [ -z "$1" ]; then
  echo "Error: first parameter should be number of jobs."
  exit 1
fi

t=infer
p=toybox

echo "Running infer on toybox"
dispatcher -t $t -p $p -r $t.$p.json --log $t.$p.log --jobs $1

echo "Running infer on toybox (baselines)"
dispatcher -t $t -p $p -r $t.$p.baseline.json --log $t.$p.baseline.log --jobs $1 --baselines --sample-size 10
