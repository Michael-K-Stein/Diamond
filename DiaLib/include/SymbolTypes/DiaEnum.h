#pragma once
#include "DiaData.h"
#include "DiaSymbol.h"
#include "DiaSymbolEnumerator.h"
#include "DiaSymbolTypes.h"
#include "DiaTypeResolution.h"

namespace dia
{
/// @brief Enumerations are identified by SymTagEnum symbols. Each enumeration value appears as a class child with a SymTagConstant tag.
class Enum : public Symbol
{
public:
    using Symbol::Symbol;
    USING_BASE_OPERATORS(Symbol);

    using Symbol::getBaseType;
    using Symbol::getClassParent;
    using Symbol::getClassParentId;
    using Symbol::getConstructor;
    using Symbol::getConstType;
    using Symbol::getHasAssignmentOperator;
    using Symbol::getHasCastOperator;
    using Symbol::getHasNestedTypes;
    using Symbol::getLength;
    using Symbol::getLexicalParent;
    using Symbol::getLexicalParentId;
    using Symbol::getName;
    using Symbol::getNested;
    using Symbol::getOverloadedOperator;
    using Symbol::getPacked;
    using Symbol::getScoped;
    using Symbol::getSymIndexId;
    using Symbol::getSymTag;
    using Symbol::getType;
    using Symbol::getTypeId;
    using Symbol::getUnalignedType;
    using Symbol::getVolatileType;

    auto getValues() const { return DiaSymbolEnumerator<Data>::enumerate(static_cast<const Symbol&>(*this), SymTagData); };
};
}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::Enum& udt);
