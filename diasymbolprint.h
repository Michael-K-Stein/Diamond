#pragma once
#include "DiaSymbolTypes.h"
#include <string>

namespace dia
{
std::wstring callingConventionToString(const CvCall& callingConvention);
}

std::wostream& operator<<(std::wostream& os,
                          const dia::CvCall& callingConvention);
std::wostream& operator<<(std::wostream& os, const dia::ArrayType& arr);
