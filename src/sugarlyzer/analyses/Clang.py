import itertools
import logging
import subprocess
import tempfile
import time
from pathlib import Path
from typing import Iterable, Optional

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
        cmd = ["time", "clang-11", '--analyze', "-Xanalyzer", "-analyzer-output=text",
               *list(itertools.chain(*zip(itertools.cycle(["-I"]), included_dirs))),
               *list(itertools.chain(*zip(itertools.cycle(["--include"]), included_files))),
               *command_line_defs,
               '-nostdinc',
               "-c", file.absolute()]
        logger.info(f"Running cmd {' '.join(str(s) for s in cmd)}")

        pipes = subprocess.Popen(cmd, stderr=subprocess.PIPE, stdout=subprocess.PIPE)
        stdout, stderr = pipes.communicate()
        stdout = str(stdout, 'UTF-8')
        stderr = str(stderr, 'UTF-8')
        if (pipes.returncode != 0) or ("error" in stdout.lower()):
            logger.warning(f"Running clang on file {str(file)} potentially failed.")
            logger.warning(stdout)

        with open(output_location + '/report.report','w') as o:
            o.write(stderr)

        logger.critical(f"Analysis time: {stdout.split('\n')[-1]}")
            
        for root, dirs, files in os.walk(output_location):
            for fil in files:
                if fil.startswith("report") and fil.endswith(".report"):
                    r = Path(root) / fil
                    logger.debug(f"Yielding report file {r}")
                    yield Path(root) / fil
