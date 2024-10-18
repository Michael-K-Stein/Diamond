#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"
#include "TypeResolution.h"

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

namespace std
{
template <>
struct hash<dia::Function>
{
    size_t operator()(const dia::Function& v) const
    {
        size_t calculatedHash = 0;
        hash_combine(
            calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())),
            v.getAccess(), v.getAddressSection(), v.getClassParent(),
            v.getConstType(), v.getCustomCallingConvention(), v.getFarReturn(),
            v.getHasAlloca(), v.getHasEH(), v.getHasEHa(), v.getHasInlAsm(),
            v.getHasLongJump(), v.getHasSecurityChecks(), v.getHasSEH(),
            v.getHasSetJump(), v.getInlSpec(), v.getInterruptReturn(),
            v.getIntro(), v.getIsNaked(), v.getIsStatic(), v.getLength(),
            v.getLocationType(), v.getName(), v.getNoInline(), v.getNoReturn(),
            v.getNoStackOrdering(), v.getNotReached(),
            v.getOptimizedCodeDebugInfo(), v.getPure(), v.getToken(),
            v.getType(), v.getUnalignedType(), v.getUndecoratedName(),
            v.getVirtual(), v.getVirtualAddress(), v.getVolatileType());

        return calculatedHash;
    }
};
} // namespace std
