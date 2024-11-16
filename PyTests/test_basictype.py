
import os
import pytest
from common import get_ntdll_datasource, get_test_resources_dir
import pydia
from pydia import DataSource, SymTag


def test_basic_type_enum():
    data_source = get_ntdll_datasource()
    base_types = data_source.get_symbols(SymTag.BaseType)
    assert base_types
    for export in base_types:
        assert isinstance(export, pydia.BaseType)
        assert isinstance(export.get_base_type(), pydia.BasicType)