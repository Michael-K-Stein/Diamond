#include "pch.h"
//
#include "DiaUnion.h"
#include "DataMember.h"
#include "DiaSymbolEnumerator.h"

namespace std
{
template <>
struct hash<dia::Union>
{
    size_t operator()(const dia::Union& diaUnion) const
    {
        size_t calculatedHash = 0;
        const size_t nameHash = hash<std::wstring>()(diaUnion.getName());
        hash_combine(calculatedHash, std::wstring(L"Union"), nameHash);

        for (const auto& member : diaUnion.enumerateMembers())
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
DiaSymbolEnumerator<DataMember> Union::enumerateMembers() const { return enumerate<DataMember>(*this, SymTagData); }

size_t Union::calcHash() const { return std::hash<Union>()(*this); }
}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::Union& v)
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
