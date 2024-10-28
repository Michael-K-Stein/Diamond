import pytest
from common import get_ntdll_datasource
from pydia import DataSource


def test_find_struct():
    data_source = get_ntdll_datasource()
    assert data_source
    struct = data_source.get_struct("_KUSER_SHARED_DATA")
    assert struct


def test_enum_members_and_hash():
    # Currently, this crashes on an assertion regarding BaseType in hashing
    data_source = get_ntdll_datasource()
    struct = data_source.get_struct("_KUSER_SHARED_DATA")
    first_member = list(struct.enumerate_members())[0]
    hash(first_member)