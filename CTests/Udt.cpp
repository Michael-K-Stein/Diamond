#include "pch.h"
// pch.h MUST be before CppUnitTest.h
#include "Common.h"
#include "CppUnitTest.h"

#include "DiaDataSource.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Udt
{
TEST_CLASS(Dependencies)
{
public:
    TEST_METHOD(AllDependendsOnTypesFound)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const std::set<std::wstring> dependencyTypeNames = {L"_LIST_ENTRY", L"_LDRP_CSLIST", L"_LDR_DDAG_STATE", L"_SINGLE_LIST_ENTRY"};

        const auto types                                 = dataSource.getStruct("_LDR_DDAG_NODE").queryDependsOnTypes();
        std::vector<std::wstring> typeNames;
        std::transform(types.begin(), types.end(), std::back_inserter(typeNames), [](const dia::UserDefinedType& type) { return type.getName(); });

        for (const auto& dependencyName : typeNames)
        {
            Assert::IsTrue(dependencyTypeNames.find(dependencyName) != dependencyTypeNames.end(), L"An unexpected dependency was found!");
        }

        for (const auto& dependencyName : dependencyTypeNames)
        {
            Assert::IsTrue(std::find(typeNames.begin(), typeNames.end(), dependencyName) != typeNames.end(),
                           L"An expected dependency was not found!");
        }
    }

    TEST_METHOD(AllForwardDependendsOnTypesFound)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(LOCAL_NTDLL_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const std::set<std::wstring> dependencyTypeNames = {L"_LDR_SERVICE_TAG_RECORD"};

        const auto types                                 = dataSource.getStruct("_LDR_DDAG_NODE").queryDependsOnForwardTypes();
        std::vector<std::wstring> typeNames;
        std::transform(types.begin(), types.end(), std::back_inserter(typeNames), [](const dia::UserDefinedType& type) { return type.getName(); });

        for (const auto& dependencyName : typeNames)
        {
            Assert::IsTrue(dependencyTypeNames.find(dependencyName) != dependencyTypeNames.end(), L"An unexpected dependency was found!");
        }

        for (const auto& dependencyName : dependencyTypeNames)
        {
            Assert::IsTrue(std::find(typeNames.begin(), typeNames.end(), dependencyName) != typeNames.end(),
                           L"An expected dependency was not found!");
        }
    }
};
}  // namespace Udt