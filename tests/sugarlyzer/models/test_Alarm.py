import re

from hypothesis import given
from hypothesis.strategies import text, integers, composite, from_regex

from src.sugarlyzer.models.Alarm import Alarm


@composite
def build_alarm(draw,
                strings=text(),
                nums=integers()):
    return Alarm(file=draw(strings),
                 start_line=draw(nums),
                 end_line=draw(nums),
                 alarm_type=draw(strings),
                 message=draw(strings))


@given(build_alarm())
def test_alarm_sanitize_length_invariant(alarm: Alarm):
    assert (len(alarm.sanitized_message) <= len(alarm.message))


@given(build_alarm(strings=from_regex(r" '\S+'")))
def test_alarm_sanitize_no_var_names_invariant(alarm: Alarm):
    assert (not re.match(r" '\S+'", alarm.sanitized_message.replace("'x'", "")))


@given(build_alarm(strings=from_regex(r" \[.*\]$")))
def test_alarm_sanitize_no_brackets(alarm: Alarm):
    assert (not re.match(r" \[.*\]$", alarm.sanitized_message))


@given(build_alarm(), build_alarm())
def test_alarm_unique_ids(alarm1: Alarm, alarm2: Alarm):
    assert (alarm1.id != alarm2.id)
