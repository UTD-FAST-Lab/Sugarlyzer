import logging
import subprocess
import tempfile
from pathlib import Path
from typing import Iterable, Optional

from src.sugarlyzer.analyses.AbstractTool import AbstractTool
import os
from src.sugarlyzer.readers.PhasarReader import PhasarReader

logger = logging.getLogger(__name__)

class Phasar(AbstractTool):

    def __init__(self):
        super().__init__(PhasarReader())

    def analyze(self, file: Path, includes: Optional[Iterable[str]] = None) -> Iterable[Path]:
        if includes is None:
            includes = []
        output_location = tempfile.mkdtemp()
        #create ll file
        llFile = str(file)[:-2]+'.ll'
        cmd = ['clang-12','-emit-llvm','-S','-fno-discard-value-names','-c','-g',*includes,str(file.absolute()),'-o',llFile]
        logger.info(f"Running cmd {cmd}")
        subprocess.run(cmd)
        #run phasar on ll
        cmd = ['/phasar/build/tools/phasar-llvm/phasar-llvm','-D','IFDSUninitializedVariables','-m',llFile,'-O',output_location]
        logger.info(f"Running cmd {cmd}")
        subprocess.run(cmd)
        for root, dirs, files in os.walk(output_location):
            for f in files:
                if f.startswith("psr-report") and f.endswith(".txt"):
                    yield Path(root) / f

