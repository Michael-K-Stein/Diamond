#include "pch.h"
// pch.h MUST be before CppUnitTest.h
#include "Common.h"
#include "CppUnitTest.h"

#include "DiaDataSource.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define STRUCTURED_FILE_TREE_NTDLL_DIR CTESTS_RESOURCES_DIR L"_NTDLL\\"
#define STRUCTURED_FILE_TREE_NTDLL_DLL_FILE_PATH STRUCTURED_FILE_TREE_NTDLL_DIR L"ntdll.dll"
#define STRUCTURED_FILE_TREE_NTDLL_PDB_FILE_PATH STRUCTURED_FILE_TREE_NTDLL_DIR L"ntdll.pdb\\FB228B943D718A0426415A200E27CB761\\ntdll.pdb"

namespace DataSource
{
TEST_CLASS(CtorAndLoad)
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

#if 0
    // Not yet properly implemented
    TEST_METHOD(ExeLoadFindsPdbInStructuredSymstore)
    {
        const std::wstring dllFilePath = STRUCTURED_FILE_TREE_NTDLL_DLL_FILE_PATH;
        dia::DataSource dataSource{};
        dataSource.addSymtoreDirectory(STRUCTURED_FILE_TREE_NTDLL_DIR);
        dataSource.loadDataForExe(dllFilePath);
        Assert::AreEqual(dataSource.getLoadedPdbFile(), std::filesystem::absolute(STRUCTURED_FILE_TREE_NTDLL_PDB_FILE_PATH).wstring());
    }
#endif
};
}  // namespace DataSource
