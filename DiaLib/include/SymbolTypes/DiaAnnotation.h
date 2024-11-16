#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolTypes.h"
#include "DiaTypeResolution.h"

namespace dia
{
/// @brief A location program code can be annotated with a SymTagAnnotation symbol.
class Annotation : public Symbol
{
public:
    Annotation() = default;
    using Symbol::Symbol;
    USING_BASE_OPERATORS(Symbol);

    using Symbol::getAddressOffset;
    using Symbol::getAddressSection;
    using Symbol::getDataKind;
    using Symbol::getRelativeVirtualAddress;
    using Symbol::getSymIndexId;
    using Symbol::getSymTag;
    using Symbol::getValue;
    using Symbol::getVirtualAddress;
};
}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::Annotation& data);
