import importlib.resources
import itertools
import logging
import os
import re
import subprocess
from dataclasses import dataclass
from pathlib import Path
from typing import List, Iterable, Optional, Dict, Tuple, TypeVar

from tqdm import tqdm

logger = logging.getLogger(__name__)


class ProgramSpecification:

    def __init__(self, name: str,
                 build_script: str,
                 source_location: Optional[List[str]] = None,
                 remove_errors: bool = False,
                 no_std_libs: bool = False,
                 included_files_and_directories: Iterable[Dict] = None,
                 sample_directory: Path = None
                 ):
        self.name = name
        self.remove_errors = remove_errors
        self.no_std_libs = no_std_libs
        self.__build_script = build_script
        self.__source_location = source_location
        self.inc_dirs_and_files = [] if included_files_and_directories is None else included_files_and_directories
        self.sample_directory = sample_directory

    @property
    def build_script(self):
        return self.try_resolve_path(self.__build_script, importlib.resources.path('resources.programs', ''))

    @property
    def source_locations(self) -> Iterable[Path]:
        if self.__source_location is None:
            return [Path('/targets')]
        else:
            return map(lambda x: self.try_resolve_path(x, '/targets'), self.__source_location)

    def get_source_files(self) -> Iterable[Path]:
        """
        :return: All .c or .i files that are in the program's source locations.
        """
        for s in self.source_locations:
            for root, dirs, files in os.walk(s):
                for f in files:
                    if f.endswith(".c") or f.endswith(".i"):
                        yield Path(root)/f

    def get_inc_files_and_dirs(self, file: Path) -> Tuple[Iterable[Path], Iterable[Path]]:
        """
        Iterates through the program.json's get_recommended_space field,
        returning the first match. See program_schema.json for more info.
        :param file: The source file to search for.
        :return: included_files, included_directories for the first object in
        get_recommended_space with a regular expression that matches the **absolute** file name.
        """

        inc_dirs, inc_files = [], []
        for spec in self.inc_dirs_and_files:

            # Note the difference between s[a] and s.get(a) is the former will
            #  raise an exception if a is not in s, while s.get will return None.

            if spec.get('file_pattern') is None or re.match(spec.get('file_pattern'), str(file.absolute())):
                logging.info(f"File {file} matched specification {spec}")
                inc_files.extend(Path(p) for p in spec['included_files'])
                inc_dirs.extend(Path(p) for p in spec['included_directories'])

        return inc_files, inc_dirs

    def download(self) -> int:
        """
        Runs the script to obtain the program's source code.
        :return: The return code
        """
        ps = subprocess.run(self.build_script)
        return ps.returncode

    def try_resolve_path(self, path: str, root: str = "/") -> Path:
        """
        Copied directly from ECSTATIC.
        :param root: The root from which to try to resolve the path.
        :return: The fully resolved path.
        """
        if path is None:
            return None
        logging.info(f'Trying to resolve {path} in {root}')
        if path.startswith("/"):
            path = path[1:]
        if os.path.exists(joined_path := Path(root)/path):
            return os.path.abspath(joined_path)
        results = set()
        for rootdir, dirs, _ in os.walk(os.path.join(root, "benchmarks")):
            cur = os.path.join(os.path.join(root, "benchmarks"), rootdir)
            if os.path.exists(os.path.join(cur, path)):
                results.add(os.path.join(cur, path))
            for d in dirs:
                if os.path.exists(os.path.join(os.path.join(cur, d), path)):
                    results.add(os.path.join(os.path.join(cur, d), path))
        match len(results):
            case 0:
                raise FileNotFoundError(f"Could not resolve path {path} from root {root}")
            case 1:
                return results.pop()
            case _:
                raise RuntimeError(f"Path {path} in root {root} is ambiguous. Found the following potential results: "
                                   f"{results}. Try adding more context information to the index.json file, "
                                   f"so that the path is unique.")

    @dataclass
    class BaselineConfig:
        source_file: Path
        configuration: List[Tuple[str, str]]

    def get_baseline_configurations(self) -> Iterable[BaselineConfig]:
        if self.sample_directory is None:
            # If we don't have a sample directory, we use the get_all_macros function to get every possible configuration.
            for source_file in tqdm(self.get_source_files()):
                macros: List[str] = self.get_all_macros(source_file)
                logging.info(f"Macros for file {source_file} are {macros}")

                T = TypeVar('T')
                G = TypeVar('G')

                def all_configurations(options: List[str]) -> List[List[Tuple[str, str]]]:
                    if len(options) == 0:
                        return [[]]
                    else:
                        result = [a + [(b, options[-1])] for a in all_configurations(options[:-1]) for b in ["DEF", "UNDEF"]]
                        return result

                return (ProgramSpecification.BaselineConfig(source_file, c) for c in all_configurations(macros))
        else:
            configs = []
            for s in self.sample_directory.iterdir():
                with open(s) as f:
                    lines = f.readlines()
                config = [("UNDEF" if s.startswith('#') else "DEF", s.strip()) for s in lines]
                configs.append(config)
            return (ProgramSpecification.BaselineConfig(file, config) for file in self.get_source_files() for config in configs)

    def get_all_macros(fpa):
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
