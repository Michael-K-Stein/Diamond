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
    Union& asUnion() const;

    bool isStruct() const;
    Struct& asStruct() const;

protected:
    using Symbol::get;

private:
};
} // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::UserDefinedType& udt);
