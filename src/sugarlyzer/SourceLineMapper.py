from src.sugarlyzer.models.Alarm import VariabilityAlarm, Alarm


class SourceLineMapper:
    @classmethod
    def map_source_line(cls, alarm: Alarm) -> VariabilityAlarm:
        """
        Given an alarm, map it back to original source and associate it with conditionals
        :param alarm: The alarm to map.
        :return: A VariabilityAlarm (i.e., an alarm with an associated conditional)
        """
        pass
