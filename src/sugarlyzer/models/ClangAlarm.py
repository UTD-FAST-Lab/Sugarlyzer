import re
from pathlib import Path
from typing import Iterable, Dict

from src.sugarlyzer.models.Alarm import Alarm


class ClangAlarm(Alarm):

    def __init__(self,
                 source_code_file: Path = None,
                 line_in_source_file: int = None,
                 message: str = None,
                 warning_path: Iterable[int] = None,
                 alarm_type: str = None
                 ):
        super().__init__(source_code_file, line_in_source_file, message)
        if warning_path is None:
            warning_path = []
        self.warning_path: Iterable[int] = [int(i) for i in warning_path]
        self.alarm_type = alarm_type

    def as_dict(self) -> Dict[str, str]:
        result = super().as_dict()
        result['desugared_path'] = str(self.warning_path),
        result['alarm_type'] = self.alarm_type
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

