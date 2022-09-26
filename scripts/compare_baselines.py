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

    ## Transformations
    for e in experimental_results:
        if (toks := e['original_line'].split(':'))[0] != toks[1]:
            raise ValueError("Need to implement handling for original line ranges.")
        else:
            e['original_line'] = int(toks[0])

    for b in baselines:
        matches = (e for e in experimental_results if e['original_line'] == b['input_line'] and \
                   e['sanitized_message'] == b['message'] and \
                   e['input_file'].split('.')[0] == b['input_file'].split('.')[0])


        for m in matches:
            m['presence_condition'] = re.sub("\(defined (.*?)\)", "(\1)", m['presence_condition'])
            print(m['presence_condition'])
            # Now, to construct the Z3 stuff *rolls sleeves up*

if __name__ == '__main__':
    main()