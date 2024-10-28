#include "pch.h"
//
#include "DiaUDT.h"

namespace dia
{
size_t Udt::calcHash() const { return std::hash<dia::Udt>()(*this); }
}  // namespace dia
