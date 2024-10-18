#pragma once
#include "DiaSymbol.h"
#include <string>
namespace dia
{
/// @brief Resolves a symbol to its full type name
/// @param symbol The symbol to resolve
/// @return A string which represents the closest match to the original "C type"
/// assigned to the source symbol.
std::wstring resolveTypeName(const Symbol& symbol);

std::wstring symTagToName(const enum SymTagEnum v);
std::wstring locationTypeToName(const enum LocationType v);

} // namespace dia
