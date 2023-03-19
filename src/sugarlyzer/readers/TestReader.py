from pathlib import Path
from typing import List, Iterable

from src.sugarlyzer.analyses.AbstractTool import AbstractTool
from src.sugarlyzer.models.Alarm import Alarm
from src.sugarlyzer.readers.AbstractReader import AbstractReader


class TestReader(AbstractReader):

    def read_output(self, report_file: Path) -> Iterable[Alarm]:
        return []
