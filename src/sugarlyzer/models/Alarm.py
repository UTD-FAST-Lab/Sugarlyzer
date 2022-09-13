import json
import logging
from pathlib import Path
from typing import List, Dict, ClassVar, Optional, Iterable
from dataclasses import dataclass, field
import itertools
import re

from z3.z3 import ModelRef


def sanitize(message: str):
    san = message.rstrip()
    if " '" in san:
        san = re.sub(r" '\S+'", " 'x'", san)
    if san.endswith(']'):
        san = re.sub(r' \[.*\]$', '', san)
    return san


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

    def __init__(self, file: Path,
                 desugared_lines: Iterable[int],
                 alarm_type: str,
                 message: str):
        self.file: Path = file
        self.desugared_lines: Iterable[int] = desugared_lines
        self.original_lines: Iterable[IntegerRange] = []
        self.alarm_type: str = alarm_type
        self.message: str = message

        self.id: int = next(Alarm.__id_generator)
        self.sanitized_message: str = sanitize(self.message)

        self.asserts: List[Dict[str, str | bool]] = []
        self.feasible: Optional[bool] = None
        self.model: Optional[ModelRef] = None

    def as_dict(self) -> Dict[str, str]:
        return {
            "file": str(self.file.absolute()),
            "original_lines": [str(s) for s in self.original_lines],
            "desugared_lines": [str(s) for s in self.desugared_lines],
            "alarm_type": self.alarm_type,
            "message": self.message,
            "sanitized_message": self.sanitized_message,
            "id": self.id,
            "asserts": [{str(k): str(v) for k, v in f.items()} for f in self.asserts],
            "feasible": str(self.feasible),
            "model": str(self.model)
        }


@dataclass
class VariabilityAlarm(Alarm):
    conditional: str = ""  # TODO: How do we want to represent conditionals?
