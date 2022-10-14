import functools
import logging
import operator
import time
from abc import ABC, abstractmethod
from pathlib import Path
from typing import Iterable, Optional

from src.sugarlyzer.util.decorators import log_all_params_and_return
from src.sugarlyzer.models.Alarm import Alarm, map_source_line
from src.sugarlyzer.readers.AbstractReader import AbstractReader

logger = logging.getLogger(__name__)


class AbstractTool(ABC):

    def __init__(self, reader: AbstractReader):
        self.reader = reader

    @log_all_params_and_return
    def analyze_and_read(self, desugared_file: Path, command_line_defs: Iterable[str] = None,
                         included_dirs: Iterable[Path] = None, included_files: Iterable[Path] = None,
                         user_defined_space=None, no_std_libs=False) -> Iterable[Alarm]:
        """
        Analyzes a desugared .c file, and returns the alarms generated.
        :param no_std_libs:
        :param includes: Includes to specify to the tool (right now, just used to pass in macro definitions.
        :param desugared_file: The file to analyze.
        :return: A collection of alarms.
        """
        start_time = time.time()
        alarms =\
            functools.reduce(operator.iconcat, [self.reader.read_output(f) for f in
                                                self.analyze(file=desugared_file,
                                                             command_line_defs=command_line_defs,
                                                             included_dirs=included_dirs,
                                                             included_files=included_files,
                                                             user_defined_space=user_defined_space,
                                                             no_std_libs=no_std_libs)], [])
        total_time = time.time() - start_time
        for a in alarms:
            a.input_file = desugared_file
            a.time = total_time
            yield a
        return alarms

    @abstractmethod
    def analyze(self, file: Path,
                command_line_defs: Iterable[str] = None,
                included_dirs: Iterable[Path] = None,
                included_files: Iterable[Path] = None,
                user_defined_space=None,
                no_std_libs: bool = False) -> Iterable[Path]:
        """
        Analyzes a file and returns the location of its output.
        :param file: The file to run analysis on.
        :return: The output file produced by running the tool.
        """
        pass
