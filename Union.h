#pragma once
#include "UserDefinedType.h"
namespace dia
{
class DiaSymbolEnumerator;

class Union : public UserDefinedType
{
public:
    using UserDefinedType::UserDefinedType;
    Union(const UserDefinedType& base) : UserDefinedType{base} {}
    Union(UserDefinedType&& base) : UserDefinedType{std::move(base)} {}

    DiaSymbolEnumerator enumerateMembers() const;
};
} // namespace dia
std::wostream& operator<<(std::wostream& os, const dia::Union& v);
