from enum import StrEnum, auto

class WarningTypes(StrEnum):
    DEAD_STORE = auto()
    UNINITIALIZED_VALUE = auto()
    CONTROL_FLOW = auto()
    CASE_NOT_TERMINATED = auto()
    STATIC_FREE = auto()
    DOUBLE_FREE = auto()
    CAST_TO_POINTER = auto()
    MEMORY_LEAK = auto()
    UNDECLARED_IDENTIFIER = auto()


def get_warning_type(msg: str, is_family: bool) -> str:
    if is_family:
        if "is a dead store" in msg:
            return WarningTypes.DEAD_STORE
        elif "is used uninitialized" in msg:
            return WarningTypes.UNINITIALIZED_VALUE
        elif "Control flow of non-void function" in msg:
            return WarningTypes.CONTROL_FLOW
        elif "Case statement is not terminated" in msg:
            return WarningTypes.CASE_NOT_TERMINATED
        elif "is freed although not dynamically" in msg:
            return WarningTypes.STATIC_FREE
        elif "is freed multiple times" in msg:
            return WarningTypes.DOUBLE_FREE
        elif "makes pointer from" in msg:
            return WarningTypes.CAST_TO_POINTER
        elif "switch statement has dangling code":
            return WarningTypes.CONTROL_FLOW
        else:
            raise RuntimeError(f"Couldn't handle {msg}")
    else:
        if "is never read" in msg:
            return WarningTypes.DEAD_STORE
        elif "is an uninitialized value" in msg:
            return WarningTypes.UNINITIALIZED_VALUE
        elif "leak of memory" in msg or "potential memory leak":
            return WarningTypes.MEMORY_LEAK
        else:
            raise RuntimeError(f"Couldn't handle {msg}")
