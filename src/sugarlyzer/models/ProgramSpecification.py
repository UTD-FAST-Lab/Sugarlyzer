import importlib.resources
import logging
import os
import subprocess
from pathlib import Path
from typing import List, Iterable

logger = logging.getLogger(__name__)


class ProgramSpecification:

    def __init__(self, name: str, build_script: str,
                 source_location: List[str]):
        self.name = name
        self.__build_script = build_script
        self.__source_location = source_location

    @property
    def build_script(self):
        return self.try_resolve_path(self.__build_script, importlib.resources.path('resources.programs', ''))

    @property
    def source_locations(self) -> Iterable[str]:
        return map(lambda x: self.try_resolve_path(x, '/targets'), self.__source_location)

    def get_source_files(self) -> Iterable[Path]:
        for s in self.source_locations:
            for root, dirs, files in os.walk(s):
                for f in files:
                    if f.endswith(".c"):
                        yield Path(root)/f

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
