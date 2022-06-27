import typing
from dataclasses import dataclass, field
import itertools
import re


@dataclass
class Alarm:
    # -- Instance variables which we should initialize in the constructor.
    file: str
    start_line: int
    end_line: int
    alarm_type: str
    message: str

    # -- Class variables
    __id_generator: typing.ClassVar[itertools.count] = itertools.count()

    # -- Instance variables that should not be initialized in the constructor.
    id: int = field(init=False)
    __sanitized_message: str = field(init=False, default=None)

    def __post_init__(self):
        self.id = next(Alarm.__id_generator)

    @property
    def sanitized_message(self) -> str:
        if self.__sanitized_message is None:
            san = self.message.rstrip()
            if " '" in san:
                san = re.sub(r" '\S+'", " 'x'", san)
            if san.endswith(']'):
                san = re.sub(r' \[.*\]$', '', san)
            self.__sanitized_message = san
        return self.__sanitized_message

    def __str__(self):
        return ' '.join(['(' + self.sanitized_message + ')', str(self.file),
                         str(self.start_line), str(self.end_line)])

    def includes(self, other):
        """
        Substitute for Zach's areEq method
        :param other:
        :return:
        """
        return self.sanitized_message == other.sanitized_message and \
               self.start_line <= other.start_line and \
               self.end_line >= other.end_line


@dataclass(eq=False, unsafe_hash=False)
class VariabilityAlarm(Alarm):
    conditional: str  # TODO: How do we want to represent conditionals?

    def __eq__(self, other):
        return isinstance(other, VariabilityAlarm) and \
               self.conditional == other.conditional and \
               super().__eq__(other)
