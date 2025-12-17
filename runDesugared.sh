#!/bin/bash

if [ -z "${1:-}" ]; then
  echo "Error: first parameter should be number of jobs."
  exit 1
fi

JOBS="$1"
ROOT="${2:-.}"
RESULTS_DIR="$ROOT/experiment_results/transformation-based"

TOOLS=(infer clang phasar)
PROGRAMS=(axtls toybox busybox)
ITERATIONS=5

for i in $(seq 1 "$ITERATIONS"); do
  for t in "${TOOLS[@]}"; do
    for p in "${PROGRAMS[@]}"; do
      BASE_DIR="$RESULTS_DIR/$t/$p"

        printf "Running %s on %s #%d\n" "$t" "$p" "$i"
        ITERATION_DIR="$BASE_DIR/run_$i"

        mkdir -p "$ITERATION_DIR"

        dispatcher \
          -t "$t" \
          -p "$p" \
          --output-dir "$ITERATION_DIR" \
          -r "$ITERATION_DIR/results.json" \
          --log "$ITERATION_DIR/run.log" \
          --jobs "$JOBS"
    done
  done
done

