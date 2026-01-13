import itertools
import logging
import subprocess
import tempfile
import time
from pathlib import Path
from typing import Iterable

from src.sugarlyzer.analyses.AbstractTool import AbstractTool
import os

from src.sugarlyzer.readers.ClangReader import ClangReader

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


        start_time = time.monotonic()
        output_location = tempfile.mkdtemp()
        cmd = ["/usr/bin/time", "-v", "timeout", "--preserve-status", "2h", "clang-11", '-w', '--analyze', "-Xanalyzer",
               "-analyzer-output=text",
               *list(itertools.chain(*zip(itertools.cycle(["-I"]), included_dirs))),
               *list(itertools.chain(*zip(itertools.cycle(["--include"]), included_files))),
               *command_line_defs,
               '-nostdinc',
               "-c", file.absolute()]
        logger.debug(f"Running cmd {' '.join(str(s) for s in cmd)}")
        ps = subprocess.run(" ".join(str(s) for s in cmd), text=True, shell=True, capture_output=True, executable='/bin/bash')

        logger.info(f"Stdout:\n{ps.stdout}\n")
        logger.debug(f"Stderr:\n{ps.stderr}")

        if (ps.returncode != 0):
            logger.warning(f"Running clang on file {str(file)} failed.")

        with open(output_location + '/report.report','w') as o:
            o.write(ps.stderr)

        logger.info(f"True time to analyze file {str(file)} took {time.monotonic() - start_time}s")

        lines = ps.stdout.split("\n")
        logger.critical(f"Analysis time: {lines[-1]}")
            
        for root, _, files in os.walk(output_location):
            for fil in files:
                if fil.startswith("report") and fil.endswith(".report"):
                    r = Path(root) / fil
                    logger.debug(f"Yielding report file {r}")
                    yield Path(root) / fil
