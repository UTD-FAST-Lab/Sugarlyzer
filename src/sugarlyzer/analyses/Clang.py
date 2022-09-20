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

    def analyze(self, file: Path, includes: Optional[Iterable[str]] = None) -> Iterable[Path]:
        if includes is None:
            includes = []
        output_location = tempfile.mkdtemp()
        cmd = ["scan-build", "-o", output_location, "clang", *includes, "-c", file.absolute()]
        logger.info(f"Running cmd {cmd}")
        subprocess.run(cmd)
        for root, dirs, files in os.walk(output_location):
            for f in files:
                if f.startswith("report") and f.endswith(".html"):
                    yield Path(root) / f
