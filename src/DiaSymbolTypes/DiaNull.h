#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"

namespace dia
{
/// @brief Indicates that the symbol has no type.
class Null : protected Symbol
{
public:
    using Symbol::Symbol;
    TRIVIAL_CONVERT(Symbol, Null);
};
} // namespace dia

namespace std
{
template <>
struct hash<dia::Null>
{
    size_t operator()(const dia::Null& diaNull) const
    {
        throw std::runtime_error(
            "Hashing for type dia::Null has not yet been implemented!");
    }
};
} // namespace std
