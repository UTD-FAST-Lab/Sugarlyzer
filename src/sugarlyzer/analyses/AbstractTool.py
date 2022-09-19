import functools
import operator
from abc import ABC, abstractmethod
from pathlib import Path
from typing import Iterable

from src.sugarlyzer.SugarCRunner import process_alarms
from src.sugarlyzer.models.Alarm import Alarm, map_source_line
from src.sugarlyzer.readers.AbstractReader import AbstractReader


class AbstractTool(ABC):

    def __init__(self, reader: AbstractReader):
        self.reader = reader

    def analyze_and_read(self, desugared_file: Path) -> Iterable[Alarm]:
        """
        Analyzes a desugared .c file, and returns the alarms generated.
        :param desugared_file: The file to analyze.
        :return: A collection of alarms.
        """
        alarms: Iterable[Alarm] =\
            functools.reduce(operator.iconcat, [self.reader.read_output(f) for f in self.analyze(desugared_file)], [])
        for a in alarms:
            a.desugared_file = desugared_file
        return process_alarms(alarms, desugared_file)


    @abstractmethod
    def analyze(self, file: Path) -> Iterable[Path]:
        """
        Analyzes a file and returns the location of its output.
        :param file: The file to run analysis on.
        :return: The output file produced by running the tool.
        """
        pass
