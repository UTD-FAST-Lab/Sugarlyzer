import importlib
import re
from pathlib import Path
from typing import List, Dict

from hypothesis import given
from hypothesis import strategies as st
import pytest

from src.sugarlyzer.SugarCRunner import find_condition_scope, get_condition_mapping
from src.sugarlyzer.models.Alarm import Alarm, map_source_line


@st.composite
def build_alarm(draw,
                strings=st.text(),
                lines=st.lists(st.integers())):
    return Alarm(input_file=draw(strings),
                 desugared_lines=draw(lines),
                 alarm_type=draw(strings),
                 message=draw(strings))


@given(build_alarm())
def test_alarm_sanitize_length_invariant(alarm: Alarm):
    assert (len(alarm.sanitized_message) <= len(alarm.message))


@given(build_alarm(strings=st.from_regex(r" '\S+'")))
def test_alarm_sanitize_no_var_names_invariant(alarm: Alarm):
    assert (not re.match(r" '\S+'", alarm.sanitized_message.replace("'x'", "")))


@given(build_alarm(strings=st.from_regex(r" \[.*\]$")))
def test_alarm_sanitize_no_brackets(alarm: Alarm):
    assert (not re.match(r" \[.*\]$", alarm.sanitized_message))


@given(build_alarm(), build_alarm())
def test_alarm_unique_ids(alarm1: Alarm, alarm2: Alarm):
    assert (alarm1.id != alarm2.id)


@pytest.mark.parametrize("fi", [importlib.resources.path("tests.resources", "constantPropNegative.desugared.c")])
@pytest.mark.parametrize("desugared_line,original_line",
                         [(40, 3), (49, 0), (50, 9), (54, 0), (55, 14),
                          (63, 17), (75, 0), (77, 0), (88, 0), (95, 21)])
def test_getCorrelateLine_constantPropNegative(fi: Path, desugared_line: int, original_line: int):
    assert map_source_line(fi, desugared_line) == original_line


@pytest.mark.parametrize("file",
                         [importlib.resources.path("tests.resources",
                                                   "constantPropNegative.desugared.c")])
@pytest.mark.parametrize("start,going_up,expected_result",
                         [(39, True, -1), (48, False, 50), (49, True, 48),
                          (53, False, 55), (54, True, 53), (62, True, -1),
                          (74, True, -1), (76, False, 86), (87, False, 108), (94, True, 87)])
def test_findConditionScope_constantPropNegative(start: int, file: Path, going_up: bool, expected_result: int):
    assert (find_condition_scope(start, file, going_up) == expected_result)


def __test_calculateAsserts_constantPropNegative(file: Path, lines: List[int],
                                                 expected_result: List[Dict[str, str | bool]]):
    # TODO: Ask Zach which lines are supposed to be passed to calculate asserts:
    #  desugared or original? How should these be represented in the Alarm class?

    ## Desugared
    alarm = Alarm(None, None, None, None)


def test_getConditionMapping_constantPropNegative():
    varisRep = {}
    replacersRep = {}
    idsRep = {}
    conditions = [
        '__static_condition_renaming("__static_condition_default_5", "(defined READ_X)");\n',
        '__static_condition_renaming("__static_condition_default_6", "!(defined READ_X)");\n',
        '__static_condition_renaming("__static_condition_default_7", "(defined INC)");\n',
        '__static_condition_renaming("__static_condition_default_8", "!(defined INC)");\n',
        '__static_condition_renaming("__static_condition_default_9", "(defined READ_X)");\n',
        '__static_condition_renaming("__static_condition_default_10", "!(defined READ_X)");\n',
    ]
    for l in conditions:
        res = get_condition_mapping(l, False)
        varisRep.update(res.varis)
        replacersRep.update(res.replacers)
        idsRep.update(res.ids)

    assert (idsRep['defined READ_X'] == 'varis["DEF_READ_X"]')
    assert (idsRep['defined INC'] == 'varis["DEF_INC"]')
    assert (replacersRep['__static_condition_default_5'] == '(varis["DEF_READ_X"])')
    assert (replacersRep['__static_condition_default_6'] == 'Not(varis["DEF_READ_X"])')
    assert (replacersRep['__static_condition_default_7'] == '(varis["DEF_INC"])')
    assert (replacersRep['__static_condition_default_8'] == 'Not(varis["DEF_INC"])')
    assert (replacersRep['__static_condition_default_9'] == '(varis["DEF_READ_X"])')
    assert (replacersRep['__static_condition_default_10'] == 'Not(varis["DEF_READ_X"])')
