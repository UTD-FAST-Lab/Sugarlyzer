import logging
import re
import json
from pathlib import Path
from typing import List, Iterable

from src.sugarlyzer.analyses.AbstractTool import AbstractTool
from src.sugarlyzer.models.Alarm import Alarm
from src.sugarlyzer.models.InferAlarm import InferAlarm
from src.sugarlyzer.readers.AbstractReader import AbstractReader

from src.sugarlyzer.readers.AbstractReader import AbstractReader

logger = logging.getLogger(__name__)

class InferReader(AbstractReader):

  def read_output(self, report_file: Path) -> Iterable[Alarm]:
    if not Path(report_file).exists():
      return []
    with open(report_file, 'r') as rf:
      reportData = json.load(rf)
      logging.info(f"alarms are in {report_file}")
      alarmList = []
      logging.info(f"reportData is {reportData}")
      for alarmData in reportData:
        logging.info(f"Alarm is {alarmData}")
        warningLines = []
        for alarmTrace in alarmData['bug_trace']:
          if alarmTrace['line_number'] not in warningLines:
            warningLines.append(alarmTrace['line_number'])
        ret = InferAlarm(line_in_input_file=alarmData['line'],
                    bug_type=alarmData['bug_type'],
                    message=alarmData['qualifier'],
                    alarm_type=alarmData['severity'],
                    warning_path=warningLines)
        alarmList.append(ret)
        
      print('ALarms:',alarmList)
      return alarmList
