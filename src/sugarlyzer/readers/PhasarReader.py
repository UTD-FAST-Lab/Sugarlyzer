import logging
import re
import json
from pathlib import Path
from typing import List, Iterable

from src.sugarlyzer.analyses.AbstractTool import AbstractTool
from src.sugarlyzer.models.Alarm import Alarm
from src.sugarlyzer.models.PhasarAlarm import PhasarAlarm
from src.sugarlyzer.readers.AbstractReader import AbstractReader

logger = logging.getLogger(__name__)


class PhasarReader(AbstractReader):

    def read_output(self, report_file: Path) -> Iterable[Alarm]:
        if not Path(report_file).exists():
            return []
        with open(report_file, 'r') as rf:
            logging.info(f"alarms are in {report_file}")
            alarmList = []
            warning = {}
            for l in rf:
                if 'Use  --------' in l:
                    if 'function' in warning.keys() and 'variables' in warning.keys() and 'line' in warning.keys():
                        for var in warning['variables']:
                            alarmList.append(PhasarAlarm(function=warning['function'],
                                                         line_in_input_file=warning['line'],
                                                         variable_name=var))
                    warning = {}
                elif 'Function   :' in l:
                    warning['function'] = l.split('Function   : ')[1].lstrip().rstrip()
                elif 'Variable(s):' in l:
                    warning['variables'] = l.split('Variable(s):')[1].lstrip().rstrip().split(',')
                elif 'Line       :' in l:
                    warning['line'] = int(l.split('Line       : ')[1].lstrip().rstrip())
            if 'function' in warning.keys() and 'variables' in warning.keys() and 'line' in warning.keys():
                for var in warning['variables']:
                    alarmList.append(PhasarAlarm(function=warning['function'],
                                                 line_in_input_file=warning['line'],
                                                 variable_name=var))

            return alarmList
