#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"

namespace dia
{
/// @brief Indicates that the symbol is an .exe file.
/// There is only one SymTagExe symbol per symbol store.
/// It serves as the global scope and does not have a lexical parent.
class Exe : protected Symbol
{
public:
    using Symbol::Symbol;
    TRIVIAL_CONVERT(Symbol, Exe);

    using Symbol::getSymTag;
};
}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::Exe& exe);

namespace std
{
template <>
struct hash<dia::Exe>
{
    size_t operator()(const dia::Exe& v) const
    {
        size_t calculatedHash = 0;
        hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())));

        return calculatedHash;
    }
};
}  // namespace std
