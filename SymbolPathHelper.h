#pragma once
#include <string>
namespace dia
{
const std::wstring getBasicSymbolSearchPath();
const std::wstring
getSymbolSearchPathForExecutable(const std::wstring& executableFilePath);
} // namespace dia