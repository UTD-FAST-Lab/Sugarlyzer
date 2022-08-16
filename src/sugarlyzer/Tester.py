import argparse
import dataclasses
from pathlib import Path
import logging
import functools

import importlib
import json
import os
from pathos.multiprocessing import ProcessPool
from typing import Iterable, List, Dict, Any
from jsonschema.validators import RefResolver, Draft7Validator

from src.sugarlyzer import SugarCRunner
from src.sugarlyzer.SourceLineMapper import SourceLineMapper
from src.sugarlyzer.analyses.AnalysisToolFactory import AnalysisToolFactory
from src.sugarlyzer.models.Alarm import Alarm
from src.sugarlyzer.models.ProgramSpecification import ProgramSpecification

logger = logging.getLogger(__name__)


class Tester:
    def __init__(self, tool: str, program: str):
        self.tool: str = tool

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
        self.program = ProgramSpecification(**program_as_json)

    def execute(self):

        logger.info(f"Current environment is {os.environ}")
        # 1. Download target program.
        logger.info(f"Downloading target program {self.program}")
        if (returnCode := self.program.download()) != 0:
            raise RuntimeError(f"Tried building program but got return code of {returnCode}")
        logger.info(f"Finished downloading target program.")

        # 2. Run SugarC
        logger.info(f"Desugaring the source code in {list(self.program.source_locations)}")

        # TODO: Need an application-specific way to specify header files.
        partial = functools.partial(SugarCRunner.desugar_file,
                                    user_defined_space=SugarCRunner.get_recommended_space(None),
                                    remove_errors=True, no_stdlibs=True,
                                    included_files=["/SugarlyzerConfig/axtlsInc.h"],
                                    included_directories=["/SugarlyzerConfig/stdinc/usr/include/",
                                                          "/SugarlyzerConfig/stdinc/usr/include/x86_64-linux-gnu/",
                                                          "/SugarlyzerConfig/stdinc/usr/lib/gcc/x86_64-linux-gnu/9/include/"])
        logger.info(f"Source files are {list(self.program.get_source_files())}")
        desugared_files: Iterable[str, str] = ProcessPool(8).map(partial, self.program.get_source_files())
        logger.info(f"Finished desugaring the source code.")

        # 3/4. Run analysis tool, and read its results
        logger.info(f"Collected {len([c for c in self.program.get_source_files()])} .c files to analyze.")

        tool = AnalysisToolFactory().get_tool(self.tool)
        alarm_collections: List[Iterable[Alarm]] = [tool.analyze_and_read(f) for f, _ in desugared_files]
        alarms = list()
        for collec in alarm_collections:
            alarms.extend(collec)
        logger.info(f"Got {len(alarms)} unique alarms.")

        with open("/results/alarms.txt", 'w') as f:
            json.dump(list(map(lambda x: dataclasses.asdict(x), alarms)), f)

        [print(str(a)) for a in alarms]
        # (Optional) 6. Optional unsoundness checker
        pass

def get_arguments() -> argparse.Namespace:
    p = argparse.ArgumentParser()
    p.add_argument("tool", help="The tool to run.")
    p.add_argument("program", help="The target program.")
    p.add_argument("-v", dest="verbosity", action="count", help="""Level of verbosity. No v's will print only WARNING or above messages. One 
    v will print INFO and above. Two or more v's will print DEBUG or above.""")
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
    t = Tester(args.tool, args.program)
    t.execute()


if __name__ == '__main__':
    main()
