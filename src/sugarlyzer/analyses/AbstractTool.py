import functools
import operator
from abc import ABC, abstractmethod
from pathlib import Path
from typing import Iterable

from src.sugarlyzer.models.Alarm import Alarm
from src.sugarlyzer.readers.AbstractReader import AbstractReader


class AbstractTool(ABC):

    def __init__(self, reader: AbstractReader):
        self.reader = reader

    def analyze_and_read(self, file: str) -> Iterable[Alarm]:
        """
        Analyzes a desugared .c file, and returns the alarms generated.
        :param file: The file to analyze.
        :return: A collection of alarms.
        """
        return functools.reduce(operator.iconcat, [self.reader.read_output(f) for f in self.analyze(file)], [])

    @abstractmethod
    def analyze(self, file: str) -> Iterable[Path]:
        """
        Analyzes a file and returns the location of its output.
        :param file: The file to run analysis on.
        :return: The output file produced by running the tool.
        """
        pass
