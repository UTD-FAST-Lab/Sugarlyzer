import itertools
import json
import logging
import re

from z3 import Solver, And, Or, Not, Bool

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

    # Fix ids:
    id = 0
    for b in itertools.chain(baselines, experimental_results):
        b['id'] = id
        id += 1

    rows = []
    ## Transformations
    for e in experimental_results:
        if (toks := e['original_line'].split(':'))[0] != toks[1]:
            raise ValueError("Need to implement handling for original line ranges.")
        else:
            e['original_line'] = int(toks[0])
        print('\t'.join(["experimental", *[str(s) for s in e.values()]]))

    results = []
    for b in baselines:
        matches = [e for e in experimental_results if e['original_line'] == b['input_line'] and \
                   e['input_file'].split('.')[0] == b['input_file'].split('.')[0]]
        exact_matches = [m['id'] for m in matches if b['message'] == m['sanitized_message']]
        partial_matches = [m['id'] for m in matches if m not in exact_matches]
        vals = list(b.values())

        vals.extend([exact_matches, partial_matches, len(exact_matches), len(partial_matches)])
        print('\t'.join(["baseline", *[str(s) for s in vals]]))




            # Now, to construct the Z3 stuff *rolls sleeves up*


if __name__ == '__main__':
    main()
