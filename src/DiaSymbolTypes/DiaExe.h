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
};
} // namespace dia
