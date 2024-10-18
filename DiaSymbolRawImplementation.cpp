#include "DiaSymbol.h"
#include "Exceptions.h"
namespace dia
{

DWORD Symbol::getSymIndexId(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_symIndexId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_symIndexId failed!", result);
    return retVal;  
}

enum SymTagEnum Symbol::getSymTag(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_symTag(&retVal);
    CHECK_DIACOM_EXCEPTION("get_symTag failed!", result);
    _ASSERT((0 <= retVal) && (retVal < static_cast<DWORD>(SymTagMax)));
    return static_cast<enum SymTagEnum>(retVal);
}

const BstrWrapper Symbol::getName(const Symbol& symbol)
{
    BSTR retVal = nullptr;
    const auto result = symbol.get()->get_name(&retVal);
    CHECK_DIACOM_EXCEPTION("get_name failed!", result);
    return retVal;
}

const Symbol Symbol::getLexicalParent(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_lexicalParent(&retVal);
    CHECK_DIACOM_EXCEPTION("get_lexicalParent failed!", result);
    return Symbol{retVal};
}

const Symbol Symbol::getClassParent(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_classParent(&retVal);
    CHECK_DIACOM_EXCEPTION("get_classParent failed!", result);
    return Symbol{retVal};
}

const Symbol Symbol::getType(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_type(&retVal);
    CHECK_DIACOM_EXCEPTION("get_type failed!", result);
    return Symbol{retVal};
}

enum DataKind Symbol::getDataKind(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_dataKind(&retVal);
    CHECK_DIACOM_EXCEPTION("get_dataKind failed!", result);
    return static_cast<enum DataKind>(retVal);
}

enum LocationType Symbol::getLocationType(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_locationType(&retVal);
    CHECK_DIACOM_EXCEPTION("get_locationType failed!", result);
    _ASSERT((0 <= retVal) && (retVal < static_cast<DWORD>(LocTypeMax)));
    return static_cast<enum LocationType>(retVal);
}

DWORD Symbol::getAddressSection(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_addressSection(&retVal);
    CHECK_DIACOM_EXCEPTION("get_addressSection failed!", result);
    return retVal;
}

DWORD Symbol::getAddressOffset(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_addressOffset(&retVal);
    CHECK_DIACOM_EXCEPTION("get_addressOffset failed!", result);
    return retVal;
}

DWORD Symbol::getRelativeVirtualAddress(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_relativeVirtualAddress(&retVal);
    CHECK_DIACOM_EXCEPTION("get_relativeVirtualAddress failed!", result);
    return retVal;
}

ULONGLONG Symbol::getVirtualAddress(const Symbol& symbol)
{
    ULONGLONG retVal = 0;
    const auto result = symbol.get()->get_virtualAddress(&retVal);
    CHECK_DIACOM_EXCEPTION("get_virtualAddress failed!", result);
    return retVal;
}

DWORD Symbol::getRegisterId(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_registerId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_registerId failed!", result);
    return retVal;
}

LONG Symbol::getOffset(const Symbol& symbol)
{
    LONG retVal = 0;
    const auto result = symbol.get()->get_offset(&retVal);
    CHECK_DIACOM_EXCEPTION("get_offset failed!", result);
    return retVal;
}

ULONGLONG Symbol::getLength(const Symbol& symbol)
{
    ULONGLONG retVal = 0;
    const auto result = symbol.get()->get_length(&retVal);
    CHECK_DIACOM_EXCEPTION("get_length failed!", result);
    return retVal;
}

} // namespace dia