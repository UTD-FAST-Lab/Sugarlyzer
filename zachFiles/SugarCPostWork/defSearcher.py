import sys
import os
import shutil
import json
import re
from z3 import *
SLOC = "~/Documents/Research/SugarCPostWork/scanBuildAtomizer"
sys.path.append(SLOC)

def getAllMacros(fpa):
  ff = open(fpa,'r')
  lines = ff.read().split('\n')
  defs = []
  for l in lines:
    if '#if' in l:
      m = re.match(' *#ifdef *([a-zA-Z0-9_]+).*',l)
      if m:
        v = m.group(1)
        if v not in defs:
          defs.append(v)
        continue
      m = re.match(' *#ifndef *([a-zA-Z0-9_]+).*',l)
      if m:
        v = m.group(1)
        if v not in defs:
          defs.append(v)
        continue
      m = re.match(' *#if *([a-zA-Z0-9_]+).*',l)
      if m:
        v = m.group(1)
        if v not in defs:
          defs.append(v)
        continue
      ds = re.findall(r'defined *([a-zA-Z0-9_]+?)',l)
      for d in ds:
        if d not in defs:
          defs.append(d)
  return defs
      
