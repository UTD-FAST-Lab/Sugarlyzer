import functools
import importlib.resources
import itertools
import logging
import os
import re
import subprocess
import sys
from dataclasses import dataclass
from io import StringIO
from pathlib import Path
from typing import List, Iterable, Optional, Dict, Tuple, TypeVar

from tqdm import tqdm

from src.sugarlyzer.util.MacroDiscoveryPreprocessor import MacroDiscoveryPreprocessor
from src.sugarlyzer.util.decorators import log_all_params_and_return

logger = logging.getLogger(__name__)


class ProgramSpecification:

    def __init__(self,
                 name: str,
                 build_script: str,
                 project_root: str,
                 config_prefix: str = None,
                 whitelist: str = None,
                 kgen_map: str = None,
                 remove_errors: bool = False,
                 source_dir: Optional[str] = None,
                 make_root: Optional[str] = None,
                 included_files_and_directories: Optional[Iterable[Dict]] = None,
                 sample_dir: Optional[str] = None,
                 makefile_location: str = None,
                 oldconfig_location: Optional[str] = None
                 ):
        self.name = name
        self.remove_errors = remove_errors
        self.config_prefix = config_prefix
        self.whitelist = whitelist
        self.kgen_map = kgen_map
        self.no_std_libs = True
        self.__project_root = project_root
        self.__source_dir = source_dir
        self.__make_root = make_root
        self.__build_script = build_script
        self.__source_location = source_dir
        self.inc_dirs_and_files = [] if included_files_and_directories is None else included_files_and_directories
        self.__sample_directory = sample_dir
        self.__makefile_location = makefile_location
        self.__search_context = "/targets"
        self.__oldconfig_location = "config/.config" if oldconfig_location is None else oldconfig_location

    @property
    def oldconfig_location(self):
        return self.try_resolve_path(self.__oldconfig_location, self.make_root)

    @property
    def search_context(self):
        p = Path(self.__search_context)
        if not p.exists():
            raise RuntimeError(f"Search context {p} does not exist.")
        else:
            return p

    @property
    def project_root(self):
        return self.try_resolve_path(self.__project_root, self.search_context)

    @property
    def source_directory(self):
        return self.try_resolve_path(self.__source_dir, self.search_context) if self.__source_dir is not None else self.project_root

    @property
    def sample_directory(self):
        return self.try_resolve_path(self.__sample_directory, importlib.resources.path('resources.programs', ''))

    @property
    def make_root(self):
        return self.try_resolve_path(self.__make_root, self.search_context) if self.__make_root is not None else self.project_root

    @property
    def build_script(self):
        return self.try_resolve_path(self.__build_script, importlib.resources.path('resources.programs', ''))

    def get_source_files(self) -> Iterable[Path]:
        """
        :return: All .c or .i files that are in the program's source locations.
        """
        for root, dirs, files in os.walk(self.source_directory):
            for f in files:
                if f.endswith(".c") or f.endswith(".i"):
                    yield Path(root) / f

    def inc_files_and_dirs_for_file(self, file: Path) -> Tuple[Iterable[Path], Iterable[Path], Iterable[str]]:
        """
        Iterates through the program.json's get_recommended_space field,
        returning the first match. See program_schema.json for more info.
        :param file: The source file to search for.
        :return: included_files, included_directories for the first object in
        get_recommended_space with a regular expression that matches the **absolute** file name.
        """

        inc_dirs, inc_files, cmd_decs = [], [], []
        for spec in self.inc_dirs_and_files:

            # Note the difference between s[a] and s.get(a) is the former will
            #  raise an exception if a is not in s, while s.get will return None.
            if spec.get('file_pattern') is None or re.search(spec.get('file_pattern'), str(file.absolute())):
                logger.debug(f"File {file} matched specification {spec}")
                if (rt := spec.get('relative_to')) is not None:
                    relative_to = Path(rt)
                else:
                    relative_to = self.project_root
                if 'included_files' in spec.keys():
                    inc_files.extend(self.try_resolve_path(Path(p), relative_to) for p in spec['included_files'])
                if 'included_directories' in spec.keys():
                    inc_dirs.extend(self.try_resolve_path(Path(p), relative_to) for p in spec['included_directories'])
                if 'macro_definitions' in spec.keys():
                    cmd_decs.extend(spec['macro_definitions'])

        return inc_files, inc_dirs, cmd_decs

    def download(self) -> int:
        """
        Runs the script to obtain the program's source code.
        :return: The return code
        """
        ps = subprocess.run(self.build_script)
        return ps.returncode

    @functools.cache
    def try_resolve_path(self, path: str | Path, root: Path = Path("/")) -> Path:
        """
        Copied directly from ECSTATIC.
        :param path: The path to resolve.
        :param root: The root from which to try to resolve the path.
        :return: The fully resolved path.
        """
        if not isinstance(path, Path):
            path = Path(path)
        if path is None:
            raise ValueError("Supplied path is None")

        logger.debug(f'Trying to resolve {path} in {root}')
        if path.name == root.name:
            return root
        if path.is_absolute():
            ##logger.warning(f"Tried to resolve an absolute path {str(path)} from root {str(root)}. May lead to incorrect resolutions.")
            return path
        if os.path.exists(joined_path := Path(root) / path):
            return joined_path.absolute()
        results = set()
        for rootdir, _, _ in os.walk(root):
            if (cur := Path(rootdir) / path).exists():
                logger.debug(f"Checking if {cur} exists.")
                results.add(cur)
        match len(results):
            case 0:
                raise FileNotFoundError(f"Could not resolve path {path} from root {root}")
            case 1:
                logger.debug(f"Result of trying to resolve {path} with {root} was {list(results)[0]}")
                return results.pop()
            case _:
                raise RuntimeError(f"Path {path} in root {root} is ambiguous. Found the following potential results: "
                                   f"{results}. Try adding more context information to the index.json file, "
                                   f"so that the path is unique.")

    @dataclass
    class BaselineConfig:
        source_file: Path
        configuration: List[Tuple[str, str]] | Path

    def get_baseline_configurations(self) -> Iterable[Path]:
        if self.sample_directory is None:
            # If we don't have a sample directory, we use the get_all_macros function to get every possible configuration.
            raise RuntimeError("Need to reimplement this.")
        else:
            yield from self.try_resolve_path(self.sample_directory).iterdir()

    def get_all_macros(self, fpa):
        parser = MacroDiscoveryPreprocessor()
        with open(fpa, 'r') as f:
            parser.parse(f.read())
        parser.write(StringIO())
        logger.debug(f"Discovered the following macros in file {fpa}: {parser.collected}")
        return parser.collected

    @search_context.setter
    def search_context(self, value):
        self.__search_context = value
