from src.sugarlyzer.analyses.AbstractTool import AbstractTool


class TestTool(AbstractTool):

    def __init__(self):
        self.reader = None

    def analyze(self, file: str) -> str:
        print(f"Analyzing {file}")
        return file
