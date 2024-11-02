#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"
#include "DiaTypeResolution.h"
#include "Exceptions.h"

namespace dia
{
/// @brief All variables, such as parameters, local variables, global variables,
/// and class members, are identified by `SymTagData` symbols. Constant values
/// (`LocIsConstant`) are also identified with this type.
class Data : public Symbol
{
public:
    Data() = default;
    using Symbol::Symbol;

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

    size_t calcHash() const;
};
}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::Data& data);
