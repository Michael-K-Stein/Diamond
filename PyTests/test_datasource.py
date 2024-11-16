import os
import pytest
from common import get_test_resources_dir
from pydia import DataSource, Error


def test_create_empty_datasource():
    with pytest.raises(TypeError) as e_info:
        data_source = DataSource()


def test_create_datasource_from_nonexistant_file():
    with pytest.raises(Error) as e_info:
        data_source = DataSource("$$THIS FILE NAME~#@!@# DOES NOT EXIST")


def test_create_datasource_from_pdb():
    file_path = os.path.join(get_test_resources_dir(), "ntdll.dll")
    data_source = DataSource(file_path)
    assert data_source
