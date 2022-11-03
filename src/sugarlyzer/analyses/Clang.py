import itertools
import logging
import subprocess
import tempfile
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
                command_line_defs: Iterable[str] = None):
        if command_line_defs is None:
            command_line_defs = []
        if included_dirs is None:
            included_dirs = []
        if included_files is None:
            included_files = []

        output_location = tempfile.mkdtemp()
        checkers = ['core.CallAndMessage','core.DivideZero','core.NonNullParamChecker','core.NullDereference','core.StackAddressEscape',
         'core.UndefinedBinaryOperatorResult','core.VLASize','core.uninitialized.ArraySubscript','core.uninitialized.Assign',
         'core.uninitialized.Branch','core.uninitialized.CapturedBlockVariable','core.uninitialized.UndefReturn'
         'unix.API','unix.Malloc','unix.MallocSizeof','unix.MismatchedDeallocator','unix.Vfork','unix.cstring.BadSizeArg','unix.cstring.NullArg']
        for checker in checkers:
            cmd = ["scan-build", "-o", output_location, "clang", '--analyze', '--analyzer-no-default-checks', '-Xanalyzer', '-analyzer-checker=' + checker,
               *list(itertools.chain(*zip(itertools.cycle(["-I"]), included_dirs))),
               *list(itertools.chain(*zip(itertools.cycle(["--include"]), included_files))),
               *command_line_defs,
               '-nostdinc',
               "-c", file.absolute()]
            logger.info(f"Running cmd {' '.join(str(s) for s in cmd)}")
            ps = subprocess.run(cmd, stderr=subprocess.STDOUT, stdout=subprocess.PIPE, text=True)
            if (ps.returncode != 0) or ("error" in ps.stdout.lower()):
                logger.warning(f"Running clang on file {str(file)} potentially failed.")
                logger.warning(ps.stdout)

        for root, dirs, files in os.walk(output_location):
            for fil in files:
                if fil.startswith("report") and fil.endswith(".html"):
                    r = Path(root) / fil
                    logger.debug(f"Yielding report file {r}")
                    yield Path(root) / fil
