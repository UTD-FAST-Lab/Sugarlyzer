from abc import ABC, abstractmethod
from typing import Iterable

from src.sugarlyzer.models.Alarm import Alarm


class AbstractReader(ABC):

    @abstractmethod
    def read_output(self, file: str) -> Iterable[Alarm]:
        """
        Given the output of an analysis tool, read in the file and return the alarms.
        :param file: The analysis tool result.
        :return: The alarms in the file.
        """
        pass
