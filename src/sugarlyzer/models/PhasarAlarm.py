import re
from pathlib import Path
from typing import Iterable, Dict

from src.sugarlyzer.models.Alarm import Alarm


class PhasarAlarm(Alarm):

    def __init__(self,
                 input_file: Path = None,
                 function: str = None,
                 line_in_input_file: int = None,
                 variable_name: str = None,
                 message: str = 'Uninitialized Variable'
                 ):
        super().__init__(input_file, line_in_input_file, message)
        warning_path = [line_in_input_file]
        self.warning_path: Iterable[int] = [int(i) for i in warning_path]
        self.variable_name = variable_name
        self.function = function

    def as_dict(self) -> Dict[str, str]:
        result = super().as_dict()
        result['warning_path'] = str(self.warning_path),
        result['function'] = self.function
        result['variable'] = self.variable_name
        return result

    def sanitize(self, message: str):
        san = message.rstrip()
        return san

    @property
    def all_relevant_lines(self) -> Iterable[int]:
        """
        Since in Clang, desugared path always includes the desugared line, we just return the desugared path.

        :return: An iterator over the lines Clang returns as the path in the desugared file.
        """
        return self.warning_path  ## We expect desugared_path to contain desugared_line
