import itertools
import itertools
import logging
import os
import re
import subprocess
import tempfile
import time
from dataclasses import dataclass, field
from hashlib import sha256
from pathlib import Path
from typing import List, Optional, Dict, Iterable

# noinspection PyUnresolvedReferences
from z3.z3 import Solver, sat, Bool, Int, Not, And, Or

from src.sugarlyzer.models.Alarm import Alarm
from src.sugarlyzer.util.ParseBashTime import parse_bash_time

USER_DEFS = '/tmp/__sugarlyzerPredefs.h'

logger = logging.getLogger(__name__)


def get_recommended_space(file: Path, inc_files: Iterable[Path], inc_dirs: Iterable[Path],
                          no_stdlibs: bool = True) -> str:
    """
    Explores the provided file. Looks for inclusion guards or other
    macros that would be assumed to be false and recommends them to be turned off.
    Also grabs the default conditions of the machine provided by gcc.

    :param no_stdlibs: Whether to ignore stdlibs.
    :param inc_dirs: The included directories to search.
    :param inc_files: The included files to search.
    :param file: The file to read and determines the recommended configuration space.
    :return: A string to be added to an included file in desugaring
    """

    # still need to create the code to search for inclusion guards
    logger.debug('In getRecommendedSpace')

    def parse_file(curFile: str) -> tuple:
        '''Parses through a file line by line, on each line it searches for
        inclusions of other files and potential guard macros. We define guard
        macros as:
        (#ifndef|!defined) X_H(_|__)
        #ifndef X_defined
        #defined(__need_X)

        Parameters:
        curFle (str): file we are parsing

        Returns:
        List of all guard macros encountered
        List of all files included
        '''

        included = []
        guarded = []
        Fil = open(curFile, 'r')
        # meant for match
        continued = False
        for lin in Fil:
            lin = lin.lstrip().rstrip()
            res = re.match(r'\s*#\s*include\s*(<|")\s*([^\s>"]+)\s*("|>)\s*', lin)
            if res:
                logger.debug('adding file to check:' + res.group(2))
                included.append(res.group(2))
            res = re.search(r'#\s*(ifndef|if|ifdef)', lin)
            if res or continued:
                if lin.endswith('\\'):
                    continued = True
                else:
                    continued = False
                res = re.findall(r'\s([^(\s]+_+(defined|DEFINED|h|H)_*)', lin)
                if res:
                    for macro in res:
                        macro = macro[0].lstrip().rstrip()
                        if macro != '__H':
                            logger.debug('undefining' + macro)
                            guarded.append(macro)
                res = re.findall(r'\s(__need_[^)\s]+)(\s|\)?)', lin)
                if res:
                    for macro in res:
                        logger.debug('undefining' + macro[0])
                        guarded.append(macro[0])

        Fil.close()
        return guarded, included

    guards = []
    searchingDirs = list(inc_dirs)
    searchingDirs.append(os.getcwd())
    if no_stdlibs:
        fd, fil = tempfile.mkstemp(suffix=".c", text=True)
        with os.fdopen(fd, 'w') as f:
            f.write("int main() {return 0;}\n")
        gccOut = subprocess.Popen(f'gcc -v {fil}', shell=True, stdout=subprocess.PIPE,
                                  stderr=subprocess.PIPE)
        out, err = gccOut.communicate()
        gccOut = err.decode()
        gccOut = gccOut.split('\n')
        inRange = False
        logger.debug(f"GCC's output for file {f.name}")
        for lin in gccOut:
            logger.debug(lin)
            if 'End of search list.' in lin:
                inRange = False
            elif inRange:
                searchingDirs.append(lin.lstrip().rstrip())
            elif '#include <...> search starts here:' in lin:
                inRange = True
        logger.debug('dirs to search:' + str(searchingDirs))
    files = []
    files.append(file)
    for f in inc_files:
        files.append(os.path.abspath(os.path.expanduser(f)))
    fc = 0
    while fc < len(files):
        try:
            macros, includes = parse_file(files[fc])
        except UnicodeDecodeError as ude:
            logger.exception("Could not decode file {files[fc]}")
        else:
            for m in macros:
                if m not in guards:
                    guards.append(m)
            for i in includes:
                logger.debug('searching for file:' + i)
                for sd in searchingDirs:
                    comboFile = os.path.expanduser(os.path.join(sd, i))
                    if os.path.exists(comboFile):
                        logger.debug('file found:' + comboFile)
                        trueFile = os.path.abspath(comboFile)
                        if trueFile not in files:
                            files.append(trueFile)
        finally:
            fc += 1

    gccDefs = os.popen('echo | gcc -dM -E -').read()
    if len(guards) > 0:
        return '\n#undef ' + '\n#undef '.join(guards) + '\n' + gccDefs
    return gccDefs


def desugar_file(file_to_desugar: Path,
                 recommended_space: str,
                 output_file: str = '',
                 log_file: str = '',
                 remove_errors: bool = False,
                 config_prefix: str = None,
                 whitelist: str = None,
                 no_stdlibs: bool = False,
                 keep_mem: bool = False,
                 make_main: bool = False,
                 included_files: Optional[Iterable[Path]] = None,
                 included_directories: Optional[Iterable[Path]] = None,
                 commandline_declarations: Optional[Iterable[str]] = None) -> tuple[Path, Path]:
    """
    Runs the SugarC command.
    :param file_to_desugar: The C source code file to desugar.
    :param recommended_space: defines and undefs to be assumed while desugaring
    :param output_file: If provided, will specify the location of the output. Otherwise tacks on .desugared.c to the end of the base file name
    :param log_file: If provided will specify the location of the logged data. Otherwise tacks on .Log to the end of the base file name
    :param remove_errors: Whether or not the desugared output should be re-run to remove bad configurations
    :param no_stdlibs: If this machine's standard library should be used or not.
    :param commandline_args: A list of other commandline arguments SugarC is to use.
    :param included_files: A list of individual files to be included. (The config space is always included, and does not need to be specified)
    :param included_directories: A list of directories to be included.
    :return: (desugared_file_location, log_file_location)
    """
    if included_directories is None:
        included_directories = []
    if included_files is None:
        included_files = []

    outfile = tempfile.NamedTemporaryFile(delete=False, mode="w")
    if recommended_space not in ['', None]:
        outfile.write(recommended_space)
    included_files.append(outfile.name)
    outfile.flush()
    included_files = list(itertools.chain(*zip(['-include'] * len(included_files), included_files)))
    included_directories = list(itertools.chain(*zip(['-I'] * len(included_directories), included_directories)))
    commandline_args = []
    commandline_args = ['-nostdinc', *commandline_args] if no_stdlibs else commandline_args
    commandline_args = ['-keep-mem', *commandline_args] if keep_mem else commandline_args
    commandline_args = ['-make-main', *commandline_args] if make_main else commandline_args
    commandline_args = [*commandline_declarations, *commandline_args] if commandline_declarations else commandline_args

    match output_file:
        case '' | None:
            desugared_file = Path(file_to_desugar).with_suffix('.desugared.c')
        case _:
            desugared_file = Path(output_file)

    match log_file:
        case '' | None:
            log_file = file_to_desugar.with_suffix('.log')
        case _:
            log_file = Path(log_file)
    if config_prefix != None:
        cmd = ['/usr/bin/time', '-v', 'timeout -k 10 10m', 'java', '-Xmx32g', 'superc.SugarC', '-showActions', '-useBDD', '-restrictConfigToPrefix', config_prefix, *commandline_args, *included_files, *included_directories,file_to_desugar]
    elif whitelist != None:
        cmd = ['/usr/bin/time', '-v', 'timeout -k 10 10m', 'java', '-Xmx32g', 'superc.SugarC', '-showActions', '-useBDD', '-restrictConfigToWhitelist', whitelist, *commandline_args, *included_files, *included_directories,file_to_desugar]
    else:
        cmd = ['/usr/bin/time', '-v', 'timeout -k 10 10m', 'java', '-Xmx32g', 'superc.SugarC', '-showActions', '-useBDD', *commandline_args, *included_files, *included_directories,file_to_desugar]
    cmd = [str(s) for s in cmd]

    to_append = None
    if remove_errors:
        run_sugarc(" ".join(cmd), file_to_desugar, desugared_file, log_file)
        logger.debug(f"Created desugared file {desugared_file}")
        to_append = get_bad_constraints(desugared_file)
        for d in to_append:
            outfile.write(d + "\n")
        outfile.flush()
        logger.debug(f'{desugared_file} removed errors: {to_append}')

    logger.debug(f"Cmd is {' '.join(cmd)}")
    if not remove_errors or remove_errors and len(to_append) > 0:
        run_sugarc(" ".join(cmd), file_to_desugar, desugared_file, log_file)
    logger.debug(f"Wrote to {log_file}")
    outfile.close()
    return desugared_file, log_file


def run_sugarc(cmd_str, file_to_desugar: Path, desugared_output: Path, log_file):
    current_directory = os.curdir
    os.chdir(file_to_desugar.parent)
    logger.debug(f"In run_sugarc, running cmd {cmd_str} from directory {os.curdir}")
    start = time.monotonic()
    to_hash = list()
    for tok in cmd_str.split(' ')[1:]:  # Skip /usr/bin/time
        if (path := Path(tok)).exists() and path.is_file():
            with open(path, 'r') as infile:
                try:
                    to_hash.extend(infile.readlines())
                except UnicodeError:
                    print(f'failed to extend hash ::{infile.name}::')
        else:
            to_hash.extend(tok)

    hasher = sha256()
    for st in sorted(to_hash):
        hasher.update(bytes(st, 'utf-8'))

    digest = hasher.hexdigest()
    usr_time = 0
    sys_time = 0
    try:
        if (digest_file := (Path("/cached_desugared") / Path((digest + desugared_output.name)))).exists():
            logger.debug("Cache hit!")
            with open(desugared_output, 'wb') as outfile:
                with open(digest_file, 'rb') as infile:
                    outfile.write(infile.read())
        else:
            logger.debug("Cache miss")
            logger.debug("Cmd string is " + cmd_str)
            ps = subprocess.run(cmd_str, capture_output=True, text=True, shell=True, executable='/bin/bash')
            try:
                times = "\n".join(ps.stderr.split("\n")[-30:])
                usr_time, sys_time, max_memory = parse_bash_time(times)
                logger.info(f"CPU time to desugar {file_to_desugar} was {usr_time + sys_time}s")
                logger.info(f"Total memory usage to desugar {file_to_desugar} was {max_memory}kb")
            except Exception as ve:
                logger.exception("Could not parse time in string " + times)

            with open(desugared_output, 'w') as f:
                f.write(ps.stdout)
            with open(digest_file, 'w') as f:
                f.write(ps.stdout)
            logger.debug(f"Wrote to {desugared_output}")
            with open(log_file, 'w') as f:
                f.write(ps.stderr)
    finally:
        if (not desugared_output.exists()) or (os.path.getsize(desugared_output) == 0):
            try:
                logger.error(f"Could not desugar file {file_to_desugar}")  # \n\tSugarC stdout: {ps.stdout}\n\tSugarC stderr: {ps.stderr}")
            except UnboundLocalError:
                logger.error(f"Could not desugar file {file_to_desugar}. Tried to output what went wrong but couldn't access subprocess output.")
        os.chdir(current_directory)
    logger.info(f"{desugared_output} desugared in time:{time.monotonic()-start} (cpu time {usr_time + sys_time}) to file size:{desugared_output.stat().st_size}")
        

def process_alarms(alarms: Iterable[Alarm], desugared_file: Path) -> Iterable[Alarm]:
    """
    Runs the analysis, and compiles the results into a report.

    :param alarms: The list of alarms.
    :param desugared_file: The location of the desugared file.
    :return: A report containing all results. TODO: Replace with some data structure?
    """
    logger.debug("In process_alarms")

    with open(desugared_file, 'r') as fl:
        lines = list(map(lambda x: x.strip("\n"), fl.readlines()))

    condition_mapping = ConditionMapping()
    for line in lines:
        condition_mapping: ConditionMapping = get_condition_mapping(line, condition_mapping)

    report = ''
    varis = condition_mapping.varis
    for w in alarms:
        w: Alarm
        w.static_condition_results = calculate_asserts(w, desugared_file)
        s = Solver()
        missingCondition = False
        for a in w.static_condition_results:
            if a['var'] == '' or not a['var'] in condition_mapping.replacers.keys() or '"' in condition_mapping.replacers[a['var']]:
                missingCondition = True
                break
            if a['val']:
                s.add(eval(condition_mapping.replacers[a['var']]))
            else:
                s.add(eval('Not(' + condition_mapping.replacers[a['var']] + ')'))
        if missingCondition:
            print('broken condition')
            w.feasible = False
            w.model = None
        elif s.check() == sat:
            m = s.model()
            w.feasible = True
            w.model = {}
            for decl in m.decls():
                w.model[str(decl)] = str(m[decl])
            allConditions = []
            for a in w.static_condition_results:
                if a['val']:
                    allConditions.append(condition_mapping.replacers[a['var']])
                else:
                    allConditions.append('Not(' + condition_mapping.replacers[a['var']] + ')')
            varisUseRemoved = re.sub(r'varis\[\"(USE_[a-zA-Z_0-9]+)\"\]', r'\1', "And(" + ','.join(allConditions) + ')')
            varisDefRemoved = re.sub(r'varis\[\"(DEF_[a-zA-Z_0-9]+)\"\]', r'\1', varisUseRemoved)
            w.presence_condition = varisDefRemoved
            report += str(w) + '\n'
        else:
            print('impossible constraints')
            w.feasible = False
            w.model = None
            # Use None and make correNum an Optional type
            # w.correNum = '-1'
    return alarms


def find_condition_scope(start, fpa, goingUp):
    """
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
    """
    result = -1
    ff = open(fpa, 'r')
    lines = ff.read().split('\n')
    ff.close()
    if goingUp:
        Rs = 0
        l = start
        while l >= 0:
            Rs += lines[l].count('}')
            Rs -= lines[l].count('{')
            m = re.match('if \((__static_condition_default_\d+)\(\)\).*', lines[l])
            if Rs < 0 and m:
                result = l
                break
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


def calculate_asserts(w: Alarm, fpa):
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
    for line in w.all_relevant_lines:
        line -= 1
        fl = lines[line]
        if 'static_condition_default' in fl:
            if line != w.line_in_input_file-1:
                start = line
                end = find_condition_scope(line, fpa, False)
                if end == -1:
                    continue
                found = False
                for x in w.all_relevant_lines:
                    if start < x - 1 <= end:
                        found = True
                        break
                #if not found:
                    #asrt = {'var': fl.split("(")[1].split(')')[0], 'val': False}
                    #result.append(asrt)

        else:
            top = find_condition_scope(line, fpa, True)
            if top == -1 or 'static_condition_default' not in lines[top]:
                continue
            asrt = {'var': lines[top].split("(")[1].split(')')[0], 'val': True}

            result.append(asrt)
    return result


def check_non_flow(alarm: Alarm, desugared_output: str) -> List[Dict[str, str | bool]]:
    """
    Logic is as follows, we take advantage of the fact that we always use braces
    We start at our line number and reverse search up. Whenever we find a }
    we skip lines until we match {. This way we can only explore up a scope level
    If we find a __static_condition_renaming, we are in logically true,
    global scope, or in a function without an explicit condition in the body

    :param alarm:
    :param desugared_output:
    :return:
    """
    logger.debug("Inside check_non_flow")
    result = []
    with open(desugared_output, 'r') as ff:
        lines: List[str] = ff.readlines()
        additional_scopes = 0
        line_to_read: int = alarm.original_line_range.start_line
        while line_to_read >= 0:
            additional_scopes += lines[line_to_read].count('}')
            if additional_scopes == 0:
                m = re.match(r"if \((__static_condition_default_\d+)\(\)\).*", lines[line_to_read])
                if m:
                    result.append({'var': str(m.group(1)), 'val': True})
            additional_scopes -= lines[line_to_read].count('{')
            if additional_scopes < 0:
                additional_scopes = 0
            line_to_read -= 1
    return result


def get_bad_constraints(desugared_file: Path) -> List[str]:
    """
    Given a desugared file, find conditions that will always result in an error. These conditions
    are not worth exploring. TODO: Is this list a conjunction or disjunction?
    :param desugared_file: The location of the desugared file.
    :return: The list of constraints that always result in errors.
    """
    logger.debug("In get_bad_constraints")
    with open(desugared_file, 'r') as infile:
        lines = infile.readlines()

    condition_mapping = ConditionMapping()
    for l in lines:
        condition_mapping: ConditionMapping = get_condition_mapping(l, condition_mapping, True)

    # noinspection PyUnusedLocal
    varis = condition_mapping.varis  # To make the evals work (why did you do this to me)
    condition_mapping.constraints = []
    logger.debug(f"Condition mapping is {str(condition_mapping)}")
    line_index = len(lines) - 1
    is_error = False
    solver = Solver()
    while line_index > 0:
        if lines[line_index].startswith('__static_type_error'):
            errorLine = find_condition_scope(line_index,desugared_file,True)
            condition = re.match('if \((__static_condition_default_\d+)\(\)\).*', lines[errorLine])
            if condition:
                to_eval = condition_mapping.replacers[condition.group(1)]
                logger.debug(f"to_eval is {to_eval}")
                try:
                    solver.add(eval(to_eval))
                except NameError as ne:
                    logger.exception(f"File is {desugared_file}")
        line_index -= 1
    for key in condition_mapping.ids.keys():
        if key.startswith('defined ') and key[len('defined '):] not in condition_mapping.ids.keys():
            solver.push()
            expr = eval(condition_mapping.ids[key])
            logging.debug(f"Expr {condition_mapping.ids[key]} was evaluated to {expr}")
            solver.add(eval(condition_mapping.ids[key]))
            if solver.check() != sat:
                condition_mapping.constraints.append('#undef ' + key[len('defined '):])
                solver.pop()
                continue
            solver.pop()
            solver.push()
            solver.add(eval('Not(' + condition_mapping.ids[key] + ')'))
            if solver.check() != sat:
                condition_mapping.constraints.append('#define ' + key[len('defined '):])
            solver.pop()
    return condition_mapping.constraints

@dataclass
class ConditionMapping:
    ids: Dict[str, str] = field(default_factory=dict)
    replacers: Dict[str, str] = field(default_factory=dict)
    varis: Dict[str, str] = field(default_factory=dict)
    constraints: List[str] = field(default_factory=list)

    def __str__(self):
        return f"ids: {self.ids}\nreplacers: {self.replacers}\n" \
               f"varis: {self.varis}\nconstraints: {self.constraints}"


def get_condition_mapping(line, current_result: ConditionMapping = ConditionMapping(),
                          invert: bool = False, debug: bool = False) -> ConditionMapping:
    """
    The method takese in a line and rewrites it into Z3 format, it simultaneously
    creates Z3 variables for future reference, as well as maps the variables to their
    renamings.
    The method is broken into two parts, part 1 identifies all of the mappings and creates
    the Z3 variables to be used. Part 2 rewrites the string to be in the Z3 format and
    maps it to the static_condition_default.
    :param line: Line we will attempt to make a mapping of
    :param ConditionMapping: A collection of dictionaries we use for Z3 solving, if none is provided, a new one is made
    :param invert: If we want the inverse of this condition or not
    :param debug: If debug information should be displayed
    :return: The condition mapping variable passed in, with the new mappings added in
    """
    # Example line:
    # ---Renaming text------------Static Condition ID we map to---Presence Condition
    # __static_condition_renaming("__static_condition_default_5", "(defined READ_X)");
    logger.debug("In get_condition_mapping")
    # All conditions start with the renaming, if the line doesn't have this text, we aren't interested
    if not line.startswith('__static_condition_renaming('):
        return current_result
    # A comma will separate the __static_condition_default from the condition
    cc = line.split(',')
    # Remove the tailend of the presence condition
    conds = re.search('(.*").*?$', cc[1]).group(1)
    logger.debug(f"Conds is {cc[1]} -> {conds}")
    #Replace bit shift with something python friendly
    conds = re.sub(r'<<',r'*2**',conds)
    # We make some substitutions to enforce format consistency
    conds = re.sub(r'(&&|\|\|) !([a-zA-Z_0-9]+)( |")', r'\1 !(\2)\3', conds)
    conds = re.sub(r'(&&|\|\|) ([a-zA-Z_0-9]+)( |")', r'\1 (\2)\3', conds)
    conds = re.sub(r' "([a-zA-Z_0-9]+)', r' "(\1)', conds)
    conds = re.sub(r' "!([a-zA-Z_0-9]+)', r' "!(\1)', conds)
    # Currently have:  "(defined READ_X)"
    # remove the last ", and then seperate by ( to get each condition. We ensured these exist with our substituions
    conds = conds[:-1]
    inds = conds.split('(')
    # inds[0] is ' "', so we ignore it
    inds = inds[1:]
    logger.debug('checking individual conditions 0:0')
    # need to access id often, for performance we manually iterate
    indxx = 0
    # each i is a condition
    # This loop is the meat of Part 1
    for i in inds:
        logger.debug('checking individual conditions' + str(indxx) + ':' + str(len(inds)))
        splits = i.split(' ')
        if len(splits) == 0 or splits[0] == '':
            continue
        # Macros in IFs are used in one of three ways
        # Check if it is defined, check if is a non 0 value, check an expression
        # We separate these into a boolean for if it is defined, and an int value
        # while the check for a non-zero value is written as #if X, we rewrite to be X != 0
        # this makes it more consistant and allows us to use the same variable for comparisons

        # if this is checking definition
        if 'defined' == splits[0]:
            # we prepend DEF_ to the front
            v = 'DEF_' + splits[1][:-1]
            # We need to be able to refer to this variable in Z3, to keep track of these
            # we create a map. The variable usage (in this case defined X)  is mapped to a string.
            # when evaluated, this string accesses our Z3 variable map. Allowing us to create
            # an unknown number of conditions that we can easily refer to in different equations
            current_result.ids['defined ' + splits[1][:-1]] = 'varis["' + v + '"]'
            current_result.varis[v] = Bool(v)
        # the else follows the same logic, but it is with USE prepended instead of DEF
        else:
            if splits[0][-1] == ')':
                v = 'USE_' + splits[0][:-1]
                current_result.ids[splits[0][:-1]] = 'varis["' + v + '"] != 0'
                current_result.varis[v] = Int(v)
            else:
                for segment in splits:
                    if re.match(r'\(?^[A-Za-z_][A-Za-z0-9_]+\)?$',segment):
                        snipped = segment if segment[-1] != ")" else segment[:-1]
                        v = 'USE_' + snipped
                        current_result.ids[snipped] = 'varis["' + v + '"]'
                        current_result.varis[v] = Int(v)
        indxx += 1
    # accessing our string again, removing the ' "'
    condstr = conds[2:]
    logger.debug('replacing names in string')

    # replace all of our variable names with their varis references (the Z3 mappings)
    # this starts Part 2
    for x in sorted(list(current_result.ids.keys()), key=len, reverse=True):
        if x.startswith('defined '):
            condstr = condstr.replace(x, current_result.ids[x])
        else:
            condstr = condstr.replace('(' + x, '(' + current_result.ids[x])
            condstr = condstr.replace(' ' + x + ' ', ' ' + current_result.ids[x] + ' ')
            condstr = condstr.replace(' ' + x + ')', ' ' + current_result.ids[x] + ')')

    # replace ! with the Not method
    condstr = condstr.replace('!(', 'Not(')
    # we treat this like RPN solvers with stacks, we need a stack of operators and operands
    # being boolean logic and conditions respectively
    orsplits = condstr.split('||')
    orsfixed = []
    for o in orsplits:
        orsfixed.append('And (' + ','.join(o.split('&&')) + ')')
    reformatted = 'Or (' + ','.join(orsfixed) + ')'

    cs = re.split('&&|\|\|', condstr)
    ops = []
    logger.debug('rearranging ops 0:0')
    # or and and methods need to be called in plae of the binary operators
    for d in range(0, len(condstr)):
        if condstr[d] == '&' and condstr[d + 1] == '&':
            ops.append('And')
        elif condstr[d] == '|' and condstr[d + 1] == '|':
            ops.append('Or')
    ncondlist = list()
    ands = 0
    ors = 0
    opxx = 0
    # In this loop we look for And and Or statements on our stack. We set this up in a way
    # such that something like X & Y & Z ends up -> And( X, And(Y, Z))
    # If our current operator is And, we pop it off the stack along with the next operand
    # If our current operator is Or, We add one more Operand to close out the most recent
    # And, and then right paren close all of the ands, we prepend our OR to the front and
    # continue
    # if we were to add all strings, it would be an N^2 alg, so we append to a list and join later
    for o in ops:
        logger.debug('rearranging ops' + str(opxx) + ':' + str(len(ops)))
        if o == 'And':
            ands += 1
            ncondlist.append('And(' + cs[0] + ',')
            cs.pop(0)
        else:
            ncondlist.insert(0, 'Or(')
            ncondlist.append(cs[0] + ands * ')')
            if ors > 0:
                ncondlist.append(')')
            ncondlist.append(',')
            ands = 0
            ors += 1
            cs.pop(0)
        opxx += 1
    # we close our ands same as when we find an Or
    ncondlist.append(cs[0] + ands * ')')
    # we close our ors
    if ors > 0:
        ncondlist.append(')')
    # conjoin our strings
    ncondstr = ''.join(ncondlist).rstrip()
    ncondlist.clear()
    # if we are looking for the inverse (say we specifically do not take an if statement)
    # we want the inverse, so wrap it all in a Not method
    ncondstr = reformatted
    if invert:
        ncondstr = 'Not(' + ncondstr + ')'
    # Finally map the static condition renaming to the re-written presence condition
    current_result.replacers[cc[0][len('__static_condition_renaming("'):-1]] = ncondstr
    return current_result
