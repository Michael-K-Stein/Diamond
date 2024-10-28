#pragma once
#include "DiaSymbol.h"
#include "DiaSymbolEnumerator.h"
#include "DiaUserDefinedTypeWrapper.h"
#include "Hashing.h"
#include <atlbase.h>
#include <cstddef>  // For std::ptrdiff_t
#include <dia2.h>
#include <iterator>  // For std::forward_iterator_tag
#include <set>
#include <string>

namespace std
{
template <>
struct hash<dia::DEPRECATED__Struct>;
}  // namespace std

namespace dia
{
class DataMember;

class DEPRECATED__Struct : public UserDefinedType
{
public:
    using UserDefinedType::UserDefinedType;

    DEPRECATED__Struct(const UserDefinedType& other)
        : UserDefinedType{other}
    {
    }

    DEPRECATED__Struct& operator=(const UserDefinedType& other)
    {
        DEPRECATED__Struct symbol{other};
        symbol.get().p->AddRef();
        return symbol;
    }

    DEPRECATED__Struct(UserDefinedType&& other)
        : UserDefinedType{std::move(other)}
    {
    }

    DEPRECATED__Struct& operator=(UserDefinedType&& other)
    {
        DEPRECATED__Struct symbol{std::move(other)};
        return symbol;
    }

    /// @brief Query a list of all the user defined types that this struct
    /// depends on.
    /// @return A set of UserDefinedType's which this struct depends
    std::set<UserDefinedType> queryDependsOnTypes() const;
    /// @brief Query a list of all the user defined types that this struct
    /// depends on with forward declerations. That is: user defined types used
    /// by-reference/pointer in this struct.
    /// @return A set of UserDefinedType's which this struct depends
    std::set<UserDefinedType> queryDependsOnForwardTypes() const;

    virtual size_t calcHash() const override;

protected:
    using UserDefinedType::get;

    friend DiaSymbolEnumerator<DataMember>
    enumerate<DataMember>(const Symbol& parentSymbol, enum SymTagEnum symTag, LPCOLESTR name, DWORD compareFlags);
};

}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::DEPRECATED__Struct& diaDEPRECATED__Struct);
