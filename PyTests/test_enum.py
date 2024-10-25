import os
import pytest
from common import get_ntdll_datasource, get_test_resources_dir
from pydia import DataSource


def test_find_enum():
    data_source = get_ntdll_datasource()
    pool_type_enum = data_source.get_enum("_POOL_TYPE")
    assert pool_type_enum
    assert pool_type_enum.get_name() == "_POOL_TYPE"


def test_list_enum_value_names():
    data_source = get_ntdll_datasource()
    pool_type_enum = data_source.get_enum("_POOL_TYPE")
    EXPECTED_VALUE_NAMES = [
        "NonPagedPool",
        "NonPagedPoolExecute",
        "PagedPool",
        "NonPagedPoolMustSucceed",
        "DontUseThisType",
        "NonPagedPoolCacheAligned",
        "PagedPoolCacheAligned",
        "NonPagedPoolCacheAlignedMustS",
        "MaxPoolType",
        "NonPagedPoolBase",
        "NonPagedPoolBaseMustSucceed",
        "NonPagedPoolBaseCacheAligned",
        "NonPagedPoolBaseCacheAlignedMustS",
        "NonPagedPoolSession",
        "PagedPoolSession",
        "NonPagedPoolMustSucceedSession",
        "DontUseThisTypeSession",
        "NonPagedPoolCacheAlignedSession",
        "PagedPoolCacheAlignedSession",
        "NonPagedPoolCacheAlignedMustSSession",
        "NonPagedPoolNx",
        "NonPagedPoolNxCacheAligned",
        "NonPagedPoolSessionNx",
    ]

    assert EXPECTED_VALUE_NAMES == list(
        value.get_name() for value in pool_type_enum.get_values()
    )


def test_list_enum_value_values():
    data_source = get_ntdll_datasource()
    pool_type_enum = data_source.get_enum("_POOL_TYPE")
    EXPECTED_VALUE_VALUES = [
        0x0,
        0x0,
        0x1,
        0x2,
        0x3,
        0x4,
        0x5,
        0x6,
        0x7,
        0x0,
        0x2,
        0x4,
        0x6,
        0x20,
        0x21,
        0x22,
        0x23,
        0x24,
        0x25,
        0x26,
        0x200,
        0x204,
        0x220,
    ]

    assert EXPECTED_VALUE_VALUES == list(
        value.get_value() for value in pool_type_enum.get_values()
    )