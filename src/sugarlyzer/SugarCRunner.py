import functools
import itertools
import logging
import os
import re
import subprocess
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Tuple, List, Optional, Dict, Iterable

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


def desugar_file(file_to_desugar: Path,
                 user_defined_space: str,
                 output_file: str = '',
                 log_file: str = '',
                 remove_errors: bool = False,
                 no_stdlibs: bool = False,
                 commandline_args=None,
                 included_files: Optional[List[str]] = None,
                 included_directories: Optional[List[str]] = None) -> tuple[Path, Path]:
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
    if commandline_args is None:
        commandline_args = ['-keep-mem']
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
            desugared_file = Path(file_to_desugar).with_suffix('.desugared.c')
        case _:
            desugared_file = Path(output_file)

    match log_file:
        case '' | None:
            log_file = file_to_desugar.with_suffix('.log')
        case _:
            log_file = Path(log_file)

    cmd = ['java', 'superc.SugarC', *commandline_args, *included_files, *included_directories,
           file_to_desugar]
    cmd = [str(s) for s in cmd]
    logging.info(f"Cmd is {' '.join(cmd)}")

    with open(USER_DEFS, 'w') as outfile:
        outfile.write(user_defined_space + "\n")
        if remove_errors:
            to_append = ['']
            its = 0
            while len(to_append) > 0 and its < 2:
                its += 1
                logger.debug(f"to_append is {to_append}")
                for d in to_append:
                    outfile.write(d + "\n")
                run_sugarc(" ".join(cmd), desugared_file, log_file)
                logging.debug(f"Created desugared file {desugared_file}")
                to_append = get_bad_constraints(desugared_file)

    run_sugarc(" ".join(cmd), desugared_file, log_file)
    logger.debug(f"Wrote to {log_file}")
    return desugared_file, log_file


@functools.cache
def run_sugarc(cmd_str, desugared_file, log_file):
    logger.debug(f"In run_sugarc, running cmd {cmd_str}")
    ps = subprocess.run(cmd_str.split(" "), capture_output=True)
    with open(desugared_file, 'wb') as f:
        f.write(ps.stdout)
    logger.info(f"Wrote to {desugared_file}")
    with open(log_file, 'wb') as f:
        f.write(ps.stderr)


def process_alarms(alarms: List[Alarm], desugared_file: str) -> Iterable[Alarm]:
    """
    Runs the analysis, and compiles the results into a report.

    :param alarms: The list of alarms.
    :param desugared_file: The location of the desugared file.
    :return: A report containing all results. TODO: Replace with some data structure?
    """
    logger.debug("In process_alarms")
    ids = {}
    replacers = {}
    varis = {}

    with open(desugared_file, 'r') as fl:
        lines = list(map(lambda x: x.strip("\n"), fl.readlines()))

    for line in lines:
        condition_mapping: ConditionMapping = get_condition_mapping(line)
        ids.update(condition_mapping.ids)
        replacers.update(condition_mapping.replacers)
        varis.update(condition_mapping.varis)

    report = ''
    for w in alarms:
        w: Alarm
        w.presence_condition = calculate_asserts(w, desugared_file)
        s = Solver()
        for a in w.presence_condition:
            if a['val']:
                s.add(eval(replacers[a['var']]))
            else:
                s.add(eval('Not(' + replacers[a['var']] + ')'))
        if s.check() == sat:
            m = s.model()
            w.feasible = True
            w.model = m
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
    for line in w.all_desugared_lines:
        line -= 1
        fl = lines[line]
        if 'static_condition_default' in fl:
            start = line
            end = find_condition_scope(line, fpa, False)
            if end == -1:
                continue
            found = False
            for x in w.all_desugared_lines:
                if start < x - 1 < end:
                    found = True
                    break
            if not found:
                asrt = {'var': fl.split("(")[1].split(')')[0], 'val': False}
                result.append(asrt)

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
                m = re.match(r"if \((__static_condition_default_\d+)\).*", lines[line_to_read])
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

    varis = condition_mapping.varis  # To make the evals work (Zach why did you do this to me)
    print(f"Condition mapping is {str(condition_mapping)}")
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
                to_eval = condition_mapping.replacers[condition.group(1)]
                print(f"to_eval is {to_eval}")
                try:
                    solver.add(eval(to_eval))
                except NameError as ne:
                    logger.exception(f"File is {desugared_file}")
                is_error = False
        line_index -= 1
    for key in condition_mapping.ids.keys():
        if key.startswith('defined '):
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
    TODO Document this function, I don't really get what it's doing.
    :param line:
    :param invert:
    :return:
    """
    logger.debug("In get_condition_mapping")

    if not line.startswith('__static_condition_renaming('):
        return current_result
    cc = line.split(',')
    conds = cc[1][:-3]
    conds = re.sub(r'(&&|\|\|) !([a-zA-Z_0-9]+)( |")', r'\1 !(\2)\3', conds)
    conds = re.sub(r'(&&|\|\|) ([a-zA-Z_0-9]+)( |")', r'\1 (\2)\3', conds)
    conds = re.sub(r' "([a-zA-Z_0-9]+)', r' "(\1)', conds)
    conds = re.sub(r' "!([a-zA-Z_0-9]+)', r' "!(\1)', conds)
    conds = conds[:-1]
    inds = conds.split('(')
    inds = inds[1:]
    if debug:
        print('checking individual conditions 0:0')
    indxx = 0
    for i in inds:
        if debug:
            sys.stdout.write('\x1b[1A')
            sys.stdout.write('\x1b[2K')
            print('checking individual conditions', indxx, ':', len(inds))
        splits = i.split(' ')
        if len(splits) <= 1:
            continue
        if 'defined' == splits[0]:
            v = 'DEF_' + splits[1][:-1]
            current_result.ids['defined ' + splits[1][:-1]] = 'varis["' + v + '"]'
            current_result.varis[v] = Bool(v)
        else:
            if splits[0][-1] == ')':
                v = 'USE_' + splits[0][:-1]
                current_result.ids[splits[0][:-1]] = 'varis["' + v + '"] != 0'
                current_result.varis[v] = Int(v)
            else:
                v = 'USE_' + splits[0]
                current_result.ids[splits[0]] = 'varis["' + v + '"]'
                current_result.varis[v] = Int(v)
        indxx += 1
    condstr = conds[2:]
    if debug:
        sys.stdout.write('\x1b[1A')
        sys.stdout.write('\x1b[2K')
        print('replacing names in string')

    for x in sorted(list(current_result.ids.keys()), key=len, reverse=True):
        if x.startswith('defined '):
            condstr = condstr.replace(x, current_result.ids[x])
        else:
            condstr = condstr.replace('(' + x, '(' + current_result.ids[x])
    condstr = condstr.replace('!(', 'Not(')
    cs = re.split('&&|\|\|', condstr)
    ops = []
    if debug:
        sys.stdout.write('\x1b[1A')
        sys.stdout.write('\x1b[2K')
        print('rearranging ops 0:0')

    for d in range(0, len(condstr)):
        if condstr[d] == '&' and condstr[d + 1] == '&':
            ops.append('And')
        elif condstr[d] == '|' and condstr[d + 1] == '|':
            ops.append('Or')
    ncondlist = list()
    ands = 0
    ors = 0
    opxx = 0
    for o in ops:
        if debug:
            sys.stdout.write('\x1b[1A')
            sys.stdout.write('\x1b[2K')
            print('rearranging ops', opxx, ':', len(ops))
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
    ncondlist.append(cs[0] + ands * ')')
    if ors > 0:
        ncondlist.append(')')
    ncondstr = ''.join(ncondlist).rstrip()
    ncondlist.clear()
    if invert:
        ncondstr = 'Not(' + ncondstr + ')'
    if debug:
        sys.stdout.write('\x1b[1A')
        sys.stdout.write('\x1b[2K')

    current_result.replacers[cc[0][len('__static_condition_renaming("'):-1]] = ncondstr
    return current_result
