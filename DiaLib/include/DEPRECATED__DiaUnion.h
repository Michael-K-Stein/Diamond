#pragma once
#include "DiaUserDefinedTypeWrapper.h"
#include "Hashing.h"

namespace std
{
template <>
struct hash<dia::DEPRECATED__Union>;
}  // namespace std

namespace dia
{
class DataMember;
template <typename T>
class DiaSymbolEnumerator;

class DEPRECATED__Union : public UserDefinedType
{
public:
    using UserDefinedType::UserDefinedType;

    DEPRECATED__Union(const UserDefinedType& base)
        : UserDefinedType{base}
    {
    }

    DEPRECATED__Union(UserDefinedType&& base)
        : UserDefinedType{std::move(base)}
    {
    }

    DiaSymbolEnumerator<DataMember> enumerateMembers() const;

    virtual size_t calcHash() const override;

private:
    friend DiaSymbolEnumerator<DataMember>
    enumerate<DataMember>(const Symbol& parentSymbol, enum SymTagEnum symTag, LPCOLESTR name, DWORD compareFlags);
};
}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::DEPRECATED__Union& v);
