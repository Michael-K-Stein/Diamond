#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"

namespace dia
{
/// @brief Indicates that the symbol is a function.
class Function : protected Symbol
{
public:
    using Symbol::getAccess;
    using Symbol::getAddressOffset;
    using Symbol::getAddressSection;
    using Symbol::getClassParent;
    using Symbol::getClassParentId;
    using Symbol::getConstType;
    using Symbol::getCustomCallingConvention;
    using Symbol::getFarReturn;
    using Symbol::getHasAlloca;
    using Symbol::getHasEH;
    using Symbol::getHasEHa;
    using Symbol::getHasInlAsm;
    using Symbol::getHasLongJump;
    using Symbol::getHasSecurityChecks;
    using Symbol::getHasSEH;
    using Symbol::getHasSetJump;
    using Symbol::getInlSpec;
    using Symbol::getInterruptReturn;
    using Symbol::getIntro;
    using Symbol::getIsNaked;
    using Symbol::getIsStatic;
    using Symbol::getLength;
    using Symbol::getLexicalParent;
    using Symbol::getLexicalParentId;
    using Symbol::getLocationType;
    using Symbol::getName;
    using Symbol::getNoInline;
    using Symbol::getNoReturn;
    using Symbol::getNoStackOrdering;
    using Symbol::getNotReached;
    using Symbol::getOptimizedCodeDebugInfo;
    using Symbol::getPure;
    using Symbol::getRelativeVirtualAddress;
    using Symbol::getSymIndexId;
    using Symbol::getSymTag;
    using Symbol::getToken;
    using Symbol::getType;
    using Symbol::getTypeId;
    using Symbol::getUnalignedType;
    using Symbol::getUndecoratedName;
    using Symbol::getUndecoratedNameEx;
    using Symbol::getVirtual;
    using Symbol::getVirtualAddress;
    using Symbol::getVirtualBaseOffset;
    using Symbol::getVolatileType;
};
} // namespace dia
