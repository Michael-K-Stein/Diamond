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
std::wstring resolveBaseTypeName(const Symbol& symbol);

std::wstring symTagToName(const enum SymTagEnum v);
std::wstring locationTypeToName(const enum LocationType v);
/// @brief Returns the string name of the CvCall value
/// @param v A calling convention value from the enum.
/// @return A string version of the name from the enum.
std::wstring callingConventionToName(const CvCall v);
/// @brief Returns a C-style function modifier attribute which represents the given calling convention.
/// @param v A calling convention value from the enum.
/// @return One of "__stdcall", "__thiscall", "__cdecl", ...
std::wstring resolveCppCallingConventionAttribute(const CvCall v);

/// @brief Returns a string version of the BasicType.
/// @param  The basic type to stringify.
/// @return A string version of the basic type's name.
/// @note DO NOT USE! For internal testing usage only!
/// You most likely want to use `resolveTypeName`.
std::wstring resolveBasicTypeName(enum BasicType baseType);


}  // namespace dia
