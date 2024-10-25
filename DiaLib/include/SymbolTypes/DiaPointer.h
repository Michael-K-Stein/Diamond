#pragma once
#include "DiaTypeResolution.h"
#include "SymbolTypes/DiaSymbolTypes.h"
#include <string>

namespace dia
{
/// @brief Each pointer is identified by a SymTagPointerType symbol.
class Pointer : protected Symbol
{
public:
    using Symbol::Symbol;
    TRIVIAL_CONVERT(Symbol, Pointer);

    using Symbol::getConstType;
    using Symbol::getLength;
    using Symbol::getLexicalParent;
    using Symbol::getLexicalParentId;
    using Symbol::getReference;
    using Symbol::getSymIndexId;
    using Symbol::getSymTag;
    using Symbol::getType;
    using Symbol::getTypeId;
    using Symbol::getUnalignedType;
    using Symbol::getVolatileType;
};
}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::Pointer& pointer);

namespace std
{
template <>
struct hash<dia::Pointer>
{
    size_t operator()(const dia::Pointer& v) const
    {
        size_t calculatedHash = 0;
        hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), v.getConstType(), v.getLength(), v.getLexicalParent(),
                     v.getReference(), v.getUnalignedType(), v.getVolatileType());
        return calculatedHash;
    }
};
}  // namespace std
