import argparse
import logging
logging.basicConfig(level=logging.DEBUG)
import os
import importlib.resources
import subprocess
from pathlib import Path
from typing import List


def getDirsInPackage(package: str) -> List[str]:
    _, dirs, _ = next(os.walk(importlib.resources.path(package, '')))
    return dirs

p = argparse.ArgumentParser(description="A toolchain for desugaring C analyses.")
p.add_argument('-t', '--tools', help='Tools to run on', nargs='+',
               choices=(tools :=
                        list(filter(lambda x: not x.startswith('__'), getDirsInPackage('resources.tools')))),
               default=tools)
p.add_argument('-p', '--programs', help='Programs to run on', nargs='+',
               choices=(programs :=
                        list(filter(lambda x: not x.startswith('__'), getDirsInPackage('resources.programs')))),
               default=programs)
args = p.parse_args()

logger = logging.getLogger(__name__)

class Dispatcher:
    def get_image_name(self, tool: str):
        if tool is None or tool == "":
            return "sugarlyzer/base"
        else:
            return f"sugarlyzer/{tool}"

    def main(self, args):
        self.build_images(args.tools)

    def build_images(self, tools: List[str], nocache: bool = False):
        os.environ['DOCKER_BUILDKIT'] = '1'

        cmds = []
        # 1. Build base image.
        cmds.append(['docker', 'build', '.', '-t', 'sugarlyzer/base'])
        for t in tools:
            cmds.append(['docker', 'build', '-f', importlib.resources.path('resources.tools', t), f'sugarlyzer/{t}'])

        if nocache:
            map(lambda x: x.append('--no-cache'), cmds)
        logger.info('Building images....')

        for cmd in cmds:
            logging.info(f'Running cmd {" ".join(cmd)}')
            ps = subprocess.run(cmd)
            logging.debug(ps.stdout)

if __name__ == '__main__':
    Dispatcher().main(args)
