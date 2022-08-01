import sys
import os
import shutil
import json
import re
from z3 import *
from abc import ABC, abstractmethod
import unittest

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
        return ' '.join(['(' + self.sanitize() + ')', str(self.line), str(self.lineA), str(self.lineB)])

    def areEq(self, inner):
        print(self.tostr() + ' ||' + inner.tostr())
        return self.sanitize() == inner.sanitize() and inner.line >= self.lineA and inner.line <= self.lineB


class Sugarlyzer:
    def __init__(self):
        self.fil = ''
        self.userDefinedMacros = ''
        self.desug = ''

    def setFile(self, fileName: str):
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
        # still need to create the code to search for inclusion guards
        return os.popen('echo | gcc -dM -E -').read()

    def desugarFile(self, userDefinedSpace: str, output_file='', log_file='', remove_errors=False, no_stdlibs=False,
                    commandline_args=[], included_files=[], included_directories=[]):
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

    def analyze(self, report_location='') -> str:
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
        fl = open(self.desug, 'r')
        for l in fl:
            ls.append(l)
            getConditionMapping(l, ids, varis, replacers, False)
        fl.close()
        alarms = self.runAnalyzer(self.desug, True)
        reportstr = ''
        for w in alarms:
            w['asserts'] = calculateAsserts(w, self.desug)
            s = Solver()
            for a in w['asserts']:
                if a['val']:
                    s.add(eval(replacers[a['var']]))
                else:
                    s.add(eval('Not(' + replacers[a['var']] + ')'))
            if s.check() == sat:
                m = s.model()
                w['feasible'] = True
                w['model'] = m
                w['correNum'] = getCorrelateLine(self.desug, w['loc'])
                reportstr += str(w) + '\n'
            else:
                print('impossible constraints')
                w['feasible'] = False
                w['correNum'] = '-1'
        return reportstr

    # Clean up Analyzer calls

    @abstractmethod
    def runAnalyzer(self, fileName: str, isDesugared: bool) -> list:
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
        '''
        Returns whether or not two Alarm objects reference the same alarm
        
        Parameters:
        alarmA (Alarm):The first alarm to be compared
        alarmB (Alarm):The second alarm to be compared
        
        Returns:
        bool: whether or not the alarms reference the same alarm
        '''
        pass


def getCorrelateLine(fpa, loc):
    lin = loc-1
    fl = open(fpa, 'r')
    lines = fl.read().split('\n')
    fl.close()
    theLine = lines[lin]
    if '// L' not in theLine:
        return '0'
    return theLine.split('// L')[1]

def findConditionScope(start,fpa,goingUp):
    '''
    Finds the line that dictates start/end of the condition
    associated with the starting line. If going down, finds
    end of the scope defined by the first line. If going up
    finds the line that dictates the condition associated with
    the starting line

    Parameters:
    start (int):Line that the search starts from
    fpa (str):File to search
    goingUp (bool):Whether to search up in the file, or down

    Returns:
    int: line that ends the scope, -1 if not found
    '''
    result = -1
    ff = open(fpa, 'r')
    lines = ff.read().split('\n')
    ff.close()
    if goingUp:
        Rs = 0
        l = start
        while l >= 0:
            Rs += lines[l].count('}')
            m = re.match('if \((__static_condition_default_\d+)\).*', lines[l])
            if Rs == 0 and m:
               result = l
               break
            Rs -= lines[l].count('{')
            if Rs < 0:
                Rs = 0
            l -= 1
    else:
        Rs = 0
        l = start
        while l < len(lines):
            Rs += lines[l].count('{')
            Rs -= lines[l].count('}')
            if Rs <= 0:
                result = l
                break
            l += 1  
    return result

def calculateAsserts(w,fpa):
    '''
    Given the warning, the lines are gone over to find associated
    presence conditions. If the line is a static condition if statement, 
    we check if a line exists in it's scope, if it does not, we 
    assert the conidition is false. For any other line, we assume 
    the parent condition is true.
    '''
    ff = open(fpa, 'r')
    lines = ff.read().split('\n')
    ff.close()
    result = []
    for line in w['lines']:
        line -= 1
        fl = lines[line]
        if 'static_condition_default' in fl:
            start = line
            end = findConditionScope(line,fpa,False)
            if end == -1:
                continue
            found = False
            for x in w['lines']:
                if x-1 > start and x-1 < end:
                    found = True
                    break
            if not found:
                asrt = {}
                asrt['var'] = fl.split("(")[1].split(')')[0]
                asrt['val'] = False
                result.append(asrt)
                    
        else:
            top = findConditionScope(line,fpa,True)
            if top == -1 or 'static_condition_default' not in lines[top]:
                continue
            asrt = {}
            asrt['var'] = lines[top].split("(")[1].split(')')[0]
            asrt['val'] = True
            
            result.append(asrt)
    return result

def getBadConstraints(desugFile):
    ids = {}
    replacers = {}
    ls = []
    varis = {}
    fl = open(desugFile, 'r')
    constraints = []
    for l in fl:
        ls.append(l)
        getConditionMapping(l, ids, varis, replacers, True)
    fl.close()
    i = len(ls) - 1
    isError = False
    s = Solver()
    while i > 0:
        if not isError:
            if ls[i].startswith('__static_parse_error') or ls[i].startswith('__static_type_error'):
                isError = True
        else:
            m = re.match('if \((__static_condition_default_\d+)\).*', ls[i])
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
                v = 'DEF_' + splits[1][:-1]
                ids['defined ' + splits[1][:-1]] = 'varis["' + v + '"]'
                varis[v] = Bool(v)
            else:
                if splits[0][-1] == ')':
                    v = 'USE_' + splits[0][:-1]
                    ids[splits[0][:-1]] = 'varis["' + v + '"] != 0'
                    varis[v] = Int(v)
                else:
                    v = 'USE_' + splits[0]
                    ids[splits[0]] = 'varis["' + v + '"]'
                    varis[v] = Int(v)
        condstr = conds[2:]
        for x in sorted(list(ids.keys()), key=len, reverse=True):
            if x.startswith('defined '):
                condstr = condstr.replace(x, ids[x])
            else:
                condstr = condstr.replace('(' + x, '(' + ids[x])
        condstr = condstr.replace('!(', 'Not(')
        cs = re.split('&&|\|\|', condstr)
        ops = []
        for d in range(0, len(condstr)):
            if condstr[d] == '&' and condstr[d + 1] == '&':
                ops.append('And')
            elif condstr[d] == '|' and condstr[d + 1] == '|':
                ops.append('Or')
        ncondstr = ''
        ands = 0
        ors = 0
        for o in ops:
            if o == 'And':
                ands += 1
                ncondstr = ncondstr + 'And(' + cs[0] + ','
                cs = cs[1:]
            else:
                ncondstr = 'Or(' + ncondstr + cs[0] + ands * ')'
                if ors > 0:
                    ncondstr += ')'
                ncondstr += ','
                ands = 0
                ors += 1
                cs = cs[1:]
        ncondstr += cs[0] + ands * ')'
        if ors > 0:
            ncondstr += ')'
        ncondstr = ncondstr.rstrip()
        if invert:
            ncondstr = 'Not(' + ncondstr + ')'
        replacers[cc[0][len('__static_condition_renaming("'):-1]] = ncondstr


class SugarlyzerTester(unittest.TestCase):
    def test_getCorrelateLine_constantPropNegative(self):
        f = "unitTestFiles/constantPropNegative.desugared.c"
        self.assertEqual(getCorrelateLine(f,40),'3')
        self.assertEqual(getCorrelateLine(f,49),'0')
        self.assertEqual(getCorrelateLine(f,50),'9')
        self.assertEqual(getCorrelateLine(f,54),'0')
        self.assertEqual(getCorrelateLine(f,55),'14')
        self.assertEqual(getCorrelateLine(f,63),'17')
        self.assertEqual(getCorrelateLine(f,75),'0')
        self.assertEqual(getCorrelateLine(f,77),'0')
        self.assertEqual(getCorrelateLine(f,88),'0')
        self.assertEqual(getCorrelateLine(f,95),'21')
        
    def test_findConditionScope_constantPropNegative(self):
        f = "unitTestFiles/constantPropNegative.desugared.c"
        #-1 is to use the array access point, rather than line number
        self.assertEqual(findConditionScope(40-1,f,True),-1)
        self.assertEqual(findConditionScope(49-1,f,False),51-1)
        self.assertEqual(findConditionScope(50-1,f,True),49-1)
        self.assertEqual(findConditionScope(54-1,f,False),56-1)
        self.assertEqual(findConditionScope(55-1,f,True),54-1)
        self.assertEqual(findConditionScope(63-1,f,True),-1)
        self.assertEqual(findConditionScope(75-1,f,True),-1)
        self.assertEqual(findConditionScope(77-1,f,False),87-1)
        self.assertEqual(findConditionScope(88-1,f,False),109-1)
        self.assertEqual(findConditionScope(95-1,f,True),88-1)
    
    def test_calculateAsserts_constantPropNegative(self):
        f = "unitTestFiles/constantPropNegative.desugared.c"
        alarm1 = {}
        alarm2 = {}
        alarm1['lines'] = [40,49,50,54,55,63,75,77,88,95]
        alarm2['lines'] = [40,49,50,54,63,75,77,88,95]
        rslt1 = calculateAsserts(alarm1,f)
        rslt2 = calculateAsserts(alarm2,f)
        #conds bug 1
        self.assertEqual(rslt1[0]['var'],'__static_condition_default_6')
        self.assertTrue(rslt1[0]['val'])
        self.assertEqual(rslt1[1]['var'],'__static_condition_default_7')
        self.assertTrue(rslt1[1]['val'])
        self.assertEqual(rslt1[2]['var'],'__static_condition_default_9')
        self.assertFalse(rslt1[2]['val'])
        self.assertEqual(rslt1[3]['var'],'__static_condition_default_10')
        self.assertTrue(rslt1[3]['val'])
        #conds bug 2
        self.assertEqual(rslt2[0]['var'],'__static_condition_default_6')
        self.assertTrue(rslt2[0]['val'])
        self.assertEqual(rslt2[1]['var'],'__static_condition_default_7')
        self.assertFalse(rslt2[1]['val'])
        self.assertEqual(rslt2[2]['var'],'__static_condition_default_9')
        self.assertFalse(rslt2[2]['val'])
        self.assertEqual(rslt2[3]['var'],'__static_condition_default_10')
        self.assertTrue(rslt2[3]['val'])

    def test_getConditionMapping_constantPropNegative(self):
        varisRep = {}
        replacersRep = {}
        idsRep = {}
        conditions = [
        '__static_condition_renaming("__static_condition_default_5", "(defined READ_X)");\n',
        '__static_condition_renaming("__static_condition_default_6", "!(defined READ_X)");\n',
        '__static_condition_renaming("__static_condition_default_7", "(defined INC)");\n',
        '__static_condition_renaming("__static_condition_default_8", "!(defined INC)");\n',
        '__static_condition_renaming("__static_condition_default_9", "(defined READ_X)");\n',
        '__static_condition_renaming("__static_condition_default_10", "!(defined READ_X)");\n',
        ]
        for l in conditions:
            getConditionMapping(l,idsRep,varisRep,replacersRep,False)
        self.assertEqual(idsRep['defined READ_X'], 'varis["DEF_READ_X"]')
        self.assertEqual(idsRep['defined INC'], 'varis["DEF_INC"]')
        self.assertEqual(replacersRep['__static_condition_default_5'],'(varis["DEF_READ_X"])')
        self.assertEqual(replacersRep['__static_condition_default_6'],'Not(varis["DEF_READ_X"])')
        self.assertEqual(replacersRep['__static_condition_default_7'],'(varis["DEF_INC"])')
        self.assertEqual(replacersRep['__static_condition_default_8'],'Not(varis["DEF_INC"])')
        self.assertEqual(replacersRep['__static_condition_default_9'],'(varis["DEF_READ_X"])')
        self.assertEqual(replacersRep['__static_condition_default_10'],'Not(varis["DEF_READ_X"])')

    def test_getCorrelateLine_constantPropPositive(self):
        f = "unitTestFiles/constantPropPositive.desugared.c"
        self.assertEqual(getCorrelateLine(f,36),'3')
        self.assertEqual(getCorrelateLine(f,45),'0')
        self.assertEqual(getCorrelateLine(f,46),'9')
        self.assertEqual(getCorrelateLine(f,50),'0')
        self.assertEqual(getCorrelateLine(f,51),'14')
        self.assertEqual(getCorrelateLine(f,59),'17')
        self.assertEqual(getCorrelateLine(f,71),'0')
        self.assertEqual(getCorrelateLine(f,79),'20')
        
    def test_findConditionScope_constantPropPositive(self):
        f = "unitTestFiles/constantPropPositive.desugared.c"
        #-1 is to use the array access point, rather than line number
        self.assertEqual(findConditionScope(36-1,f,True),-1)
        self.assertEqual(findConditionScope(45-1,f,False),47-1)
        self.assertEqual(findConditionScope(46-1,f,True),45-1)
        self.assertEqual(findConditionScope(50-1,f,False),52-1)
        self.assertEqual(findConditionScope(51-1,f,True),50-1)
        self.assertEqual(findConditionScope(59-1,f,True),-1)
        self.assertEqual(findConditionScope(71-1,f,True),-1)
        self.assertEqual(findConditionScope(79-1,f,True),-1)

    def test_calculateAsserts_constantPropPositive(self):
        f = "unitTestFiles/constantPropPositive.desugared.c"
        alarm1 = {}
        alarm2 = {}
        alarm1['lines'] = [36,45,46,50,51,59,71,79]
        alarm2['lines'] = [36,45,46,59,71,79]
        rslt1 = calculateAsserts(alarm1,f)
        rslt2 = calculateAsserts(alarm2,f)
        #conds bug 1
        self.assertEqual(rslt1[0]['var'],'__static_condition_default_6')
        self.assertTrue(rslt1[0]['val'])
        self.assertEqual(rslt1[1]['var'],'__static_condition_default_7')
        self.assertTrue(rslt1[1]['val'])
        #conds bug 2
        self.assertEqual(rslt2[0]['var'],'__static_condition_default_6')
        self.assertTrue(rslt2[0]['val'])
        
    def test_getConditionMapping_constantPropPositive(self):
        varisRep = {}
        replacersRep = {}
        idsRep = {}
        conditions = [
        '__static_condition_renaming("__static_condition_default_5", "(defined READ_X)");\n',
        '__static_condition_renaming("__static_condition_default_6", "!(defined READ_X)");\n',
        '__static_condition_renaming("__static_condition_default_7", "(defined INC)");\n',
        '__static_condition_renaming("__static_condition_default_8", "!(defined INC)");\n',
        ]
        for l in conditions:
            getConditionMapping(l,idsRep,varisRep,replacersRep,False)
        self.assertEqual(idsRep['defined READ_X'], 'varis["DEF_READ_X"]')
        self.assertEqual(idsRep['defined INC'], 'varis["DEF_INC"]')
        self.assertEqual(replacersRep['__static_condition_default_5'],'(varis["DEF_READ_X"])')
        self.assertEqual(replacersRep['__static_condition_default_6'],'Not(varis["DEF_READ_X"])')
        self.assertEqual(replacersRep['__static_condition_default_7'],'(varis["DEF_INC"])')
        self.assertEqual(replacersRep['__static_condition_default_8'],'Not(varis["DEF_INC"])')

    def test_complexConditionMapping(self):
        varisRep = {}
        replacersRep = {}
        idsRep = {}
        conditions = [ '__static_condition_renaming("__static_condition_default_357", "!(defined __need___FILE) && (defined _FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS == 64) && (defined _FORTIFY_SOURCE) && (_FORTIFY_SOURCE > 0) && (defined __OPTIMIZE__) && (__OPTIMIZE__ > 0) && (defined __FILE_defined)");\n',
                       '__static_condition_renaming("__static_condition_default_433", "!(defined __need___FILE) && (defined __FILE_defined) && !(defined _ANSI_STDARG_H_) && (defined __GNUC_VA_LIST) || !(defined __need___FILE) && (defined __FILE_defined) && (defined _ANSI_STDARG_H_)");\n'
            ]
        for l in conditions:
            getConditionMapping(l,idsRep,varisRep,replacersRep,False)
        self.assertEqual(replacersRep['__static_condition_default_357'],'And(Not(varis["DEF___need___FILE"]) ,And( (varis["DEF__FILE_OFFSET_BITS"]) ,And( (varis["USE__FILE_OFFSET_BITS"] == 64) ,And( (varis["DEF__FORTIFY_SOURCE"]) ,And( (varis["USE__FORTIFY_SOURCE"] > 0) ,And( (varis["DEF___OPTIMIZE__"]) ,And( (varis["USE___OPTIMIZE__"] > 0) , (varis["DEF___FILE_defined"]))))))))')
        self.assertEqual(replacersRep['__static_condition_default_433'],'Or(And(Not(varis["DEF___need___FILE"]) ,And( (varis["DEF___FILE_defined"]) ,And( Not(varis["DEF__ANSI_STDARG_H_"]) , (varis["DEF___GNUC_VA_LIST"]) ))),And( Not(varis["DEF___need___FILE"]) ,And( (varis["DEF___FILE_defined"]) , (varis["DEF__ANSI_STDARG_H_"]))))')

        
if __name__ == '__main__':
    unittest.main()
