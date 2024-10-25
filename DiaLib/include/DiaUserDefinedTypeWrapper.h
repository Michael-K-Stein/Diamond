#pragma once
#include "SymbolTypes/DiaUDT.h"

namespace dia
{

class DataSource;
// Derived Types
class Struct;
class Union;
class Enum;

/// @brief High level wrapper for any UserDefinedType
class UserDefinedType : public Udt
{
public:
    using Udt::Udt;
    TRIVIAL_CONVERT(Udt, UserDefinedType);

    bool isUnion() const;
    Union asUnion() const;

    bool isStruct() const;
    Struct asStruct() const;

    virtual size_t calcHash() const;

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
}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::UserDefinedType& udt);
