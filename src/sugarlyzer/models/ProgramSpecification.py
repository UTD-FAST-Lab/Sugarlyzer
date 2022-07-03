import subprocess
from typing import Optional, Dict, Any


class ProgramSpecification:

    def __init__(self, build_script: str,
                 source_location: str,
                 variable_specification: Optional[Dict[str, Any]] = None):
        self.build_script = build_script
        self.source_location = source_location
        self.variable_specification = variable_specification

    def download(self) -> int:
        """
        Runs the script to obtain the program's source code.
        :return: The return code
        """
        ps = subprocess.run(self.build_script)
        return ps.returncode
