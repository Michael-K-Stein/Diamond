#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolEnumerator.h"
#include "DiaSymbolTypes.h"
#include "DiaTypeResolution.h"

namespace dia
{
/// @brief Internal - DO NOT USE! Use dia::UserDefinedSymbol instead!
/// Each class, structure, and union is identified by a SymTagUDT symbol.
/// Each member, function, data, or nested type, and each base class, appears as
/// a class child of the user-defined type (UDT).
class Udt : public Symbol
{
public:
    using Symbol::Symbol;
    USING_BASE_OPERATORS(Symbol);

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
    using Symbol::getUdtKind;
    using Symbol::getUnalignedType;
    using Symbol::getVirtualTableShape;
    using Symbol::getVirtualTableShapeId;
    using Symbol::getVolatileType;

    size_t calcHash() const;
};
}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::Udt& udt);
