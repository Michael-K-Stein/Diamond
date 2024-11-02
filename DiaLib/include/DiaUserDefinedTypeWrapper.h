#pragma once
#include "AnyString.h"
#include "SymbolTypes/DiaUDT.h"
#include <set>

namespace dia
{

class DataSource;

/// @brief High level wrapper for any UserDefinedType
class UserDefinedType : public Udt
{
public:
    using Udt::Udt;
    USING_BASE_OPERATORS(Udt);

    using Udt::calcHash;

    DiaSymbolEnumerator<Data> enumerateMembers() const;

    std::set<UserDefinedType> queryDependencies() const;
    std::set<UserDefinedType> queryForwardDependencies() const;

    Data getMember(const AnyString& memberName) const;

protected:
    using Udt::get;

private:
    friend class DataSource;
};

using Class       = UserDefinedType;
using TaggedUnion = UserDefinedType;
using Struct      = UserDefinedType;
using Union       = UserDefinedType;
using Interface   = UserDefinedType;

}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::UserDefinedType& udt);
