from abc import ABC, abstractmethod
from pathlib import Path
from typing import Iterable

from src.sugarlyzer.models.Alarm import Alarm


class AbstractReader(ABC):

    @abstractmethod
    def read_output(self, report_file: Path) -> Iterable[Alarm]:
        """
        Given the output of an analysis tool, read in the file and return the alarms.
        :param report_file: The analysis tool result.
        :return: The alarms in the file.
        """
        pass
