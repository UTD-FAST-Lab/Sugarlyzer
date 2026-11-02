#!/bin/bash

usage () {
    echo "usage: $0 -t clang|infer -p axtls|toybox|busybox|varbugs [-s product|transformation] [-n samples] [-j jobs] [-o outdir] [-k]" >&2
  exit 2
}

TOOL="" PROGRAM="" STARGET=product SAMPLES=100 JOBS="" OUT=results

while getopts "t:p:s:n:j:o" opt; do
  case $opt in
    t) TOOL=$OPTARG ;;
    p) PROGRAM=$OPTARG ;;
    s) STRATEGY=$OPTARG ;;
    n) SAMPLES=$OPTARG ;;
    j) JOBS=$OPTARG ;;
    o) OUT=$OPTARG ;;
    *) usage ;;
  esac
done
case $TOOL in clang|infer) ;; *) usage ;; esac
case $PROGRAM in axtls|toybox|busybox|varbugs) ;; *) usage ;; esac
case $STRATEGY in product|transformation) ;; *) usage ;; esac

name="${TOOL}_${PROGRAM}_${STRATEGY}"
mkdir -p "$OUT/$name"
results="$(cd "$OUT/$name" && pwd)"
volume="sugarlyzer_${name}"

args=(--program "$PROGRAM" --tool "$TOOL" --strategy "$STRATEGY" --sample_size "$SAMPLES")
[[ -n $JOBS ]] && args+=(--jobs "$JOBS")

phase() {
docker run --rm \
  -v "$volume:/workspace" \
  -v "$results:/results" \
  "sugarlyzer/$1" --phase "$2" "${args[@]}"
}

{
  echo "== $name: build phase =="
  phase program build
  echo "== $name: analysis phase =="
  phase "$TOOL" analyze
  echo "== $name: done; result in $results =="
} 2>&1
