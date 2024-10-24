#pragma once
#include "DiaTypeResolution.h"
#include <ostream>
#include <type_traits>

static std::wostream& operator<<(std::wostream& os, const enum SymTagEnum& v)
{
    os << dia::symTagToName(v);
    return os;
}

static std::wostream& operator<<(std::wostream& os, const enum LocationType& v)
{
    os << dia::locationTypeToName(v);
    return os;
}
