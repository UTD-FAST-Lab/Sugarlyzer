import sys
import os
import shutil
import json
import re
from z3 import *
from abc import ABC,abstractmethod
from Sugarlyzer import *
SLOC = "~/Documents/Research/SugarCPostWork/scanBuildAtomizer"
sys.path.append(SLOC)
from scanBuildAtomizer import scan


class ClangAlyzer(Sugarlyzer):
  def __init__(self):
    Sugarlyzer.__init__(self)
    
  def runAnalyzer(self,fileName: str,isDesugared: bool) -> list:
    print (fileName,fileName.split('/')[-1][:-2],fileName.split('/')[-2])
    return scan(fileName.split('/')[-2],fileName.split('/')[-1][:-2],fileName)
  
  def compareAlarms(self, alarmA: Alarm, alarmB: Alarm) -> bool:
    pass

if __name__ == "__main__":
  n = sys.argv[1]
  c = ClangAlyzer()
  c.setFile(n)
  r = c.getRecommendedSpace()
  cma = ['-keep-mem']
  incf = ["~/SystemConfig/baseInc.h"]
  incd = ["~/SystemConfig/original/use/include/", "~/SystemConfig/original/use/include/x86_64-linux-gnu/", "~/SystemConfig/original/usr/lib/gcc/x86_64-linux-gnu/9/include/"] 
  df = c.desugarFile(r,remove_errors=True,no_stdlibs=True,commandline_args=cma,included_files=incf,included_directories=incd)
  print (c.analyze()) 