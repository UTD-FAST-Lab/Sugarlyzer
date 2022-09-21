import functools
import logging
import operator
from abc import ABC, abstractmethod
from pathlib import Path
from typing import Iterable, Optional

from src.sugarlyzer.SugarCRunner import process_alarms
from src.sugarlyzer.models.Alarm import Alarm, map_source_line
from src.sugarlyzer.readers.AbstractReader import AbstractReader

logger = logging.getLogger(__name__)


class AbstractTool(ABC):

    def __init__(self, reader: AbstractReader):
        self.reader = reader

    def analyze_and_read(self,
                         desugared_file: Path,
                         includes: Optional[Iterable[str]] = None) -> Iterable[Alarm]:
        """
        Analyzes a desugared .c file, and returns the alarms generated.
        :param includes: Includes to specify to the tool (right now, just used to pass in macro definitions.
        :param desugared_file: The file to analyze.
        :return: A collection of alarms.
        """
        alarms: Iterable[Alarm] =\
            functools.reduce(operator.iconcat, [self.reader.read_output(f) for f in self.analyze(desugared_file, includes)], [])
        for a in alarms:
            a.source_code_file = desugared_file
        return alarms

    @abstractmethod
    def analyze(self, file: Path,
                includes: Optional[Iterable[str]] = None) -> Iterable[Path]:
        """
        Analyzes a file and returns the location of its output.
        :param includes: Includes to specify to the tool (right now, just used to pass in macro definitions.
        :param file: The file to run analysis on.
        :return: The output file produced by running the tool.
        """
        pass
