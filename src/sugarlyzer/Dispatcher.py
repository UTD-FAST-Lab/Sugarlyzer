import argparse
import logging
import os
import importlib.resources
from pathlib import Path
from typing import List


def getDirsInPackage(package: str) -> List[str]:
    _, dirs, _ = next(os.walk(importlib.resources.path(package, '')))
    return dirs

p = argparse.ArgumentParser(description="A toolchain for desugaring C analyses.")
p.add_argument('-t', '--tools', help='Tools to run on', nargs='+', required=True,
               choices=(tools :=
                        list(filter(lambda x: not x.startswith('__'), getDirsInPackage('resources.tools')))),
               default=tools)
p.add_argument('-p', '--programs', help='Programs to run on', nargs='+', required=True,
               choices=(programs :=
                        list(filter(lambda x: not x.startswith('__'), getDirsInPackage('resources.programs')))),
               default=programs)
args = p.parse_args()

logger = logging.getLogger(__name__)


class Dispatcher:
    def main(args):
        pass


if __name__ == '__main__':
    Dispatcher().main(args)
