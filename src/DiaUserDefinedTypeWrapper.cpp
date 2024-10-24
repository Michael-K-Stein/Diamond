#include "DiaUserDefinedTypeWrapper.h"
#include "DiaStruct.h"
#include "DiaUnion.h"
#include "Utils/Exceptions.h"

namespace dia
{
bool UserDefinedType::isUnion() const { return UdtUnion == getUdtKind(); }

Union UserDefinedType::asUnion() const
{
    Union u{*this};
    return u;
}

bool UserDefinedType::isStruct() const { return UdtStruct == getUdtKind(); }

Struct UserDefinedType::asStruct() const
{
    Struct s{*this};
    return s;
}

size_t UserDefinedType::calcHash() const
{
    if (isStruct())
    {
        return asStruct().calcHash();
    }
    if (isUnion())
    {
        return asUnion().calcHash();
    }
    throw std::runtime_error("Invalid UDT kind!");
}

}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::UserDefinedType& udt)
{
    if (udt.isUnion())
    {
        const auto& u = udt.asUnion();
        os << u;
    }
    else if (udt.isStruct())
    {
        const auto& s = udt.asStruct();
        os << s;
    }
    return os;
}
