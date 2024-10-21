#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"
#include "TypeResolution.h"

namespace dia
{
/// @brief Each unique function signature is identified by a
/// SymTagFunctionArgType symbol. Each parameter is identified as a class child
/// symbol with a SymTagFunctionArgType tag.
class FunctionArgType : protected Symbol
{
public:
    using Symbol::Symbol;
    TRIVIAL_CONVERT(Symbol, FunctionArgType);

    using Symbol::getClassParent;
    using Symbol::getClassParentId;
    using Symbol::getLexicalParent;
    using Symbol::getLexicalParentId;
    using Symbol::getSymIndexId;
    using Symbol::getSymTag;
    using Symbol::getType;
    using Symbol::getTypeId;
};
} // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::FunctionArgType& func);

namespace std
{
template <>
struct hash<dia::FunctionArgType>
{
    size_t operator()(const dia::FunctionArgType& v) const
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
