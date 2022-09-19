import re
from pathlib import Path
from typing import Iterable, Dict

from src.sugarlyzer.models.Alarm import Alarm


class ClangAlarm(Alarm):

    def __init__(self,
                 original_file: Path = None,
                 desugared_file: Path = None,
                 desugared_line: int = None,
                 message: str = None,
                 desugared_code_path: Iterable[int] = None,
                 alarm_type: str = None
                 ):
        super().__init__(original_file, desugared_file, desugared_line, message)
        if desugared_code_path is None:
            desugared_code_path = []
        self.desugared_code_path: Iterable[int] = desugared_code_path
        self.alarm_type = alarm_type

    def as_dict(self) -> Dict[str, str]:
        result = super().as_dict()
        result['desugared_path'] = str(self.desugared_code_path),
        result['alarm_type'] = self.alarm_type
        return result

    def sanitize(self, message: str):
        san = message.rstrip()
        san = re.sub(r'__(.*)_\d+', r'\1', san)
        if san.endswith(']'):
            san = re.sub(r' \[.*\]$', '', san)
        return san

    @property
    def all_desugared_lines(self) -> Iterable[int]:
        """
        Since in Clang, desugared path always includes the desugared line, we just return the desugared path.

        :return: An iterator over the lines Clang returns as the path in the desugared file.
        """
        return self.desugared_code_path  ## We expect desugared_path to contain desugared_line

