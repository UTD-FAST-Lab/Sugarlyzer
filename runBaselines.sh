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

RESULTS_DIR=$ROOT/experiment_results/product-based

for t in infer clang phasar
do
  for p in axtls toybox busybox
  do
    for i in $(seq 1 5)
    do
      echo "Running $t on $p #$i\n"
      dispatcher -t $t -p $p -r "$RESULTS_DIR/$t/$p/"$i"_results.json" --log "$RESULTS_DIR/$t/$p/"$i".log" --jobs $1 --baselines
    done
  done
done
