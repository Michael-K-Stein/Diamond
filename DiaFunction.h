#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"

namespace dia
{
/// @brief Indicates that the symbol is a function.
class Function : protected Symbol
{
public:
    using Symbol::getName;
    using Symbol::getType;
};
} // namespace dia
