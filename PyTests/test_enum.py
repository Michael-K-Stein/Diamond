import os
import pytest
from common import get_ntdll_datasource, get_test_resources_dir
from pydia import DataSource


def test_find_enum():
    data_source = get_ntdll_datasource()
    pool_type_enum = data_source.get_enum("_POOL_TYPE")
    assert pool_type_enum
    assert pool_type_enum.get_name() == "_POOL_TYPE"
