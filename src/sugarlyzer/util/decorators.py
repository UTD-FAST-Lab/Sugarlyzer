import logging
from typing import Callable

logger = logging.getLogger(__name__)


def log_all_params_and_return(func: Callable):
    def wrapper(*args, **kwargs):
        ret = func(*args, **kwargs)
        logger.debug(f"Called a function {str(func)} with args {args} and kwargs {kwargs}, and it returned {ret}")
        return ret
    return wrapper
