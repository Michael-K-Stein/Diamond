#pragma once
#include "DiaSymbol.h"
namespace dia
{

// Derived Types
class Struct;
class Union;
class Enum;

class UserDefinedType : public Symbol
{
public:
    using Symbol::Symbol;
    UserDefinedType(const Symbol& other) : Symbol{other} {}
    UserDefinedType& operator=(const Symbol& other)
    {
        UserDefinedType symbol{other};
        symbol.get().p->AddRef();
        return symbol;
    }
    UserDefinedType(Symbol&& other) : Symbol{std::move(other)} {}
    UserDefinedType& operator=(Symbol&& other)
    {
        UserDefinedType symbol{std::move(other)};
        return symbol;
    }

    enum UdtKind getUdtKind() const;

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
    using Symbol::get;

private:
};
} // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::UserDefinedType& udt);
