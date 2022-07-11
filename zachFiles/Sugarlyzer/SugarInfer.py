import sys
import os
import shutil
import json
import re
from z3 import *
from abc import ABC,abstractmethod
from Sugarlyzer import *


class InferAlyzer(Sugarlyzer):
  def __init__(self):
    Sugarlyzer.__init__(self)
    
  def runAnalyzer(self,fileName: str,isDesugared: bool) -> list:
    outFi = fileName[:-2]+'.inferres'
    os.system('infer --pulse-only --enable-issue-type NULLPTR_DEREFERENCE_LATENT -- clang -c ' + fileName + ' > ' + outFi)
    fi = open(outFi,'r')
    lines = fi.read().split('\n')
    fi.close()
    i = 0
    alarms = []
    while i < len(lines):
      if lines[i].rstrip().endswith('error: Null Dereference') and lines[i+1].lstrip().startswith("`"):
        alarm = {}
        alarm['msg'] = 'Null Dereference'
        alarm['msgtype'] = 'error'
        alarm['loc'] = int(lines[i].split(':')[1])
        alarm['lines'] = []
        m = re.search(r'last assigned on line (\d+)',lines[i+1])
        print (m, lines[i+1])
        if m:
          alarm['lines'].append(int(m.group(1)))
        alarm['lines'].append(alarm['loc'])
        alarms.append(alarm)
      i += 1
    return alarms
    
    
  def compareAlarms(self, alarmA: Alarm, alarmB: Alarm) -> bool:
    pass

if __name__ == "__main__":
  n = sys.argv[1]
  i = InferAlyzer()
  i.setFile(n)
  r = i.getRecommendedSpace()
  cma = ['-keep-mem']
  incf = ["~/SystemConfig/baseInc.h"]
  incd = ["~/SystemConfig/original/usr/include/", "~/SystemConfig/original/usr/include/x86_64-linux-gnu/", "~/SystemConfig/original/usr/lib/gcc/x86_64-linux-gnu/9/include/"] 
  df = i.desugarFile(r,remove_errors=True,no_stdlibs=True,commandline_args=cma,included_files=incf,included_directories=incd)
  print (i.analyze()) 
