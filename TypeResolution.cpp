#include "TypeResolution.h"

static const wchar_t* SYM_TAG_BASE_TYPE_NAMES[] = {
    L"NoType", // = 0,
    L"VOID",   // = 1,
    L"CHAR",   // = 2,
    L"WCHAR",  // = 3,
    L"Unknown4",  L"Unknown5",
    L"INT",     // = 6,
    L"UINT",    // = 7,
    L"float",   // = 8,
    L"BCD",     // = 9,
    L"BOOLEAN", // = 10,
    L"Unknown11", L"Unknown12",
    L"LONG",  // = 13,
    L"ULONG", // = 14,
    L"Unknown15", L"Unknown16", L"Unknown17", L"Unknown18", L"Unknown19",
    L"Unknown20", L"Unknown21", L"Unknown22", L"Unknown23", L"Unknown24",
    L"Currency", // = 25,
    L"Date",     // = 26,
    L"Variant",  // = 27,
    L"Complex",  // = 28,
    L"Bit",      // = 29,
    L"BSTR",     // = 30,
    L"HRESULT",  // = 31,
    L"Char16",   // = 32,  // char16_t
    L"Char32",   // = 33,  // char32_t
    L"Char8",    // = 34,  // char8_t
};
constexpr auto SYM_TAG_BASE_TYPE_NAMES_COUNT =
    sizeof(SYM_TAG_BASE_TYPE_NAMES) / sizeof(SYM_TAG_BASE_TYPE_NAMES[0]);

static inline std::wstring resolveBaseTypeName(DWORD baseType)
{
    if (baseType >= SYM_TAG_BASE_TYPE_NAMES_COUNT)
    {
        throw std::runtime_error("baseType index out of bounds!");
    }
    return SYM_TAG_BASE_TYPE_NAMES[baseType];
}

static const wchar_t* SYM_TAG_TYPE_NAMES[] = {
    L"Null",
    L"Exe",
    L"Compiland",
    L"CompilandDetails",
    L"CompilandEnv",
    L"Function",
    L"Block",
    L"Data",
    L"Annotation",
    L"Label",
    L"PublicSymbol",
    L"UDT",
    L"Enum",
    L"FunctionType",
    L"PointerType",
    L"ArrayType",
    L"BaseType",
    L"Typedef",
    L"BaseClass",
    L"Friend",
    L"FunctionArgType",
    L"FuncDebugStart",
    L"FuncDebugEnd",
    L"UsingNamespace",
    L"VTableShape",
    L"VTable",
    L"Custom",
    L"Thunk",
    L"CustomType",
    L"ManagedType",
    L"Dimension",
    L"CallSite",
    L"InlineSite",
    L"BaseInterface",
    L"VectorType",
    L"MatrixType",
    L"HLSLType",
    L"Caller",
    L"Callee",
    L"Export",
    L"HeapAllocationSite",
    L"CoffGroup",
    L"Inlinee",
    L"TaggedUnionCase", // a case of a tagged union UDT type
    L"Max",
};
constexpr auto SYM_TAG_TYPE_NAMES_COUNT =
    sizeof(SYM_TAG_TYPE_NAMES) / sizeof(SYM_TAG_TYPE_NAMES[0]);
std::wstring dia::symTagToName(const enum SymTagEnum v)
{
    const size_t vIndex = static_cast<size_t>(v);
    if (vIndex >= SYM_TAG_TYPE_NAMES_COUNT)
    {
        throw std::runtime_error("v index out of bounds!");
    }
    return SYM_TAG_TYPE_NAMES[vIndex];
}

constexpr const wchar_t* LOCATION_TYPE_NAMES[] = {
    L"LocIsNull",     L"LocIsStatic",   L"LocIsTLS",
    L"LocIsRegRel",   L"LocIsThisRel",  L"LocIsEnregistered",
    L"LocIsBitField", L"LocIsSlot",     L"LocIsIlRel",
    L"LocInMetaData", L"LocIsConstant", L"LocIsRegRelAliasIndir",
    L"LocTypeMax",
};
constexpr const auto LOCATION_TYPE_NAMES_COUNT =
    sizeof(LOCATION_TYPE_NAMES) / sizeof(LOCATION_TYPE_NAMES[0]);

std::wstring dia::locationTypeToName(const enum LocationType v)
{
    const size_t vIndex = static_cast<size_t>(v);
    if (vIndex >= LOCATION_TYPE_NAMES_COUNT)
    {
        throw std::runtime_error("v index out of bounds!");
    }
    return LOCATION_TYPE_NAMES[vIndex];
}

std::wstring dia::resolveTypeName(const Symbol& symbol)
{
    const auto symTag = symbol.getSymTag();

    if (SymTagData == symTag)
    {
        throw std::runtime_error(
            "Invalid usage! Resolution of type names is "
            "invalid for struct members! Try resolving the type name of the "
            "/type/ of the member instead.");
    }

    switch (symTag)
    {
    case SymTagBaseType:
    {
        return resolveBaseTypeName(symbol.getBaseType());
    }
    case SymTagPointerType:
    {
        return resolveTypeName(symbol.getType()) + L"*";
    }
    case SymTagArrayType:
    {
        const auto elementType = symbol.getType();
        const auto elementCount = symbol.getCount();
        return resolveTypeName(elementType) + L"[" +
               std::to_wstring(elementCount) + L"]";
    }
    case SymTagTypedef:
    {
        const auto underlyingType = symbol.getType();
        return resolveTypeName(underlyingType);
    }
    case SymTagUDT:
    case SymTagEnum:
    {
        const auto typeName = symbol.getName();
        return typeName;
    }
    default:
        std::wcerr << L"Unknown tag type: " << std::to_wstring(symTag)
                   << std::endl;
        return L"unknown";
    }
}
