import subprocess
import tempfile
from pathlib import Path
from typing import Iterable

from src.sugarlyzer.analyses.AbstractTool import AbstractTool
import sys
import os
import shutil
import json
import re

from src.sugarlyzer.readers.ClangReader import ClangReader

configFile = "~/Documents/Research/SugarCPostWork/scanBuildAtomizer/configs.txt"


def parseConf():
    global configFile
    global ScanBuild
    global Clang
    fx = open(configFile, 'r')
    for l in fx:
        if l.startswith('scanbuild'):
            n = l.rstrip()
            ScanBuild = n.split('=')[1]
        if l.startswith('clang'):
            n = l.rstrip()
            Clang = n.split('=')[1]


def scan(projStr, fileStr, filePath):
    global ScanBuild
    global Clang
    parseConf()
    reports = []
    scanOut = '/tmp/' + projStr + '/' + fileStr
    os.system('rm -r ' + scanOut)
    os.system(' '.join([ScanBuild, '-o', scanOut, Clang, '-c', filePath]))
    for report in os.listdir(scanOut):
        reportPack = scanOut + '/' + report
        for r in os.listdir(reportPack):
            if r.startswith('report') and r.endswith('.html'):
                print(reportPack + '/' + r)
                rep = atomize(reportPack + '/' + r)
                reports.append(rep)
    return reports




class Clang(AbstractTool):

    def __init__(self):
        super().__init__(ClangReader())

    def analyze(self, file: str) -> Iterable[Path]:
        output_location = tempfile.mkdtemp()
        subprocess.run(["scan-build", "-o", output_location, "clang", "-c", os.path.abspath(file)])
        for root, dirs, files in os.walk(output_location):
            for f in files:
                if f.startswith("report") and f.endswith(".html"):
                    yield Path(root)/f


if __name__ == '__main__':
    if (len(sys.argv) != 4):
        print("must have 3 arguments")
        exit()
    scan(sys.argv[1], sys.argv[2], sys.argv[3])  # Project , file name , path to file
