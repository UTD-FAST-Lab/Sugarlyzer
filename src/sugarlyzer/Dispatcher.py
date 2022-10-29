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
    p.add_argument('-r', '--result', help='File to put results', default='results.json')
    p.add_argument('--no-cache', help="Build all images fresh without using Docker's cache.", action='store_true')
    p.add_argument('-v', dest='verbosity', action='count', help="""Level of verbosity. No v's will print only WARNING or above messages. One 
v will print INFO and above. Two or more v's will print DEBUG or above.""", default=0)
    p.add_argument('--log', help='If specified, logs will be printed to the specified file. Otherwise, logs are printed'
                                 ' to the console.')
    p.add_argument('--force', action='store_true',
                   help='Do not ask permission to delete existing log and results files.')
    p.add_argument("--baselines", action="store_true",
                   help="""Run the baseline experiments. In these, we configure each 
                   file with every possible configuration, and then run the experiments.""")
    p.add_argument("--no-recommended-space", help="""Do not generate a recommended space.""", action='store_true')
    p.add_argument("--jobs", help="The number of jobs to use. If None, will use all CPUs", type=int)
    p.add_argument("--validate",
                   help="""Try running desugared alarms with Z3's configuration to see if they are retained.""",
                   action='store_true')
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
def build_images(tools: List[str], nocache: bool = False, jobs: int = None) -> None:
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
    if jobs is None:
        import multiprocessing
        jobs = multiprocessing.cpu_count()

    map(lambda x: x.extend(["--build-arg", f"JOBS={jobs}"]), cmds)

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

    bind_volumes = {Path(args.result).absolute(): {"bind": "/results.json", "mode": "rw"},
                    Path(args.log).absolute(): {"bind": "/log", "mode": "rw"}}

    for p in args.programs:
        command = f"tester {t} {p}"
        if args.verbosity > 0:
            command = command + " -" + ("v" * args.verbosity)
        if args.baselines:
            command = command + " --baselines"
        if args.no_recommended_space:
            command += " --no-recommended-space"
        if args.jobs is not None:
            command += f" --jobs {args.jobs}"
        if args.validate:
            command += " --validate"
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

    if args.log in ['', None]:
        args.log = args.result + '.log'

    match args.verbosity:
        case 0:
            logging_level = logging.WARNING
        case 1:
            logging_level = logging.INFO
        case _:
            logging_level = logging.DEBUG

    for fi in (Path(p) for p in [args.log, args.result]):
        ensure_empty_file_ask_if_necessary(fi, args.force)

    logging_format = '%(asctime)s %(name)s %(levelname)s %(message)s'
    kwargs = {"format": logging_format, "level": logging_level, "filename": args.log}

    logging.basicConfig(**kwargs)
    build_images(args.tools)
    for t in args.tools:
        start_tester(t, args)


def ensure_empty_file_ask_if_necessary(file: Path, force: bool):
    """
    Given a file, checks if it exists. If it does and force is true, it deletes it and
    creates an empty one. If it does and force is false, it will ask the user permission
    to delete. Will exit the program if user says no. After this function, if the program
    is still running, the file is guaranteed to exist and be empty.

    :param file: The file to check.
    :param force: Whether to delete without permission.
    :return:
    """
    file.parent.mkdir(parents=True, exist_ok=True)
    if file.exists():
        if force:
            os.remove(file)
        else:
            while (char := input(f"{str(file.absolute())} exists. Delete? y/n ")) not in ['y', 'n']:
                logger.debug(f"Char is {char}")
                pass
            if char == 'y':
                os.remove(file)
            else:
                exit(-1)
    file.touch()


if __name__ == '__main__':
    main()
