#!/bin/bash

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


DEFAULT_LLFILE_CMD="clang-12 -emit-llvm -S -fno-discard-value-names -c -g -I /SugarlyzerConfig -I /SugarlyzerConfig/stdinc/usr/include -I /SugarlyzerConfig/stdinc/usr/include/x86_64-linux-gnu -I /SugarlyzerConfig/stdinc/usr/lib/gcc/x86_64-linux-gnu/9/include"

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

# Run clang if we found a source file
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

  echo $DEFAULT_LLFILE_CMD $FILTERED_ARGS --include /SugarlyzerConfig/"$PROGRAM"Inc.h -nostdinc -c $SOURCE_FILE -o ${SOURCE_FILE%.c}.ll >&2

  # Create LL file
  $DEFAULT_LLFILE_CMD $FILTERED_ARGS --include /SugarlyzerConfig/"$PROGRAM"Inc.h -nostdinc -c $SOURCE_FILE -o ${SOURCE_FILE%.c}.ll 2>&1

  DEFAULT_RUN_COMMAND="/phasar/build/tools/phasar-llvm/phasar-llvm -D IFDSUninitializedVariables -m "

  echo "" >> "$RESULTING_ALARMS"
  echo "========================================" >> "$RESULTING_ALARMS"
  echo "[$(date '+%Y-%m-%d %H:%M:%S')] Running Phasar" >> "$RESULTING_ALARMS"
  echo "Command: $DEFAULT_RUN_COMMAND" >> "$RESULTING_ALARMS"
  echo "Source: ${SOURCE_FILE%.c}.ll" >> "$RESULTING_ALARMS"
  echo "========================================" >> "$RESULTING_ALARMS"

  echo $DEFAULT_RUN_COMMAND ${SOURCE_FILE%.c}.ll >&2

  $DEFAULT_RUN_COMMAND ${SOURCE_FILE%.c}.ll >> $RESULTING_ALARMS 2>&1

  echo "----------------------------------------" >> "$RESULTING_ALARMS"

fi

exec gcc "$@"
