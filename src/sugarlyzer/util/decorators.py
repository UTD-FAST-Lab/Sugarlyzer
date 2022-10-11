import logging
from typing import Callable

logger = logging.getLogger(__name__)


def log_all_params(func: Callable):
    def wrapper(*args, **kwargs):
        logger.debug(f"Called a function {str(func)} with args {args} and kwargs {kwargs}")
        return func(*args, **kwargs)

    return wrapper
