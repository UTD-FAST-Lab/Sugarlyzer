from src.sugarlyzer.readers.AbstractTool import AbstractReader


class ReaderFactory:

    @classmethod
    def get_reader(cls, tool) -> AbstractReader:
        """
        Given the name of a tool, return the appropriate reader.
        :param tool: The name of the tool.
        :return: The reader.
        """
        pass
