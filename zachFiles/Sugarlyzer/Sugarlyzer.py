import sys
import os
import shutil
import json
import re
from z3 import *
from abc import ABC,abstractmethod

userDefs = '/tmp/__sugarlyzerPredefs.h'

idCounter = 1

class Alarm:
  def __init__(self):
    global idCounter
    self.msg = ''
    self.line = 0
    self.lineA = 0
    self.lineB = 0
    self.idn = idCounter
    idCounter += 1

  def sanitize(self):
    san = self.msg.rstrip()
    if " '" in san:
      san = re.sub(r" '\S+'", " 'x'", san)
    if san.endswith(']'):
      san = re.sub(r' \[.*\]$', '', san)
    return san

  def tostr(self):
    return ' '.join(['('+self.sanitize()+')',str(self.line),str(self.lineA),str(self.lineB)])
      
  def areEq(self,inner):
    print(self.tostr() + ' ||' + inner.tostr())
    return self.sanitize() == inner.sanitize() and inner.line >= self.lineA and inner.line <= self.lineB


class Sugarlyzer:
  def __init__(self):
    self.fil = ''
    self.userDefinedMacros = ''
    self.desug = ''
 
  def setFile(self,fileName: str):
     '''Specifies the file that will be desugared and analyzed.
     
     Parameters:
     fileName (str): absolute path of the file
     
     Returns:
     void
     '''
     self.fil = os.path.abspath(fileName)

  def getRecommendedSpace(self) -> str:
    '''Explores the file provided in setFile. Looks for inclusion guards or other
    macros that would be assumed to be false and recommends them to be turned off.
    Also grabs the default conditions of the machine provided by gcc.
     
    Returns:
    A string to be added to an included file in desugaring
    '''
    #still need to create the code to search for inclusion guards
    return os.popen('echo | gcc -dM -E -').read()

    
  def desugarFile(self,userDefinedSpace: str,output_file='',log_file='',remove_errors=False,no_stdlibs=False,commandline_args=[],included_files=[],included_directories=[]):
    '''Runs the SugarC command
    
    Parameters:
    output_file (str):If provided, will specify the location of the output. Otherwise tacks on .desugared.c to the end of the base file name
    log_file (str):If provided will specify the location of the logged data. Otherwise tacks on .Log to the end of the base file name
    no_stdlibs (bool):If this machine's standard library should be used or not.
    commandline_args (list(str)):A list of other commandline arguments SugarC is to use.
    included_files (list(str)):A list of individual files to be included. (The config space is always included, and does not need to be specified)
    included_directories (list(str)): A list of directories to be included.
    userDefinedSpace (str): defines and undefs to be assumed while desugaring
    remove_errors (bool): whether or not the desugared output should be re-run to remove bad configurations

    Returns:
    str: desugared output file, absolute path
    str: log file, absolute path
    '''
    incFilesStr = ' '
    if len(included_files) > 0:
      incFilesStr = ' -include ' + ' -include '.join(included_files) + ' '
    incFilesStr = incFilesStr + ' -include ' + userDefs + ' '
    incDirStr = ' '
    if len(included_directories) > 0:
      incDirStr = ' -I ' + ' -I '.join(included_directories) + ' '
    cmdArgs = ' '.join(commandline_args) + ' '
    if no_stdlibs:
      cmdArgs = ' -nostdinc ' + cmdArgs + ' '
    if output_file == '':
      self.desug = self.fil + '.desugared.c'
    else:
      self.desug = os.path.abspath(output_file)
    log = ''
    if log_file == '':
      log = self.fil + '.Log'
    else:
      log = os.path.abspath(log_file)
    desugarCommand = 'java superc.SugarC ' + cmdArgs + incFilesStr + incDirStr + self.fil + ' > ' + self.desug + ' 2> ' + log
    os.system('echo "' + userDefinedSpace + '" > ' + userDefs)
    if remove_errors:
      toAppend = ['']
      while len(toAppend) > 0:
        for d in toAppend:
          os.system('echo "' + d + '" >> ' + userDefs)
        os.system(desugarCommand)
        toAppend = getBadConstraints(self.desug)
    os.system(desugarCommand)
    return self.desug, log    
    
    
    
  def analyze(self,report_location='') -> str:
    '''Operates the pipeline of running the analyzer, and compiling the results
    into a report.

    Parameters:
    report_location (str):If provided will specify the location of the report. Otherwise tacks on .report to the end of the base file name

    Returns:
    str: a report containing all results
    '''
    ids = {}
    replacers = {}
    ls = []
    varis = {}
    fl = open(self.desug,'r')
    for l in fl:
      ls.append(l)
      getConditionMapping(l, ids, varis, replacers, False)
    fl.close()
    alarms = self.runAnalyzer(self.desug,True)
    reportstr = ''
    for w in alarms:
      checkNonFlow(w,self.desug)
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
        w['correNum'] = getCorrelateLine(self.desug,w['loc'])
        reportstr += str(w) + '\n'
      else:
        print ('impossible constraints')
        w['feasible'] = False
        w['correNum'] = '-1'
    return reportstr

  #Clean up Analyzer calls
  
  @abstractmethod
  def runAnalyzer(self,fileName: str,isDesugared: bool) -> list:
    '''Runs the command to analyze the file. isDesugared is marked as True or False
    specifying whether or not the file being analyzed is the desugared output. This way
    a different approach can be used for both. Alarms are then to be broken down and 
    returned.

    Parameters:
    fileName (str):The file to be analyzed, absolute path
    isDesugared (bool): whether or not the file to be analyzed is the desugared output or not

    Returns:
    list: a list of alarm objects
    '''
    pass
  
  @abstractmethod
  def compareAlarms(self, alarmA: Alarm, alarmB: Alarm) -> bool:
    '''Returns whether or not two Alarm objects reference the same alarm

    Parameters:
    alarmA (Alarm):The first alarm to be compared
    alarmB (Alarm):The second alarm to be compared

    Returns:
    bool: whether or not the alarms reference the same alarm
    '''
    pass

def getCorrelateLine(fpa,loc):
  lin = int(loc.split(',')[0][5:])
  fl = open(fpa,'r')
  lines = fl.read().split('\n')
  theLine = lines[lin-1]
  if '// L' not in theLine:
    return '0'
  return theLine.split('// L')[1]

  
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

  
def getBadConstraints(desugFile):
  ids = {}
  replacers = {}
  ls = []
  varis = {}
  fl = open(desugFile,'r')
  constraints = []
  for l in fl:
    ls.append(l)
    getConditionMapping(l, ids, varis, replacers, True)
  fl.close()
  i = len(ls)-1
  isError = False
  s = Solver()
  while i > 0:
    if not isError:
      if ls[i].startswith('__static_parse_error') or ls[i].startswith('__static_type_error'):
        isError = True
    else:
      m = re.match('if \((__static_condition_default_\d+)\).*',ls[i])
      if m:
        s.add(eval(replacers[m.group(1)]))
        isError = False
    i -= 1
  for k in ids.keys():
    if k.startswith('defined '):
      s.push()
      s.add(eval(ids[k]))
      if s.check() != sat:
        constraints.append('#undef ' + k[len('defined '):])
        s.pop()
        continue
      s.pop()
      s.push()
      s.add(eval('Not(' + ids[k] + ')'))
      if s.check() != sat:
        constraints.append('#define ' + k[len('defined '):])
      s.pop()
  return constraints

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
