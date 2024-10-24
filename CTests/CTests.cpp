#include "pch.h"
// pch.h MUST be before CppUnitTest.h
#include "CppUnitTest.h"

#include "DiaDataSource.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define CTESTS_RESOURCES_DIR L".\\..\\..\\CTests\\Resources\\"
#define LOCAL_NTDLL_PDB_FILE_PATH CTESTS_RESOURCES_DIR L"ntdll.pdb"
#define LOCAL_NTDLL_DLL_FILE_PATH CTESTS_RESOURCES_DIR L"ntdll.dll"

#define STRUCTURED_FILE_TREE_NTDLL_DIR CTESTS_RESOURCES_DIR L"_NTDLL\\"
#define STRUCTURED_FILE_TREE_NTDLL_DLL_FILE_PATH STRUCTURED_FILE_TREE_NTDLL_DIR L"ntdll.dll"
#define STRUCTURED_FILE_TREE_NTDLL_PDB_FILE_PATH STRUCTURED_FILE_TREE_NTDLL_DIR L"ntdll.pdb\\FB228B943D718A0426415A200E27CB761\\ntdll.pdb"

namespace CTests
{
TEST_CLASS(DataSource)
{
public:
    TEST_METHOD(PdbLoadedIsPdbLoaded)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        Assert::AreEqual(dataSource.getLoadedPdbFile(), pdbFilePath);
    }

    TEST_METHOD(PdbLoadedIsPdbLoaded_RelPath)
    {
        const std::wstring pdbFilePath = LOCAL_NTDLL_PDB_FILE_PATH;
        dia::DataSource dataSource{pdbFilePath};
        Assert::AreEqual(dataSource.getLoadedPdbFile(), std::filesystem::absolute(pdbFilePath).wstring());
    }

    TEST_METHOD(ExeLoadFindsNeighborPdb)
    {
        const std::wstring dllFilePath = LOCAL_NTDLL_DLL_FILE_PATH;
        dia::DataSource dataSource{dllFilePath};
        Assert::AreEqual(dataSource.getLoadedPdbFile(), std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH).wstring());
    }

    TEST_METHOD(ExeLoadFindsPdbInStructuredSymstore)
    {
        const std::wstring dllFilePath = STRUCTURED_FILE_TREE_NTDLL_DLL_FILE_PATH;
        dia::DataSource dataSource{};
        dataSource.addSymtoreDirectory(STRUCTURED_FILE_TREE_NTDLL_DIR);
        dataSource.loadDataForExe(dllFilePath);
        Assert::AreEqual(dataSource.getLoadedPdbFile(), std::filesystem::absolute(STRUCTURED_FILE_TREE_NTDLL_PDB_FILE_PATH).wstring());
    }
};

TEST_CLASS(FindStructs)
{
public:
    TEST_METHOD(FindSimpleStruct)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const auto unicodeStringStructSymbol = dataSource.getStruct(L"_UNICODE_STRING");
        Assert::AreEqual(std::wstring{unicodeStringStructSymbol.getName()}, std::wstring{L"_UNICODE_STRING"});
    }

    TEST_METHOD(DontFindFakeStruct)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};

        Assert::ExpectException<dia::StructNotFound>(
            [&]
            {
                const auto unicodeStringStructSymbol = dataSource.getStruct(L"_UNICODE_STRING_df9ed8fa_8973_4e6c_950a_dcad266c3b78");
                UNREFERENCED_PARAMETER(unicodeStringStructSymbol);
            });
    }

    TEST_METHOD(ProperlyOrderedStructMembers)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const auto unicodeStringStructSymbol = dataSource.getStruct(L"_UNICODE_STRING");
        std::vector<dia::DataMember> members{};
        for (const auto& member : unicodeStringStructSymbol.enumerateMembers())
        {
            members.push_back(member);
        }

        Assert::AreEqual(std::wstring{L"Length"}, std::wstring{members[0].getFieldName()});
        Assert::AreEqual(std::wstring{L"MaximumLength"}, std::wstring{members[1].getFieldName()});
        Assert::AreEqual(std::wstring{L"Buffer"}, std::wstring{members[2].getFieldName()});
    }

    TEST_METHOD(ProperStructMemberTypes)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const auto unicodeStringStructSymbol = dataSource.getStruct(L"_UNICODE_STRING");
        std::vector<dia::DataMember> members{};
        for (const auto& member : unicodeStringStructSymbol.enumerateMembers())
        {
            members.push_back(member);
        }

        Assert::AreEqual(std::wstring{L"Length"}, std::wstring{members[0].getFieldName()});
        Assert::AreEqual(std::wstring{L"USHORT"}, std::wstring{members[0].getFieldCType().getTypeName()});

        Assert::AreEqual(std::wstring{L"MaximumLength"}, std::wstring{members[1].getFieldName()});
        Assert::AreEqual(std::wstring{L"USHORT"}, std::wstring{members[1].getFieldCType().getTypeName()});

        Assert::AreEqual(std::wstring{L"Buffer"}, std::wstring{members[2].getFieldName()});
        // PWSTR == WCHAR*
        Assert::AreEqual(std::wstring{L"WCHAR*"}, std::wstring{members[2].getFieldCType().getTypeName()});
    }

    TEST_METHOD(ProperStructMemberOffsets)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const auto unicodeStringStructSymbol = dataSource.getStruct(L"_UNICODE_STRING");
        std::vector<dia::DataMember> members{};
        for (const auto& member : unicodeStringStructSymbol.enumerateMembers())
        {
            members.push_back(member);
        }

        Assert::AreEqual(std::wstring{L"Length"}, std::wstring{members[0].getFieldName()});
        Assert::AreEqual(static_cast<LONG>(0), members[0].getOffset());

        Assert::AreEqual(std::wstring{L"MaximumLength"}, std::wstring{members[1].getFieldName()});
        Assert::AreEqual(static_cast<LONG>(sizeof(USHORT)), members[1].getOffset());

        Assert::AreEqual(std::wstring{L"Buffer"}, std::wstring{members[2].getFieldName()});
        // We use sizeof(void*) here for compatibility with x86, where this will be at offset 4 since there won't be any padding added before the
        // pointer.
        Assert::AreEqual(static_cast<LONG>(sizeof(void*)), members[2].getOffset());
    }

    TEST_METHOD(ProperStructMemberSizes)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const auto unicodeStringStructSymbol = dataSource.getStruct(L"_UNICODE_STRING");
        std::vector<dia::DataMember> members{};
        for (const auto& member : unicodeStringStructSymbol.enumerateMembers())
        {
            members.push_back(member);
        }

        Assert::AreEqual(std::wstring{L"Length"}, std::wstring{members[0].getFieldName()});
        Assert::AreEqual(static_cast<ULONGLONG>(sizeof(USHORT)), members[0].getFieldCType().getLength());

        Assert::AreEqual(std::wstring{L"MaximumLength"}, std::wstring{members[1].getFieldName()});
        Assert::AreEqual(static_cast<ULONGLONG>(sizeof(USHORT)), members[1].getFieldCType().getLength());

        Assert::AreEqual(std::wstring{L"Buffer"}, std::wstring{members[2].getFieldName()});
        // We use sizeof(void*) here for compatibility with x86, where this will be at offset 4 since there won't be any padding added before the
        // pointer.
        Assert::AreEqual(static_cast<ULONGLONG>(sizeof(void*)), members[2].getFieldCType().getLength());
    }

    TEST_METHOD(ProperStructTotalSize)
    {
        const auto roundTo             = [](unsigned int value, unsigned int roundTo) { return (value + (roundTo - 1)) & ~(roundTo - 1); };

        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const auto unicodeStringStructSymbol = dataSource.getStruct(L"_UNICODE_STRING");
        Assert::AreEqual(static_cast<ULONGLONG>(roundTo(sizeof(USHORT) + sizeof(USHORT) + sizeof(void*), sizeof(void*))),
                         unicodeStringStructSymbol.getLength());
    }
};
}  // namespace CTests
