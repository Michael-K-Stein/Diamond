#pragma once
#include <string>

namespace dia
{
const std::wstring getBasicSymbolSearchPath(bool withSrv = true);
const std::wstring getSymbolSearchPathForExecutable(const std::wstring& executableFilePath, bool withSrv = true);
}  // namespace dia