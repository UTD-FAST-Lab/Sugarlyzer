import pytest
import re
from src.sugarlyzer.Tester import Tester

"""
Config structure: [(config_name, option), (config_name2, option2)]

"""

@pytest.fixture
def tester():
    return Tester(tool="testTool", program="testProgram", baselines=False, no_recommended_space=False, test_mode=True)


class TestPostprocessAlarmConfigs:
    def test_normalize_file_path_removes_config_number(self, tester):
        alarms = [
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 42,
                "message": "error on line 1",
                "configuration": [("config_bool", "y"), ("config_num", "2"), ("config_str", "123.4.5")]
            }
        ]
        tester.postprocess_alarm_configs(alarms)
        key = list(tester.alarm_config_map.keys())[0]
        assert "/123.config/" not in key[0]
        assert key == ("/path/to/file.txt", 42, "error on line 1")

    def test_storing_alarm_config_options(self, tester):
        alarms = [
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 42,
                "message": "error on line 1",
                "configuration": [("config_bool", "y"), ("config_num", "2"), ("config_str", "config1")]
            }
        ]
        tester.postprocess_alarm_configs(alarms)
        key = ('/path/to/file.txt', alarms[0]['input_line'], alarms[0]['message'])

        assert key in tester.alarm_config_map
        value = tester.alarm_config_map[key]
        assert value == [("config_bool", "y"), ("config_num", "2"), ("config_str", "config1")] 

    def test_one_duplicate_config_intersection(self, tester):
        alarms = [
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 42,
                "message": "error on line 1",
                "configuration": [("config_bool", "y"), ("config_num", "2"), ("config_str", "config1")]
            },
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 42,
                "message": "error on line 1",
                "configuration": [("config_bool", "y"), ("config_num", "3"), ("config_str", "config2")]
            }
        ]
        tester.postprocess_alarm_configs(alarms)
        key = ('/path/to/file.txt', alarms[0]['input_line'], alarms[0]['message'])

        assert len(tester.alarm_config_map) == 1
        assert key in tester.alarm_config_map
        value = tester.alarm_config_map[key]
        assert value == [("config_bool", "y")] 

    def test_none_duplicate_config_intersection(self, tester):
        alarms = [
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 42,
                "message": "error on line 1",
                "configuration": [("config_bool", "y"), ("config_num", "2"), ("config_str", "config1")]
            },
            {
                "input_file": "/path/to/123.config/file2.txt",
                "input_line": 42,
                "message": "error on line 1",
                "configuration": [("config_bool", "y"), ("config_num", "3"), ("config_str", "config2")]
            }
        ]
        tester.postprocess_alarm_configs(alarms)
        key1 = ('/path/to/file.txt', alarms[0]['input_line'], alarms[0]['message'])
        key2 = ('/path/to/file2.txt', alarms[1]['input_line'], alarms[1]['message'])

        assert len(tester.alarm_config_map) == 2
        assert key1 in tester.alarm_config_map
        assert key2 in tester.alarm_config_map
        assert tester.alarm_config_map[key1] == [("config_bool", "y"), ("config_num", "2"), ("config_str", "config1")]
        assert tester.alarm_config_map[key2] == [("config_bool", "y"), ("config_num", "3"), ("config_str", "config2")]



    def test_many_duplicate_config_intersection(self, tester):
        alarms = [
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 42,
                "message": "error on line 1",
                "configuration": [("config_bool", "y"), ("config_num", "2"), ("config_str", "config1")]
            },
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 42,
                "message": "error on line 1",
                "configuration": [("config_bool", "y"), ("config_num", "3"), ("config_str", "config1")]
            },
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 42,
                "message": "error on line 1",
                "configuration": [("config_bool", "y"), ("config_num", "3"), ("config_str", "config2")]
            }
        ]
        tester.postprocess_alarm_configs(alarms)
        key = ('/path/to/file.txt', alarms[0]['input_line'], alarms[0]['message'])

        assert len(tester.alarm_config_map) == 1
        assert key in tester.alarm_config_map
        value = tester.alarm_config_map[key]
        assert value == [("config_bool", "y")] 


