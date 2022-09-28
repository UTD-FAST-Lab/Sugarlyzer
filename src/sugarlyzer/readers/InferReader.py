import logging
import re
import json
from html.parser import HTMLParser
from pathlib import Path
from typing import List, Iterable

from src.sugarlyzer.analyses.AbstractTool import AbstractTool
from src.sugarlyzer.models.Alarm import Alarm
from src.sugarlyzer.readers.AbstractReader import AbstractReader

logger = logging.getLogger(__name__)

class InferReader(AbstractReader):

  def read_output(self, report_file: Path) -> Iterable[Alarm]:
    with open(report_file, 'r') as rf:
      reportData = json.load(rf)
      logging.info(f"alarms are in {report_file}")
      alarmList = []
      for alarmData in reportData:
        logging.info(f"Alarm is {alarmData}")
        warningLines = []
        for alarmTrace in alarmData['bug_trace']:
          if alarmTrace['line_number'] not in warningLines:
            warningLines.append(alarmTrace['line_number'])
        ret = Alarm(line_in_file=alarmData['line_number'],
                    bug_type=alarmData['bug_type'],
                    message=alarmData['qualifer'],
                    alarm_type=alarmData['severity'],
                    warning_path=warningLines)
        alarmList.append(ret)
        
      return alarmList
