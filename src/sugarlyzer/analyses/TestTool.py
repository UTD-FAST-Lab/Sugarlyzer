from src.sugarlyzer.analyses.AbstractTool import AbstractTool
from pathlib import Path
from typing import Iterable, Optional
from src.sugarlyzer.readers.TestReader import TestReader


class TestTool(AbstractTool):

    def __init__(self):
        super().__init__(TestReader(), name='testTool', keep_mem=True, make_main=True, remove_errors=False)
    def analyze(self, file: Path,
                included_dirs: Iterable[Path] = None,
                included_files: Iterable[Path] = None,
                command_line_defs: Iterable[str] = None):
        print(f"Analyzing {file}")
        yield file
