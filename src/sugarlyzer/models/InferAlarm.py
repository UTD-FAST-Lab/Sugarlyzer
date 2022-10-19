import re
from pathlib import Path
from typing import Iterable, Dict

from src.sugarlyzer.models.Alarm import Alarm


class InferAlarm(Alarm):

    def __init__(self,
                 input_file: Path = None,
                 line_in_input_file: int = None,
                 bug_type: str = None,
                 message: str = None,
                 warning_path: Iterable[int] = None,
                 alarm_type: str = None
                 ):
        super().__init__(input_file, line_in_input_file, message)
        if warning_path is None:
            warning_path = []
        self.warning_path: Iterable[int] = [int(i) for i in warning_path]
        self.alarm_type = alarm_type
        self.bug_type = bug_type

    def as_dict(self) -> Dict[str, str]:
        result = super().as_dict()
        result['warning_path'] = self.warning_path,
        result['alarm_type'] = self.alarm_type
        result['bug_type'] = self.bug_type
        return result

    def sanitize(self, message: str):
        san = message.rstrip()
        san = re.sub(r'__(.*)_\d+', r'\1', san)
        if san.endswith(']'):
            san = re.sub(r' \[.*\]$', '', san)
        return san

    @property
    def all_relevant_lines(self) -> Iterable[int]:
        """
        Since in Clang, desugared path always includes the desugared line, we just return the desugared path.

        :return: An iterator over the lines Clang returns as the path in the desugared file.
        """
        return self.warning_path  ## We expect desugared_path to contain desugared_line
