#include "pch.h"
// pch.h MUST be before CppUnitTest.h
#include "Common.h"
#include "CppUnitTest.h"

#include <DiaDataSource.h>
#include <SymbolTypes/DiaPointer.h>

#define SIMPLE_HASHABLES_PDB_FILE_PATH CTESTS_ADHOC_RESOURCES_DIR L"simple_hashables.pdb"
#define COMPLEX_HASHABLES_PDB_FILE_PATH CTESTS_ADHOC_RESOURCES_DIR L"complex_hashables.pdb"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Hashing
{
TEST_CLASS(BaseTypes)
{
public:
    TEST_METHOD(HashBasicInts)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(SIMPLE_HASHABLES_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const AnyString structName = "IntHash_s";
        Assert::AreNotEqual(0uLL, dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(dataSource.getStruct(structName).calcHash(), dataSource.getStruct(structName).calcHash());
    }

    TEST_METHOD(HashBasicUints)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(SIMPLE_HASHABLES_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const AnyString structName = "UintHash_s";
        Assert::AreNotEqual(0uLL, dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(dataSource.getStruct(structName).calcHash(), dataSource.getStruct(structName).calcHash());
    }

    TEST_METHOD(HashBasicMixedStruct)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(SIMPLE_HASHABLES_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const AnyString structName = "MixedHash_s";
        Assert::AreNotEqual(0uLL, dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(dataSource.getStruct(structName).calcHash(), dataSource.getStruct(structName).calcHash());
    }

    TEST_METHOD(HashesAreSomewhatUnique)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(SIMPLE_HASHABLES_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const AnyString struct1Name = "IntHash_s";
        const AnyString struct2Name = "UintHash_s";
        const AnyString struct3Name = "MixedHash_s";
        Assert::AreNotEqual(dataSource.getStruct(struct1Name).calcHash(), dataSource.getStruct(struct2Name).calcHash());
        Assert::AreNotEqual(dataSource.getStruct(struct2Name).calcHash(), dataSource.getStruct(struct3Name).calcHash());
        Assert::AreNotEqual(dataSource.getStruct(struct3Name).calcHash(), dataSource.getStruct(struct1Name).calcHash());
    }

    TEST_METHOD(HashesAreDeterministic)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(SIMPLE_HASHABLES_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const AnyString struct1Name = "IntHash_s";
        const AnyString struct2Name = "UintHash_s";
        const AnyString struct3Name = "MixedHash_s";

        const auto capturedStruct1  = dataSource.getStruct(struct1Name);
        const auto capturedStruct2  = dataSource.getStruct(struct2Name);
        const auto capturedStruct3  = dataSource.getStruct(struct3Name);

        const auto firstStruct1Hash = dataSource.getStruct(struct1Name).calcHash();
        const auto firstStruct2Hash = dataSource.getStruct(struct2Name).calcHash();
        const auto firstStruct3Hash = dataSource.getStruct(struct3Name).calcHash();

        Assert::AreEqual(capturedStruct1.calcHash(), firstStruct1Hash);
        Assert::AreEqual(capturedStruct2.calcHash(), firstStruct2Hash);
        Assert::AreEqual(capturedStruct3.calcHash(), firstStruct3Hash);

        for (size_t i = 0; i < 0x1000; ++i)
        {
            const auto struct1Hash = dataSource.getStruct(struct1Name).calcHash();
            const auto struct2Hash = dataSource.getStruct(struct2Name).calcHash();
            const auto struct3Hash = dataSource.getStruct(struct3Name).calcHash();

            Assert::AreNotEqual(struct1Hash, struct2Hash);
            Assert::AreNotEqual(struct2Hash, struct3Hash);
            Assert::AreNotEqual(struct3Hash, struct1Hash);

            Assert::AreEqual(firstStruct1Hash, struct1Hash);
            Assert::AreEqual(firstStruct2Hash, struct2Hash);
            Assert::AreEqual(firstStruct3Hash, struct3Hash);

            Assert::AreEqual(capturedStruct1.calcHash(), struct1Hash);
            Assert::AreEqual(capturedStruct2.calcHash(), struct2Hash);
            Assert::AreEqual(capturedStruct3.calcHash(), struct3Hash);
        }
    }
};

TEST_CLASS(ComplexStructs)
{
    TEST_METHOD(HashComTypes)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(COMPLEX_HASHABLES_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const AnyString structName    = "ComObjHash_s";
        const auto capturedStruct     = dataSource.getStruct(structName);
        const auto capturedStructHash = capturedStruct.calcHash();
        Assert::AreNotEqual(0uLL, dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(dataSource.getStruct(structName).calcHash(), dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(capturedStructHash, dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(capturedStruct.calcHash(), dataSource.getStruct(structName).calcHash());
    }

    TEST_METHOD(HashParentStruct)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(COMPLEX_HASHABLES_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const AnyString structName    = "ParentHash_s";
        const auto capturedStruct     = dataSource.getStruct(structName);
        const auto capturedStructHash = capturedStruct.calcHash();
        Assert::AreNotEqual(0uLL, dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(dataSource.getStruct(structName).calcHash(), dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(capturedStructHash, dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(capturedStruct.calcHash(), dataSource.getStruct(structName).calcHash());
    }

    TEST_METHOD(HashRecursiveStruct)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(COMPLEX_HASHABLES_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const AnyString structName    = "RecursiveHash_s";
        const auto capturedStruct     = dataSource.getStruct(structName);
        const auto capturedStructHash = capturedStruct.calcHash();
        Assert::AreNotEqual(0uLL, dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(dataSource.getStruct(structName).calcHash(), dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(capturedStructHash, dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(capturedStruct.calcHash(), dataSource.getStruct(structName).calcHash());
    }

    TEST_METHOD(RecursiveStructHashEqualToRecursiveMemberHash)
    {
        const std::wstring pdbFilePath = std::filesystem::absolute(COMPLEX_HASHABLES_PDB_FILE_PATH);
        dia::DataSource dataSource{pdbFilePath};
        const AnyString structName    = "RecursiveHash_s";
        const auto capturedStruct     = dataSource.getStruct(structName);
        const auto capturedStructHash = capturedStruct.calcHash();

        Assert::AreNotEqual(0uLL, dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(dataSource.getStruct(structName).calcHash(), dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(capturedStructHash, dataSource.getStruct(structName).calcHash());
        Assert::AreEqual(capturedStruct.calcHash(), dataSource.getStruct(structName).calcHash());

        const auto recursiveMember     = capturedStruct.getMember("Next");

        const auto recursiveMemberType = recursiveMember.getType();
        Assert::IsTrue(recursiveMemberType.isPointer());
        const dia::Pointer recusivePointer = static_cast<const dia::Pointer&>(recursiveMemberType);
        const auto recursivePointerDecayType{recusivePointer.getType()};
        Assert::IsTrue(recursivePointerDecayType.isUserDefinedType());

        Assert::AreEqual(capturedStructHash, recursivePointerDecayType.calcHash());
    }
};
}  // namespace Hashing
