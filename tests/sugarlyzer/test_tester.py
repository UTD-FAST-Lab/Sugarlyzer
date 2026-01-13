import pytest
from src.sugarlyzer.Tester import Tester

"""
Config structure: [(config_name, option), (config_name2, option2)]

"""

@pytest.fixture
def tester():
    return Tester(tool="testTool", program="testProgram", baselines=False, no_recommended_space=False)


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



    # 2 dup 1 dif
    def test_one_fill_incomplete_config_progs(self, tester):
        alarms = [
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 42,
                "message": "use-after-free",
                "configuration": [("config_bool", "y"), ("config_num", "2"), ("config_str", "config1")]
            },
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 42,
                "message": "use-after-free",
                "configuration": [("config_bool", "y"), ("config_num", "3"), ("config_str", "config1")]
            },
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 41,
                "message": "double-free",
                "configuration": [("config_bool", "y"), ("config_num", "3"), ("config_str", "config2")]
            }
        ]

        config_prog_counts = tester.postprocess_alarm_configs(alarms)
        key1 = ('/path/to/file.txt', alarms[0]['input_line'], alarms[0]['message'])
        key2 = ('/path/to/file.txt', alarms[2]['input_line'], alarms[2]['message'])

        assert len(config_prog_counts) == 2
        assert key1 in config_prog_counts
        assert key2 in config_prog_counts

        prog1 = config_prog_counts[key1]
        prog2 = config_prog_counts[key2]

        assert prog1 == [3, 2]
        assert prog2 == [3, 3]


    # 3 dup 3 dif
    def test_multiple_fill_incomplete_config_progs(self, tester):
        alarms = [
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 42,
                "message": "use-after-free",
                "configuration": [("config_bool", "y"), ("config_num", "2"), ("config_str", "config1")]
            },
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 42,
                "message": "use-after-free",
                "configuration": [("config_bool", "y"), ("config_num", "3"), ("config_str", "config1")]
            },
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 42,
                "message": "use-after-free",
                "configuration": [("config_bool", "n"), ("config_num", "3"), ("config_str", "config1")]
            },
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 41,
                "message": "double-free",
                "configuration": [("config_bool", "y"), ("config_num", "3"), ("config_str", "config2")]
            },
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 40,
                "message": "unused variable",
                "configuration": [("config_bool", "y"), ("config_num", "3"), ("config_str", "config2")]
            },
            {
                "input_file": "/path/to/123.config/file.txt",
                "input_line": 39,
                "message": "bad code",
                "configuration": [("config_bool", "y"), ("config_num", "3"), ("config_str", "config2")]
            }
        ]

        config_prog_counts = tester.postprocess_alarm_configs(alarms)
        key1 = ('/path/to/file.txt', alarms[0]['input_line'], alarms[0]['message'])
        key2 = ('/path/to/file.txt', alarms[3]['input_line'], alarms[3]['message'])
        key3 = ('/path/to/file.txt', alarms[4]['input_line'], alarms[4]['message'])
        key4 = ('/path/to/file.txt', alarms[5]['input_line'], alarms[5]['message'])

        assert len(config_prog_counts) == 4
        assert key1 in config_prog_counts
        assert key2 in config_prog_counts

        prog1 = config_prog_counts[key1]
        prog2 = config_prog_counts[key2]
        prog3 = config_prog_counts[key3]
        prog4 = config_prog_counts[key4]

        assert prog1 == [3, 2, 1]
        assert prog2 == [3, 3, 3]
        assert prog3 == [3, 3, 3]
        assert prog3 == [3, 3, 3]
        assert prog4 == [3, 3, 3]

    def test_one_average_config_prog(self, tester):
        config_progs = {
            "Alarm1": [50, 40, 35, 30, 30],
        }
        averages = tester.get_avg_config_per_occurence(config_progs)
        assert len(averages) == 5
        assert averages == [50, 40, 35, 30, 30]

    def test_multiple_average_config_prog(self, tester):
        config_progs = {
            "Alarm1": [50, 40, 35, 30, 30],
            "Alarm2": [50, 40, 30, 30, 30],
            "Alarm3": [50, 40, 40, 40, 40],
            "Alarm4": [50, 50, 50, 50, 50],
        }
        averages = tester.get_avg_config_per_occurence(config_progs)
        assert len(averages) == 5
        assert averages == [50.0, 42.5, 38.75, 37.5, 37.5]

