import os
from pydia import DataSource


def get_test_resources_dir():
    return os.path.join(os.path.dirname(__file__), "..", "CTests", "Resources")


def get_ntdll_datasource():
    return DataSource(os.path.join(get_test_resources_dir(), "ntdll.dll"))


def get_adhoc_test_file(test_file_name: str):
    return os.path.join(get_test_resources_dir(), "AdHoc", "out", test_file_name)
