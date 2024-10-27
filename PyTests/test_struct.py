import pytest
from common import get_ntdll_datasource
from pydia import DataSource


def test_find_struct():
    data_source = get_ntdll_datasource()
    assert data_source
    struct = data_source.get_struct("_KERNEL_USER_TIMES")
    assert struct
