#pragma once
#include "Base.h"
#include "BstrWrapper.h"
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

    using Base::makeFromRaw;
    using Base::operator!;
    using Base::operator=;

    using Base::get;

#if 0
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

    bool isArray() const;
    bool isPointer() const;

    bool isUserDefinedType() const
    {
        return SymTagUDT == getSymTag() || SymTagEnum == getSymTag() ||
               SymTagTypedef == getSymTag();
    }
    UserDefinedType asUserDefinedType() const;
#endif

protected:
    auto getSymIndexId() const { return getSymIndexId(*this); }
    auto getSymTag() const { return getSymTag(*this); }
    auto getName() const { return getName(*this); }
    auto getLexicalParent() const { return getLexicalParent(*this); }
    auto getClassParent() const { return getClassParent(*this); }
    auto getType() const { return getType(*this); }
    auto getDataKind() const { return getDataKind(*this); }
    auto getLocationType() const { return getLocationType(*this); }
    auto getAddressSection() const { return getAddressSection(*this); }
    auto getAddressOffset() const { return getAddressOffset(*this); }
    auto getRelativeVirtualAddress() const
    {
        return getRelativeVirtualAddress(*this);
    }
    auto getVirtualAddress() const { return getVirtualAddress(*this); }
    auto getAddressOffset() const { return getAddressOffset(*this); }
    auto getRegisterId() const { return getRegisterId(*this); }
    auto getOffset() const { return getOffset(*this); }
    auto getLength() const { return getLength(*this); }

private:
    using Base::get;

    using SymbolEnum = DiaSymbolEnumerator<Symbol>;
    using LineEnum =
        DiaSymbolEnumerator<Symbol>; // TODO: Should be
                                     // DiaSymbolEnumerator<dia::Line>

    friend DiaSymbolEnumerator<Symbol>
    enumerate<Symbol>(const Symbol& parentSymbol, enum SymTagEnum symTag,
                      LPCOLESTR name, DWORD compareFlags);
    friend DiaSymbolEnumerator<DataMember>
    enumerate<DataMember>(const Symbol& parentSymbol, enum SymTagEnum symTag,
                          LPCOLESTR name, DWORD compareFlags);
};
} // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::Symbol& v);
std::wostream& operator<<(std::wostream& os, const enum SymTagEnum& v);
std::wostream& operator<<(std::wostream& os, const enum LocationType& v);
