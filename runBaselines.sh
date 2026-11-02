#!/bin/bash

if [ -z "${1:-}" ]; then
  echo "Error: first parameter should be number of jobs."
  exit 1
fi

if [ -z "${2:-}" ]; then
  echo "Error: second parameter should be number of samples."
  exit 1
fi

JOBS="$1"
ROOT="${3:-.}"
RESULTS_DIR="$ROOT/experiment_results/product-based"

TOOLS=(infer clang cppcheck phasar)
PROGRAMS=(axtls toybox busybox varbugs)
ITERATIONS=5

for i in $(seq 1 "$ITERATIONS"); do
  for t in "${TOOLS[@]}"; do
    for p in "${PROGRAMS[@]}"; do
      BASE_DIR="$RESULTS_DIR/$t/$p"
      printf "Running %s on %s #%d\n" "$t" "$p" "$i"
      ITERATION_DIR="$BASE_DIR/run_$i"
      mkdir -p "$ITERATION_DIR"
      ./run.sh -t "$t" -p "$p" -s product -n "$2" -o "$ITERATION_DIR" -j "$JOBS" 
    done
  done
done
