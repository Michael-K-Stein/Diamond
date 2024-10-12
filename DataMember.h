#pragma once
#include "DiaSymbol.h"
namespace dia
{
class DataMember : public Symbol
{
public:
    using Symbol::Symbol;
    DataMember(const Symbol& other);
    DataMember& operator=(const Symbol& other);
    DataMember(Symbol&& other);
    DataMember& operator=(Symbol&& other);

    std::wstring getFieldName() const;
    Symbol getFieldCType() const;

protected:
private:
};
} // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::DataMember& member);
