#include "pch.h"
//
#include "DiaSymbolEnumerator.h"
#include "DiaUserDefinedTypeWrapper.h"
#include "SymbolTypes/DiaPointer.h"
#include <set>
#include <stdexcept>

namespace dia
{
DiaSymbolEnumerator<Data> UserDefinedType::enumerateMembers() const { return enumerate<Data>(*this, SymTagData); }

std::set<Symbol> UserDefinedType::queryDependencies() const { return dia::queryDependencies(*this); }

std::set<UserDefinedType> UserDefinedType::queryForwardDependencies() const
{

    std::set<UserDefinedType> types{};
    for (const auto& member : enumerateMembers())
    {
        const auto& cType = member.getType();
        if (!cType.isPointer())
        {
            continue;
        }
        const Pointer& cTypeAsPointer = static_cast<const Pointer&>(cType);
        // Get the pointed-to type
        const auto decayType = cTypeAsPointer.getType();
        if (!decayType.isUserDefinedType())
        {
            continue;
        }
        types.insert(static_cast<const UserDefinedType&>(decayType));
    }
    return types;
}

Data UserDefinedType::getMember(const AnyString& memberName) const
{
    auto dataMembers = enumerate<Data>(*this, SymTagData, memberName.c_str());
    if (1 != dataMembers.count())
    {
        throw dia::TooManyMatchesForFindException("Too many members match the given name!");
    }
    for (const auto& member : dataMembers)
    {
        return member;
    }
    throw std::runtime_error("Unreachable code reached!");
}
}  // namespace dia
