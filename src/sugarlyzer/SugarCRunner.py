import logging
import os
import re
import subprocess
import itertools
from dataclasses import dataclass, field
from typing import Tuple, List, Optional, Dict

from z3 import *
from z3.z3 import Solver, sat, Bool, Int

from src.sugarlyzer.models.Alarm import Alarm

USER_DEFS = '/tmp/__sugarlyzerPredefs.h'

logger = logging.getLogger(__name__)
def get_recommended_space(file: str) -> str:
    """
    Explores the provided file. Looks for inclusion guards or other
    macros that would be assumed to be false and recommends them to be turned off.
    Also grabs the default conditions of the machine provided by gcc.

    :param file: The file to read and determines the recommended configuration space.
    :return: A string to be added to an included file in desugaring
    """

    # still need to create the code to search for inclusion guards
    return os.popen('echo | gcc -dM -E -').read()


def desugar_file(file_to_desugar: str,
                 user_defined_space: str,
                 output_file: str = '',
                 log_file: str = '',
                 remove_errors: bool = False,
                 no_stdlibs: bool = False,
                 commandline_args: Optional[List[str]] = ['-keep-mem'],
                 included_files: Optional[List[str]] = None,
                 included_directories: Optional[List[str]] = None) -> Tuple[str, str]:
    """
    Runs the SugarC command.

    :param file_to_desugar: The C source code file to desugar.
    :param user_defined_space: defines and undefs to be assumed while desugaring
    :param output_file: If provided, will specify the location of the output. Otherwise tacks on .desugared.c to the end of the base file name
    :param log_file: If provided will specify the location of the logged data. Otherwise tacks on .Log to the end of the base file name
    :param remove_errors: Whether or not the desugared output should be re-run to remove bad configurations
    :param no_stdlibs: If this machine's standard library should be used or not.
    :param commandline_args: A list of other commandline arguments SugarC is to use.
    :param included_files: A list of individual files to be included. (The config space is always included, and does not need to be specified)
    :param included_directories: A list of directories to be included.
    :return: (desugared_file_location, log_file_location)
    """
    logger.info("In desugar file function")
    if included_directories is None:
        included_directories = []
    if included_files is None:
        included_files = []
    if commandline_args is None:
        commandline_args = []

    included_files = list(itertools.chain(*zip(['-include'] * len(included_files), included_files)))
    included_directories = list(itertools.chain(*zip(['-I'] * len(included_directories), included_directories)))
    commandline_args = ['-nostdinc', *commandline_args] if no_stdlibs else commandline_args

    match output_file:
        case '' | None:
            desugared_file = file_to_desugar + '.desugared.c'
        case _:
            desugared_file = os.path.abspath(output_file)

    match log_file:
        case '' | None:
            log_file = file_to_desugar + '.log'
        case _:
            log_file = os.path.abspath(log_file)

    cmd = ['java', 'superc.SugarC', *commandline_args, *included_files, *included_directories,
           file_to_desugar]
    logging.info(f"Cmd is {' '.join(cmd)}")

    with open(USER_DEFS, 'w') as outfile:
        outfile.write(user_defined_space + "\n")
        if remove_errors:
            to_append = ['']
            while len(to_append) > 0:
                logger.info(f"to_append is {to_append}")
                for d in to_append:
                    outfile.write(d + "\n")
                run_sugarc(cmd, desugared_file, log_file)
                logging.info(f"Created desugared file {desugared_file}")
                to_append = get_bad_constraints(desugared_file)

    run_sugarc(cmd, desugared_file, log_file)
    logger.info(f"Wrote to {log_file}")
    return desugared_file, log_file


def run_sugarc(cmd, desugared_file, log_file):
    logger.info("In run_sugarc")
    ps = subprocess.run(cmd, capture_output=True)
    with open(desugared_file, 'wb') as f:
        f.write(ps.stdout)
    logger.info(f"Wrote to {desugared_file}")
    with open(log_file, 'wb') as f:
        f.write(ps.stderr)


def process_alarms(alarms: List[Alarm], desugared_file: str) -> str:
    """
    Runs the analysis, and compiles the results into a report.

    :param alarms: The list of alarms.
    :param desugared_file: The location of the desugared file.
    :return: A report containing all results. TODO: Replace with some data structure?
    """
    logger.info("In process_alarms")
    ids = {}
    replacers = {}
    varis = {}

    with open(desugared_file, 'r') as fl:
        lines = list(map(lambda x: x.strip("\n"), fl.readlines()))

    for line in lines:
        condition_mapping: ConditionMapping = get_condition_mapping(line, False)
        ids.update(condition_mapping.ids)
        replacers.update(condition_mapping.replacers)
        varis.update(condition_mapping.varis)

    report = ''
    for w in alarms:
        w.asserts = check_non_flow(w, desugared_file)
        s = Solver()
        for a in w.asserts:
            if a['val']:
                s.add(eval(replacers[a['var']]))
            else:
                s.add(eval('Not(' + replacers[a['var']] + ')'))
        if s.check() == sat:
            m = s.model()
            w.feasible = True
            w.model = m
            w.correlated_lines = get_correlate_line(desugared_file, w.start_line)
            report += str(w) + '\n'
        else:
            print('impossible constraints')
            w.feasible = False
            # Use None and make correNum an Optional type
            # w.correNum = '-1'
    return report


def get_correlate_line(desugared_output: str, desugared_location: int) -> str:
    """
    Given the desugared output and a location in the desugared output (given by an analysis tool),
    opens the desugared output and finds the mapping back to the
    :param desugared_output:
    :param desugared_location:
    :return:
    """
    logger.info("In get_correlate_line")
    with open(desugared_output, 'r') as infile:
        lines: List[str] = list(map(lambda x: x.strip('\n'), infile.readlines()))
        the_line: str = lines[desugared_location - 1]
        match (mat := re.match(r"//L(.*)$", the_line)).lastindex:
            case 1:
                return mat.lastgroup
            case x if x > 1:
                raise ValueError(f"Line {the_line} has multiple matches for the pattern (this should not be"
                                 f" possible!)")
            case _:
                raise ValueError(f"Line {the_line} has no correlated line.")


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
    logger.info("Inside check_non_flow")
    result = []
    with open(desugared_output, 'r') as ff:
        lines: List[str] = ff.readlines()
        additional_scopes = 0
        line_to_read: int = alarm.start_line
        while line_to_read >= 0:
            additional_scopes += lines[line_to_read].count('}')
            if additional_scopes == 0:
                m = re.match(r"if \((__static_condition_default_\d+)\).*", lines[line_to_read])
                if m:
                    result.append({'var': str(m.group(1)), 'val': True})
            additional_scopes -= lines[line_to_read].count('{')
            if additional_scopes < 0:
                additional_scopes = 0
            line_to_read -= 1
    return result


def get_bad_constraints(desugared_file: str) -> List[str]:
    """
    Given a desugared file, find conditions that will always result in an error. These conditions
    are not worth exploring. TODO: Is this list a conjunction or disjunction?
    :param desugared_file: The location of the desugared file.
    :return: The list of constraints that always result in errors.
    """
    logger.info("In get_bad_constraints")
    with open(desugared_file, 'r') as infile:
        lines = infile.readlines()

    ids = {}
    replacers = {}
    varis = {}
    constraints = []
    for l in lines:
        cd: ConditionMapping = get_condition_mapping(l, True)
        ids.update(cd.ids)
        replacers.update(cd.replacers)
        varis.update(cd.varis)
        constraints.extend(cd.constraints)

    line_index = len(lines) - 1
    is_error = False
    solver = Solver()
    while line_index > 0:
        if not is_error:
            if lines[line_index].startswith('__static_parse_error') or \
                    lines[line_index].startswith('__static_type_error'):
                is_error = True
        else:
            condition = re.match('if \((__static_condition_default_\d+)\).*', lines[line_index])
            if condition:
                to_eval = replacers[condition.group(1)]
                solver.add(eval(to_eval))
                is_error = False
        line_index -= 1
    for key in ids.keys():
        if key.startswith('defined '):
            solver.push()
            solver.add(eval(ids[key]))
            if solver.check() != sat:
                constraints.append('#undef ' + key[len('defined '):])
                solver.pop()
                continue
            solver.pop()
            solver.push()
            solver.add(eval('Not(' + ids[key] + ')'))
            if solver.check() != sat:
                constraints.append('#define ' + key[len('defined '):])
            solver.pop()
    return constraints


@dataclass
class ConditionMapping:
    ids: Dict[str, str] = field(default_factory=dict)
    replacers: Dict[str, str] = field(default_factory=dict)
    varis: Dict[str, str] = field(default_factory=dict)
    constraints: List[str] = field(default_factory=list)


def get_condition_mapping(line, invert: bool = False) -> ConditionMapping:
    """
    TODO Document this function, I don't really get what it's doing.
    :param line:
    :param invert:
    :return:
    """
    logger.info("In get_condition_mapping")
    result = ConditionMapping()

    if not line.startswith('__static_condition_renaming('):
        return result

    logging.info(f"Line is {line}")
    cc = line.split(',')
    conditions = cc[1][:-3]
    conditions = re.sub(r'(&&|\|\|) !([a-zA-Z_0-9]+)( |")', r'\1 !(\2)\3', conditions)
    conditions = re.sub(r'(&&|\|\|) ([a-zA-Z_0-9]+)( |")', r'\1 (\2)\3', conditions)
    conditions = re.sub(r' "([a-zA-Z_0-9]+)', r' "(\1)', conditions)
    conditions = re.sub(r' "!([a-zA-Z_0-9]+)', r' "!(\1)', conditions)
    conditions = conditions[:-1]
    inds = conditions.split('(')
    inds = inds[1:]
    for i in inds:
        splits = i.split(' ')
        if 'defined' == splits[0]:
            v = 'DEF_' + splits[1][:-1]
            result.ids['defined ' + splits[1][:-1]] = 'varis["' + v + '"]'
            result.varis[v] = Bool(v)
        else:
            if splits[0][-1] == ')':
                v = 'USE_' + splits[0][:-1]
                result.ids[splits[0][:-1]] = 'varis["' + v + '"] != 0'
                result.varis[v] = Int(v)
            else:
                v = 'USE_' + splits[0]
                result.ids[splits[0]] = 'varis["' + v + '"]'
                result.varis[v] = Int(v)
    condstr = conditions[2:]
    for x in sorted(list(result.ids.keys()), key=len, reverse=True):
        if x.startswith('defined '):
            condstr = condstr.replace(x, result.ids[x])
        else:
            condstr = condstr.replace('(' + x, '(' + result.ids[x])
    condstr = condstr.replace('0v', '0, v')
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
    logging.info(f"Ops is {ops}")
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
    result.replacers[cc[0][len('__static_condition_renaming("'):-1]] = ncondstr

    return result
