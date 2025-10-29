#!/bin/bash

: << COMMAND
TOOD: 

  Implement flock to sync writes to file so we can read the outputs properly.

COMMAND

RESULTING_ALARMS=/tmp/result_alarms.txt

for arg in "$@"; do
  case "$arg" in
    -MM|-M|-MD|-MF|-MT|-MQ) # Makesure real compile command not dep gen
      exec gcc "$@"
      exit 
      ;;
  esac
done

# Also skip if no -c flag
if ! echo "$@" | grep -q -- "-c"; then
  exec gcc "$@"
  exit 
fi

# Default infer command prefix
DEFAULT_INFER_CMD="clang-11 --analyze -Xanalyzer -analyzer-output=text -I /SugarlyzerConfig -I /SugarlyzerConfig/stdinc/usr/include -I /SugarlyzerConfig/stdinc/usr/include/x86_64-linux-gnu -I /SugarlyzerConfig/stdinc/usr/lib/gcc/x86_64-linux-gnu/9/include"

echo "runClang.sh called with: $@" >&2

# Find the source file and convert to absolute path
SOURCE_FILE=""
for arg in "$@"; do
  case "$arg" in *.c)
      if [ -f "$arg" ]; then
        if [ "${arg#/}" != "$arg" ]; then
          SOURCE_FILE="$arg"
        else
          SOURCE_FILE="$(cd "$(dirname "$arg")" 2>/dev/null && pwd)/$(basename "$arg")"
        fi
      fi
      ;;
  esac
done

# Run infer if we found a source file
if [ -n "$SOURCE_FILE" ]; then
  FILTERED_ARGS=""
  for arg in "$@"; do
    case "$arg" in
      *.c|-fno-guess-branch-probability) # Skip additional .c files (we'll use SOURCE_FILE instead)
        if [ "$arg" != "$(basename "$SOURCE_FILE")" ] && [ "$arg" != "$SOURCE_FILE" ]; then
          continue
        fi
        ;;
      *)
        FILTERED_ARGS="$FILTERED_ARGS $arg"
        ;;
    esac
  done

  FULL_INFER_CMD="$DEFAULT_INFER_CMD $FILTERED_ARGS --include /SugarlyzerConfig/"$PROGRAM"Inc.h -nostdinc -c $SOURCE_FILE"

  echo "" >> "$RESULTING_ALARMS"
  echo "========================================" >> "$RESULTING_ALARMS"
  echo "[$(date '+%Y-%m-%d %H:%M:%S')] Running INFER" >> "$RESULTING_ALARMS"
  echo "Command: $FULL_INFER_CMD" >> "$RESULTING_ALARMS"
  echo "Source: $SOURCE_FILE" >> "$RESULTING_ALARMS"
  echo "========================================" >> "$RESULTING_ALARMS"

  $DEFAULT_INFER_CMD $FILTERED_ARGS --include /SugarlyzerConfig/"$PROGRAM"Inc.h -nostdinc -c "$SOURCE_FILE" >> "$RESULTING_ALARMS" 2>&1

  echo "----------------------------------------" >> "$RESULTING_ALARMS"
fi

exec gcc "$@"
