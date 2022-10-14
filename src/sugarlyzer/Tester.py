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
from typing import Iterable, List, Dict, Any, TypeVar, Tuple, Set

# noinspection PyUnresolvedReferences
from dill import pickle
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
    def __init__(self, tool: str, program: str, baselines: bool, keep_mem: bool, make_main: bool):
        self.tool: str = tool
        self.baselines = baselines
        self.keep_mem = keep_mem
        self.make_main = make_main

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

    def get_inc_files_and_dirs_for_file(self, file: Path):
        included_files, included_directories = self.program.get_inc_files_and_dirs(file)
        logger.info(f"Included files, included directories for {file}: {included_files} {included_directories}")
        user_defined_space = SugarCRunner.get_recommended_space(file, included_files, included_directories,
                                                                self.program.no_std_libs)
        logger.info(f"User defined space for file {file} is {user_defined_space}")
        return included_directories, included_files, user_defined_space

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

            command_line = []
            if self.keep_mem:
                command_line.append('-keep-mem')
            if self.make_main:
                command_line.append('-make-main')

            def desugar(file: Path) -> Tuple[Path, Path]:
                included_directories, included_files, user_defined_space = self.get_inc_files_and_dirs_for_file(file)
                return SugarCRunner.desugar_file(file,
                                                 user_defined_space=user_defined_space,
                                                 remove_errors=tool.remove_errors,
                                                 no_stdlibs=True,
                                                 included_files=included_files,
                                                 included_directories=included_directories,
                                                 keep_mem = tool.keep_mem,
                                                 make_main = tool.make_main)


            logger.info(f"Source files are {list(self.program.get_source_files())}")
            input_files: Iterable[str] = ProcessPool(8).map(desugar, self.program.get_source_files())
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

            buckets: List[List[Alarm]] = [[]]

            def alarm_match(a: Alarm, b: Alarm):
                return a.line_in_input_file == b.line_in_input_file and a.message == b.message and a.input_file == b.input_file

            # Collect alarms into "buckets" based on equivalence.
            # Then, for each bucket, we will return one alarm, combining all of the
            #  models into a list.
            for ba in alarms:
                for bucket in buckets:
                    if len(bucket) > 0 and alarm_match(bucket[0], ba):
                        bucket.append(ba)
                        break

                    # If we get here, then there wasn't a bucket that this could fit into,
                    #  So it gets its own bucket and we add a new one to the end of the list.
                    buckets[-1].append(ba)
                    buckets.append([])

            alarms = []
            for bucket in (b for b in buckets if len(b) > 0):
                alarms.append(bucket[0])
                alarms[-1].presence_condition = f"Or({','.join(m.presence_condition for m in bucket)})"

        else:
            baseline_alarms: List[Alarm] = []

            count = 0
            count += 1
            def run_config_and_get_alarms(b: ProgramSpecification.BaselineConfig) -> Iterable[Alarm]:
                config_builder = []
                for d, s in b.configuration :
                    if d == "DEF":
                        config_builder.append('-D' + ((s + '=1') if '=' not in s else s))
                    elif d == "UNDEF":
                        config_builder.append('-U' + s)

                inc_files, inc_dirs = self.program.get_inc_files_and_dirs(b.source_file)
                alarms = tool.analyze_and_read(b.source_file, command_line_defs=config_builder,
                                               included_files=inc_files,
                                               included_dirs=inc_dirs,
                                               user_defined_space=SugarCRunner.get_recommended_space(b.source_file,
                                                                                                     inc_files, inc_dirs, no_stdlibs=self.program.no_std_libs),
                                               no_std_libs=self.program.no_std_libs)
                for a in alarms:
                    a.model = [f"{du}_{op}" for du, op in b.configuration]
                logger.debug(f"Returning {alarms})")
                return alarms

            for i in tqdm(ProcessPool().imap(run_config_and_get_alarms, i:=list(self.program.get_baseline_configurations()),
                                              total=len(list(i)))):
                baseline_alarms.extend(i)

            alarms = baseline_alarms

        # TODO: Deduplicate results.
        with open("/results.json", 'w') as f:
            json.dump([a.as_dict() for a in alarms], f)

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
                      "handlers": [logging.StreamHandler(), logging.FileHandler("/log", 'w')]}

    logging.basicConfig(**logging_kwargs)


def main():
    args = get_arguments()
    set_up_logging(args)
    t = Tester(args.tool, args.program, args.baselines, args.keep_mem, args.make_main)
    t.execute()


if __name__ == '__main__':
    main()

