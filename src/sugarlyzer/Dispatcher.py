import argparse
import logging

logging.basicConfig(level=logging.DEBUG)
import os
import importlib.resources
import subprocess
from pathlib import Path
from typing import List, Optional


def get_dirs_in_package(package: str) -> List[str]:
    """
    Get the directories in a specific package.
    :param package: The name of the package.
    :return: A list of directories.
    """
    _, dirs, _ = next(os.walk(importlib.resources.path(package, '')))
    return dirs


p = argparse.ArgumentParser(description="A toolchain for desugaring C analyses.")
p.add_argument('-t', '--tools', help='Tools to run on', nargs='+',
               choices=(tools :=
                        list(filter(lambda x: not x.startswith('__'), get_dirs_in_package('resources.tools')))),
               default=tools)
p.add_argument('-p', '--programs', help='Programs to run on', nargs='+',
               choices=(programs :=
                        list(filter(lambda x: not x.startswith('__'), get_dirs_in_package('resources.programs')))),
               default=programs)
p.add_argument('--no-cache', help="Build all images fresh without using Docker's cache.")
args = p.parse_args()

logger = logging.getLogger(__name__)


def get_image_name(tool: Optional[str]) -> str:
    """
    Returns the image name to use for a tool name.
    :param tool: The name of the tool, or None if we want the base image name.
    :return: The name of the image.
    """
    if tool is None or tool == "":
        return "sugarlyzer/base"
    else:
        return f"sugarlyzer/{tool}"


def build_images(tools: List[str], nocache: bool = False) -> None:
    """
    Builds the Docker images for the base image and any provided tools.
    :param tools: The list of tools for which Docker images should be constructed.
    :param nocache: If true, then we will direct Docker to rebuild everything from scratch.
    """
    os.environ['DOCKER_BUILDKIT'] = '1'

    # Accumulator for commands.
    cmds = []

    # Build base image.
    cmds.append(['docker', 'build', '.', '-t', 'sugarlyzer/base'])

    # Add commands to build any images for tools.
    for t in tools:
        cmds.append(['docker', 'build', str(importlib.resources.path('resources.tools', t)),
                     '-t', f'sugarlyzer/{t}'])

    if nocache:
        map(lambda x: x.append('--no-cache'), cmds)
    logger.info('Building images....')

    for cmd in cmds:
        logging.info(f'Running cmd {" ".join(cmd)}')
        ps = subprocess.run(cmd)
        logging.debug(ps.stdout)


class Dispatcher:

    def main(self, args) -> None:
        """
        Build images, and start the Sugarlyzer process within each container.
        :param args: The command-line arguments.
        """
        build_images(args.tools)


if __name__ == '__main__':
    Dispatcher().main(args)
