import argparse
import importlib
import json
import os
import subprocess
from typing import Optional, Dict, Any, Iterable, Set

from src.sugarlyzer.Alarm import Alarm
from src.sugarlyzer.AnalysisToolFactory import AnalysisToolFactory
from src.sugarlyzer.ReaderFactory import ReaderFactory
from src.sugarlyzer.SourceLineMapper import SourceLineMapper
from src.sugarlyzer.SugarCRunner import SugarCRunner

p = argparse.ArgumentParser()
p.add_argument("tool", help="The tool to run.")
p.add_argument("program", help="The target program.")
args = p.parse_args()


class ProgramSpecification:

    def __init__(self, build_script: str,
                 source_location: str,
                 variable_specification: Optional[Dict[str, Any]] = None):
        self.build_script = build_script
        self.source_location = source_location
        self.variable_specification = variable_specification

    def build(self) -> int:
        ps = subprocess.run(self.build_script)
        return ps.returncode


class Tester:
    def __init__(self, tool: str, program: str):
        self.tool: str = tool
        with open(importlib.resources.path(f'resources.programs.{program}', 'program.json')) as f:
            self.program = ProgramSpecification(**json.load(f))

    def execute(self):
        # 1. Download target program.
        if (returnCode := self.program.build()) != 0:
            raise RuntimeError(f"Tried building program but got return code of {returnCode}")

        # 2. Run SugarC
        sugar_c_runner = SugarCRunner()
        sugar_c_runner.desugar(self.program.source_location)

        # 3. Run analysis tool
        tool = AnalysisToolFactory().get_tool(self.tool)
        all_c_files = []
        for root, dirs, files in os.walk(self.program.source_location):
            files_ending_in_dot_c = [os.path.join(root, f) for f in list(filter(lambda x: x.endswith('.c'), files))]
            all_c_files.extend(files_ending_in_dot_c)

        output_locations = [tool.analyze(f) for f in all_c_files]

        # 4. Read results
        reader = ReaderFactory().get_reader(self.tool)
        alarms: Set[Alarm] = set()
        for a in map(reader.readRawResult, output_locations):
            a: Iterable[Alarm]
            alarms.extend(a)

        # 5. Map desugared lines to source code lines.
        alarms = map(lambda x: SourceLineMapper.mapSourceLine, alarms)

        # (Optional) 6. Optional unsoundness checker
        pass


if __name__ == '__main__':
    t = Tester(args.tool, args.program)
    t.execute()
