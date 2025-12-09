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

TOOLS=(infer clang phasar)
PROJECTS=(axtls toybox busybox)
ITERATIONS=5

for t in "${TOOLS[@]}"; do
  for p in "${PROJECTS[@]}"; do
    BASE_DIR="$RESULTS_DIR/$t/$p"

    for i in $(seq 1 "$ITERATIONS"); do
      printf "Running %s on %s #%d\n" "$t" "$p" "$i"
      ITERATION_DIR="$BASE_DIR/run_$i"

      mkdir -p "$ITERATION_DIR"

      dispatcher \
        -t "$t" \
        -p "$p" \
        --output-dir "$ITERATION_DIR" \
        -r "$ITERATION_DIR/results.json" \
        --log "$ITERATION_DIR/run.log" \
        --jobs "$JOBS" \
        --sample-size "$2" \
        --baselines
    done
  done
done
