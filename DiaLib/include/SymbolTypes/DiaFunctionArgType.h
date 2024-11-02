#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"
#include "DiaTypeResolution.h"

namespace dia
{
/// @brief Each parameter of a function is identified by a SymTagFunctionArgType
/// symbol.
class FunctionArgType : public Symbol
{
public:
    FunctionArgType() = default;
    using Symbol::Symbol;
    USING_BASE_OPERATORS(Symbol);

    using Symbol::getClassParent;
    using Symbol::getClassParentId;
    using Symbol::getLexicalParent;
    using Symbol::getLexicalParentId;
    using Symbol::getSymIndexId;
    using Symbol::getSymTag;
    using Symbol::getType;
    using Symbol::getTypeId;
};
}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::FunctionArgType& param);

namespace std
{
template <>
struct hash<dia::FunctionArgType>
{
    size_t operator()(const dia::FunctionArgType& v) const
    {
        size_t calculatedHash = 0;
        hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), v.getType());

        return calculatedHash;
    }
};
}  // namespace std
