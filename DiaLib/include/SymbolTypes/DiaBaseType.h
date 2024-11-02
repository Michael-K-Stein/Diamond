#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"
#include "DiaTypeResolution.h"

namespace dia
{
/// @brief Base types are identified by SymTagBaseType symbols.
class BaseType : public Symbol
{
public:
    BaseType() = default;
    using Symbol::Symbol;
    USING_BASE_OPERATORS(Symbol);

    using Symbol::getBaseType;
    using Symbol::getConstType;
    using Symbol::getLength;
    using Symbol::getLexicalParent;
    using Symbol::getLexicalParentId;
    using Symbol::getSymIndexId;
    using Symbol::getSymTag;
    using Symbol::getUnalignedType;
    using Symbol::getVolatileType;
};
}  // namespace dia

namespace std
{
template <>
struct hash<dia::BaseType>
{
    size_t operator()(const dia::BaseType& v) const
    {
        size_t calculatedHash = 0;
        hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), v.getBaseType(), v.getConstType(), v.getLength(),
                     v.getLexicalParentId(), v.getUnalignedType(), v.getVolatileType());
        return calculatedHash;
    }
};
}  // namespace std

std::wostream& operator<<(std::wostream& os, const dia::BaseType& data);
