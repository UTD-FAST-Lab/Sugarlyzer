import argparse
import functools
import importlib
import itertools
import json
import logging
import os
import re
from enum import Enum, auto
from pathlib import Path
from typing import Iterable, List, Dict, Any, TypeVar, Tuple

from jsonschema.validators import RefResolver, Draft7Validator
from pathos.multiprocessing import ProcessPool
# noinspection PyUnresolvedReferences
from dill import pickle
from tqdm import tqdm

from src.sugarlyzer import SugarCRunner
from src.sugarlyzer.SugarCRunner import process_alarms
from src.sugarlyzer.analyses.AnalysisToolFactory import AnalysisToolFactory
from src.sugarlyzer.models.Alarm import Alarm
from src.sugarlyzer.models.ProgramSpecification import ProgramSpecification

logger = logging.getLogger(__name__)


class Tester:
    def __init__(self, tool: str, program: str, baselines: bool):
        self.tool: str = tool
        self.baselines = baselines

        def read_json_and_validate(file: str) -> Dict[str, Any]:
            """
            Given a JSON file that corresponds to a program specification,
            we read it in and validate that it conforms to the schema (resources.programs.program_schema.json)
            :param file: The program file to read.
            :return: The JSON representation of the program file. Throws an exception if the file is malformed.
            """
            with open(importlib.resources.path(f'resources.programs', 'program_schema.json'), 'r') as schema_file:
                resolver = RefResolver.from_schema(schema := json.load(schema_file))
                validator = Draft7Validator(schema, resolver)
            with open(file, 'r') as program_file:
                result = json.load(program_file)
            validator.validate(result)
            return result

        program_as_json = read_json_and_validate(
            importlib.resources.path(f'resources.programs.{program}', 'program.json'))
        self.program = ProgramSpecification(program, **program_as_json)

    def execute(self):

        logger.info(f"Current environment is {os.environ}")

        output_folder = Path("/results") / Path(self.tool) / Path(self.program.name)
        output_folder.mkdir(exist_ok=True, parents=True)

        # 1. Download target program.
        logger.info(f"Downloading target program {self.program}")
        if (returnCode := self.program.download()) != 0:
            raise RuntimeError(f"Tried building program but got return code of {returnCode}")
        logger.info(f"Finished downloading target program.")
        tool = AnalysisToolFactory().get_tool(self.tool)

        if not self.baselines:
            # 2. Run SugarC
            logger.info(f"Desugaring the source code in {list(self.program.source_locations)}")

            # TODO: Need an application-specific way to specify header files.
            def desugarer(src: Path) -> Tuple[Path, Path]:
                inc_files, inc_dirs = self.program.get_inc_files_and_dirs(src)
                return SugarCRunner.desugar_file(
                    file_to_desugar=src,
                    user_defined_space=SugarCRunner.get_recommended_space(src, inc_files, inc_dirs),
                    remove_errors=self.program.remove_errors,
                    no_stdlibs=self.program.no_std_libs,
                    included_files=inc_files,
                    included_directories=inc_dirs
                )

            logger.info(f"Source files are {list(self.program.get_source_files())}")
            input_files: Iterable[str] = ProcessPool(8).map(desugarer, self.program.get_source_files())
            logger.info(f"Finished desugaring the source code.")
            # 3/4. Run analysis tool, and read its results
            logger.info(f"Collected {len([c for c in self.program.get_source_files()])} .c files to analyze.")

            def analyze_read_and_process(input_file: Path) -> Iterable[Alarm]:
                return process_alarms(tool.analyze_and_read(input_file), input_file)

            alarm_collections: List[Iterable[Alarm]] = [analyze_read_and_process(f) for f, _ in input_files]
            alarms = list()
            for collec in alarm_collections:
                alarms.extend(collec)
            logger.info(f"Got {len(alarms)} unique alarms.")

        else:
            baseline_alarms: List[Alarm] = []
            # 2. Collect files and their macros.
            for source_file in tqdm(self.program.get_source_files()):
                macros: Iterable[str] = getAllMacros(source_file)
                logging.info(f"Macros for file {source_file} are {macros}")

                T = TypeVar('T')
                G = TypeVar('G')

                def cross_product(set_a: Iterable[T], set_b: Iterable[G]) -> Iterable[Tuple[T, G]]:
                    return ((a, b) for a in set_a for b in set_b)

                def powerset(iterable: Iterable[Tuple[T, G]]) -> Iterable[Iterable[Tuple[T, G]]]:
                    # Recipe from https://docs.python.org/3/library/itertools.html#itertools-recipes
                    "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
                    s = list(iterable)
                    return itertools.chain.from_iterable(itertools.combinations(s, r) for r in range(len(s) + 1))

                # 3. Construct every possible configuration.
                config_space = powerset(cross_product(["DEF", "UNDEF"], macros))

                def run_config_and_get_alarms(config: Iterable[Tuple[str, str]]) -> Iterable[Alarm]:
                    config_builder = []
                    config: Iterable[Tuple[str, str]]
                    for d, s in config:
                        if d == "DEF":
                            config_builder.append('-D' + s + '=1')
                        elif d == "UNDEF":
                            config_builder.append('-U' + s)

                    alarms = tool.analyze_and_read(source_file, config_builder)
                    for a in alarms:
                        a.presence_condition = [{"var": v, "val": "True" if k == "DEF" else "False"} for
                                                k, v in config]
                    return alarms

                baseline_alarms.extend(itertools.chain.from_iterable(ProcessPool(32).map(
                    run_config_and_get_alarms, config_space)))
            alarms = baseline_alarms

        with open(output_folder / "results.json", 'w') as f:
            json.dump(list(map(lambda x: {str(k): str(v) for k, v in x.items()},
                               map(lambda x: x.as_dict(), alarms))), f)

        [print(str(a)) for a in alarms]
        # (Optional) 6. Optional unsoundness checker
        pass


def get_arguments() -> argparse.Namespace:
    p = argparse.ArgumentParser()
    p.add_argument("tool", help="The tool to run.")
    p.add_argument("program", help="The target program.")
    p.add_argument("-v", dest="verbosity", action="count", default=0,
                   help="""Level of verbosity. No v's will print only WARNING or above messages. One 
                   v will print INFO and above. Two or more v's will print DEBUG or above.""")
    p.add_argument("--baselines", action="store_true",
                   help="""Run the baseline experiments. In these, we configure each 
                   file with every possible configuration, and then run the experiments.""")
    return p.parse_args()


def set_up_logging(args: argparse.Namespace) -> None:
    match args.verbosity:
        case 0:
            logging_level = logging.WARNING
        case 1:
            logging_level = logging.INFO
        case _:
            logging_level = logging.DEBUG

    logging_kwargs = {"level": logging_level, "format": '%(asctime)s %(name)s %(levelname)s %(message)s',
                      "handlers": [logging.StreamHandler()]}
    if (log_file := Path("/log.txt")).exists():
        logging_kwargs["handlers"].append(logging.FileHandler(str(log_file)))

    logging.basicConfig(**logging_kwargs)


def main():
    args = get_arguments()
    set_up_logging(args)
    t = Tester(args.tool, args.program, args.baselines)
    t.execute()


if __name__ == '__main__':
    main()


def getAllMacros(fpa):
    ff = open(fpa, 'r')
    lines = ff.read().split('\n')
    defs = []
    for l in lines:
        if '#if' in l:
            m = re.match(' *#ifdef *([a-zA-Z0-9_]+).*', l)
            if m:
                v = m.group(1)
                if v not in defs:
                    defs.append(v)
                continue
            m = re.match(' *#ifndef *([a-zA-Z0-9_]+).*', l)
            if m:
                v = m.group(1)
                if v not in defs:
                    defs.append(v)
                continue
            m = re.match(' *#if *([a-zA-Z0-9_]+).*', l)
            if m:
                v = m.group(1)
                if v not in defs:
                    defs.append(v)
                continue
            ds = re.findall(r'defined *([a-zA-Z0-9_]+?)', l)
            for d in ds:
                if d not in defs:
                    defs.append(d)
    return defs
