import itertools
import logging
import subprocess
import tempfile
from pathlib import Path
from typing import Iterable, Optional

from src.sugarlyzer.analyses.AbstractTool import AbstractTool
import os

from src.sugarlyzer.readers.ClangReader import ClangReader

logger = logging.getLogger(__name__)


class Clang(AbstractTool):

    def __init__(self):
        super().__init__(ClangReader())

    def analyze(self, file: Path,
                command_line_defs: Iterable[str] = None,
                included_dirs: Iterable[Path] = None,
                included_files: Iterable[Path] = None,
                user_defined_space=None,
                no_std_libs = False) -> Path:
        if command_line_defs is None:
            command_line_defs = []
        if included_dirs is None:
            included_dirs = []
        if included_files is None:
            included_files = []

        if not (user_defined_space in [None, '']):
            f = tempfile.TemporaryFile(mode='w')
            f.write(user_defined_space)
            included_files = included_files.append(f)

        output_location = tempfile.mkdtemp()
        cmd = ["scan-build", "-o", output_location, "clang",
               *(zip(itertools.cycle(["-I"]), included_dirs)),
               *(zip(itertools.cycle(["--include"]), included_files)),
               *command_line_defs,
               *(['-nostdinc'] if no_std_libs else []),
               "-c", file.absolute()]
        logger.info(f"Running cmd {cmd}")
        subprocess.run(cmd)
        f.close()
        for root, dirs, files in os.walk(output_location):
            for f in files:
                if f.startswith("report") and f.endswith(".html"):
                    yield Path(root) / f
