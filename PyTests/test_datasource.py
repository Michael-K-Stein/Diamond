import os
import pytest
from common import get_test_resources_dir
from pydia import DataSource


def test_create_empty_datasource():
    data_source = DataSource()
    assert data_source


def test_create_datasource_from_pdb():
    file_path = os.path.join(get_test_resources_dir(), "ntdll.dll")
    data_source = DataSource(file_path)
    assert data_source
