#include "pch.h"
// pch.h MUST be before CppUnitTest.h
#include "Common.h"
#include "CppUnitTest.h"

#include "DiaDataSource.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Enum
{
TEST_CLASS(Decleration)
{
    TEST_METHOD(EnumName)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};

        const wchar_t* enumNames[] = {
            L"_POOL_TYPE",
            L"_EX_POOL_PRIORITY",
            L"_EX_GEN_RANDOM_DOMAIN",
            L"_FILE_INFORMATION_CLASS",
            L"_REG_NOTIFY_CLASS",
            L"DISPLAYCONFIG_SCANLINE_ORDERING",
            L"_FS_FILTER_SECTION_SYNC_TYPE",
        };

        for (const auto& enumName : enumNames)
        {
            const auto enumSymbol = dataSource.getEnum(AnyString{enumName});
            Assert::AreEqual(enumName, enumSymbol.getName().c_str());
        }
    }

    TEST_METHOD(EnumBaseType)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};

        const wchar_t* enumNames[] = {
            L"_POOL_TYPE",
            L"_EX_POOL_PRIORITY",
            L"_EX_GEN_RANDOM_DOMAIN",
            L"_FILE_INFORMATION_CLASS",
            L"_REG_NOTIFY_CLASS",
            L"DISPLAYCONFIG_SCANLINE_ORDERING",
            L"_FS_FILTER_SECTION_SYNC_TYPE",
        };

        for (const auto& enumName : enumNames)
        {
            const auto enumSymbol = dataSource.getEnum(AnyString{enumName});
            Assert::AreEqual(btInt, enumSymbol.getBaseType());
        }
    }

    TEST_METHOD(EnumBaseTypeLength)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};

        const wchar_t* enumNames[] = {
            L"_POOL_TYPE",
            L"_EX_POOL_PRIORITY",
            L"_EX_GEN_RANDOM_DOMAIN",
            L"_FILE_INFORMATION_CLASS",
            L"_REG_NOTIFY_CLASS",
            L"DISPLAYCONFIG_SCANLINE_ORDERING",
            L"_FS_FILTER_SECTION_SYNC_TYPE",
        };

        for (const auto& enumName : enumNames)
        {
            const auto enumSymbol = dataSource.getEnum(AnyString{enumName});
            Assert::AreEqual(sizeof(int32_t), enumSymbol.getLength());
        }
    }

    TEST_METHOD(EnumModifiers)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};

        const wchar_t* enumNames[] = {
            L"_POOL_TYPE",
            L"_EX_POOL_PRIORITY",
            L"_EX_GEN_RANDOM_DOMAIN",
            L"_FILE_INFORMATION_CLASS",
            L"_REG_NOTIFY_CLASS",
            L"DISPLAYCONFIG_SCANLINE_ORDERING",
            L"_FS_FILTER_SECTION_SYNC_TYPE",
        };

        for (const auto& enumName : enumNames)
        {
            const auto enumSymbol = dataSource.getEnum(AnyString{enumName});
            Assert::IsFalse(enumSymbol.getConstType());
            Assert::IsFalse(enumSymbol.getVolatileType());
            Assert::IsFalse(enumSymbol.getUnalignedType());
        }
    }
};

TEST_CLASS(Values)
{
public:
    TEST_METHOD(EnumValuesNames)
    {
        /*
        enum _POOL_TYPE : __int32
        {
            NonPagedPool = 0x0,
            NonPagedPoolExecute = 0x0,
            PagedPool = 0x1,
            NonPagedPoolMustSucceed = 0x2,
            DontUseThisType = 0x3,
            NonPagedPoolCacheAligned = 0x4,
            PagedPoolCacheAligned = 0x5,
            NonPagedPoolCacheAlignedMustS = 0x6,
            MaxPoolType = 0x7,
            NonPagedPoolBase = 0x0,
            NonPagedPoolBaseMustSucceed = 0x2,
            NonPagedPoolBaseCacheAligned = 0x4,
            NonPagedPoolBaseCacheAlignedMustS = 0x6,
            NonPagedPoolSession = 0x20,
            PagedPoolSession = 0x21,
            NonPagedPoolMustSucceedSession = 0x22,
            DontUseThisTypeSession = 0x23,
            NonPagedPoolCacheAlignedSession = 0x24,
            PagedPoolCacheAlignedSession = 0x25,
            NonPagedPoolCacheAlignedMustSSession = 0x26,
            NonPagedPoolNx = 0x200,
            NonPagedPoolNxCacheAligned = 0x204,
            NonPagedPoolSessionNx = 0x220,
        };
        */

        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};

        const auto enumSymbol                   = dataSource.getEnum("_POOL_TYPE");
        const std::vector<dia::Data> enumValues = enumSymbol.getValues();

        const wchar_t* expectedEnumValues[]     = {
            L"NonPagedPool",
            L"NonPagedPoolExecute",
            L"PagedPool",
            L"NonPagedPoolMustSucceed",
            L"DontUseThisType",
            L"NonPagedPoolCacheAligned",
            L"PagedPoolCacheAligned",
            L"NonPagedPoolCacheAlignedMustS",
            L"MaxPoolType",
            L"NonPagedPoolBase",
            L"NonPagedPoolBaseMustSucceed",
            L"NonPagedPoolBaseCacheAligned",
            L"NonPagedPoolBaseCacheAlignedMustS",
            L"NonPagedPoolSession",
            L"PagedPoolSession",
            L"NonPagedPoolMustSucceedSession",
            L"DontUseThisTypeSession",
            L"NonPagedPoolCacheAlignedSession",
            L"PagedPoolCacheAlignedSession",
            L"NonPagedPoolCacheAlignedMustSSession",
            L"NonPagedPoolNx",
            L"NonPagedPoolNxCacheAligned",
            L"NonPagedPoolSessionNx",
        };

        for (size_t i = 0; i < sizeof(expectedEnumValues) / sizeof(expectedEnumValues[0]); ++i)
        {
            const auto& expectedValue = expectedEnumValues[i];
            const auto& foundValue    = enumValues[i].getName();

            Assert::AreEqual(expectedValue, foundValue.c_str());
        }
    }

    TEST_METHOD(EnumValuesValue)
    {
        /*
        enum _POOL_TYPE : __int32
        {
            NonPagedPool = 0x0,
            NonPagedPoolExecute = 0x0,
            PagedPool = 0x1,
            NonPagedPoolMustSucceed = 0x2,
            DontUseThisType = 0x3,
            NonPagedPoolCacheAligned = 0x4,
            PagedPoolCacheAligned = 0x5,
            NonPagedPoolCacheAlignedMustS = 0x6,
            MaxPoolType = 0x7,
            NonPagedPoolBase = 0x0,
            NonPagedPoolBaseMustSucceed = 0x2,
            NonPagedPoolBaseCacheAligned = 0x4,
            NonPagedPoolBaseCacheAlignedMustS = 0x6,
            NonPagedPoolSession = 0x20,
            PagedPoolSession = 0x21,
            NonPagedPoolMustSucceedSession = 0x22,
            DontUseThisTypeSession = 0x23,
            NonPagedPoolCacheAlignedSession = 0x24,
            PagedPoolCacheAlignedSession = 0x25,
            NonPagedPoolCacheAlignedMustSSession = 0x26,
            NonPagedPoolNx = 0x200,
            NonPagedPoolNxCacheAligned = 0x204,
            NonPagedPoolSessionNx = 0x220,
        };
        */

        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};

        const auto enumSymbol                   = dataSource.getEnum("_POOL_TYPE");
        const std::vector<dia::Data> enumValues = enumSymbol.getValues();

        const LONG expectedEnumValues[]         = {
            0x0, 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x0, 0x2, 0x4, 0x6, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x200, 0x204, 0x220,
        };

        for (size_t i = 0; i < sizeof(expectedEnumValues) / sizeof(expectedEnumValues[0]); ++i)
        {
            const auto& expectedValue = expectedEnumValues[i];
            const auto& foundValue    = enumValues[i].getValue().lVal;

            Assert::AreEqual(expectedValue, foundValue);
        }
    }
};
}  // namespace Enum
