#include "pch.h"
//
#include "DEPRECATED__DiaUnion.h"
#include "DiaDataMember.h"
#include "DiaSymbolEnumerator.h"

namespace std
{
template <>
struct hash<dia::DEPRECATED__Union>
{
    size_t operator()(const dia::DEPRECATED__Union& diaDEPRECATED__Union) const
    {
        size_t calculatedHash = 0;
        const size_t nameHash = hash<std::wstring>()(diaDEPRECATED__Union.getName());
        hash_combine(calculatedHash, std::wstring(L"DEPRECATED__Union"), nameHash);

        for (const auto& member : diaDEPRECATED__Union.enumerateMembers())
        {
            const auto memberOffset   = member.getOffset();
            const auto memberTypeName = member.getFieldCType().getTypeName();
            const auto memberName     = member.getFieldName();
            const auto memberLength   = member.getLength();
            hash_combine(calculatedHash, memberOffset, memberTypeName, memberName, memberLength);
        }

        return calculatedHash;
    }
};
}  // namespace std

namespace dia
{
DiaSymbolEnumerator<DataMember> DEPRECATED__Union::enumerateMembers() const { return enumerate<DataMember>(*this, SymTagData); }

size_t DEPRECATED__Union::calcHash() const { return std::hash<DEPRECATED__Union>()(*this); }
}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::DEPRECATED__Union& v)
{
    const auto& unionName      = v.getName();
    const auto& structPureName = unionName.c_str() + 1;
    os << L"typedef union " << unionName << L" {\n";
    for (const auto& member : v.enumerateMembers())
    {
        os << L"\t/* 0x" << std::hex << member.getOffset() << L" */ \t";
        os << member;
        os << L";\n";
    }
    os << L"} " << structPureName << L", *P" << structPureName << L";";
    return os;
}
