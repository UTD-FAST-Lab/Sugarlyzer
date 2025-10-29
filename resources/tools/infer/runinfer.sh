#!/bin/bash

# set -x # debug
# set +x
: << COMMAND
line 292 CC is being set in busybox

TASK:
  Figure out why there are issues with compiling when using our script in busybox

Command the OG is running:

ERROR TRACE FROM ORIGINAL SUGARLYZER

multiprocess.pool.remotetraceback:
"""
traceback (most recent call last):
  file "/venv/lib/python3.10/site-packages/multiprocess/pool.py", line 125, in worker
    result = (true, func(*args, **kwds))
  file "/venv/lib/python3.10/site-packages/pathos/helpers/mp_helper.py", line 15, in <lambda>
    func = lambda args: f(*args)
  file "/sugarlyzer/src/sugarlyzer/tester.py", line 183, in <lambda>
    for result in tqdm(p.imap(lambda x: analyze_read_and_process(*x), ((d, o, dt) for d, _, o, dt in input_files)),
  file "/sugarlyzer/src/sugarlyzer/tester.py", line 173, in analyze_read_and_process
    alarms = process_alarms(self.tool.analyze_and_read(desugared_file, included_files=included_files,
  file "/sugarlyzer/src/sugarlyzer/sugarcrunner.py", line 319, in process_alarms
    s.add(eval(condition_mapping.replacers[a['var']]))
  file "<string>", line 1, in <module>
  file "/venv/lib/python3.10/site-packages/z3/z3.py", line 1901, in not
    a = s.cast(a)
  file "/venv/lib/python3.10/site-packages/z3/z3.py", line 1579, in cast
    _z3_assert(self.eq(val.sort()), "value cannot be converted into a z3 boolean value")
  file "/venv/lib/python3.10/site-packages/z3/z3.py", line 115, in _z3_assert
    raise z3exception(msg)
z3.z3types.z3exception: value cannot be converted into a z3 boolean value
"""

The above exception was the direct cause of the following exception:

Traceback (most recent call last):
  File "/venv/bin/tester", line 8, in <module>

    sys.exit(main())
  File "/Sugarlyzer/src/sugarlyzer/Tester.py", line 541, in main

    t.execute()
  File "/Sugarlyzer/src/sugarlyzer/Tester.py", line 183, in execute
    for result in tqdm(p.imap(lambda x: analyze_read_and_process(*x), ((d, o, dt) for d, _, o, dt in input_files)),
  File "/venv/lib/python3.10/site-packages/tqdm/std.py", line 1181, in __iter__

    for obj in iterable:
  File "/venv/lib/python3.10/site-packages/multiprocess/pool.py", line 873, in next

    raise value
z3.z3types.Z3Exception: Value cannot be converted into a Z3 Boolean value


SIMILAR EXCEPTION WHEN RUNNING TESTER INSIDE OF INFER CONTAINER:
 19%|███████████████                                                                 | 250/1332 [01:29<06:27,  2.79it/s]
multiprocess.pool.RemoteTraceback:
"""
Traceback (most recent call last):
  File "/venv/lib/python3.10/site-packages/multiprocess/pool.py", line 125, in worker
    result = (True, func(*args, **kwds))
  File "/venv/lib/python3.10/site-packages/pathos/helpers/mp_helper.py", line 15, in <lambda>
    func = lambda args: f(*args)
  File "/Sugarlyzer/src/sugarlyzer/Tester.py", line 183, in <lambda>
    for result in tqdm(p.imap(lambda x: analyze_read_and_process(*x), ((d, o, dt) for d, _, o, dt in input_files)),
  File "/Sugarlyzer/src/sugarlyzer/Tester.py", line 173, in analyze_read_and_process
    alarms = process_alarms(self.tool.analyze_and_read(desugared_file, included_files=included_files,
  File "/Sugarlyzer/src/sugarlyzer/SugarCRunner.py", line 319, in process_alarms
    s.add(eval(condition_mapping.replacers[a['var']]))
  File "<string>", line 1, in <module>
  File "/venv/lib/python3.10/site-packages/z3/z3.py", line 1901, in Not
    a = s.cast(a)
  File "/venv/lib/python3.10/site-packages/z3/z3.py", line 1579, in cast
    _z3_assert(self.eq(val.sort()), "Value cannot be converted into a Z3 Boolean value")
  File "/venv/lib/python3.10/site-packages/z3/z3.py", line 115, in _z3_assert
    raise Z3Exception(msg)
z3.z3types.Z3Exception: Value cannot be converted into a Z3 Boolean value
"""

The above exception was the direct cause of the following exception:

Traceback (most recent call last):
  File "/venv/bin/tester", line 8, in <module>
    sys.exit(main())
  File "/Sugarlyzer/src/sugarlyzer/Tester.py", line 541, in main
INFER COMMAND: /usr/bin/time -v timeout --preserve-status 2h infer --pulse-only -o /tmp/tmpjpkifxi7 -- clang -I /targets/busybox-1_28_0 -I /SugarlyzerConfig/stdinc/usr/include -I /SugarlyzerConfig/stdinc/usr/include/x86_64-linux-gnu -I /SugarlyzerConfig/stdinc/usr/lib/gcc/x86_64-linux-gnu/9/include --include /SugarlyzerConfig/busyboxInc.h -nostdinc -c /targets/busybox-1_28_0/archival/libarchive/lzo1x_c.desugared.desugared.c
    t.execute()
  File "/Sugarlyzer/src/sugarlyzer/Tester.py", line 183, in execute
    for result in tqdm(p.imap(lambda x: analyze_read_and_process(*x), ((d, o, dt) for d, _, o, dt in input_files)),
  File "/venv/lib/python3.10/site-packages/tqdm/std.py", line 1181, in __iter__
    for obj in iterable:
  File "/venv/lib/python3.10/site-packages/multiprocess/pool.py", line 873, in next
    raise value
z3.z3types.Z3Exception: Value cannot be converted into a Z3 Boolean value


SAVING THIS ERROR TRACE:
root@8c782c2f2f52:/targets/busybox-1_28_0# make CC="/usr/local/intercept/runInfer.sh"
  CC      applets/applets.o
runInfer.sh called with:
  LD      applets/built-in.o
  CC      applets/applets.o
runInfer.sh called with:
  LD      applets/built-in.o
  CC      archival/ar.o
runInfer.sh called with:
  CC      archival/bbunzip.o
runInfer.sh called with:
  CC      archival/bzip2.o
runInfer.sh called with:
  CC      archival/cpio.o
runInfer.sh called with:
archival/cpio.c: In function 'cpio_main':
archival/cpio.c:401:31: error: 'archive_handle_t' has no member named 'cpio__owner'
  401 |                 archive_handle->cpio__owner = G.owner_ugid;
      |                               ^~
archival/cpio.c:507:23: error: 'archive_handle_t' has no member named 'cpio__blocks'
  507 |         archive_handle->cpio__blocks = (off_t)-1;
      |                       ^~
archival/cpio.c:511:27: error: 'archive_handle_t' has no member named 'cpio__blocks'
  511 |         if (archive_handle->cpio__blocks != (off_t)-1
      |                           ^~
archival/cpio.c:514:71: error: 'archive_handle_t' has no member named 'cpio__blocks'
  514 |                 fprintf(stderr, "%"OFF_FMT"u blocks\n", archive_handle->cpio__blocks);
      |                                                                       ^~
make[1]: *** [scripts/Makefile.build:198: archival/cpio.o] Error 1
make: *** [Makefile:743: archival] Error 2
root@8c782c2f2f52:/targets/busybox-1_28_0#


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
DEFAULT_INFER_CMD="infer --pulse-only -o /tmp/infer_$(date +%s)_$$ -- clang -I /SugarlyzerConfig -I /SugarlyzerConfig/stdinc/usr/include -I /SugarlyzerConfig/stdinc/usr/include/x86_64-linux-gnu -I /SugarlyzerConfig/stdinc/usr/lib/gcc/x86_64-linux-gnu/9/include"

echo "runInfer.sh called with: $@" >&2

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
