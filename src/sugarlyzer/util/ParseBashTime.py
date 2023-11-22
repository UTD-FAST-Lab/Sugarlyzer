import typing
import re


def parse_bash_time(stderr: str) -> typing.Tuple[float, float, float]:
    usr_time_match = re.search(r"User time \(seconds\): ([\d.]*)", stderr)
    usr_time = float(usr_time_match.group(1))
    sys_time_match = re.search(r"System time \(seconds\): ([\d.]*)", stderr)
    sys_time = float(sys_time_match.group(1))
    max_memory_match = re.search("Maximum resident set size \(kbytes\): ([\\d]*)")
    max_memory = int(max_memory_match.group(1))
    return usr_time, sys_time, max_memory
