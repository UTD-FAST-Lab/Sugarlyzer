import logging
import re
from pathlib import Path
from typing import List, Iterable

from src.sugarlyzer.analyses.AbstractTool import AbstractTool
from src.sugarlyzer.models.Alarm import Alarm
from src.sugarlyzer.models.ClangAlarm import ClangAlarm
from src.sugarlyzer.readers.AbstractReader import AbstractReader

logger = logging.getLogger(__name__)

class ClangReader(AbstractReader):

    def read_output(self, report_file: Path) -> Iterable[ClangAlarm]:
        res = []
        with open(report_file, 'r') as rf:
            currentAlarm = None
            for l in rf:
                l = l.lstrip().rstrip()
                if ': warning:' in l:
                    if currentAlarm != None:
                        res.append(currentAlarm)
                    file = l.split(':')[0]
                    line = int(l.split(':')[1])
                    message = ':'.join(l.split(':')[4:])
                    message = '['.join(message.split('[')[:-1])
                    logger.critical(f"l={l}; line={line}; message={message}")
                    currentAlarm = ClangAlarm(line_in_input_file=line,
                                              message=message,
                                              input_file=file,
                                              alarm_type='warning',
                                              warning_path = [])
                elif ': note:' in l:
                    line = int(l.split(':')[1])
                    if currentAlarm != None and line not in currentAlarm.warning_path:
                        currentAlarm.warning_path.append(line)
        if currentAlarm != None:
            res.append(currentAlarm)        
        return res

