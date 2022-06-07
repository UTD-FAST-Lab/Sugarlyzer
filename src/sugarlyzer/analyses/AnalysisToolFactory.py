from src.sugarlyzer.analyses.AbstractTool import AbstractTool
from src.sugarlyzer.readers.AbstractTool import AbstractReader
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

        reader: AbstractReader = ReaderFactory.get_reader(tool)
        pass
