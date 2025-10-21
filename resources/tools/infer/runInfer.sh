#!/bin/bash

# set -x # debug
# set +x
: << COMMAND

CURRENT INFER COMMAND:
infer --pulse-only -o /tmp/infer_1760935939_666 -- clang -I /SugarlyzerConfig -I /SugarlyzerConfig/stdinc/usr/include -I /SugarlyzerConfig/stdinc/usr/include/x86_64-linux-gnu -I /SugarlyzerConfig/stdinc/usr/lib/gcc/x86_64-linux-gnu/9/include  -I../config -I../ssl -I../crypto -Wall -Wstrict-prototypes -Wshadow -fPIC -O3 -c -o sha1.o --include /SugarlyzerConfig/axtlsInc.h -nostdinc -c /targets/axtls-code/crypto/sha1.c

ORIGINAL INFER COMMAND:
/usr/bin/time -v timeout --preserve-status 2h infer --pulse-only -o /tmp/tmpbi5_iywj -- clang -I /SugarlyzerConfig -I /SugarlyzerConfig/stdinc/usr/include -I /SugarlyzerConfig/stdinc/usr/include/x86_64-linux-gnu -I /SugarlyzerConfig/stdinc/usr/lib/gcc/x86_64-linux-gnu/9/include -I /targets/axtls-code/config -I /targets/axtls-code/ssl -I /targets/axtls-code/crypto --include /SugarlyzerConfig/axtlsInc.h -nostdinc -c /targets/axtls-code/samples/c/axssl.desugared.c


clang -Wp,-MD,util-linux/volume_id/.fat.o.d  -Iinclude -Ilibbb  -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D"BB_VER=KBUILD_STR(1.28.0)"     -D"KBUILD_STR(s)=#s" -D"KBUILD_BASENAME=KBUILD_STR(fat)"  -D"KBUILD_MODNAME=KBUILD_STR(fat)" -c -o util-linux/volume_id/fat.o util-linux/volume_id/fat.c;  scripts/basic/fixdep util-linux/volume_id/.fat.o.d util-linux/volume_id/fat.o 'clang -Wp,-MD,util-linux/volume_id/.fat.o.d  -Iinclude -Ilibbb  -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D"BB_VER=KBUILD_STR(1.28.0)"     -D"KBUILD_STR(s)=#s" 
-D"KBUILD_BASENAME=KBUILD_STR(fat)"  

-D"KBUILD_MODNAME=KBUILD_STR(fat)" 

-c -o util-linux/volume_id/fat.o util-linux/volume_id/fat.c' > util-linux/volume_id/.fat.o.tmp; 

rm -f util-linux/volume_id/.fat.o.d; 

mv -f util-linux/volume_id/.fat.o.tmp util-linux/volume_id/.fat.o.cmd

COMMAND

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
DEFAULT_INFER_CMD="infer --pulse-only -o /tmp/infer_$(date +%s)_$$ -- clang -I /SugarlyzerConfig -I /SugarlyzerConfig/stdinc/usr/include -I /SugarlyzerConfig/stdinc/usr/include/x86_64-linux-gnu -I /SugarlyzerConfig/stdinc/usr/lib/gcc/x86_64-linux-gnu/9/include"

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
      *.c) # Skip additional .c files (we'll use SOURCE_FILE instead)
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

  eval "$FULL_INFER_CMD" >> "$RESULTING_ALARMS" 2>&1

  echo "----------------------------------------" >> "$RESULTING_ALARMS"
fi

exec gcc "$@"
