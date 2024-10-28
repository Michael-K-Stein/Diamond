#pragma once
#include "SymbolTypes/DiaUDT.h"

namespace dia
{

class DataSource;

/// @brief High level wrapper for any UserDefinedType
class UserDefinedType : public Udt
{
public:
    using Udt::Udt;
    TRIVIAL_CONVERT(Udt, UserDefinedType);

    using Udt::calcHash;

    DiaSymbolEnumerator<Data> enumerateMembers() const;

    bool operator==(const UserDefinedType& other) const { return calcHash() == other.calcHash(); }

    bool operator!=(const UserDefinedType& other) const { return !(*this == other); }

    bool operator<(const UserDefinedType& other) const { return calcHash() < other.calcHash(); }

    bool operator<=(const UserDefinedType& other) const { return !(*this > other); }

    bool operator>(const UserDefinedType& other) const { return calcHash() > other.calcHash(); }

    bool operator>=(const UserDefinedType& other) const { return !(*this < other); }

protected:
    using Udt::get;

private:
    friend class DataSource;
};

using Class       = UserDefinedType;
using TaggedUnion = UserDefinedType;
using Struct      = UserDefinedType;
using Union       = UserDefinedType;
using Interface   = UserDefinedType;

}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::UserDefinedType& udt);
