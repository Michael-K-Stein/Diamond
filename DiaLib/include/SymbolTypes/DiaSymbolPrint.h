#pragma once
#include "SymbolTypes/DiaSymbolTypes.h"
#include <string>

namespace dia
{
std::wstring callingConventionToString(const CvCall& callingConvention);
}

std::wostream& operator<<(std::wostream& os, const dia::CvCall& callingConvention);
