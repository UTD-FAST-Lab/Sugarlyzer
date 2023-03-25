import argparse
import copy
import functools
import importlib
import json
import logging
import multiprocessing
import os
import shutil
import subprocess
import tempfile
import time
from pathlib import Path
from tempfile import NamedTemporaryFile
from typing import Iterable, List, Dict, Any, Tuple

# noinspection PyUnresolvedReferences
from dill import pickle
from jsonschema.validators import RefResolver, Draft7Validator
from pathos.pools import ProcessPool
# noinspection PyUnresolvedReferences
from tqdm import tqdm

# noinspection PyUnresolvedReferences
from z3.z3 import Solver, sat, Bool, Int, Not, And, Or

from src.sugarlyzer import SugarCRunner
from src.sugarlyzer.SugarCRunner import process_alarms
from src.sugarlyzer.analyses.AbstractTool import AbstractTool
from src.sugarlyzer.analyses.AnalysisToolFactory import AnalysisToolFactory
from src.sugarlyzer.models.Alarm import Alarm
from src.sugarlyzer.models.ProgramSpecification import ProgramSpecification

multiprocessing.set_start_method("spawn")
logger = logging.getLogger(__name__)


class Tester:
    def __init__(self, tool: str, program: str, baselines: bool, no_recommended_space: bool, jobs: int = None,
                 validate: bool = False):
        self.baselines = baselines
        self.no_recommended_space = no_recommended_space
        self.jobs: int = jobs
        self.validate = validate

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
        self.program: ProgramSpecification = ProgramSpecification(program, **program_as_json)
        self.tool: AbstractTool = AnalysisToolFactory().get_tool(tool)
        self.remove_errors = self.tool.remove_errors if self.program.remove_errors is None else self.program.remove_errors
        self.config_prefix = self.program.config_prefix
        self.whitelist = self.program.whitelist

    @functools.cache
    def get_inc_files_and_dirs_for_file(self, file: Path):
        included_files, included_directories, cmd_decs = self.program.inc_files_and_dirs_for_file(file)
        logger.debug(f"Included files, included directories for {file}: {included_files} {included_directories}")
        if self.no_recommended_space:
            recommended_space = None
        else:
            recommended_space = SugarCRunner.get_recommended_space(file, included_files, included_directories)
        logger.debug(f"User defined space for file {file} is {recommended_space}")
        return included_directories, included_files, cmd_decs, recommended_space

    def analyze_one_file(self, fi: Path, ps: ProgramSpecification) -> Iterable[Alarm]:
        inc_files, inc_dirs, cmd_decs = ps.inc_files_and_dirs_for_file(fi)
        alarms = self.tool.analyze_and_read(fi, command_line_defs=cmd_decs,
                                            included_files=inc_files,
                                            included_dirs=inc_dirs)
        return alarms

    @staticmethod
    def configure_code(program: ProgramSpecification, config: Path):
        logger.info(f"Running configuration {config.name}")
        # Copy config to .config
        logger.debug(f"Copying {config.name} to {program.oldconfig_location}")
        shutil.copyfile(config, program.oldconfig_location)
        cwd = os.curdir
        os.chdir(program.make_root)
        logger.debug("Running make oldconfig")
        cp: subprocess.CompletedProcess = subprocess.run(make_cmd := ["make", "clean"],
                                                         stdout=subprocess.PIPE,
                                                         stderr=subprocess.STDOUT,
                                                         text=True)
        if cp.returncode != 0:
            logger.warning(f"Running command {' '.join(make_cmd)} resulted in a non-zero error code.\n"
                           f"Output was:\n" + cp.stdout)
        cp: subprocess.CompletedProcess = subprocess.run(make_cmd := ["make", "oldconfig"],
                                                         stdout=subprocess.PIPE,
                                                         stderr=subprocess.STDOUT,
                                                         text=True)
        if cp.returncode != 0:
            logger.warning(f"Running command {' '.join(make_cmd)} resulted in a non-zero error code.\n"
                           f"Output was:\n" + cp.stdout)
        cp: subprocess.CompletedProcess = subprocess.run(make_cmd := ["make"],
                                                         stdout=subprocess.PIPE,
                                                         stderr=subprocess.STDOUT,
                                                         text=True)
        logger.debug("make finished.")
        os.chdir(cwd)
        if cp.returncode != 0:
            logger.warning(f"Running command {' '.join(make_cmd)} resulted in a non-zero error code.\n"
                           f"Output was:\n" + cp.stdout)

    @staticmethod
    def clone_program_and_configure(ps: ProgramSpecification, config: Path) -> ProgramSpecification:
        """Clones a program spec to a new directory, and returns a program spec with updated search context."""
        code_dest = Path("/targets") / Path(config.name) / Path(ps.project_root.name)
        code_dest.parent.mkdir(parents=True)
        logger.debug(f"Cloning {ps.project_root} to {code_dest}")

        shutil.copytree(ps.project_root, code_dest)
        ps_copy = copy.deepcopy(ps)
        ps_copy.search_context = code_dest.parent
        Tester.configure_code(ps_copy, config)
        return ps_copy

    def execute(self):

        logger.info(f"Current environment is {os.environ}")

        output_folder = Path("/results") / Path(self.tool.name) / Path(self.program.name)
        output_folder.mkdir(exist_ok=True, parents=True)

        # 1. Download target program.
        logger.info(f"Downloading target program {self.program}")
        if (returnCode := self.program.download()) != 0:
            raise RuntimeError(f"Tried building program but got return code of {returnCode}")
        logger.info(f"Finished downloading target program.")

        if not self.baselines:
            # 2. Run SugarC
            logger.info(f"Desugaring the source code in {self.program.source_directory}")

            def desugar(file: Path) -> Tuple[Path, Path, Path, float]:  # God, what an ugly tuple
                included_directories, included_files, cmd_decs, recommended_space = self.get_inc_files_and_dirs_for_file(
                    file)
                start = time.time()
                # noinspection PyTypeChecker
                return (*SugarCRunner.desugar_file(file,
                                                   recommended_space=None,
                                                   remove_errors=self.remove_errors,
                                                   config_prefix=self.config_prefix,
                                                   whitelist=self.whitelist,
                                                   no_stdlibs=True,
                                                   included_files=included_files,
                                                   included_directories=included_directories,
                                                   commandline_declarations=cmd_decs,
                                                   keep_mem=self.tool.keep_mem,
                                                   make_main=self.tool.make_main), file, time.time() - start)

            logger.info(f"Source files are {list(self.program.get_source_files())}")
            input_files: List[Tuple] = []
            logger.info("Desugaring files....")
            for result in tqdm(ProcessPool(self.jobs).imap(desugar, self.program.get_source_files()),
                               total=len(list(self.program.get_source_files()))):
                input_files.append(result)
            logger.info(f"Finished desugaring the source code.")
            # 3/4. Run analysis tool, and read its results
            logger.info(f"Collected {len([c for c in self.program.get_source_files()])} .c files to analyze.")

            def analyze_read_and_process(desugared_file: Path, original_file: Path, desugaring_time: float = None) -> \
                    Iterable[Alarm]:
                included_directories, included_files, cmd_decs, user_defined_space = self.get_inc_files_and_dirs_for_file(
                    original_file)
                alarms = process_alarms(self.tool.analyze_and_read(desugared_file, included_files=included_files,
                                                                   included_dirs=included_directories),
                                        desugared_file)
                for a in alarms:
                    a.desugaring_time = desugaring_time
                return alarms

            alarms = []
            logger.info("Running analysis....")
            with ProcessPool(self.jobs) as p:
                for result in tqdm(p.imap(lambda x: analyze_read_and_process(*x), ((d, o, dt) for d, _, o, dt in input_files)),
                                   total=len(input_files)):
                    alarms.extend(result)

            logger.info(f"Got {len(alarms)} unique alarms.")

            buckets: List[List[Alarm]] = [[]]

            def alarm_match(a: Alarm, b: Alarm):
                return a.line_in_input_file == b.line_in_input_file and a.sanitized_message == b.sanitized_message and a.input_file == b.input_file and a.feasible == b.feasible

            # Collect alarms into "buckets" based on equivalence.
            # Then, for each bucket, we will return one alarm, combining all of the
            #  models into a list.
            logger.debug("Now deduplicating results.")
            for ba in alarms:
                for bucket in buckets:
                    if len(bucket) > 0 and alarm_match(bucket[0], ba):
                        logger.debug("Found matching bucket.")
                        bucket.append(ba)
                        break

                # If we get here, then there wasn't a bucket that this could fit into,
                #  So it gets its own bucket and we add a new one to the end of the list.
                logger.debug("Creating a new bucket.")
                buckets[-1].append(ba)
                buckets.append([])

            logger.debug("Now aggregating alarms.")
            alarms = []
            for bucket in (b for b in buckets if len(b) > 0):
                alarms.append(bucket[0])
                alarms[-1].presence_condition = f"Or({','.join(str(m.presence_condition) for m in bucket)})"
            logger.debug("Done.")

            if self.validate:
                logger.info("Now validating....")
                with ProcessPool(self.jobs) as p:
                    alarms = list(tqdm(p.imap(self.verify_alarm, alarms)))
        else:
            alarms = self.run_baseline_experiments()

        logger.debug("Writing alarms to file.")
        with open("/results.json", 'w') as f:
            json.dump([a.as_dict() for a in alarms], f)

    def verify_alarm(self, alarm):
        alarm = copy.deepcopy(alarm)
        alarm.verified = "UNVERIFIED"
        logger.debug(f"Constructing model {alarm.model}")
        if alarm.model is not None:
            config_string = ""
            for k, v in alarm.model.items():
                if k.startswith('DEF_'):
                    match v.lower():
                        case 'true':
                            config_string += f"{k[4:]}=y\n"
                        case 'false':
                            config_string += f"{k[4:]}=n\n"
                elif k.startswith('USE_'):
                    config_string += f"{k[4:]}={v}\n"
                else:
                    logger.critical(f"Ignored constraint {str(k)}={str(v)}")
            loggable_config_string = config_string.replace("\n", ", ")
            logger.debug(f"Configuration is {loggable_config_string}")
            ntf = tempfile.NamedTemporaryFile(delete=False, mode="w")
            ntf.write(loggable_config_string)
            ps: ProgramSpecification = self.clone_program_and_configure(self.program, Path(ntf.name))
            updated_file = alarm.input_file.relative_to(self.program.source_directory).relative_to(ps.source_directory)
            logger.debug(f"Mapped file {alarm.input_file} to {updated_file}")
            verify = self.analyze_file_and_associate_configuration(updated_file, Path(ntf.name))
            logger.debug(
                f"Got the following alarms {[json.dumps(b.as_dict()) for b in verify]} when trying to verify alarm {json.dumps(alarm.as_dict())}")
            ntf.close()
            for v in verify:
                logger.debug(f"Comparing alarms {alarm.as_dict()} and {v.as_dict()}")
                if alarm.sanitized_message == v.sanitized_message and \
                        alarm.verified not in ["FUNCTION_LEVEL", "FULL"]:
                    alarm.verified = "MESSAGE_ONLY"
                try:
                    if alarm.sanitized_message == v.sanitized_message and \
                            alarm.function_line_range[1].includes(v.line_in_input_file) and \
                            alarm.verified != "FULL":
                        alarm.verified = "FUNCTION_LEVEL"
                except ValueError as ve:
                    pass
                try:
                    if alarm.sanitized_message == v.sanitized_message and \
                            alarm.original_line_range.includes(v.line_in_input_file):
                        alarm.verified = "FULL"
                        break  # no need to continue
                except ValueError as ve:
                    pass
            logger.debug(f"Alarm with validation updated: {alarm.as_dict()}")
            return alarm


    def analyze_file_and_associate_configuration(self, file: Path, config: Path, ps: ProgramSpecification) -> Iterable[Alarm]:
        def get_config_object(config: Path) -> List[Tuple[str, str]]:
            with open(config, 'r') as f:
                lines = [l.strip() for l in f.readlines()]

            result = []
            for x in lines:
                if x.startswith("#"):
                    result.append((x[1:].strip().split(" ")[0], False))
                else:
                    result.append(((toks := x.strip().split("="))[0], toks[1]))

            return result

        alarms_from_one_file = self.analyze_one_file(file, ps)
        for a in alarms_from_one_file:
            a.model = get_config_object(config)
        return alarms_from_one_file

    def run_baseline_experiments(self) -> Iterable[Alarm]:
        alarms: List[Alarm] = []
        count = 0
        count += 1

        logger.info("Performing code cloning for baseline experiments:")

        spec_config_pairs: List[Tuple[ProgramSpecification, Path]] = []
        all_configs = list(self.program.get_baseline_configurations())
        logger.debug(f"All configs are {all_configs}")
        i = 0

        with ProcessPool(self.jobs) as p:
            for result in tqdm(p.imap(lambda x: (self.clone_program_and_configure(self.program, x), x),
                                      all_configs),
                               total=len(all_configs)):
                # logger.info(f"Copying configuration {i}/1000")
                i += 1
                spec_config_pairs.append(result)

        logger.debug(f"Config pairs is {list((ps.search_context, x) for ps, x in spec_config_pairs)}")
        source_files_config_spec_triples: List[Tuple[Path, Path, ProgramSpecification]] = []
        for spec, config in spec_config_pairs:
            source_files_config_spec_triples.extend((fi, config, spec) for fi in spec.get_source_files())

        logger.info("Running analysis:")
        logger.debug(f"Running analysis on pairs {source_files_config_spec_triples}")
        with ProcessPool(self.jobs) as p:
            alarms = list()
            for i in tqdm(
                    p.imap(lambda x: self.analyze_file_and_associate_configuration(*x), source_files_config_spec_triples),
                    total=len(source_files_config_spec_triples)):
                alarms.extend(i)

        for alarm in alarms:
            alarm.get_recommended_space = (not self.no_recommended_space)
            alarm.remove_errors = self.remove_errors

        return alarms


def get_arguments() -> argparse.Namespace:
    p = argparse.ArgumentParser()
    p.add_argument("tool", help="The tool to run.")
    p.add_argument("program", help="The target program.")
    p.add_argument("-v", dest="verbosity", action="store_true", help="""Print debug messages.""")
    p.add_argument("--baselines", action="store_true",
                   help="""Run the baseline experiments. In these, we configure each 
                   file with every possible configuration, and then run the experiments.""")
    p.add_argument("--no-recommended-space", help="""Do not generate a recommended space.""", action='store_true')
    p.add_argument("--jobs", help="The number of jobs to use. If None, will use all CPUs", type=int)
    p.add_argument("--validate",
                   help="""Try running desugared alarms with Z3's configuration to see if they are retained.""",
                   action='store_true')
    return p.parse_args()


def set_up_logging(args: argparse.Namespace) -> None:
    if args.verbosity:
        logging_level = logging.DEBUG
    else:
        logging_level = logging.INFO

    logging_kwargs = {"level": logging_level,
                      "format": '%(asctime)s %(name)s [%(levelname)s - %(process)d] %(message)s',
                      "handlers": [logging.StreamHandler(), logging.FileHandler("/log", 'w')]}

    logging.basicConfig(**logging_kwargs)


def main():
    start = time.time()
    args = get_arguments()
    set_up_logging(args)
    t = Tester(args.tool, args.program, args.baselines, True, args.jobs, args.validate)
    t.execute()
    print(f'total time: {time.time() - start}')

if __name__ == '__main__':
    main()
