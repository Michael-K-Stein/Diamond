#pragma once
#include "Base.h"
#include <atlbase.h>
#include <dia2.h>
#include <iostream>
#include <string>

namespace dia
{

// Forward decleration
class Symbol;
class DataMember;

template <typename T>
class DiaSymbolEnumerator;

template <typename T>
DiaSymbolEnumerator<T> enumerate(const Symbol& parentSymbol,
                                 enum SymTagEnum symTag, LPCOLESTR name,
                                 DWORD compareFlags);

// Derived Types
class UserDefinedType;

class Symbol : public Base<IDiaSymbol>
{
public:
    using Base::Base;

    const std::wstring getName() const;
    LONG getOffset() const;
    Symbol getType() const;
    std::wstring getTypeName() const;
    enum SymTagEnum getSymTag() const;
    DWORD getBaseType() const;
    DWORD getCount() const;
    enum LocationType getLocationType() const;
    DWORD getBitPosition() const;
    ULONGLONG getLength() const;
    bool isVolatile() const;

    using Base::makeFromRaw;
    using Base::operator!;
    using Base::operator=;

    bool isArray() const;
    bool isPointer() const;

    bool isUserDefinedType() const
    {
        return SymTagUDT == getSymTag() || SymTagEnum == getSymTag() ||
               SymTagTypedef == getSymTag();
    }
    UserDefinedType asUserDefinedType() const;

protected:
    using Base::get;

private:
    friend DiaSymbolEnumerator<Symbol>
    enumerate<Symbol>(const Symbol& parentSymbol, enum SymTagEnum symTag,
                      LPCOLESTR name, DWORD compareFlags);
    friend DiaSymbolEnumerator<DataMember>
    enumerate<DataMember>(const Symbol& parentSymbol, enum SymTagEnum symTag,
                          LPCOLESTR name, DWORD compareFlags);
};
} // namespace dia

// namespace std
//{
// template <>
// struct hash<dia::Symbol>
//{
//    size_t operator()(const dia::Symbol& diaSymbol) const
//    {
//        static_assert(false, "Hashing of arbitrary symbol is unimplemented!");
//    }
//};
//} // namespace std
std::wostream& operator<<(std::wostream& os, const dia::Symbol& v);
std::wostream& operator<<(std::wostream& os, const enum SymTagEnum& v);
std::wostream& operator<<(std::wostream& os, const enum LocationType& v);
