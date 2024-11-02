#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"
#include "DiaTypeResolution.h"

namespace dia
{
/// @brief An array is identified by a `SymTagArray` symbol.
class Array : public Symbol
{
public:
    using Symbol::Symbol;
    USING_BASE_OPERATORS(Symbol);

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

std::wostream& operator<<(std::wostream& os, const dia::Array& arr);
