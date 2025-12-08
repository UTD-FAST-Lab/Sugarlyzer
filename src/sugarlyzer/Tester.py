import argparse
import copy
import functools
from importlib.resources import as_file, files
import json
import logging
import multiprocessing
import os
import random
import shutil
import tempfile
import time
import re
from pathlib import Path
from typing import Iterable, List, Dict, Any, Tuple


import pandas as pd

# noinspection PyUnresolvedReferences
from jsonschema.validators import RefResolver, Draft7Validator
from pathos.pools import ProcessPool
# noinspection PyUnresolvedReferences
from tqdm import tqdm

# noinspection PyUnresolvedReferences

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
                 validate: bool = False, sample_size: int = 1000):
        self.baselines = baselines
        self.no_recommended_space = no_recommended_space
        self.jobs: int = jobs
        self.validate = validate
        self.sample_size = sample_size
        self.alarm_config_map = {}
        self.all_configs = []

        if tool == 'testTool' or program == 'testProgram':
            return

        def read_json_and_validate(file: str) -> Dict[str, Any]:
            """
            Given a JSON file that corresponds to a program specification,
            we read it in and validate that it conforms to the schema (resources.programs.program_schema.json)

            :param file: The program file to read.
            :return: The JSON representation of the program file. Throws an exception if the file is malformed.
            """
            with as_file(files("resources.programs").joinpath("program_schema.json")) as f:
                with open(f, 'r') as schema_file:
                    resolver = RefResolver.from_schema(
                        schema := json.load(schema_file))
                    validator = Draft7Validator(schema, resolver)
                with open(file, 'r') as program_file:
                    result = json.load(program_file)
                validator.validate(result)
                return result

        with as_file(files(f'resources.programs.{program}').joinpath("program.json")) as f:
            program_as_json = read_json_and_validate(f)
        self.program: ProgramSpecification = ProgramSpecification(
            program, **program_as_json)
        self.tool: AbstractTool = AnalysisToolFactory().get_tool(tool)
        self.remove_errors = self.tool.remove_errors if self.program.remove_errors is None else self.program.remove_errors
        self.config_prefix = self.program.config_prefix
        self.whitelist = self.program.whitelist
        self.kgen_map = self.program.kgen_map


    @functools.cache
    def get_inc_files_and_dirs_for_file(self, file: Path):
        included_files, included_directories, cmd_decs = self.program.inc_files_and_dirs_for_file(
            file)
        logger.debug(
            f"Included files, included directories for {file}: {included_files} {included_directories}")
        if self.no_recommended_space:
            recommended_space = None
        else:
            recommended_space = SugarCRunner.get_recommended_space(
                file, included_files, included_directories)
        logger.debug(
            f"User defined space for file {file} is {recommended_space}")
        return included_directories, included_files, cmd_decs, recommended_space

    def analyze_one_file(self, fi: Path, ps: ProgramSpecification) -> Iterable[Alarm]:
        inc_files, inc_dirs, cmd_decs = ps.inc_files_and_dirs_for_file(fi)
        alarms = self.tool.analyze_and_read(
            fi, command_line_defs=cmd_decs, included_files=inc_files, included_dirs=inc_dirs)
        return alarms

    @staticmethod
    def configure_code(program: ProgramSpecification, config: Path):
        logger.debug(f"Running configuration {config.name}")
        # Copy config to .config
        cwd = os.curdir
        os.chdir(program.make_root)
        logger.debug(f"Copying {config.name} to {program.oldconfig_location}")
        shutil.copyfile(config, program.oldconfig_location)
        exit_code = os.system('yes | make oldconfig; make')
        if exit_code != 0:
            logger.warn(f"Make for config {str(config)} failed.")
        logger.debug("make finished.")
        os.chdir(cwd)
        # if cp.returncode != 0:
        #    logger.warning(f"Running command {' '.join(make_cmd)} resulted in a non-zero error code.\n"
        #                   f"Output was:\n" + cp.stdout)

    @staticmethod
    def clone_program_and_configure(ps: ProgramSpecification, config: Path) -> ProgramSpecification:
        """Clones a program spec to a new directory, and returns a program spec with updated search context."""
        code_dest = Path("/targets") / Path(config.name) / \
            Path(ps.project_root.name)
        code_dest.parent.mkdir(parents=True)
        logger.debug(f"Cloning {ps.project_root} to {code_dest}")

        shutil.copytree(ps.project_root, code_dest)
        ps_copy = copy.deepcopy(ps)
        ps_copy.search_context = code_dest.parent
        Tester.configure_code(ps_copy, config)
        return ps_copy

    def execute(self):
        logger.info(f"Current environment is {os.environ}")

        output_folder = Path("/results") / \
            Path(self.tool.name) / Path(self.program.name)
        output_folder.mkdir(exist_ok=True, parents=True)

        # 1. Download target program.
        logger.info(f"Downloading target program {self.program}")
        if (returnCode := self.program.download()) != 0:
            raise RuntimeError(
                f"Tried building program but got return code of {returnCode}")
        logger.info(f"Finished downloading target program.")

        if not self.baselines:
            # 2. Run SugarC
            logger.info(
                f"Desugaring the source code in {self.program.source_directory}")

            # God, what an ugly tuple
            def desugar(file: Path) -> Tuple[Path, Path, Path, float]:
                included_directories, included_files, cmd_decs, recommended_space = self.get_inc_files_and_dirs_for_file(
                    file)
                start = time.monotonic()
                # noinspection PyTypeChecker
                desugared_file_location, log_file = SugarCRunner.desugar_file(file,
                                                                              recommended_space=None,
                                                                              remove_errors=self.remove_errors,
                                                                              config_prefix=self.config_prefix,
                                                                              whitelist=self.whitelist,
                                                                              no_stdlibs=True,
                                                                              included_files=included_files,
                                                                              included_directories=included_directories,
                                                                              commandline_declarations=cmd_decs,
                                                                              keep_mem=self.tool.keep_mem,
                                                                              make_main=self.tool.make_main)

                return desugared_file_location, log_file, file, time.monotonic() - start

            # Only need to get the source files for a pogram once
            source_files = list(self.program.get_source_files())

            logger.info(f"Source files are {source_files}")
            input_files: List[Tuple] = []
            logger.info("Desugaring files....")

            for result in tqdm(ProcessPool(self.jobs).imap(desugar, source_files), total=len(source_files)):
                input_files.append(result)

            logger.info(f"Finished desugaring the source code.")
            # 3/4. Run analysis tool, and read its results

            logger.info(
                f"Collected {len(fis := [c for c in source_files])} .c files to analyze: {fis}.")

            # Get the compile command components for original_file -> run analysis on desugared_file -> get resulting alarms from analysis.
            def analyze_read_and_process(desugared_file: Path, original_file: Path, desugaring_time: float = None) -> Iterable[Alarm]:

                included_directories, included_files, cmd_decs, user_defined_space = self.get_inc_files_and_dirs_for_file(
                    original_file)

                alarms = process_alarms(self.tool.analyze_and_read(
                    desugared_file, included_files=included_files, included_dirs=included_directories), desugared_file)

                for a in alarms:
                    a.desugaring_time = desugaring_time

                return alarms

            alarms = []
            logger.info("Running analysis....")
            with ProcessPool(self.jobs) as p:

                # d = Desugared file | o = Original file | dt = Desugaring time
                for result in tqdm(p.imap(lambda x: analyze_read_and_process(*x), ((d, o, dt) for d, _, o, dt in input_files)), total=len(input_files)):
                    alarms.extend(result)

            buckets: List[List[Alarm]] = [[]]

            def alarm_match(a: Alarm, b: Alarm):
                return a.line_in_input_file == b.line_in_input_file and a.sanitized_message == b.sanitized_message and a.input_file == b.input_file and a.feasible == b.feasible

            # Collect alarms into "buckets" based on equivalence.
            # Then, for each bucket, we will return one alarm, combining all of the models into a list.
            logger.info("Now deduplicating results.")
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

            logger.info("Now aggregating alarms.")
            alarms = []

            for bucket in (b for b in buckets if len(b) > 0):
                alarms.append(bucket[0])
                alarms[-1].presence_condition = f"Or({','.join(str(m.presence_condition) for m in bucket)})"

            logger.debug("Done.")

            if self.validate:
                logger.info("Now validating....")
                with ProcessPool(self.jobs) as p:
                    alarms = list(tqdm(p.imap(self.verify_alarm, alarms)))

            alarms = self.postprocess_experimental_results([a.as_dict() for a in alarms])

        else:
            alarms = self.run_baseline_experiments()

            logger.info("Deduplicating alarms")
            logger.info(f"Collected Alarms: {alarms}")

            alarm_progs = self.postprocess_alarm_configs([a.as_dict() for a in alarms])

            self.build_csv_config_prog_table(alarm_progs)
            self.build_csv_alarm_occurrence_config_table(alarm_progs)

            alarms = self.dedup_and_process_alarms([a.as_dict() for a in alarms])

        # Now time to postprocess alarms
        logger.info("Got " + str(len(alarms)) + " alarms.")
        logger.debug("Writing alarms to file.")

        with open("/results.json", 'w') as f:
            json.dump(alarms, f, indent=2)


    def build_csv_config_prog_table(self, config_prog_map):
        def normalize_file_path(file_path):
            match = re.search(r'/(\d+\.config)(?:/|$)', file_path)
            config_file = match.group(1) if match else None
            return config_file

        def extract_number(config_name):
            match = re.search(r'(\d+)', config_name)
            return int(match.group(1)) if match else 0


        all_config_files = set()
        for config_file in self.all_configs:
            clean_config_file = normalize_file_path(str(config_file))
            all_config_files.add(clean_config_file)

        sorted_configs = sorted(all_config_files, key=extract_number)

        rows = []
        for alarm_key, config_list in config_prog_map.items():
            file_path, line, description = alarm_key
            alarm_identifier = f"{file_path}:{line} - {description}"

            for progress, config_file in set(config_list):
                rows.append({
                    'alarm': alarm_identifier,
                    'config': config_file,
                    'progress': progress
                })

        df = pd.DataFrame(rows)

        pivot_df = df.pivot(index='alarm', columns='config', values='progress')
        pivot_df = pivot_df.reindex(columns=sorted_configs)

        # Forward fill each row but only after first non-NaN value
        mask = pivot_df.notnull().cumsum(axis=1) > 0
        pivot_df = pivot_df.ffill(axis=1).where(mask)
        
        pivot_df.to_csv('alarm_config_progress.csv', index=True)


    def build_csv_alarm_occurrence_config_table(self, config_prog_map):
        rows = []
        for alarm_key, config_list in config_prog_map.items():
            file_path, line, description = alarm_key
            alarm_identifier = f"{file_path}:{line} - {description}"

            for i, (progress, _) in enumerate(list(dict.fromkeys(config_list))):
                rows.append({
                    'alarm': alarm_identifier,
                    'occurrence': i+1,
                    'progress': progress
                })

            df = pd.DataFrame(rows)
            pivot_df = df.pivot(index='alarm', columns='occurrence', values='progress')
            pivot_df.to_csv('alarm_occurrence_config_progress.csv', index=True)

    def postprocess_alarm_configs(self, alarms: List[Dict]) -> Dict:
        def normalize_file_path(file_path):
            match = re.search(r'/(\d+\.config)/', file_path)
            config_file = match.group(1) if match else None
            normalized = re.sub(r'/\d+\.config/', '/', file_path)
            return normalized, config_file

        config_count_history = {}

        for alarm in alarms:
            alarm_config = alarm.pop("configuration")
            file_path, config_file = normalize_file_path(alarm['input_file'])
            alarm_key = (file_path, alarm['input_line'], alarm['message'])

            if alarm_key not in config_count_history:
                config_count_history[alarm_key] = []

            if alarm_key in self.alarm_config_map:
                existing_alarm_configs = self.alarm_config_map[alarm_key]
                alarm_config = list(set(existing_alarm_configs) & set(alarm_config))

            config_count_history[alarm_key].append((len(alarm_config), config_file))

            self.alarm_config_map[alarm_key] = alarm_config

        return config_count_history 


    def postprocess_experimental_results(self, experimental_results: List[Dict]) -> List[Dict]:
        logger.info("Now postprocessing " +
                    str(len(experimental_results)) + " alarms.")

        def EQ(a, b):
            a_function_begin = a['function_line_range'].split(":")[-2]
            a_function_end = a['function_line_range'].split(":")[-1]
            b_function_begin = b['function_line_range'].split(":")[-2]
            b_function_end = b['function_line_range'].split(":")[-1]
            return a['original_line'] == b['original_line'] and \
                a_function_begin == b_function_begin and \
                a_function_end == b_function_end and\
                a['sanitized_message'] == b['sanitized_message'] and \
                a['input_file'] == b['input_file'] and \
                a['feasible'] == b['feasible']

        original_length = len(experimental_results)
        experimental_results = copy.deepcopy(experimental_results)
        i = 0
        while i < len(experimental_results):
            # Remove infeasible results.
            if not experimental_results[i]['feasible']:
                logger.info("Removed infeasible alarm.")
                experimental_results.pop(i)
                continue
            j = i + 1
            # Merge configurations of equivalent results
            while j < len(experimental_results):
                if EQ(experimental_results[i], experimental_results[j]):
                    experimental_results[i]['presence_condition'] = 'Or(' + experimental_results[i]['presence_condition'] + ',' + experimental_results[j][
                        'presence_condition'] + ')'
                    experimental_results.pop(j)
                j += 1
            i += 1
        logger.info("Postprocessing resulted in " + str(len(experimental_results)) +
                    " results compared to " + str(original_length) + " originally.")
        return experimental_results

    def verify_alarm(self, alarm):
        alarm = copy.deepcopy(alarm)
        alarm.verified = "UNVERIFIED"
        if not alarm.feasible:
            logger.debug(f'infeasible alarm left unverified')
            return alarm
        logger.debug(f"Constructing model {alarm.model}")
        if alarm.model is not None:
            config_string = ""
            for k, v in alarm.model.items():
                mappedKey = k
                mappedValue = v
                if self.kgen_map != None:
                    with as_file(files(f"resources.programs.{self.program.name}").joinpath(self.kgen_map)) as mapping:
                        with open(mapping, 'r') as op:
                            map = json.load(op)
                    kdef = k
                    if v.lower() == 'false':
                        kdef = '!'+kdef
                    if kdef in map.keys():
                        toParse = map[kdef]
                        if toParse.startswith('DEF'):
                            mappedKey = toParse
                            mappedValue = 'True'
                        elif toParse.startswith('!DEF'):
                            mappedKey = toParse[1:]
                            mappedValue = 'False'
                        else:
                            mappedKey = toParse.split(' == ')[0]
                            mappedValue = toParse.split(' == ')[1]
                if mappedKey.startswith('DEF_'):
                    match mappedValue.lower():
                        case 'true':
                            config_string += f"{mappedKey[4:]}=y\n"
                        case 'false':
                            config_string += f"{mappedKey[4:]}=n\n"
                elif k.startswith('USE_'):
                    config_string += f"{mappedKey[4:]}={mappedValue}\n"
                else:
                    logger.critical(
                        f"Ignored constraint {str(mappedKey)}={str(mappedValue)}")
            if config_string == "":
                return alarm
            loggable_config_string = config_string.replace("\n", ", ")
            logger.debug(f"Configuration is {loggable_config_string}")
            ntf = tempfile.NamedTemporaryFile(delete=False, mode="w")
            ntf.write(config_string)
            ps: ProgramSpecification = self.clone_program_and_configure(
                self.program, Path(ntf.name))
            updated_file = str(alarm.input_file.absolute()).replace(
                '/targets', f'/targets/{Path(ntf.name).name}').replace('.desugared', '')
            updated_file = Path(updated_file)
            logger.debug(f"Mapped file {alarm.input_file} to {updated_file}")
            verify = self.analyze_file_and_associate_configuration(
                updated_file, Path(ntf.name), ps)
            logger.debug(
                f"Got the following alarms {[json.dumps(b.as_dict()) for b in verify]} when trying to verify alarm {json.dumps(alarm.as_dict())}")
            ntf.close()
            for v in verify:
                logger.debug(
                    f"Comparing alarms {alarm.as_dict()} and {v.as_dict()}")
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
        else:
            return alarm

    def analyze_file_and_associate_configuration(self, file: Path, config: Path, ps: ProgramSpecification, delete=False) -> Iterable[Alarm]:
        """
        returns -> Resulting alarms from self.tool analysis on file configured by config
        """
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

        if delete:
            # Make sure we get the necessary information from the file before we delete it
            for a in alarms_from_one_file:
                x = a.function_line_range
            os.remove(file)
            try:
                os.remove(str(file.absolute())[:-2] + ".o")
            except Exception:
                pass

        return alarms_from_one_file

    def run_baseline_experiments(self) -> Iterable[Alarm]:
        alarms: List[Alarm] = []

        logger.info("Performing code cloning for baseline experiments:")

        self.all_configs = list(self.program.get_baseline_configurations())
        print(f"all_configs: {self.all_configs}")
        if self.program.name.lower() == "varbugs":
            # Need to restructure this and improve this code later, this is very hacky
            alarms = []

            def varbugs_analyze_and_read(bc: ProgramSpecification.BaselineConfig) -> Iterable[Alarm]:
                inc_files, inc_dirs, _ = self.program.inc_files_and_dirs_for_file(
                    bc.source_file)

                def stringify_macro(tp: Tuple[str, str]) -> str:
                    if tp[0].lower() == "def":
                        return f"-D{tp[1]}"
                    else:
                        return f"-U{tp[1]}"

                clds = [stringify_macro(tp) for tp in bc.macros]
                alarms = self.tool.analyze_and_read(bc.source_file, command_line_defs=clds,
                                                    included_dirs=inc_dirs, included_files=inc_files)
                for a in alarms:
                    a.model = [[f"{tp[0]} {tp[1]}" for tp in bc.macros]]

                return alarms

            with ProcessPool(self.jobs) as p:
                for i in p.imap(varbugs_analyze_and_read, self.all_configs):
                    alarms.extend(i)
        else:
            if self.sample_size < 1000:
                self.all_configs = self.all_configs[:self.sample_size]

            logger.debug(f"Selected configurations: {self.all_configs}")

            for config in self.all_configs:
                # Configure program to specific config
                spec = self.clone_program_and_configure(self.program, config)

                # file, config file, spec, delete_flag
                source_files_config_spec_triples: List[Tuple[Path, Path, ProgramSpecification, bool]] = []

                # Set of triple of file/config/spec/delete_flag
                source_files_config_spec_triples.extend((fi, config, spec, False) for fi in spec.get_source_files())

                logger.info(f"Running analysis on {config.name}:")
                logger.debug(f"Running analysis on pairs {source_files_config_spec_triples}")

                with ProcessPool(self.jobs) as p:
                    for resulting_alarms in p.imap(lambda x: self.analyze_file_and_associate_configuration(*x), source_files_config_spec_triples):
                        # We have the resulting alarms from a specific config and ran on a specific source file
                        alarms.extend(resulting_alarms)

        for alarm in alarms:
            alarm.get_recommended_space = (not self.no_recommended_space)
            alarm.remove_errors = self.remove_errors

        return alarms

    def dedup_and_process_alarms(self, alarms: List[Dict]) -> List[Dict]:
        for b in alarms:
            try:
                b['original_configuration'] = [
                    re.search(r"(\d*)\.config", b['input_file']).group(1)]
            except AttributeError as ae:
                b['original_configuration'] = []
            assert (b['original_configuration'] is not None)
            parts = b['input_file'].split('/')
            b['input_file'] = '/' + '/'.join([parts[1], '/'.join(parts[3:])])

        def eq(a, b):
            for stat in ['input_file', 'input_line', 'message']:
                if a[stat] != b[stat]:
                    return False
            if len(a['warning_path']) != len(b['warning_path']):
                return False
            for w in a['warning_path']:
                if w not in b['warning_path']:
                    return False
            return True

        deduped = []
        for b in alarms:
            assert (b['original_configuration'] is not None)
            found = False
            for d in deduped:
                assert (d['original_configuration'] is not None)
                if eq(b, d):
                    found = True
                    d['original_configuration'].extend(
                        b['original_configuration'])
                    d['configuration'].extend(b['configuration'])
                    break
            if not found:
                deduped.append(b)

        return deduped


def get_arguments() -> argparse.Namespace:
    p = argparse.ArgumentParser()
    p.add_argument("tool",
                   help="The tool to run.")

    p.add_argument("program",
                   help="The target program.")

    p.add_argument("-v",
                   dest="verbosity",
                   action="store_true",
                   help="""Print debug messages.""")

    p.add_argument("--baselines",
                   action="store_true",
                   help="""Run the baseline experiments. In these, we configure each 
                   file with every possible configuration, and then run the experiments.""")

    p.add_argument("--no-recommended-space",
                   help="""Do not generate a recommended space.""",
                   action='store_true')

    p.add_argument("--jobs",
                   help="The number of jobs to use. If None, will use all CPUs",
                   type=int)

    p.add_argument("--validate",
                   help="""Try running desugared alarms with Z3's configuration to see if they are retained.""",
                   action='store_true')

    p.add_argument("--sample-size",
                   help="The sample size to use for baselines (default 100)",
                   type=int)

    p.add_argument("--seed",
                   help="The random seed to use for sampling baseline",
                   type=int,
                   default=1002)

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
    start = time.monotonic()
    args = get_arguments()
    random.seed(args.seed)
    set_up_logging(args)
    t = Tester(args.tool, args.program, args.baselines, True,
               args.jobs, args.validate, args.sample_size)
    t.execute()
    print(f'total time: {time.monotonic() - start}')


if __name__ == '__main__':
    main()
