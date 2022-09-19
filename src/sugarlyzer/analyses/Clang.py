import subprocess
import tempfile
from pathlib import Path
from typing import Iterable

from src.sugarlyzer.analyses.AbstractTool import AbstractTool
import os

from src.sugarlyzer.readers.ClangReader import ClangReader


class Clang(AbstractTool):

    def __init__(self):
        super().__init__(ClangReader())

    def analyze(self, file: Path) -> Iterable[Path]:
        output_location = tempfile.mkdtemp()
        subprocess.run(["scan-build", "-o", output_location, "clang", "-c", file.absolute()])
        for root, dirs, files in os.walk(output_location):
            for f in files:
                if f.startswith("report") and f.endswith(".html"):
                    yield Path(root) / f
