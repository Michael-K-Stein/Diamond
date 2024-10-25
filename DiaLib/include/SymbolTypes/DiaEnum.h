#pragma once
#include "DiaData.h"
#include "DiaSymbol.h"
#include "DiaSymbolEnumerator.h"
#include "DiaSymbolTypes.h"
#include "DiaTypeResolution.h"

namespace dia
{
/// @brief Enumerations are identified by SymTagEnum symbols. Each enumeration value appears as a class child with a SymTagConstant tag.
class Enum : protected Symbol
{
public:
    using Symbol::Symbol;
    TRIVIAL_CONVERT(Symbol, Enum);

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

    const std::vector<Data> getValues() const { return DiaSymbolEnumerator<Data>::enumerate(static_cast<const Symbol&>(*this), SymTagData); };
};
}  // namespace dia

namespace std
{
template <>
struct hash<dia::Enum>
{
    size_t operator()(const dia::Enum& v) const
    {
        size_t calculatedHash = 0;
        hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), v.getBaseType(), v.getClassParent(), v.getConstructor(),
                     v.getConstType(), v.getHasAssignmentOperator(), v.getHasCastOperator(), v.getHasNestedTypes(), v.getLength(), v.getName(),
                     v.getNested(), v.getOverloadedOperator(), v.getPacked(), v.getScoped(), v.getUnalignedType(), v.getVolatileType());
        return calculatedHash;
    }
};
}  // namespace std

std::wostream& operator<<(std::wostream& os, const dia::Enum& udt);
