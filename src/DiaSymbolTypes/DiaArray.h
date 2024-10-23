#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"
#include "TypeResolution.h"

namespace dia
{
/// @brief An array is identified by a `SymTagArray` symbol.
class ArrayType : protected Symbol
{
public:
    using Symbol::Symbol;
    TRIVIAL_CONVERT(Symbol, ArrayType);

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
} // namespace dia

namespace std
{
template <>
struct hash<dia::ArrayType>
{
    size_t operator()(const dia::ArrayType& v) const
    {
        size_t calculatedHash = 0;
        hash_combine(calculatedHash,
                     std::wstring(dia::symTagToName(v.getSymTag())),
                     v.getArrayIndexType(), v.getConstType(), v.getCount(),
                     v.getLength(), v.getLexicalParent(), v.getRank(),
                     v.getUnalignedType(), v.getVolatileType());
        return calculatedHash;
    }
};
} // namespace std

std::wostream& operator<<(std::wostream& os, const dia::ArrayType& arr);
