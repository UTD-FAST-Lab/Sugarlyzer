import sys
import os
import shutil
import json
import re
from z3 import *
from abc import ABC, abstractmethod
from Sugarlyzer import *

SLOC = "/home/kisamefishfry/Documents/Research/SugarCPostWork/scanBuildAtomizer"
sys.path.append(SLOC)
from scanBuildAtomizer import scan


class ClangAlyzer(Sugarlyzer):
    def __init__(self):
        Sugarlyzer.__init__(self)

    def runAnalyzer(self, fileName: str, isDesugared: bool) -> list:
        print(fileName, fileName.split('/')[-1][:-2], fileName.split('/')[-2])
        return scan(fileName.split('/')[-2], fileName.split('/')[-1][:-2], fileName)

    def compareAlarms(self, alarmA: Alarm, alarmB: Alarm) -> bool:
        pass


if __name__ == "__main__":
    n = sys.argv[1]
    c = ClangAlyzer()
    c.setFile(n)
    c.setDebug(True)
    #incf = ["~/SystemConfig/baseInc.h"]
    #incd = ["~/SystemConfig/original/use/include/", "~/SystemConfig/original/use/include/x86_64-linux-gnu/",
    #        "~/SystemConfig/original/usr/lib/gcc/x86_64-linux-gnu/9/include/"]
    incf = []
    incd = ['~/Documents/Research/VarBugsOriginals/APACHE/ecf18a4ac25b72861bce4b7b3f5b3883052ec4e3/httpd-ecf18a4ac25b72861bce4b7b3f5b3883052ec4e3/modules/experimental','~/Documents/Research/VarBugsOriginals/APACHE/ecf18a4ac25b72861bce4b7b3f5b3883052ec4e3/httpd-ecf18a4ac25b72861bce4b7b3f5b3883052ec4e3/include']
    c.setInclusions(incf,incd,False)
    r = c.getRecommendedSpace()
    cma = ['-keep-mem']
    df = c.desugarFile(r, remove_errors=False, commandline_args=cma)
    print(c.analyze())
