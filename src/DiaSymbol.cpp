#pragma once
#include "DiaSymbol.h"
#include "BstrWrapper.h"
#include "DiaSymbolTypes/DiaArray.h"
#include "DiaSymbolTypes/DiaData.h"
#include "DiaSymbolTypes/DiaFunction.h"
#include "DiaSymbolTypes/DiaNull.h"
#include "DiaSymbolTypes/DiaPointer.h"
#include "Exceptions.h"
#include "TypeResolution.h"
#include "UserDefinedType.h"

namespace dia
{
Symbol::Symbol(const Symbol& other) : Base{other} {}
Symbol Symbol::operator=(const Symbol& other)
{
    Base::operator=(other);
    return *this;
}
Symbol::Symbol(Symbol&& other) noexcept : Base{std::move(other)} {}
Symbol Symbol::operator=(Symbol&& other) noexcept
{
    Base::operator=(std::move(other));
    return *this;
}

bool Symbol::isVolatile() const { return getVolatileType(); }
bool Symbol::isArray() const { return SymTagArrayType == getSymTag(); }
bool Symbol::isPointer() const { return SymTagPointerType == getSymTag(); }
bool Symbol::isUserDefinedType() const
{
    return SymTagUDT == getSymTag() || SymTagEnum == getSymTag() ||
           SymTagTypedef == getSymTag();
}
size_t Symbol::calcHash() const
{
#define __RETURN_HASH_SYMBOL(x) return std::hash<T>()(x);
    size_t calculatedHash = 0;
    hash_combine(calculatedHash, std::wstring(dia::symTagToName(getSymTag())),
                 std::hash<std::wstring>()(getName()));
    XBY_SYMBOL_TYPE_T((*this), T, __RETURN_HASH_SYMBOL);
}
} // namespace dia

#if 0
std::wostream& operator<<(std::wostream& os, const dia::Symbol& v)
{
    os << L"/* " << v.getType().getSymTag() << L", " << v.getLocationType()
       << " */ \t ";
    if (v.getType().isVolatile())
    {
        os << L"volatile ";
    }
    if (v.isUserDefinedType())
    {
        const auto& udt = v.asUserDefinedType();
        os << udt;
    }
    else if (v.getType().isArray())
    {
        const auto arrayField = v.getType();
        const auto elementType = arrayField.getType();
        os << elementType.getTypeName() << L" " << v.getName() << L"[0x"
           << std::hex << arrayField.getCount() << L"]";
    }
    else
    {
        os << v.getType().getTypeName() << L" " << v.getName();
    }

    return os;
}
#endif
