import collections
import itertools
import json
import logging
import re
import dill as pickle
from pathos import multiprocessing
from typing import Tuple

from z3.z3 import Solver, And, Or, Not, Bool, sat, Int

import argparse

p = argparse.ArgumentParser()
p.add_argument('baselines', help='The file containing the baseline alarms.')
p.add_argument('experimental_results', help='The file containing the experimental results.')
args = p.parse_args()


def main():
    with open(args.baselines) as f:
        baselines = json.load(f)

    with open(args.experimental_results) as f:
        experimental_results = json.load(f)

    def match_stats(baseline_result: dict, experimental_result: dict) -> Tuple:
        """
        Returns a vector of different match information.
        (a, b, c)
        a = True iff baseline and experimental have the same line number, message, and file.
        b = True iff baseline and experimental have the same message, file, and baseline is within experimental's function scope.
        c = True iff baseline's configuration is compatible with experimental's presence condition.
        """

        a = (baseline_result['message'] == experimental_result['sanitized_message'] and \
             baseline_result['input_line'] in experimental_result['original_line'] and\
             baseline_result['input_file'].split('.')[0] == experimental_result['input_file'].split('.')[0])

        b = (baseline_result['message'] == experimental_result['sanitized_message'] and \
             baseline_result['input_line'] in experimental_result['function_line_range'] and\
             baseline_result['input_file'].split('.')[0] == experimental_result['input_file'].split('.')[0])

        c = False
        if experimental_result['presence_condition'] != 'None' and (a or b):  # Don't bother doing this expensive step when the file and line number are different.
            baseline_var_mapping = {}
            for var in baseline_result['configuration']:
                if var.startswith('DEF'):
                    baseline_var_mapping[re.sub(r"^DEF_(.*)", "\1", var)] = True
                elif var.startswith('UNDEF'):
                    baseline_var_mapping[re.sub(r"^UNDEF_(.*)", "\1", var)] = False
                else:
                    raise RuntimeError(f"Don't know how to handle variable {var}")

            s = Solver()
            for var, val in baseline_var_mapping.items():
                var = Bool(var)
                if val:
                    s.add(var)
                else:
                    s.add(Not(var))

            for mat in re.findall("DEF_[a-zA-Z0-9_]+", experimental_result['presence_condition']):
                exec(f"{mat} = Bool('{mat}')")

            for mat in re.findall("USE_[a-zA-Z0-9_]+", experimental_result['presence_condition']):
                exec(f"{mat} = Int('{mat}')")

            while True:
                try:
                    s.add(eval(experimental_result['presence_condition']))  # TODO Definitely need to do more transformation here.
                    break
                except NameError as ne:
                    var = re.search("name '(.*)' is not defined", str(ne))
                    exec(f"{var.group(1)} = Int('{var.group(1)}')")

            c = s.check() == sat
        return a, b, c

    for e in experimental_results:
        toks = e['original_line'].split(':')
        try:
            e['original_line'] = list(range(int(toks[0]), int(toks[1]) + 1))
        except Exception as ex:
            e['original_line'] = []
        #print('\t'.join(["experimental", *[str(s) for s in e.values()]]).replace("\n", ""))

        if e['function_line_range'] == 'ERROR':
            e['function_line_range'] = []
        else:
            toks = e['function_line_range'].split(':')
            try:
                e['function_line_range'] = list(range(int(toks[1]), int(toks[2]) + 1))
            except Exception as ex:
                logging.exception(f"e was {e}")
        e['presence_condition'] = str(e['presence_condition'])

    def tupleize(func, args): return func(*args), tuple(args)

    summary = {}
    for result, input in multiprocessing.Pool().starmap(tupleize,
                                                        (zip(itertools.cycle([match_stats]), itertools.product(baselines, experimental_results)))):
        if (r := str(result)) not in summary:
            summary[r] = []
        summary[r].append(input)

    print(json.dumps({"summary": {k: len(summary[k]) for k in summary.keys()}, **{k: v for k, v in summary.items if k != str((False, False, False))}))


if __name__ == '__main__':
    main()
