#!/bin/bash

: << COMMAND
COMMAND

for arg in "$@"; do
  case "$arg" in
    -MM|-M|-MD|-MF|-MT|-MQ) # Ensure real compile command, not dep gen
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

mkdir -p /tmp/"$TOOL"
RESULTING_ALARMS=/tmp/"$TOOL"/"$(basename "${SOURCE_FILE:-no_source}")"_result.txt
echo "[$(date '+%Y-%m-%d %H:%M:%S')] Starting analysis" > "$RESULTING_ALARMS"

# Default infer command prefix
DEFAULT_INFER_CMD="infer --pulse-only -o /tmp/infer_$(date +%s)_$$ -- clang -I /SugarlyzerConfig -I /SugarlyzerConfig/stdinc/usr/include -I /SugarlyzerConfig/stdinc/usr/include/x86_64-linux-gnu -I /SugarlyzerConfig/stdinc/usr/lib/gcc/x86_64-linux-gnu/9/include"

# Run infer only if source file found; otherwise note skipped
if [ -n "$SOURCE_FILE" ]; then
  FILTERED_ARGS=""
  for arg in "$@"; do
    case "$arg" in
      *.c|-fno-guess-branch-probability) # Skip other .c files except the main source
        if [ "$arg" != "$(basename "$SOURCE_FILE")" ] && [ "$arg" != "$SOURCE_FILE" ]; then
          continue
        fi
        ;;
      *)
        FILTERED_ARGS="$FILTERED_ARGS $arg"
        ;;
    esac
  done

  echo "" >> "$RESULTING_ALARMS"
  echo "========================================" >> "$RESULTING_ALARMS"
  echo "[$(date '+%Y-%m-%d %H:%M:%S')] Running INFER" >> "$RESULTING_ALARMS"
  echo "Command: $DEFAULT_INFER_CMD $FILTERED_ARGS --include /SugarlyzerConfig/${PROGRAM}Inc.h -nostdinc -c $SOURCE_FILE" >> "$RESULTING_ALARMS"
  echo "Source: $SOURCE_FILE" >> "$RESULTING_ALARMS"
  echo "========================================" >> "$RESULTING_ALARMS"

  $DEFAULT_INFER_CMD $FILTERED_ARGS --include /SugarlyzerConfig/"$PROGRAM"Inc.h -nostdinc -c "$SOURCE_FILE" >> "$RESULTING_ALARMS" 2>&1

  echo "----------------------------------------" >> "$RESULTING_ALARMS"
fi

exec gcc "$@"
