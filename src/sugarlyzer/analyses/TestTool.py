from src.sugarlyzer.analyses.AbstractTool import AbstractTool


class TestTool(AbstractTool):
    def analyze(self, file: str) -> str:
        raise NotImplementedError
