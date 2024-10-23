#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"
#include "TypeResolution.h"

namespace dia
{
/// @brief All variables, such as parameters, local variables, global variables,
/// and class members, are identified by `SymTagData` symbols. Constant values
/// (`LocIsConstant`) are also identified with this type.
class Data : protected Symbol
{
public:
    using Symbol::Symbol;
    TRIVIAL_CONVERT(Symbol, Data);

    using Symbol::getAccess;
    using Symbol::getAddressOffset;
    using Symbol::getAddressSection;
    using Symbol::getAddressTaken;
    using Symbol::getBitPosition;
    using Symbol::getClassParent;
    using Symbol::getClassParentId;
    using Symbol::getCompilerGenerated;
    using Symbol::getConstType;
    using Symbol::getDataKind;
    using Symbol::getIsAggregated;
    using Symbol::getIsSplitted;
    using Symbol::getLength;
    using Symbol::getLexicalParent;
    using Symbol::getLexicalParentId;
    using Symbol::getLocationType;
    using Symbol::getName;
    using Symbol::getOffset;
    using Symbol::getRegisterId;
    using Symbol::getRelativeVirtualAddress;
    using Symbol::getSlot;
    using Symbol::getSymIndexId;
    using Symbol::getSymTag;
    using Symbol::getToken;
    using Symbol::getType;
    using Symbol::getTypeId;
    using Symbol::getUnalignedType;
    using Symbol::getValue;
    using Symbol::getVirtualAddress;
    using Symbol::getVolatileType;
};
} // namespace dia

namespace std
{
template <>
struct hash<dia::Data>
{
    size_t operator()(const dia::Data& v) const
    {
        size_t calculatedHash = 0;
        hash_combine(calculatedHash,
                     std::wstring(dia::symTagToName(v.getSymTag())),
                     v.getAccess(), v.getBitPosition(), v.getClassParent(),
                     v.getCompilerGenerated(), v.getConstType(),
                     v.getDataKind(), v.getIsAggregated(), v.getIsSplitted(),
                     v.getLength(), v.getLocationType(), v.getName(),
                     v.getOffset(), v.getSlot(), v.getSymTag(), v.getToken(),
                     v.getType(), v.getUnalignedType(), v.getVolatileType());
        return calculatedHash;
    }
};
} // namespace std

std::wostream& operator<<(std::wostream& os, const dia::Data& data);
