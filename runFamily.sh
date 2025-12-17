#!/bin/bash

TYPECHEF_PATH=$(find "$(pwd)" -type d -name "TypeChef-VAA" -print -quit)

if [[ -z "$TYPECHEF_PATH" ]]; then
  echo "Error: TypeChef path not found."
  exit 1
fi

ROOT="${1:-.}"
RESULTS_DIR="$ROOT/experiment_results/family-based"
PROGRAMS=(axtls toybox busybox varbugs)

for p in "${PROGRAMS[@]}"; do

  SCRIPT_PATH=$(find $(pwd) -type f -name "runVAA_$p.sh" -print -quit)

  BASE_DIR="$RESULTS_DIR/$p"
  ITERATION_DIR="$BASE_DIR/run_$i"
  mkdir -p "$ITERATION_DIR"

  printf "Analyzing PROGRAM: %s\n" "$p"

  bash "$SCRIPT_PATH" "$(realpath "$TYPECHEF_PATH")" "$(realpath "$ITERATION_DIR")"
done
