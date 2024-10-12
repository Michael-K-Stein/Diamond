#include "Union.h"
#include "DiaSymbolEnumerator.h"

namespace dia
{
DiaSymbolEnumerator Union::enumerateMembers() const
{
    return enumerate(*this, SymTagData);
}
} // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::Union& v)
{
    const auto& unionName = v.getName();
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


