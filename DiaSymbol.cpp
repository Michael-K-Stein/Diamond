#pragma once
#include "DiaSymbol.h"
#include "Exceptions.h"
#include "TypeResolution.h"
#include "UserDefinedType.h"

namespace dia
{
const std::wstring Symbol::getName() const
{
    if (!get())
    {
        return L"";
    }

    BSTR nameBSTR = nullptr;
    if (SUCCEEDED(get()->get_name(&nameBSTR)) && nameBSTR)
    {
        std::wstring name(nameBSTR, SysStringLen(nameBSTR));
        SysFreeString(nameBSTR);
        return name;
    }
    return L"";
}

LONG Symbol::getOffset() const
{
    LONG offset = 0;
    const auto result = get()->get_offset(&offset);
    CHECK_DIACOM_EXCEPTION("Failed to get symbol's offset!", result);
    return offset;
}

// Update the GetType() function in the Symbol class
Symbol Symbol::getType() const
{
    if (!get())
    {
        return {};
    }

    Symbol typeSymbol{};
    const auto result = get()->get_type(&typeSymbol.makeFromRaw());
    CHECK_DIACOM_EXCEPTION("Failed to get symbol's type symbol!", result);
    return typeSymbol;
}

std::wstring Symbol::getTypeName() const { return resolveTypeName(*this); }

enum SymTagEnum Symbol::getSymTag() const
{
    DWORD symTag = 0;
    const auto result = get()->get_symTag(&symTag);
    CHECK_DIACOM_EXCEPTION("Failed to get symbol's SymTag!", result);
    return static_cast<enum SymTagEnum>(symTag);
}

DWORD Symbol::getBaseType() const
{
    DWORD baseType = 0;
    const auto result = get()->get_baseType(&baseType);
    CHECK_DIACOM_EXCEPTION("Failed to get symbol's base type!", result);
    return baseType;
}

DWORD Symbol::getCount() const
{
    DWORD count = 0;
    const auto result = get()->get_count(&count);
    CHECK_DIACOM_EXCEPTION("Failed to get symbol's count!", result);
    return count;
}

enum LocationType Symbol::getLocationType() const
{
    DWORD locationType = 0;
    const auto result = get()->get_locationType(&locationType);
    CHECK_DIACOM_EXCEPTION("Failed to get symbol's location type!", result);
    return static_cast<enum LocationType>(locationType);
}

DWORD Symbol::getBitPosition() const
{
    if (getLocationType() != LocIsBitField)
    {
        throw std::runtime_error(
            "BitPosition is only valid for LocIsBitField types!");
    }
    DWORD position = 0;
    const auto result = get()->get_bitPosition(&position);
    CHECK_DIACOM_EXCEPTION("Failed to get symbol's bit position!", result);
    return position;
}

ULONGLONG Symbol::getLength() const
{
    ULONGLONG length = 0;
    const auto result = get()->get_length(&length);
    CHECK_DIACOM_EXCEPTION("Failed to get symbol's length!", result);
    return length;
}

bool Symbol::isVolatile() const
{
    BOOL volatileType = 0;
    const auto result = get()->get_volatileType(&volatileType);
    CHECK_DIACOM_EXCEPTION("Failed to get symbol's volatility type!", result);
    return (FALSE != volatileType) ? true : false;
}

bool Symbol::isArray() const { return SymTagArrayType == getSymTag(); }

UserDefinedType& Symbol::asUserDefinedType() const
{
    UserDefinedType udt(*this);
    return udt;
}

} // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::Symbol& v)
{
    os << L"/* " << v.getType().getSymTag() << L", " << v.getLocationType()
       << " */ \t ";
    if (v.getType().isVolatile())
    {
        os << L"volatile ";
    }
    if (v.isUserDefinedType())
    {
        const auto& udt = v.asUserDefinedType();
        os << udt;
    }
    else if (v.getType().isArray())
    {
        const auto arrayField = v.getType();
        const auto elementType = arrayField.getType();
        os << elementType.getTypeName() << L" " << v.getName() << L"[0x"
           << std::hex << arrayField.getCount() << L"]";
    }
    else
    {
        os << v.getType().getTypeName() << L" " << v.getName();
    }

    return os;
}

std::wostream& operator<<(std::wostream& os, const enum SymTagEnum& v)
{
    os << dia::symTagToName(v);
    return os;
}

std::wostream& operator<<(std::wostream& os, const enum LocationType& v)
{
    os << dia::locationTypeToName(v);
    return os;
}
