#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"
#include "DiaTypeResolution.h"

namespace dia
{
/// @brief There is one SymTagCompiland symbol for each Compiland linked to the .exe file. Compiland information is split between symbols with a
/// SymTagCompiland tag, which can be retrieved without loading additional compiland symbols, and symbols with a SymTagCompilandDetails tag, which
/// might require loading additional symbols.
class Compiland : public Symbol
{
public:
    Compiland() = default;
    using Symbol::Symbol;
    USING_BASE_OPERATORS(Symbol);

    using Symbol::getEditAndContinueEnabled;
    using Symbol::getLexicalParent;
    using Symbol::getLexicalParentId;
    using Symbol::getLibraryName;
    using Symbol::getName;
    using Symbol::getSourceFileName;
    using Symbol::getSymIndexId;
    using Symbol::getSymTag;
};
}  // namespace dia

namespace std
{
template <>
struct hash<dia::Compiland>
{
    size_t operator()(const dia::Compiland& v) const
    {
        size_t calculatedHash = 0;
        hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), v.getEditAndContinueEnabled(), v.getLibraryName(), v.getName(),
                     v.getSourceFileName());
        return calculatedHash;
    }
};
}  // namespace std

std::wostream& operator<<(std::wostream& os, const dia::Compiland& data);
