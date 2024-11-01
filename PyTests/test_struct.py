from time import sleep
import pytest
from common import get_adhoc_test_file, get_ntdll_datasource
import pydia
from pydia import DataSource


def test_find_struct():
    data_source = get_ntdll_datasource()
    assert data_source
    struct = data_source.get_struct("_KUSER_SHARED_DATA")
    assert struct


def test_hashing():
    data_source = get_ntdll_datasource()
    struct = data_source.get_struct("_KUSER_SHARED_DATA")
    assert hash(struct)


def test_check_simple_struct_member_attributes():
    """
    // This is the original code of this struct
    typedef struct MyCoolStruct_s
    {
        uint8_t MyUint8;
        uint16_t MyUint16;
        uint32_t MyUint32;
        uint64_t MyUint64;

    } MyCoolStruct;
    """
    data_source = DataSource(get_adhoc_test_file("my_structs.pdb"))
    assert data_source
    struct_name = "MyCoolStruct_s"
    struct_member_names = ["MyUint8", "MyUint16", "MyUint32", "MyUint64"]
    struct = data_source.get_struct(struct_name)
    assert struct
    assert struct.get_name() == struct_name
    for i, member in enumerate(struct.enumerate_members()):
        assert member
        assert member.get_name() == struct_member_names[i]
        assert member.get_access() == pydia.AccessModifier.Public
        assert member.is_const() == False
        assert member.is_volatile() == False
        assert member.get_data_kind() == pydia.DataKind.Member
        assert member.get_location_type() == pydia.LocationType.ThisRel


def test_check_volatile_struct_member_attributes():
    """
    // This is the original code of this struct
    typedef struct MyVolatileStruct_s
    {
        volatile char Member1;
        volatile uint64_t Member2;
        wchar_t* volatile Member3;
        volatile int Member4[4];

    } MyVolatileStruct;
    """
    data_source = DataSource(get_adhoc_test_file("my_structs.pdb"))
    assert data_source
    struct_name = "MyVolatileStruct_s"
    struct = data_source.get_struct(struct_name)
    assert struct
    assert struct.get_name() == struct_name
    for member in struct.enumerate_members():
        assert member
        assert member.is_volatile() == False
        if isinstance(member.get_type(), pydia.Array):
            assert member.get_type().get_type().is_volatile() == True
        else:
            assert member.get_type().is_volatile() == True


def test_packed_struct():
    """
    // This is the original code of this struct

    #pragma pack(push, 1)
    typedef struct MyPackedStruct_s
    {
        char Member1;
        char Member2;
        char Member3;
        uint32_t Member4;
        uint64_t Member5;
        uint16_t Member6;
        int8_t Member7;

    } MyPackedStruct;
    #pragma pack(pop)

    """
    data_source = DataSource(get_adhoc_test_file("my_structs.pdb"))
    assert data_source
    struct_name = "MyPackedStruct_s"
    struct = data_source.get_struct(struct_name)
    assert struct
    assert struct.get_name() == struct_name
    assert struct.is_packed() == True  # Why does this fail???


def test_structs_are_equal():
    data_source_a = DataSource(get_adhoc_test_file("equal_structs_a.pdb"))
    data_source_b = DataSource(get_adhoc_test_file("equal_structs_b.pdb"))
    assert data_source_a
    assert data_source_b
    for internal_struct_name in [
        "FirstStruct",
        "SecondStruct",
    ]:
        struct_name = f"{internal_struct_name}_s"
        struct_a = data_source_a.get_struct(struct_name)
        assert struct_a
        struct_b = data_source_b.get_struct(struct_name)
        assert struct_b
        assert hash(struct_a) == hash(struct_b)


def test_enum_members_and_hash():
    # Currently, this crashes on an assertion regarding BaseType in hashing
    data_source = get_ntdll_datasource()
    struct = data_source.get_struct("_KUSER_SHARED_DATA")
    for member in list(struct.enumerate_members()):
        assert hash(member), "Hash expected to not be 0 !"
