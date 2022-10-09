import logging
import subprocess
import tempfile
from pathlib import Path
from typing import Iterable, Optional

from src.sugarlyzer.analyses.AbstractTool import AbstractTool
import os

from src.sugarlyzer.readers.InferReader import InferReader

logger = logging.getLogger(__name__)

class Infer(AbstractTool):

    def __init__(self):
        super().__init__(InferReader())

    def analyze(self, file: Path, includes: Optional[Iterable[str]] = None) -> Iterable[Path]:
        if includes is None:
            includes = []
        output_location = tempfile.mkdtemp()
        cmd = ["infer", "--pulse-only", '-o', output_location, '--', "clang", *includes, "-c", file.absolute()]
        logger.info(f"Running cmd {cmd}")
        subprocess.run(cmd)
        report = os.path.join(output_location,'report.json')
        yield report
