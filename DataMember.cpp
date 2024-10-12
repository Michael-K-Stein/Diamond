#include "DataMember.h"
namespace dia
{
DataMember::DataMember(const Symbol& other) : Symbol{other} {}
DataMember& DataMember::operator=(const Symbol& other)
{
    DataMember member{other};
    return member;
}
DataMember::DataMember(Symbol&& other) : Symbol{std::move(other)} {}
DataMember& DataMember::operator=(Symbol&& other)
{
    DataMember member{other};
    return member;
}
std::wstring DataMember::getFieldName() const { return getName(); }
Symbol DataMember::getFieldCType() const { return getType(); }
} // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::DataMember& member)
{
    const auto& fieldName = member.getFieldName();
    const auto& ctype = member.getFieldCType();

    os << L"/* 0x" << std::hex << member.getOffset();
    if (member.getLocationType() == LocIsBitField)
    {
        os << L":" << std::hex << member.getBitPosition();
    }
    os << L" */ ";

    if (ctype.isArray())
    {
        const auto elementType = ctype.getType();
        os << elementType.getTypeName() << L" " << fieldName << L"[0x"
           << std::hex << ctype.getCount() << L"];";
    }
    else
    {
        os << ctype.getTypeName() << L" " << fieldName;
        if (member.getLocationType() == LocIsBitField)
        {
            os << L" : " << std::dec << member.getLength();
        }
        os << L";";
    }
    return os;
}
