import argparse
import copy
import functools
import importlib
import json
import logging
import multiprocessing
import os
import shutil
import subprocess
import tempfile
import time
import sys
from pathlib import Path
from tempfile import NamedTemporaryFile
from typing import Iterable, List, Dict, Any, Tuple


rese = []
found = False
c = {}
with open(sys.argv[1],'r') as res:
    for l in res.readlines():
        l = l.lstrip().rstrip()
        if l.startswith("W [") or l.startswith('- W ['):
            found = True
            c['err'] = l
        elif found:
            found = False
            c['msg'] = l
            rese.append(c)
            c = {}
with open(sys.argv[1] + ".json",'w') as out:
    json.dump(rese, out, indent=3)
