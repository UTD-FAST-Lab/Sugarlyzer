from enum import StrEnum, auto

class WarningTypes(StrEnum):
    DEAD_STORE = auto()
    UNINITIALIZED_VALUE = auto()
    CONTROL_FLOW = auto()
    CASE_NOT_TERMINATED = auto()
    STATIC_FREE = auto()
    DOUBLE_FREE = auto()
    GLOBAL_FREE = auto()
    CAST_TO_POINTER = auto()
    MEMORY_LEAK = auto()
    UNDECLARED_IDENTIFIER = auto()
    USE_AFTER_FREE = auto()
    NULL_DEREFERENCE = auto()
    MALLOC_SIZE_OF = auto()
    GARBAGE_VALUE = auto()
    NULL_POINTER_NONNULL_EXPECTED = auto()
    DISCARD_CONST_QUALIFIER = auto()
    INSECURE_API = auto()
    PROHIBITED_CALL = auto()
    UNDEFINED_BEHAVIOR = auto()
    ZERO_LENGTH_ARRAY = auto()
    ZERO_ALLOC_MEMORY = auto()
    INCOMPATIBLE_POINTERS = auto()

def get_warning_type(alarm: dict) -> str:
    if alarm['strategy'] == 'family':
        if "is a dead store" in alarm['msg']:
            return WarningTypes.DEAD_STORE
        elif "is used uninitialized" in alarm['msg']:
            return WarningTypes.UNINITIALIZED_VALUE
        elif "Control flow of non-void function" in alarm['msg']:
            return WarningTypes.CONTROL_FLOW
        elif "Case statement is not terminated" in alarm['msg']:
            return WarningTypes.CASE_NOT_TERMINATED
        elif "is freed although not dynamically" in alarm['msg']:
            return WarningTypes.STATIC_FREE
        elif "is freed multiple times" in alarm['msg']:
            return WarningTypes.DOUBLE_FREE
        elif "makes pointer from" in alarm['msg']:
            return WarningTypes.CAST_TO_POINTER
        elif "switch statement has dangling code" in alarm['msg']:
            return WarningTypes.CONTROL_FLOW
        elif "discards 'const' qualifier" in alarm['msg']:
            return WarningTypes.DISCARD_CONST_QUALIFIER
        elif "incompatible pointer type" in alarm['msg']:
            return WarningTypes.INCOMPATIBLE_POINTERS
        else:
            raise RuntimeError(f"Couldn't handle {alarm['msg']}")
    else:
        typ = alarm['originalAlarm']['alarmType']
        msg = alarm['originalAlarm']['description']
        if typ == "unix.Malloc":
            if "Use of memory after it is freed" in msg:
                return WarningTypes.USE_AFTER_FREE
            elif "Attempt to free released memory" in msg:
                return WarningTypes.DOUBLE_FREE
            elif "Potential leak" in msg:
                return WarningTypes.MEMORY_LEAK
            elif "Use of zero-allocated memory" in msg:
                return WarningTypes.ZERO_ALLOC_MEMORY
            elif "Argument to free() is the address of the global variable" in msg:
                return WarningTypes.GLOBAL_FREE
            else:
                raise RuntimeError(f"Couldn't handle {typ} with message {msg}")
        elif typ == "DEAD_STORE" or typ == "deadcode.DeadStores":
            return WarningTypes.DEAD_STORE
        elif "is an uninitialized value" in msg:
            return WarningTypes.UNINITIALIZED_VALUE
        elif typ == "NULLPTR_DEREFERENCE" or typ == "core.NullDereference":
            return WarningTypes.NULL_DEREFERENCE
        elif typ == "PULSE_UNINITIALIZED_VALUE" or "core.uninitialized" in typ:
            return WarningTypes.UNINITIALIZED_VALUE
        elif typ == "MEMORY_LEAK_C":
            return WarningTypes.MEMORY_LEAK
        elif typ == "unix.MallocSizeof":
            return WarningTypes.MALLOC_SIZE_OF
        elif typ == "USE_AFTER_FREE":
            return WarningTypes.USE_AFTER_FREE
        elif typ == "core.UndefinedBinaryOperatorResult":
            return WarningTypes.GARBAGE_VALUE
        elif typ == "core.NonNullParamChecker":
            return WarningTypes.NULL_POINTER_NONNULL_EXPECTED
        elif typ == "core.CallAndMessage":
            if "contains uninitialized data" in msg:
                return WarningTypes.UNINITIALIZED_VALUE
            elif "uninitialized pointer value" in msg:
                return WarningTypes.UNINITIALIZED_VALUE
            else:
                raise RuntimeError(f"Couldn't handle {typ} with message {msg}")
        elif "security.insecureAPI" in typ:
            return WarningTypes.INSECURE_API
        elif typ == "unix.Vfork":
            return WarningTypes.PROHIBITED_CALL
        elif typ == "core.DivideZero":
            return WarningTypes.UNDEFINED_BEHAVIOR
        elif typ == "core.VLASize" and "zero size" in msg:
            return WarningTypes.ZERO_LENGTH_ARRAY
        else:
            raise RuntimeError(f"Couldn't handle {typ} with message {msg}")
