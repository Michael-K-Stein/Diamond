#pragma once
#include "DiaSymbolTypes/DiaUDT.h"

namespace dia
{

class DataSource;
// Derived Types
class Struct;
class Union;
class Enum;

class UserDefinedType : public Udt
{
public:
    using Udt::Udt;

    UserDefinedType(const Udt& other) : Udt{other} {}
    UserDefinedType operator=(const Udt& other)
    {
        UserDefinedType udt{other};
        udt.get().p->AddRef();
        return udt;
    }
    UserDefinedType(Udt&& other) : Udt{std::move(other)} {}
    UserDefinedType operator=(Udt&& other)
    {
        UserDefinedType symbol{std::move(other)};
        return symbol;
    }

    bool isUnion() const;
    Union asUnion() const;

    bool isStruct() const;
    Struct asStruct() const;

    virtual size_t calcHash() const;

    bool operator==(const UserDefinedType& other) const
    {
        return calcHash() == other.calcHash();
    }

    bool operator<(const UserDefinedType& other) const
    {
        return calcHash() < other.calcHash();
    }

protected:
    using Udt::get;

private:
    friend class DataSource;
};
} // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::UserDefinedType& udt);
