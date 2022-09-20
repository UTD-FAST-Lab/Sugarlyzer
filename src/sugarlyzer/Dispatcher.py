import argparse
import logging

logger = logging.getLogger(__name__)
import docker as docker
from docker.models.containers import Container
import os
import importlib.resources
import subprocess
from pathlib import Path
from typing import List, Optional


def read_arguments() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="A toolchain for desugaring C analyses.")
    p.add_argument('-t', '--tools', help='Tools to run on', nargs='+',
                   choices=(tools :=
                            list(filter(lambda x: not x.startswith('__'), get_dirs_in_package('resources.tools')))),
                   default=tools)
    p.add_argument('-p', '--programs', help='Programs to run on', nargs='+',
                   choices=(programs :=
                            list(filter(lambda x: not x.startswith('__'), get_dirs_in_package('resources.programs')))),
                   default=programs)
    p.add_argument('-r', '--results', help='Location to put results', default='results')
    p.add_argument('--no-cache', help="Build all images fresh without using Docker's cache.", action='store_true')
    p.add_argument('-v', dest='verbosity', action='count', help="""Level of verbosity. No v's will print only WARNING or above messages. One 
v will print INFO and above. Two or more v's will print DEBUG or above.""", default=0)
    p.add_argument('--log', help='If specified, logs will be printed to the specified file. Otherwise, logs are printed'
                                 ' to the console.')
    return p.parse_args()


def get_dirs_in_package(package: str) -> List[str]:
    """
    Get the directories in a specific package.
    :param package: The name of the package.
    :return: A list of directories.
    """
    # noinspection PyTypeChecker
    _, dirs, _ = next(os.walk(importlib.resources.path(package, '')))
    return dirs


def get_image_name(tool: Optional[str]) -> str:
    """
    Returns the image name to use for a tool name.
    :param tool: The name of the tool, or None if we want the base image name.
    :return: The name of the image.
    """
    if tool is None or tool == "":
        return "sugarlyzer/base"
    else:
        return f"sugarlyzer/{str.lower(tool)}"


# noinspection PyListCreation
def build_images(tools: List[str], nocache: bool = False) -> None:
    """
    Builds the Docker images for the base image and any provided tools.
    :param tools: The list of tools for which Docker images should be constructed.
    :param nocache: If true, then we will direct Docker to rebuild everything from scratch.
    """

    # Accumulator for commands.
    cmds = []

    # Build base image.
    cmds.append(['docker', 'build', '.', '-t', 'sugarlyzer/base'])

    # Add commands to build any images for tools.
    for t in tools:
        cmds.append(['docker', 'build', str(importlib.resources.path('resources.tools', t)),
                     '-t', get_image_name(t)])

    if nocache:
        map(lambda x: x.append('--no-cache'), cmds)
    logger.info('Building images....')

    for cmd in cmds:
        logging.info(f'Running cmd {" ".join(cmd)}')
        ps = subprocess.run(cmd)
        logging.debug(ps.stdout)


def start_tester(t, args) -> None:
    """
    :param t: The name of the tool.
    :param args: The command-line arguments # TODO Limit only to those we need.
    """
    Path(os.path.abspath(args.results)).mkdir(exist_ok=True, parents=True)
    bind_volumes = {os.path.abspath(args.results): {"bind": "/results", "mode": "rw"}}
    if args.log not in [None, '']:
        bind_volumes[Path(args.log).absolute()] = {"bind": "/log.txt", "mode": "rw"}

    for p in args.programs:
        command = f"tester {t} {p}"
        if args.verbosity > 0:
            command = command + " -" + ("v" * args.verbosity)
        cntr: Container = docker.from_env().containers.run(
            image=get_image_name(t),
            command="/bin/bash",
            detach=True,
            tty=True,
            volumes=bind_volumes,
            auto_remove=True
        )
        _, log_stream = cntr.exec_run(cmd=command, stream=True)
        logger.info(f"Started container with cmd {command}")
        for l in log_stream:
            print(l.decode())


def main() -> None:
    """
    Build images, and start the Sugarlyzer process within each container.
    """
    args = read_arguments()

    match args.verbosity:
        case 0:
            logging_level = logging.WARNING
        case 1:
            logging_level = logging.INFO
        case _:
            logging_level = logging.DEBUG

    logging_format = '%(asctime)s %(name)s %(levelname)s %(message)s'
    kwargs = {"format": logging_format, "level": logging_level}
    if args.log not in ['', None]:
        kwargs["filename"] = args.log

    logging.basicConfig(**kwargs)
    build_images(args.tools)
    for t in args.tools:
        start_tester(t, args)


if __name__ == '__main__':
    main()
