import collections
import logging
from pathlib import Path
from typing import List, Dict, Optional, Iterable, Callable, TypeVar, Tuple
from dataclasses import dataclass
import itertools
import re

from z3.z3 import ModelRef

logger = logging.getLogger(__name__)


@dataclass
class IntegerRange:
    start_line: int
    end_line: int

    def __str__(self):
        return f"{self.start_line}:{self.end_line}"

    def is_in(self, i) -> bool:
        return self.start_line >= i.start_line and self.end_line <= i.end_line

    def includes(self, i) -> bool:
        return i.start_line >= self.start_line and i.end_line <= self.end_line


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
        self.__function_line_range = None
        self.__method_mapping = None
        self.__sanitized_message = None

        self.presence_condition: Optional[str] = None
        self.feasible: Optional[bool] = None
        self.model: Optional[ModelRef | str] = None  # TODO: More elegant way to handle the two possible types of model.

        self.string_methods = {

        }

    Printable = TypeVar('Printable')

    def as_dict(self) -> Dict[str, Printable]:
        executor = {
            "id": lambda: str(self.id),
            "input_file": lambda: str(self.input_file.absolute()),
            "input_line": lambda: self.line_in_input_file,
            "original_line": lambda: str(self.original_line_range),
            "function_line_range": lambda: str(self.function_line_range),
            "message": lambda: self.message,
            "sanitized_message": lambda: self.sanitized_message,
            "presence_condition": lambda: self.presence_condition,
            "feasible": lambda: self.feasible,
            "configuration": lambda: str(self.model)
        }

        result = {}
        for k, v in executor.items():
            try:
                result[k] = v()
            except ValueError as ve:
                result[k] = "ERROR"

        return result

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
    def function_line_range(self) -> Tuple[str, IntegerRange]:
        if self.input_file is None:
            raise ValueError

        if self.__function_line_range is None:
            with open(self.input_file) as f:
                lines = f.readlines()

            lines_to_reverse_iterate_over = lines[:self.line_in_input_file]
            lines_to_reverse_iterate_over.reverse()

            found = False
            for l in lines_to_reverse_iterate_over:
                if mat := re.search(r"(.*)//\s?M:L(\d*):L(\d*)$", l.strip()):
                    found = True
                    self.__function_line_range = (mat.group(1), IntegerRange(int(mat.group(2)), int(mat.group(3))))
                    break
            if not found:
                raise RuntimeError(f"Could not find function line mapping {self.input_file}:{self.line_in_input_file}")

            # Sanity Check
            try:
                if not self.__function_line_range[1].includes(self.original_line_range):
                    raise RuntimeError(f"Sanity check failed. Warning ({self.input_file}:{self.line_in_input_file}) has both original line range {self.original_line_range} and "
                                       f"function line range {self.__function_line_range} but the former is not included in the latter.")
            except ValueError as ve:
                logging.info("Ignoring value error likely caused by trying to access self.original_line_range")

        return self.__function_line_range




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
