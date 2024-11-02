#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"
#include "DiaTypeResolution.h"

namespace dia
{
/// @brief Symbols with SymTagTypedef tags introduce names for other types.
class Typedef : public Symbol
{
public:
    Typedef() = default;
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
    using Symbol::getReference;
    using Symbol::getScoped;
    using Symbol::getSymIndexId;
    using Symbol::getSymTag;
    using Symbol::getType;
    using Symbol::getTypeId;
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
struct hash<dia::Typedef>
{
    size_t operator()(const dia::Typedef& v) const
    {
        size_t calculatedHash = 0;
        hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), v.getBaseType(), v.getConstructor(), v.getConstType(),
                     v.getHasAssignmentOperator(), v.getHasCastOperator(), v.getHasNestedTypes(), v.getLength(), v.getLexicalParentId(), v.getName(),
                     v.getNested(), v.getOverloadedOperator(), v.getPacked(), v.getReference(), v.getScoped(), v.getType(), v.getUdtKind(),
                     v.getUnalignedType(), v.getVirtualTableShape(), v.getVolatileType());
        return calculatedHash;
    }
};
}  // namespace std

std::wostream& operator<<(std::wostream& os, const dia::Typedef& data);