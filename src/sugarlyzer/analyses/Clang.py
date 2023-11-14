import itertools
import logging
import subprocess
import tempfile
import time
from pathlib import Path
from typing import Iterable, Optional
import re

from src.sugarlyzer.analyses.AbstractTool import AbstractTool
import os

from src.sugarlyzer.readers.ClangReader import ClangReader
from src.sugarlyzer.util.decorators import log_all_params_and_return

logger = logging.getLogger(__name__)


class Clang(AbstractTool):

    def __init__(self):
        super().__init__(ClangReader(), name='clang', keep_mem=True, make_main=True, remove_errors=False)

    def analyze(self, file: Path,
                included_dirs: Iterable[Path] = None,
                included_files: Iterable[Path] = None,
                command_line_defs: Iterable[str] = None,
                **kwargs):
        if command_line_defs is None:
            command_line_defs = []
        if included_dirs is None:
            included_dirs = []
        if included_files is None:
            included_files = []

        output_location = tempfile.mkdtemp()
        cmd = ["ulimit -v 100000000;", "time", "clang-11", '--analyze', "-Xanalyzer", "-analyzer-output=text",
               *list(itertools.chain(*zip(itertools.cycle(["-I"]), included_dirs))),
               *list(itertools.chain(*zip(itertools.cycle(["--include"]), included_files))),
               *command_line_defs,
               '-nostdinc',
               "-c", file.absolute()]
        logger.info(f"Running cmd {' '.join(str(s) for s in cmd)}")

        ps = subprocess.run(" ".join(str(s) for s in cmd), capture_output=True, shell=True, text=True, executable="/bin/bash")
        stdout = ps.stdout
        stderr = ps.stderr
        times = " ".join(stderr.split('\n')[-10:])
        usr_time_match = re.search("user.*?([\\d.]*)m([\\d.]*)s", times)
        usr_time = float(usr_time_match.group(1)) * 60 + float(usr_time_match.group(2))
        logger.info("Usr time is " + str(usr_time))
        sys_time_match = re.search("sys.*?([\\d.]*)m([\\d.]*)s", times)
        sys_time = float(sys_time_match.group(1)) * 60 + float(sys_time_match.group(2))
        logger.info("Sys time is " + str(sys_time))
        logger.info(f"CPU time to analyze {file} was {usr_time + sys_time}")
        if (ps.returncode != 0) or ("error" in stdout.lower()):
            logger.warning(f"Running clang on file {str(file)} potentially failed.")
            logger.warning(stdout)

        with open(output_location + '/report.report','w') as o:
            o.write(stderr)

        lines = stdout.split("\n")
        logger.critical(f"Analysis time: {lines[-1]}")
            
        for root, dirs, files in os.walk(output_location):
            for fil in files:
                if fil.startswith("report") and fil.endswith(".report"):
                    r = Path(root) / fil
                    logger.debug(f"Yielding report file {r}")
                    yield Path(root) / fil
