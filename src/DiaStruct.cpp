#include "DiaStruct.h"
#include "DataMember.h"
#include "DiaPointer.h"
#include <sstream>

namespace std
{
template <>
struct hash<dia::Struct>
{
    size_t operator()(const dia::Struct& diaStruct) const
    {
        size_t calculatedHash = 0;
        const size_t nameHash = hash<std::wstring>()(diaStruct.getName());
        hash_combine(calculatedHash, std::wstring(L"Struct"), nameHash);

        for (const auto& member : diaStruct.enumerateMembers())
        {
            const auto memberOffset = member.getOffset();
            const auto memberTypeName = member.getFieldCType().getTypeName();
            const auto memberName = member.getFieldName();
            const auto memberLength = member.getLength();
            hash_combine(calculatedHash, memberOffset, memberTypeName,
                         memberName, memberLength);
        }

        return calculatedHash;
    }
};
} // namespace std

namespace dia
{
DiaSymbolEnumerator<DataMember> Struct::enumerateMembers() const
{
    return enumerate<DataMember>(*this, SymTagData);
}
std::set<UserDefinedType> Struct::queryDependsOnTypes() const
{
    std::set<UserDefinedType> types{};
    for (const auto& member : enumerateMembers())
    {
        if (!member.getFieldCType().isUserDefinedType())
        {
            continue;
        }
        const auto& cType = member.getFieldCType();
        const auto udt = UserDefinedType{cType};
        types.insert(udt);
    }
    return types;
}
std::set<UserDefinedType> Struct::queryDependsOnForwardTypes() const
{
    std::set<UserDefinedType> types{};
    for (const auto& member : enumerateMembers())
    {
        const auto& cType = member.getFieldCType();
        if (!cType.isPointer())
        {
            continue;
        }
        const PointerType cTypeAsPointer{cType};
        // Get the pointed-to type
        const auto decayType = cTypeAsPointer.getType();
        if (!decayType.isUserDefinedType())
        {
            continue;
        }
        const auto udt = UserDefinedType{decayType};
        types.insert(udt);
    }
    return types;
}
size_t Struct::calcHash() const { return std::hash<Struct>()(*this); }

} // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::Struct& diaStruct)
{
    const auto& structName = diaStruct.getName();
    const auto& structPureName = structName.c_str() + 1;
    os << L"typedef struct " << structName << L" {\n";

    std::wstringstream tmpUnionStream{};

    bool processingBitfield = false;
    LONG previousMemberOffset = -1;
    size_t membersInStringStream = 0;
    size_t indentationLevel = 1;

    for (const dia::DataMember& member : diaStruct.enumerateMembers())
    {
        const auto currentOffset = member.getOffset();
        if (previousMemberOffset != currentOffset)
        {
            if (membersInStringStream > 1)
            {
                for (size_t i = 0; i < indentationLevel; ++i)
                {
                    os << L"\t";
                }
                os << L"union {\n";
                os << tmpUnionStream.str();
                os << L"\t};\n";
            }
            else
            {
                os << tmpUnionStream.str();
            }
            tmpUnionStream = std::wstringstream{}; // New stringstream
            membersInStringStream = 0;
        }
        previousMemberOffset = currentOffset;
        if (member.getLocationType() == LocIsBitField)
        {
            if (!processingBitfield)
            {
                for (size_t i = 0; i < indentationLevel; ++i)
                {
                    tmpUnionStream << L"\t";
                }
                tmpUnionStream << L"/* " << " 0x" << std::hex
                               << member.getOffset() << L" */ \t "
                               << L"struct {\n";
                // Now inside an inner struct
                ++indentationLevel;
            }
            processingBitfield = true;
            for (size_t i = 0; i < indentationLevel; ++i)
            {
                tmpUnionStream << L"\t";
            }
            tmpUnionStream << member << L"\n";
        }
        else
        {
            if (processingBitfield)
            {
                for (size_t i = 0; i < indentationLevel; ++i)
                {
                    tmpUnionStream << L"\t";
                }
                tmpUnionStream << L"};\n";
                // Inner struct finished
                --indentationLevel;
            }
            processingBitfield = false;
            for (size_t i = 0; i < indentationLevel; ++i)
            {
                tmpUnionStream << L"\t";
            }
            tmpUnionStream << member << L"\n";
        }
        ++membersInStringStream;
    }
    os << L"} " << structPureName << L", *P" << structPureName << L";";
    return os;
}
