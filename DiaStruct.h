#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolEnumerator.h"
#include "UserDefinedType.h"
#include "hashing.h"
#include <atlbase.h>
#include <cstddef> // For std::ptrdiff_t
#include <dia2.h>
#include <iterator> // For std::forward_iterator_tag
#include <string>

namespace dia
{
class Struct : public UserDefinedType
{
public:
    using UserDefinedType::UserDefinedType;
    Struct(const UserDefinedType& other) : UserDefinedType{other} {}
    Struct& operator=(const UserDefinedType& other)
    {
        Struct symbol{other};
        return symbol;
    }
    Struct(UserDefinedType&& other) : UserDefinedType{std::move(other)} {}
    Struct& operator=(UserDefinedType&& other)
    {
        Struct symbol{std::move(other)};
        return symbol;
    }

    DiaSymbolEnumerator enumerateMembers() const;

protected:
    using UserDefinedType::get;
};

} // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::Struct& diaStruct);

namespace std
{
template <>
struct hash<dia::Struct>
{
    size_t operator()(const dia::Struct& diaStruct) const
    {
        size_t calculatedHash = 0;
        const size_t nameHash = hash<std::wstring>()(diaStruct.getName());
        hash_combine(calculatedHash, nameHash);

        for (const auto& member : diaStruct.enumerateMembers())
        {
            const auto memberOffset = member.getOffset();
            const auto memberTypeName = member.getTypeName();
            const auto memberName = member.getName();
            hash_combine(calculatedHash, memberOffset, memberTypeName,
                         memberName);
        }

        return calculatedHash;
    }
};
} // namespace std