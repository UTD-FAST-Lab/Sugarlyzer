from dataclasses import dataclass


@dataclass
class Alarm:
    file: str
    line_number: int
    alarm_type: str
    message: str


@dataclass
class VariabilityAlarm(Alarm):
    conditional: str  # TODO: How do we want to represent conditionals?
