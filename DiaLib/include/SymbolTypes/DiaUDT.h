#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"
#include "DiaTypeResolution.h"

namespace dia
{
/// @brief Internal - DO NOT USE! Use dia::UserDefinedSymbol instead!
/// Each class, structure, and union is identified by a SymTagUDT symbol.
/// Each member, function, data, or nested type, and each base class, appears as
/// a class child of the user-defined type (UDT).
class Udt : protected Symbol
{
public:
    using Symbol::Symbol;
    TRIVIAL_CONVERT(Symbol, Udt);

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
};
}  // namespace dia

namespace std
{
template <>
struct hash<dia::Udt>
{
    size_t operator()(const dia::Udt& v) const
    {
        size_t calculatedHash = 0;
        hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), v.getClassParent(), v.getConstructor(), v.getConstType(),
                     v.getHasAssignmentOperator(), v.getHasCastOperator(), v.getHasNestedTypes(), v.getLength(), v.getName(), v.getNested(),
                     v.getOverloadedOperator(), v.getPacked(), v.getScoped(), v.getUdtKind(), v.getUnalignedType(), v.getVirtualTableShape(),
                     v.getVolatileType());
        return calculatedHash;
    }
};
}  // namespace std

std::wostream& operator<<(std::wostream& os, const dia::Udt& udt);
