import logging
from pathlib import Path
from typing import List, Dict, Optional, Iterable, Callable, TypeVar
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
                 input_file: Path = None,
                 line_in_input_file: int = None,
                 message: str = None,
                 ):
        self.input_file: Path = input_file
        self.line_in_input_file: int = int(line_in_input_file)
        self.message: str = message
        self.id: int = next(Alarm.__id_generator)

        self.__original_line_range: IntegerRange = None
        self.__sanitized_message = None

        self.presence_condition: List[Dict[str, str | bool]] = []
        self.feasible: Optional[bool] = None
        self.model: Optional[ModelRef] = None

    @property
    def sanitized_message(self) -> str:
        if self.message is None:
            raise ValueError("Cannot compute sanitized message while self.message is None.")

        if self.__sanitized_message is None:
            self.__sanitized_message = self.sanitize(self.message)
        return self.__sanitized_message

    @property
    def original_line_range(self) -> IntegerRange:
        if self.input_file is None:
            raise ValueError("Trying to set original line range when self.original_file is none.")

        if self.__original_line_range is None:
            self.__original_line_range = map_source_line(self.input_file, self.line_in_input_file)
        return self.__original_line_range


    @property
    def all_relevant_lines(self) -> Iterable[int]:
        """
        Returns all desugared lines. Useful for use with :func:`src.sugarlyzer.SugarCRunner.calculate_asserts`

        :return: An iterator of desugared lines.
        """
        return [self.line_in_input_file]

    # noinspection PyMethodMayBeStatic
    def sanitize(self, message: str):
        logger.warning("Sanitize is not implemented.")
        return message

    def as_dict(self) -> Dict[str, Optional[str]]:
        base: Dict[str, str] = {}

        for attr in dir(self):
            if not attr.startswith('_'):
                try:
                    val = getattr(self, attr)
                    if not callable(val):
                        base[attr] = str(val)
                except Exception as ex:
                    logger.warning(f"Could not access attribute {attr} without exception.")
                    base[attr] = None
        return base



