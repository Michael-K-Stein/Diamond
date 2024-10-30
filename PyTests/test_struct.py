from time import sleep
import pytest
from common import get_ntdll_datasource
from pydia import DataSource


def test_find_struct():
    data_source = get_ntdll_datasource()
    assert data_source
    struct = data_source.get_struct("_KUSER_SHARED_DATA")
    assert struct


def test_hashing():
    # Currently, this crashes on an assertion regarding BaseType in hashing
    data_source = get_ntdll_datasource()
    struct = data_source.get_struct("_KUSER_SHARED_DATA")
    assert hash(struct)


def test_enum_members_and_hash():
    # Currently, this crashes on an assertion regarding BaseType in hashing
    data_source = get_ntdll_datasource()
    struct = data_source.get_struct("_KUSER_SHARED_DATA")
    sleep(0.1)
    for member in list(struct.enumerate_members()):
        print(member.get_name())
        assert hash(member), "Hash expected to not be 0 !"
