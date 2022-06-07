import argparse
import importlib
import json
import os
from typing import Iterable, List

from src.sugarlyzer.SourceLineMapper import SourceLineMapper
from src.sugarlyzer.SugarCRunner import SugarCRunner
from src.sugarlyzer.analyses.AnalysisToolFactory import AnalysisToolFactory
from src.sugarlyzer.models.Alarm import Alarm
from src.sugarlyzer.models.ProgramSpecification import ProgramSpecification

p = argparse.ArgumentParser()
p.add_argument("tool", help="The tool to run.")
p.add_argument("program", help="The target program.")
args = p.parse_args()


class Tester:
    def __init__(self, tool: str, program: str):
        self.tool: str = tool
        with open(importlib.resources.path(f'resources.programs.{program}', 'program.json')) as f:
            self.program = ProgramSpecification(**json.load(f))

    def execute(self):
        # 1. Download target program.
        if (returnCode := self.program.download()) != 0:
            raise RuntimeError(f"Tried building program but got return code of {returnCode}")

        # 2. Run SugarC
        sugar_c_runner = SugarCRunner()
        sugar_c_runner.desugar(self.program.source_location)

        # 3/4. Run analysis tool, and read its results
        all_c_files = []
        for root, dirs, files in os.walk(self.program.source_location):
            files_ending_in_dot_c = [os.path.join(root, f) for f in list(filter(lambda x: x.endswith('.c'), files))]
            all_c_files.extend(files_ending_in_dot_c)

        tool = AnalysisToolFactory().get_tool(self.tool)
        alarm_collections: List[Iterable[Alarm]] = [tool.analyze_and_read(f) for f in all_c_files]
        alarms = set()
        for collec in alarm_collections:
            alarms.update(collec)


        # 5. Map desugared lines to source code lines.
        variabilityAlarms = [SourceLineMapper.map_source_line(a) for a in alarms]

        # (Optional) 6. Optional unsoundness checker
        pass


if __name__ == '__main__':
    t = Tester(args.tool, args.program)
    t.execute()
