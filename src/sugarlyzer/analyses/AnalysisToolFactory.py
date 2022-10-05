from src.sugarlyzer.analyses.AbstractTool import AbstractTool
from src.sugarlyzer.analyses.Clang import Clang
from src.sugarlyzer.analyses.Infer import Infer
from src.sugarlyzer.analyses.TestTool import TestTool
from src.sugarlyzer.readers.AbstractReader import AbstractReader
from src.sugarlyzer.readers.ReaderFactory import ReaderFactory


class AnalysisToolFactory:

    # noinspection PyTypeChecker
    @classmethod
    def get_tool(cls, tool) -> AbstractTool:
        """
        Given the name of the tool, return the appropriate tool class.
        :param tool:
        :return:
        """

        match tool.lower():
            case "clang": return Clang()
            case "testtool": return TestTool()
            case "infer": return Infer()
            case _: raise ValueError(f"No tool for {tool}")
