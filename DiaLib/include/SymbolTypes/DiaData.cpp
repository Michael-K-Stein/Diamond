#include "pch.h"
//
#include "DiaData.h"

namespace dia
{
size_t Data::calcHash() const { return std::hash<dia::Data>()(*this); }
}  // namespace dia
