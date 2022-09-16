import re
from pathlib import Path
from typing import Iterable, Dict

from src.sugarlyzer.models.Alarm import Alarm


class ClangAlarm(Alarm):

    def __init__(self,
                 file: Path,
                 desugared_line: int,
                 message: str,
                 desugared_path: Iterable[int],
                 alarm_type: str
                 ):
        super().__init__(file, desugared_line, message)
        self.desugared_path: Iterable[int] = desugared_path
        self.alarm_type = alarm_type

    def as_dict(self) -> Dict[str, str]:
        result = super().as_dict()
        result['desugared_path'] = str(self.desugared_path),
        result['alarm_type'] = self.alarm_type
        return result

    def sanitize(self, message: str):
        san = message.rstrip()
        san = re.sub("__(.*)_\d+", "\1", san)
        if san.endswith(']'):
            san = re.sub(r' \[.*\]$', '', san)
        return san
