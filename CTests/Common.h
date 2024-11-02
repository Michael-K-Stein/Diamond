#pragma once
#include "CppUnitTest.h"
#include "DiaTypeResolution.h"

#define CTESTS_RESOURCES_DIR L".\\..\\..\\CTests\\Resources\\"
#define CTESTS_ADHOC_RESOURCES_DIR L".\\..\\..\\CTests\\Resources\\AdHoc\\out\\"
#define LOCAL_NTDLL_PDB_FILE_PATH CTESTS_RESOURCES_DIR L"ntdll.pdb"
#define LOCAL_NTDLL_DLL_FILE_PATH CTESTS_RESOURCES_DIR L"ntdll.dll"

namespace Microsoft
{
namespace VisualStudio
{
namespace CppUnitTestFramework
{
template <>
static std::wstring ToString<enum BasicType>(const enum BasicType& v)
{
    return dia::resolveBaseTypeName(v);
}
}  // namespace CppUnitTestFramework
}  // namespace VisualStudio
}  // namespace Microsoft
