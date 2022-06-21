import sys
import os
import shutil
import json
import re
from z3 import *
SLOC = "~/Documents/Research/SugarCPostWork/scanBuildAtomizer"
sys.path.append(SLOC)
from warningSolver import *
from scanBuildAtomizer import scan

def checkNonFlow(w,fpa):
  '''
  Logic is as follows, we take advantage off the fact that we always use braces
  We start at our line number and reverse search up. Whenever we find a }
  we skip lines until we match {. This way we can only explore up a scope level
  If we find a __static_condition_renaming, we are in logically true,
  global scope, or in a function without an explicit condition in the body
  '''
  if len(w['lines']) == 1:
    ff = open(fpa,'r')
    lines = ff.read().split('\n')
    Rs = 0
    l = int(w['lines'][0])-1
    while l >= 0:
      Rs += lines[l].count('}')
      m = re.match('if \((__static_condition_default_\d+)\).*',lines[l])
      if Rs == 0 and m:
        w['asserts'].append({'var' : str(m.group(1)), 'val' : True})
      Rs -= lines[l].count('{')
      if Rs < 0:
        Rs = 0
      l -= 1
    ff.close()

def getCorrelateLine(fpa,loc):
  lin = int(loc.split(',')[0][5:])
  fl = open(fpa,'r')
  lines = fl.read().split('\n')
  theLine = lines[lin-1]
  if '// L' not in theLine:
    return '0'
  return theLine.split('// L')[1]

def getConditionMapping(l, ids, varis, replacers, invert):
  if l.startswith('__static_condition_renaming('):
    cc = l.split(',')
    conds = cc[1][:-3]
    conds = re.sub(r'(&&|\|\|) !([a-zA-Z_0-9]+)( |")', r'\1 !(\2)\3', conds)
    conds = re.sub(r'(&&|\|\|) ([a-zA-Z_0-9]+)( |")', r'\1 (\2)\3', conds)
    conds = re.sub(r' "([a-zA-Z_0-9]+)', r' "(\1)', conds)
    conds = re.sub(r' "!([a-zA-Z_0-9]+)', r' "!(\1)', conds)
    conds = conds[:-1]
    inds = conds.split('(')
    inds = inds[1:]
    for i in inds:
      splits = i.split(' ')
      if 'defined' == splits[0]:
        v = 'DEF_'+splits[1][:-1]
        ids['defined '+splits[1][:-1]] = 'varis["' + v + '"]'
        varis[v] = Bool(v)
      else:
        if splits[0][-1] == ')':
          v = 'USE_'+splits[0][:-1]
          ids[splits[0][:-1]] = 'varis["' + v + '"] != 0'
          varis[v] = Int(v)
        else:
          v = 'USE_'+splits[0]
          ids[splits[0]] = 'varis["' + v + '"]'
          varis[v] = Int(v)
    condstr = conds[2:]
    for x in sorted(list(ids.keys()),key=len,reverse=True):
      if x.startswith('defined '):
        condstr = condstr.replace(x,ids[x])
      else:
        condstr = condstr.replace('('+x,'('+ids[x])
    condstr = condstr.replace('!(', 'Not(')
    cs = re.split('&&|\|\|',condstr)
    ops = []
    for d in range ( 0, len(condstr)):
      if condstr[d] == '&' and condstr[d+1] == '&':
        ops.append('And')
      elif condstr[d] == '|' and condstr[d+1] == '|':
        ops.append('Or')
    ncondstr = ''
    ands = 0
    ors = 0
    for o in ops:
      if o == 'And':
        ands += 1
        ncondstr = ncondstr + 'And (' + cs[0] + ','
        cs = cs[1:]
      else:
        ncondstr = 'Or(' + ncondstr + cs[0] + ands*')'
        if ors > 0:
          ncondstr += ')'
        ncondstr += ','
        ands = 0
        ors += 1
        cs = cs[1:]
    ncondstr += cs[0] + ands*')'
    if ors > 0:
      ncondstr += ')'
    ncondstr = ncondstr.rstrip()
    if invert:
      ncondstr = 'Not(' + ncondstr + ')'
    replacers[cc[0][len('__static_condition_renaming("'):-1]] = ncondstr

def main(p,f,fpa):
  ids = {}
  replacers = {}
  ls = []
  varis = {}
  fl = open(fpa,'r')
  for l in fl:
    ls.append(l)
    getConditionMapping(l, ids, varis, replacers, False)
  fl.close()
  warns = scan(p,f,fpa)
  for w in warns:
    checkNonFlow(w,fpa)
    s = Solver()
    for a in w['asserts']:
      if a['val']:
        s.add(eval(replacers[a['var']]))
      else:
        s.add(eval('Not('+replacers[a['var']]+')'))
    if s.check() == sat:
      m = s.model()
      w['feasible'] = True
      w['model'] = m
      w['correNum'] = getCorrelateLine(fpa,w['loc'])
    else:
      print ('impossible constraints')
      w['feasible'] = False
      w['correNum'] = '-1'
  return warns
     
if __name__ == '__main__':
  if len(sys.argv) < 4:
    print('Provide project name file\n')
  else:
    main(sys.argv[1],sys.argv[2],sys.argv[3])
