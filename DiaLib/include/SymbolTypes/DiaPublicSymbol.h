#pragma once
#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"
#include "DiaTypeResolution.h"

namespace dia
{
/// @brief When the .exe file is created, each public symbol (at a minimum, each global function and data symbol) is given a SymTagPublicSymbol tag.
class PublicSymbol : public Symbol
{
public:
    PublicSymbol() = default;
    using Symbol::Symbol;
    USING_BASE_OPERATORS(Symbol);

    using Symbol::getAddressOffset;
    using Symbol::getAddressSection;
    using Symbol::getCode;
    using Symbol::getFunction;
    using Symbol::getLength;
    using Symbol::getLexicalParent;
    using Symbol::getLexicalParentId;
    using Symbol::getLocationType;
    using Symbol::getManaged;
    using Symbol::getMsil;
    using Symbol::getName;
    using Symbol::getRelativeVirtualAddress;
    using Symbol::getSymIndexId;
    using Symbol::getSymTag;
    using Symbol::getUndecoratedName;
    using Symbol::getUndecoratedNameEx;
};
}  // namespace dia

namespace std
{
template <>
struct hash<dia::PublicSymbol>
{
    size_t operator()(const dia::PublicSymbol& v) const
    {
        size_t calculatedHash = 0;
        hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), v.getAddressOffset(), v.getAddressSection(), v.getCode(),
                     v.getFunction(), v.getLength(), v.getLexicalParent(), v.getLocationType(), v.getManaged(), v.getMsil(), v.getName(),
                     v.getRelativeVirtualAddress(), v.getUndecoratedName());
        return calculatedHash;
    }
};
}  // namespace std

std::wostream& operator<<(std::wostream& os, const dia::PublicSymbol& data);
