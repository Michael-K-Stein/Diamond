#pragma once
#include "DiaFunctionArgType.h"
#include "DiaSymbol.h"
#include "DiaSymbolEnumerator.h"
#include "DiaSymbolTypes.h"
#include "DiaTypeResolution.h"

namespace dia
{
/// @brief Each unique function signature is identified by a SymTagFunctionType
/// symbol. Each parameter is identified as a class child symbol with a
/// SymTagFunctionArgType tag.
class FunctionType : public Symbol
{
public:
    using Symbol::Symbol;
    USING_BASE_OPERATORS(Symbol);

    using Symbol::getCallingConvention;
    using Symbol::getClassParent;
    using Symbol::getClassParentId;
    using Symbol::getConstType;
    using Symbol::getCount;
    using Symbol::getLexicalParent;
    using Symbol::getLexicalParentId;
    using Symbol::getObjectPointerType;
    using Symbol::getSymIndexId;
    using Symbol::getSymTag;
    using Symbol::getThisAdjust;
    using Symbol::getType;
    using Symbol::getTypeId;
    using Symbol::getUnalignedType;
    using Symbol::getVolatileType;

    DiaSymbolEnumerator<FunctionArgType> enumerateParameters() const
    {
        return DiaSymbolEnumerator<FunctionArgType>::enumerate(*this, SymTagFunctionArgType);
    };

    // Iterator-related methods
    auto begin() const { return enumerateParameters().begin(); }

    auto end() const { return enumerateParameters().end(); }
};
}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::FunctionType& func);
