#include "pch.h"
// pch.h MUST be before CppUnitTest.h
#include "Common.h"
#include "CppUnitTest.h"

#include <DiaDataSource.h>
#include <SymbolTypes/DiaPointer.h>

#define SIMPLE_HASHABLES_PDB_FILE_PATH CTESTS_ADHOC_RESOURCES_DIR L"simple_hashables.pdb"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Symbol
{
TEST_CLASS(Symbol)
{
public:
    TEST_METHOD(Equivalance)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(SIMPLE_HASHABLES_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const AnyString structName      = "IntHash_s";
        const AnyString otherStructName = "UintHash_s";

        const auto originalSymbol       = dataSource.getStruct(structName);
        const auto otherSymbol          = dataSource.getStruct(otherStructName);

        Assert::IsTrue(dataSource.getSession().areSymbolsEquivalent(originalSymbol, originalSymbol));
        Assert::IsTrue(dataSource.getSession().areSymbolsEquivalent(otherSymbol, otherSymbol));
        Assert::IsFalse(dataSource.getSession().areSymbolsEquivalent(originalSymbol, otherSymbol));
    }

    TEST_METHOD(FindByFQID)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(SIMPLE_HASHABLES_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const AnyString structName = "IntHash_s";

        const auto originalSymbol  = dataSource.getStruct(structName);
        const auto symId           = originalSymbol.getSymIndexId();

        const auto foundSymbol     = dataSource.getSymbolById(symId);

        Assert::AreEqual(originalSymbol.calcHash(), foundSymbol.calcHash());
        Assert::AreEqual(originalSymbol.getSymTag(), foundSymbol.getSymTag());
        Assert::AreEqual(originalSymbol.getSymIndexId(), foundSymbol.getSymIndexId());
        Assert::IsTrue(dataSource.getSession().areSymbolsEquivalent(foundSymbol, foundSymbol));
        Assert::IsTrue(dataSource.getSession().areSymbolsEquivalent(originalSymbol, originalSymbol));
        Assert::IsTrue(dataSource.getSession().areSymbolsEquivalent(originalSymbol, foundSymbol));
    }

    TEST_METHOD(FindByFQIDAndCheckEquiv)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(SIMPLE_HASHABLES_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const AnyString structName      = "IntHash_s";
        const AnyString otherStructName = "UintHash_s";

        const auto originalSymbol       = dataSource.getStruct(structName);
        const auto otherSymbol          = dataSource.getStruct(otherStructName);

        const auto symId                = originalSymbol.getSymIndexId();
        const auto otherSymId           = otherSymbol.getSymIndexId();
        Assert::AreNotEqual(symId, otherSymId);

        const auto foundSymbol      = dataSource.getSymbolById(symId);
        const auto otherFoundSymbol = dataSource.getSymbolById(otherSymId);

        Assert::AreEqual(originalSymbol.calcHash(), foundSymbol.calcHash());
        Assert::AreEqual(originalSymbol.getSymTag(), foundSymbol.getSymTag());
        Assert::AreEqual(originalSymbol.getSymIndexId(), foundSymbol.getSymIndexId());
        Assert::IsTrue(dataSource.getSession().areSymbolsEquivalent(foundSymbol, foundSymbol));
        Assert::IsTrue(dataSource.getSession().areSymbolsEquivalent(originalSymbol, originalSymbol));
        Assert::IsTrue(dataSource.getSession().areSymbolsEquivalent(originalSymbol, foundSymbol));

        Assert::AreEqual(otherSymbol.calcHash(), otherFoundSymbol.calcHash());
        Assert::AreEqual(otherSymbol.getSymTag(), otherFoundSymbol.getSymTag());
        Assert::AreEqual(otherSymbol.getSymIndexId(), otherFoundSymbol.getSymIndexId());
        Assert::IsTrue(dataSource.getSession().areSymbolsEquivalent(otherFoundSymbol, otherFoundSymbol));
        Assert::IsTrue(dataSource.getSession().areSymbolsEquivalent(otherSymbol, otherSymbol));
        Assert::IsTrue(dataSource.getSession().areSymbolsEquivalent(otherSymbol, otherFoundSymbol));

        Assert::AreNotEqual(originalSymbol.calcHash(), otherSymbol.calcHash());
        Assert::AreNotEqual(originalSymbol.getSymTag(), otherSymbol.getSymTag());
        Assert::AreEqual(symId, originalSymbol.getSymIndexId());
        Assert::AreEqual(otherSymId, otherSymbol.getSymIndexId());
        Assert::AreNotEqual(originalSymbol.getSymIndexId(), otherSymbol.getSymIndexId());
        Assert::IsFalse(dataSource.getSession().areSymbolsEquivalent(originalSymbol, otherSymbol));

        Assert::AreNotEqual(foundSymbol.calcHash(), otherSymbol.calcHash());
        Assert::AreNotEqual(foundSymbol.getSymTag(), otherSymbol.getSymTag());
        Assert::AreNotEqual(foundSymbol.getSymIndexId(), otherSymbol.getSymIndexId());
        Assert::IsFalse(dataSource.getSession().areSymbolsEquivalent(foundSymbol, otherSymbol));

        Assert::AreNotEqual(originalSymbol.calcHash(), otherFoundSymbol.calcHash());
        Assert::AreNotEqual(originalSymbol.getSymTag(), otherFoundSymbol.getSymTag());
        Assert::AreNotEqual(originalSymbol.getSymIndexId(), otherFoundSymbol.getSymIndexId());
        Assert::IsFalse(dataSource.getSession().areSymbolsEquivalent(originalSymbol, otherFoundSymbol));

        Assert::AreNotEqual(foundSymbol.calcHash(), otherFoundSymbol.calcHash());
        Assert::AreNotEqual(foundSymbol.getSymTag(), otherFoundSymbol.getSymTag());
        Assert::AreNotEqual(foundSymbol.getSymIndexId(), otherFoundSymbol.getSymIndexId());
        Assert::IsFalse(dataSource.getSession().areSymbolsEquivalent(foundSymbol, otherFoundSymbol));
    }
};
}  // namespace Symbol
