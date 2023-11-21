import typing
import re


def parse_bash_time(stderr: str) -> typing.Tuple[float, float]:
    usr_time_match = re.search("user.*?([\\d.]*)m([\\d.]*)s", stderr)
    usr_time = float(usr_time_match.group(1)) * 60 + float(usr_time_match.group(2))
    sys_time_match = re.search("sys.*?([\\d.]*)m([\\d.]*)s", stderr)
    sys_time = float(sys_time_match.group(1)) * 60 + float(sys_time_match.group(2))
    return usr_time, sys_time
