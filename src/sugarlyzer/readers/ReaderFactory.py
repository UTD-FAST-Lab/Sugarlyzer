from src.sugarlyzer.readers.AbstractReader import AbstractReader
from src.sugarlyzer.readers.ClangReader import ClangReader


class ReaderFactory:

    @classmethod
    def get_reader(cls, tool) -> AbstractReader:
        """
        Given the name of a tool, return the appropriate reader.
        :param tool: The name of the tool.
        :return: The reader.
        """
        match tool.lower():
            case "clang": return ClangReader()
