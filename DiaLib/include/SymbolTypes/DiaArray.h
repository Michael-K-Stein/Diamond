#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"
#include "DiaTypeResolution.h"

namespace dia
{
/// @brief An array is identified by a `SymTagArray` symbol.
class Array : protected Symbol
{
public:
    using Symbol::Symbol;
    TRIVIAL_CONVERT(Symbol, Array);

    using Symbol::getArrayIndexType;
    using Symbol::getArrayIndexTypeId;
    using Symbol::getConstType;
    using Symbol::getCount;
    using Symbol::getLength;
    using Symbol::getLexicalParent;
    using Symbol::getLexicalParentId;
    using Symbol::getRank;
    using Symbol::getSymIndexId;
    using Symbol::getSymTag;
    using Symbol::getType;
    using Symbol::getTypeId;
    using Symbol::getUnalignedType;
    using Symbol::getVolatileType;
};
}  // namespace dia

namespace std
{
template <>
struct hash<dia::Array>
{
    size_t operator()(const dia::Array& v) const
    {
        size_t calculatedHash = 0;
        hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), v.getArrayIndexType(), v.getConstType(), v.getCount(),
                     v.getLength() /* Length should be well defined for arrays */, v.getLexicalParentId(), GET_RANK_OR_ZERO(v), v.getUnalignedType(),
                     v.getVolatileType());
        return calculatedHash;
    }
};
}  // namespace std

std::wostream& operator<<(std::wostream& os, const dia::Array& arr);
