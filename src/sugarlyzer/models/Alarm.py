import logging
from pathlib import Path
from typing import List, Dict, Optional, Iterable
from dataclasses import dataclass
import itertools
import re

from z3.z3 import ModelRef

logger = logging.getLogger(__name__)


@dataclass
class IntegerRange:
    start_line: int
    end_line: int

    def __str__(self): return f"{self.start_line}:{self.end_line}"


def map_source_line(desugared_file: Path, line: int) -> IntegerRange:
    """
    Given an alarm, map it back to original source and associate it with conditionals
    :param line: The linenumber to map
    :return: The source line
    """
    with open(desugared_file, 'r') as infile:
        lines: List[str] = list(map(lambda x: x.strip('\n'), infile.readlines()))
        the_line: str = lines[line - 1]
        if mat := re.search("// L(.*):L(.*)$", the_line):
            return IntegerRange(int(mat.group(1)), int(mat.group(2)))
        if mat := re.search("// L(.*)$", the_line):
            return IntegerRange(int(mat.group(1)), int(mat.group(1)))
        else:
            raise ValueError(f"Could not find source line for line {desugared_file}:{line} ({the_line})")


class Alarm:
    __id_generator = itertools.count()

    def __init__(self,
                 file: Path,
                 desugared_line: int,
                 message: str,
                 ):
        self.file: Path = file
        self.desugared_line: int = desugared_line
        self.original_line_range: IntegerRange = map_source_line(file, self.desugared_line)
        self.message: str = message

        self.id: int = next(Alarm.__id_generator)
        self.sanitized_message: str = self.sanitize(self.message)

        self.presence_condition = List[Dict[str, str | bool]] = []
        self.feasible: Optional[bool] = None
        self.model: Optional[ModelRef] = None

    @property
    def all_desugared_lines(self) -> Iterable[int]:
        """
        Returns all desugared lines.

        I wrote it this way so that in [[ 
        """
        return [self.desugared_line]
    
    # noinspection PyMethodMayBeStatic
    def sanitize(self, message: str):
        logger.warning("Sanitize is not implemented.")
        return message

    def as_dict(self) -> Dict[str, str]:
        return {
            "file": str(self.file.absolute()),
            "original_lines": str(self.original_line_range),
            "desugared_line": self.desugared_line,
            "message": self.message,
            "sanitized_message": self.sanitized_message,
            "id": self.id,
            "presence_condition": [{str(k): str(v) for k, v in f.items()} for f in self.presence_condition],
            "model": str(self.model)
        }


