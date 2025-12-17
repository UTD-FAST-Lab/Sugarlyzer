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
  mkdir -p "$BASE_DIR"

  TIMER_LOG="$BASE_DIR/timer.log"

  printf "Analyzing PROGRAM: %s\n" "$p"

  /usr/bin/time -a -o "$TIMER_LOG" --format="$p: Real %e, User %U, Sys %S, MaxRSS %MKB" \
  bash "$SCRIPT_PATH" "$(realpath "$TYPECHEF_PATH")" "$(realpath "$BASE_DIR")"
done
