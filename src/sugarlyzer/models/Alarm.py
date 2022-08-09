import json
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


@dataclass
class Alarm:
    # -- Instance variables which we should initialize in the constructor,
    # --  and which we should use in comparison and hashing.
    file: str
    start_line: int
    end_line: int
    alarm_type: str

    # We don't use message in hash, instead we use sanitized_message
    message: str = field(compare=False)

    # -- Class variables
    __id_generator: ClassVar[itertools.count] = itertools.count()

    # -- Instance variables that should not be initialized in the constructor.

    # Sanitized_message is computed in __post_init__ and is used in hashing and comparison instead of
    #  message.
    sanitized_message: str = field(init=False)

    # Everything else here should not be used in hashing or comparison.
    kw_only_no_hash = {'kw_only': True, 'compare': False}
    id: int = field(init=False, compare=False)
    lines: Iterable[int] = field(default_factory=list, **kw_only_no_hash)
    asserts: List[Dict[str, str | bool]] = field(default_factory=list, **kw_only_no_hash)
    feasible: Optional[bool] = field(default=None, **kw_only_no_hash)
    model: Optional[ModelRef] = field(default=None, **kw_only_no_hash)
    correlated_lines: Optional[str] = field(default_factory=list, **kw_only_no_hash)

    def __post_init__(self):
        self.id = next(Alarm.__id_generator)
        self.sanitized_message = sanitize(self.message)


@dataclass
class VariabilityAlarm(Alarm):
    conditional: str = ""  # TODO: How do we want to represent conditionals?
