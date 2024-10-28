#include "pch.h"
//
#include "DiaSymbolEnumerator.h"
#include "DiaUserDefinedTypeWrapper.h"

namespace dia
{
DiaSymbolEnumerator<Data> UserDefinedType::enumerateMembers() const { return enumerate<Data>(*this, SymTagData); }

}  // namespace dia
