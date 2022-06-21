import sys
import os
import shutil
import json
import re
from z3 import *
from warningSolver import *
'''
The algorithm goes as follows. A desugared file is passed in.
The file is parsed, and every static_type_error() is checked for
it's condition. We add the "Not" of each condition. Since Or of all
conditions is what is invalid, the And of the nots is the condition which
is true. We then check each individual condition and see if any conditions are
infeasible with the condition that is true. We then spit out the list of values
that can never be true, define all of these so they are valid and repeat. We
iterate this until we return an empty list. We will only check Defines.
'''

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
      

