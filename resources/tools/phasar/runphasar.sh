#!/bin/bash


# Create ll file
#
: <<COMMAND
        cmd = ['/usr/bin/time', '-v', "timeout", "--preserve-status", "2h", 'clang-12','-emit-llvm','-S','-fno-discard-value-names','-c','-g',
               *list(itertools.chain(*zip(itertools.cycle(["-I"]), included_dirs))),
               *list(itertools.chain(*zip(itertools.cycle(["--include"]), included_files))),
               *command_line_defs,
               "-nostdinc", "-c", file.absolute(), '-o', llFile]
        logger.info(f"Running cmd {cmd}")
        ps = subprocess.run(" ".join(str(s) for s in cmd), shell=True, executable="/bin/bash", capture_output=True, text=True)
COMMAND


# Run phasar on ll
: <<COMMAND
        cmd = ['/usr/bin/time', '-v', "timeout", "--preserve-status", "2h", '/phasar/build/tools/phasar-llvm/phasar-llvm','-D',
               'IFDSUninitializedVariables','-m',llFile,'-O',output_location]
        logger.info(f"Running cmd {cmd}")
        ps = subprocess.run(" ".join(str(s) for s in cmd), capture_output=True, text=True, shell=True, executable="/bin/bash")
COMMAND
