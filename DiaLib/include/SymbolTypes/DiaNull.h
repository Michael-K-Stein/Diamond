#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"

namespace dia
{
/// @brief Indicates that the symbol has no type.
class Null : public Symbol
{
public:
    using Symbol::Symbol;
    USING_BASE_OPERATORS(Symbol);
};
}  // namespace dia

namespace std
{
template <>
struct hash<dia::Null>
{
    size_t operator()(const dia::Null& diaNull) const { throw std::runtime_error("Hashing for type dia::Null has not yet been implemented!"); }
};
}  // namespace std

std::wostream& operator<<(std::wostream& os, const dia::Null& null);
