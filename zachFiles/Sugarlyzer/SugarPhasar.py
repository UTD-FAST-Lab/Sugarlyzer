import sys
import os
import shutil
import json
import re
from z3 import *
from abc import ABC,abstractmethod
from Sugarlyzer import *

'''
Sample Output:
====================== IFDS-Uninitialized-Analysis Report ======================

Total uses of uninitialized variables: 1

---------------------------------  1. Use  ---------------------------------

Variable(s): x
Line       : 8
Source code: return x;
Function   : main
File       : /phasar/build/tools/phasar-llvm/test.c

Corresponding IR Statements and uninit. Values
At IR Statement: %1 = load i32, i32* %x, align 4, !dbg !34, !psr.id !35 | ID: 12
   Uninit Value: %x = alloca i32, align 4, !psr.id !12 | ID: 1
'''


class PhasarAlyzer(Sugarlyzer):
  def __init__(self):
    Sugarlyzer.__init__(self)
    
  def runAnalyzer(self,fileName: str,isDesugared: bool) -> list:
    outFi = fileName[:-2]+'.phasarres'
    os.system('clang -O0 -g -S -emit-llvm -fno-discard-value-names ' + fileName)
    os.system('phasar-llvm -m ' + fileName[:-2] + '.ll -D IFDSUninitializedVariables > ' + outFi)
    fi = open(outFi,'r')
    lines = fi.read().split('\n')
    fi.close()
    i = 0
    alarms = []
    while i < len(lines):
      if '--------' in lines[i]:
        alarm = {}
        alarm['msg'] = 'Uninitialized Variable'
        alarm['msgtype'] = 'error'
        alarm['loc'] = int(lines[i+3].split(':')[1].lstrip().rstrip())
        alarm['lines'] = []
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
