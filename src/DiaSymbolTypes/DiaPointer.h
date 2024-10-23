#pragma once
#include "DiaSymbolTypes.h"
#include "TypeResolution.h"
#include <string>

namespace dia
{
/// @brief Each pointer is identified by a SymTagPointerType symbol.
class PointerType : protected Symbol
{
public:
    using Symbol::Symbol;
    TRIVIAL_CONVERT(Symbol, PointerType);

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
} // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::PointerType& pointer);

namespace std
{
template <>
struct hash<dia::PointerType>
{
    size_t operator()(const dia::PointerType& v) const
    {
        size_t calculatedHash = 0;
        hash_combine(
            calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())),
            v.getConstType(), v.getLength(), v.getLexicalParent(),
            v.getReference(), v.getUnalignedType(), v.getVolatileType());
        return calculatedHash;
    }
};
} // namespace std
