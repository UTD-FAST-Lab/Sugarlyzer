from abc import ABC, abstractmethod
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
        return self.reader.read_output(self.analyze(file))

    @abstractmethod
    def analyze(self, file: str) -> str:
        """
        Analyzes a file and returns the location of its output.
        :param file: The file to run analysis on.
        :return: The output file produced by running the tool.
        """
        pass
