import itertools
import logging
import subprocess
import tempfile
from pathlib import Path
from typing import Iterable, Optional
import re

from src.sugarlyzer.analyses.AbstractTool import AbstractTool
import os
from src.sugarlyzer.readers.PhasarReader import PhasarReader

logger = logging.getLogger(__name__)

class Phasar(AbstractTool):

    def __init__(self):
        super().__init__(PhasarReader(), name='phasar', keep_mem=True, make_main=True, remove_errors=False)

    def analyze(self, file: Path,
                included_dirs: Iterable[Path] = None,
                included_files: Iterable[Path] = None,
                command_line_defs: Iterable[str] = None) -> Iterable[Path]:
        if included_files is None:
            included_files = []
        if included_dirs is None:
            included_dirs = []
        if command_line_defs is None:
            command_line_defs = []
        output_location = tempfile.mkdtemp()
        #create ll file
        llFile = os.path.join(output_location,str(file)[:-2]+'.ll')
        cmd = ['time', 'clang-12','-emit-llvm','-S','-fno-discard-value-names','-c','-g',
               *list(itertools.chain(*zip(itertools.cycle(["-I"]), included_dirs))),
               *list(itertools.chain(*zip(itertools.cycle(["--include"]), included_files))),
               *command_line_defs,
               "-nostdinc", "-c", file.absolute(), '-o', llFile]
        logger.info(f"Running cmd {cmd}")
        ps = subprocess.run(" ".join(str(s) for s in cmd), shell=True, executable="/bin/bash", capture_output=True, text=True)
        if (ps.returncode != 0) or ("error" in ps.stdout.lower()):
            logger.warning(f"Running clang on file {str(file)} potentially failed.")
            logger.warning(ps.stderr)

        times = " ".join(ps.stderr.split('\n')[-10:])
        usr_time_match = re.search("user.*?([\\d.]*)m([\\d.]*)s", times)
        usr_time = float(usr_time_match.group(1)) * 60 + float(usr_time_match.group(2))
        logger.info("Usr time for clang is " + str(usr_time))
        sys_time_match = re.search("sys.*?([\\d.]*)m([\\d.]*)s", times)
        sys_time = float(sys_time_match.group(1)) * 60 + float(sys_time_match.group(2))
        logger.info("Sys time for clang is " + str(sys_time))

        #run phasar on ll
        cmd = ['time', '/phasar/build/tools/phasar-llvm/phasar-llvm','-D','IFDSUninitializedVariables','-m',llFile,'-O',output_location]
        logger.info(f"Running cmd {cmd}")
        ps = subprocess.run(" ".join(str(s) for s in cmd), capture_output=True, text=True, shell=True, executable="/bin/bash")
        if (ps.returncode != 0) or ("error" in ps.stdout.lower()):
            logger.warning(f"Running phasar on file {str(file)} potentially failed.")
            logger.warning(ps.stderr)

        times = " ".join(ps.stderr.split('\n')[-10:])
        usr_time_match = re.search("user.*?([\\d.]*)m([\\d.]*)s", times)
        usr_time += float(usr_time_match.group(1)) * 60 + float(usr_time_match.group(2))
        logger.info("Usr time for phasar is " + str(usr_time))
        sys_time_match = re.search("sys.*?([\\d.]*)m([\\d.]*)s", times)
        sys_time += float(sys_time_match.group(1)) * 60 + float(sys_time_match.group(2))
        logger.info("Sys time for phasar is " + str(sys_time))
        logger.info(f"CPU time to analyze {file} was {usr_time + sys_time}")

        for root, dirs, files in os.walk(output_location):
            for f in files:
                if f.startswith("psr-report") and f.endswith(".txt"):
                    yield Path(root) / f

