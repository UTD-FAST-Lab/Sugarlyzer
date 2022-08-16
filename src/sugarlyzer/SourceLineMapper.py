import logging
from pathlib import Path
from typing import List
import re

from src.sugarlyzer.models.Alarm import VariabilityAlarm, Alarm

logger = logging.getLogger(__name__)


class SourceLineMapper:
    @classmethod
    def map_source_line(cls, desugared_file: Path, line: int) -> int:
        """
        Given an alarm, map it back to original source and associate it with conditionals
        :param line: The linenumber to map
        :return: The source line
        """
        logger.debug("In get_correlate_line")
        try:
            with open(desugared_file, 'r') as infile:
                lines: List[str] = list(map(lambda x: x.strip('\n'), infile.readlines()))
                the_line: str = lines[line - 1]
                match (mat := re.match(r"//L(.*)$", the_line)).lastindex:
                    case 1:
                        return int(mat.lastgroup)
                    case x if x > 1:
                        raise ValueError(f"Line {the_line} has multiple matches for the pattern (this should not be"
                                         f" possible!)")
                    case _:
                        raise ValueError(f"Line {the_line} has no correlated line.")
        except ValueError:
            logger.exception(f"Couldn't compute correlated line {line} in {desugared_file}")