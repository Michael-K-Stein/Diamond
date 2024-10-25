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

/// @brief Returns a string version of the BasicType.
/// @param  The basic type to stringify.
/// @return A string version of the basic type's name.
/// @note DO NOT USE! For internal testing usage only!
/// You most likely want to use `resolveTypeName`.
std::wstring resolveBaseTypeName(enum BasicType baseType);


}  // namespace dia
