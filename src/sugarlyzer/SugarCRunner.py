import os
import subprocess
from typing import Tuple, Optional
import re

userDefs = '/tmp/__sugarlyzerPredefs.h'


class SugarCRunner:
    def desugar(self, source_location) -> str:
        """
        Given a file, desugar it.
        :param source_location: The location of the C source file.
        :return: The location of the desugared file.
        """

        # TODO: Does SugarC need any other parameters? Does it edit files in-place?
        pass


class Sugarlyzer:
    def __init__(self):
        self._file_name = ''
        self.userDefinedMacros = ''
        self.desugared_file = ''

    @property
    def file_name(self):
        return self._file_name

    @file_name.setter
    def file_name(self, file_name: str):
        """
        Specifies the file that will be desugared and analyzed.

        :param file_name: absolute path of the file
        :return: None
        """
        self._file_name = os.path.abspath(file_name)

    def get_recommended_space(self) -> str:
        """
        Explores the file provided in setFile. Looks for inclusion guards or other
        macros that would be assumed to be false and recommends them to be turned off.
        Also grabs the default conditions of the machine provided by gcc.

        :return: A string to be added to an included file in desugaring
        """

        # still need to create the code to search for inclusion guards
        return os.popen('echo | gcc -dM -E -').read()

    def desugar_file(self,
                     user_defined_space: str,
                     output_file='',
                     log_file='',
                     remove_errors=False,
                     no_stdlibs=False,
                     commandline_args=[],
                     included_files=[],
                     included_directories=[]) -> Tuple[str, str]:
        """
        Runs the SugarC command.

        :param user_defined_space: defines and undefs to be assumed while desugaring
        :param output_file: If provided, will specify the location of the output. Otherwise tacks on .desugared.c to the end of the base file name
        :param log_file: If provided will specify the location of the logged data. Otherwise tacks on .Log to the end of the base file name
        :param remove_errors: Whether or not the desugared output should be re-run to remove bad configurations
        :param no_stdlibs: If this machine's standard library should be used or not.
        :param commandline_args: A list of other commandline arguments SugarC is to use.
        :param included_files: A list of individual files to be included. (The config space is always included, and does not need to be specified)
        :param included_directories: A list of directories to be included.
        :return:
        """

        included_files = list(zip(['-include']*len(included_files), included_files))
        included_directories = list(zip(['-I']*len(included_directories), included_directories))
        commandline_args = ['-nostdinc', *commandline_args] if no_stdlibs else commandline_args

        match output_file:
            case '' | None: self.desugared_file = self.file_name + '.desugared.c'
            case _ : self.desugared_file = os.path.abspath(output_file)

        match log_file:
            case '' | None: log_file = self.file_name + '.log'
            case _ : log_file = os.path.abspath(log_file)

        cmd = ['java', 'superc.Sugar', *commandline_args, *included_files, *included_directories, self.file_name, ">",
               self.desugared_file, "2>", log_file]

        with open(userDefs, 'w') as outFile:
            outFile.write(user_defined_space + "\n")
            if remove_errors:
                toAppend = ['']
                while len(toAppend) > 0:
                    for d in toAppend:
                        outFile.write(d + "\n")
                    subprocess.run(cmd)
                    toAppend = getBadConstraints(self.desugared_file)

        subprocess.run(cmd)
        return self.desugared_file, log_file

    def analyze(self, report_location: Optional[str]) -> str:
        """
        Runs the analysis, and compiles the results into a report.

        :param report_location: If provided, will specify the location of the report. Otherwise, we will just
        tack .report to the end of the base file name.
        :return: A report containing all results.
        """

        ids = {}
        replacers = {}
        ls = []
        varis = {}
        fl = open(self.desugared_file, 'r')
        for l in fl:
            ls.append(l)
            getConditionMapping(l, ids, varis, replacers, False)
        fl.close()
        alarms = self.runAnalyzer(self.desugared_file, True)
        reportstr = ''
        for w in alarms:
            checkNonFlow(w, self.desugared_file)
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
                w['correNum'] = getCorrelateLine(self.desugared_file, w['loc'])
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

def getCorrelateLine(fpa, loc):
    lin = int(loc.split(',')[0][5:])
    fl = open(fpa, 'r')
    lines = fl.read().split('\n')
    theLine = lines[lin - 1]
    if '// L' not in theLine:
        return '0'
    return theLine.split('// L')[1]


def checkNonFlow(w, fpa):
    '''
  Logic is as follows, we take advantage off the fact that we always use braces
  We start at our line number and reverse search up. Whenever we find a }
  we skip lines until we match {. This way we can only explore up a scope level
  If we find a __static_condition_renaming, we are in logically true,
  global scope, or in a function without an explicit condition in the body
  '''
    if len(w['lines']) == 1:
        ff = open(fpa, 'r')
        lines = ff.read().split('\n')
        Rs = 0
        l = int(w['lines'][0]) - 1
        while l >= 0:
            Rs += lines[l].count('}')
            m = re.match('if \((__static_condition_default_\d+)\).*', lines[l])
            if Rs == 0 and m:
                w['asserts'].append({'var': str(m.group(1)), 'val': True})
            Rs -= lines[l].count('{')
            if Rs < 0:
                Rs = 0
            l -= 1
        ff.close()


def getBadConstraints(desugFile):
    with open(desugFile, 'r') as infile:
        ls = infile.readlines()

    ids = {}
    replacers = {}
    varis = {}
    fl = open(desugFile, 'r')
    constraints = []
    for l in ls:
        getConditionMapping(l, ids, varis, replacers, True)

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
    # l looks like __static_condition_renaming(<discarded>, <condition>, <condition>, ..., <condition>, <-3>, <-2>, <-1>)
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
                varis[v] = bool(v)
            else:
                if splits[0][-1] == ')':
                    v = 'USE_' + splits[0][:-1]
                    ids[splits[0][:-1]] = 'varis["' + v + '"] != 0'
                    varis[v] = int(v)
                else:
                    v = 'USE_' + splits[0]
                    ids[splits[0]] = 'varis["' + v + '"]'
                    varis[v] = int(v)
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
                ncondstr = ncondstr + 'And (' + cs[0] + ','
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
