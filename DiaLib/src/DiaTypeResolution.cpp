#include "pch.h"
//
#include "DiaTypeResolution.h"
#include "Exceptions.h"
#include "SymbolTypes/DiaFunctionType.h"
#include <string>

namespace dia
{
static const wchar_t* SYM_TAG_BASE_TYPE_NAMES[] = {
    L"NoType",  // = 0,
    L"Void",    // = 1,
    L"Char",    // = 2,
    L"WChar",   // = 3,
    L"Unknown4",  L"Unknown5",
    L"Int",    // = 6,
    L"UInt",   // = 7,
    L"Float",  // = 8,
    L"BCD",    // = 9,
    L"Bool",   // = 10,
    L"Unknown11", L"Unknown12",
    L"Long",   // = 13,
    L"ULong",  // = 14,
    L"Unknown15", L"Unknown16", L"Unknown17", L"Unknown18", L"Unknown19", L"Unknown20", L"Unknown21", L"Unknown22", L"Unknown23", L"Unknown24",
    L"Currency",  // = 25,
    L"Date",      // = 26,
    L"Variant",   // = 27,
    L"Complex",   // = 28,
    L"Bit",       // = 29,
    L"BSTR",      // = 30,
    L"Hresult",   // = 31,
    L"Char16",    // = 32,  // char16_t
    L"Char32",    // = 33,  // char32_t
    L"Char8",     // = 34,  // char8_t
};
constexpr auto SYM_TAG_BASE_TYPE_NAMES_COUNT = sizeof(SYM_TAG_BASE_TYPE_NAMES) / sizeof(SYM_TAG_BASE_TYPE_NAMES[0]);

std::wstring resolveBasicTypeName(enum BasicType baseType)
{
    if (static_cast<DWORD>(baseType) >= SYM_TAG_BASE_TYPE_NAMES_COUNT)
    {
        throw std::runtime_error("baseType index out of bounds!");
    }
    return SYM_TAG_BASE_TYPE_NAMES[static_cast<DWORD>(baseType)];
}

static std::wstring resolveBaseTypeNameWithLength(enum BasicType baseType, ULONGLONG length)
{
    if (baseType >= SYM_TAG_BASE_TYPE_NAMES_COUNT)
    {
        throw std::runtime_error("baseType index out of bounds!");
    }
    switch (baseType)
    {
    case btChar:
        if (sizeof(char) != length)
        {
            throw std::runtime_error("Invalid type length!");
        }
        return L"char";
    case btBool:
        if (sizeof(bool) != length)
        {
            throw std::runtime_error("Invalid type length!");
        }
        return L"bool";
    case btVoid:
        return L"void";
    case btWChar:
        if (sizeof(WCHAR) != length)
        {
            throw std::runtime_error("Invalid type length!");
        }
        return L"wchar_t";
    case btInt:
    case btLong:
        switch (length)
        {
        case 1:
            return L"int8_t";
        case 2:
            return L"int16_t";
        case 4:
            return L"int32_t";
        case 8:
            return L"int64_t";
        default:
            throw std::runtime_error("Invalid type length!");
        }
        break;
    case btUInt:
    case btULong:
        switch (length)
        {
        case 1:
            return L"uint8_t";
        case 2:
            return L"uint16_t";
        case 4:
            return L"uint32_t";
        case 8:
            return L"uint64_t";
        default:
            throw std::runtime_error("Invalid type length!");
        }
        break;
    case btHresult:
        return L"HRESULT";
    case btBSTR:
        return L"BSTR";
    case btFloat:
        switch (length)
        {
        case 4:
            return L"float";
        case 8:
            return L"double";
        default:
            throw std::runtime_error("Invalid type length!");
        }
        break;
    default:
        return resolveBasicTypeName(baseType);
    }
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
    L"Pointer",
    L"Array",
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
    L"TaggedUnionCase",  // a case of a tagged union UDT type
    L"Max",
};
constexpr auto SYM_TAG_TYPE_NAMES_COUNT = sizeof(SYM_TAG_TYPE_NAMES) / sizeof(SYM_TAG_TYPE_NAMES[0]);

std::wstring symTagToName(const enum SymTagEnum v)
{
    const size_t vIndex = static_cast<size_t>(v);
    if (vIndex >= SYM_TAG_TYPE_NAMES_COUNT)
    {
        throw std::runtime_error("v index out of bounds!");
    }
    return SYM_TAG_TYPE_NAMES[vIndex];
}

constexpr const wchar_t* LOCATION_TYPE_NAMES[] = {
    L"LocIsNull", L"LocIsStatic", L"LocIsTLS",      L"LocIsRegRel",   L"LocIsThisRel",          L"LocIsEnregistered", L"LocIsBitField",
    L"LocIsSlot", L"LocIsIlRel",  L"LocInMetaData", L"LocIsConstant", L"LocIsRegRelAliasIndir", L"LocTypeMax",
};
constexpr const auto LOCATION_TYPE_NAMES_COUNT = sizeof(LOCATION_TYPE_NAMES) / sizeof(LOCATION_TYPE_NAMES[0]);

std::wstring locationTypeToName(const enum LocationType v)
{
    const size_t vIndex = static_cast<size_t>(v);
    if (vIndex >= LOCATION_TYPE_NAMES_COUNT)
    {
        throw std::runtime_error("v index out of bounds!");
    }
    return LOCATION_TYPE_NAMES[vIndex];
}

std::wstring callingConventionToName(const CvCall v)
{
    switch (v)
    {
    case CvCall::NearC:
        return L"Near C";
    case CvCall::FarC:
        return L"Far C";
    case CvCall::NearPascal:
        return L"Near Pascal";
    case CvCall::FarPascal:
        return L"Far Pascal";
    case CvCall::NearFast:
        return L"Near Fast";
    case CvCall::FarFast:
        return L"Far Fast";
    case CvCall::Skipped:
        return L"Skipped";
    case CvCall::NearStd:
        return L"Near Standard";
    case CvCall::FarStd:
        return L"Far Standard";
    case CvCall::NearSys:
        return L"Near System";
    case CvCall::FarSys:
        return L"Far System";
    case CvCall::ThisCall:
        return L"This Call";
    case CvCall::MipsCall:
        return L"MIPS Call";
    case CvCall::Generic:
        return L"Generic Call";
    case CvCall::AlphaCall:
        return L"Alpha Call";
    case CvCall::PpcCall:
        return L"PPC Call";
    case CvCall::ShCall:
        return L"SH Call";
    case CvCall::ArmCall:
        return L"ARM Call";
    case CvCall::Am33Call:
        return L"AM33 Call";
    case CvCall::TriCall:
        return L"TriCore Call";
    case CvCall::Sh5Call:
        return L"SH5 Call";
    case CvCall::M32rCall:
        return L"M32R Call";
    case CvCall::ClrCall:
        return L"CLR Call";
    case CvCall::Inline:
        return L"Inline";
    case CvCall::NearVector:
        return L"Near Vector";
    case CvCall::Swift:
        return L"Swift";
    case CvCall::Reserved:
        return L"Reserved";
    default:
        return L"Unknown";
    }
}

std::wstring resolveCppCallingConventionAttribute(const CvCall v)
{
    // TODO: Remove non-existant calling conventions.
    switch (v)
    {
    case CvCall::NearC:
        return L"__cdecl";
    case CvCall::FarC:
        return L"__far";
    case CvCall::NearPascal:
        return L"__pascal";
    case CvCall::FarPascal:
        return L"__far __pascal";
    case CvCall::NearFast:
        return L"__fastcall";
    case CvCall::FarFast:
        return L"__far __fastcall";
    case CvCall::NearStd:
        return L"__stdcall";
    case CvCall::FarStd:
        return L"__far __stdcall";
    case CvCall::NearSys:
        return L"__syscall";
    case CvCall::FarSys:
        return L"__far __syscall";
    case CvCall::ThisCall:
        return L"__thiscall";
    case CvCall::MipsCall:
        return L"__mipscall";
    case CvCall::Generic:
        return L"__generic";
    case CvCall::AlphaCall:
        return L"__alphacall";
    case CvCall::PpcCall:
        return L"__ppccall";
    case CvCall::ShCall:
        return L"__shcall";
    case CvCall::ArmCall:
        return L"__armcall";
    case CvCall::Am33Call:
        return L"__am33call";
    case CvCall::TriCall:
        return L"__tricall";
    case CvCall::M32rCall:
        return L"__m32rcall";
    case CvCall::ClrCall:
        return L"__clrcall";
    case CvCall::Inline:
        return L"inline";  // Inline functions lack a specific calling convention attribute
    case CvCall::NearVector:
        return L"__vectorcall";
    case CvCall::Swift:
        return L"__swiftcall";
    case CvCall::Skipped:
        __fallthrough;
    case CvCall::Sh5Call:
        __fallthrough;
    case CvCall::Reserved:
        __fallthrough;
    default:
        throw std::invalid_argument("Invalid C/C++ calling convention!");
    }
}

std::string convertGuidToString(const GUID& guid)
{
    char rawGuidString[34];
    if (34 != snprintf(rawGuidString, sizeof(rawGuidString), "%.8lX-%.2hX-%.2hX-%.2hhX%.2hhX%.2hhX%.2hhX%.2hhX%.2hhX%.2hhX%.2hhX", guid.Data1,
                       guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5],
                       guid.Data4[6], guid.Data4[7]))
    {
        throw std::runtime_error("GUID must be 34 ASCII characters long!");
    }
    return std::string{rawGuidString, 34};
}

static std::wstring resolveFunctionTypeName(const FunctionType& funcTypeSymbol, bool withCallingConvention)
{
    const auto functionReturnType = funcTypeSymbol.getType();
    const auto callingConvention  = resolveCppCallingConventionAttribute(funcTypeSymbol.getCallingConvention());

    auto functionSignature        = resolveTypeName(functionReturnType) + std::wstring(L"(");
    if (withCallingConvention)
    {
        functionSignature += callingConvention + std::wstring(L"*)(");
    }

    const auto functionArgCount = funcTypeSymbol.getCount();
    DWORD functionArgIndex      = 0;
    for (const auto& functionArg : funcTypeSymbol)
    {
        functionSignature += resolveTypeName(functionArg.getType());
        if (functionArgIndex < functionArgCount - 1)
        {
            functionSignature += L", ";
        }
        functionArgIndex++;
    }

    functionSignature += L")";

    // Add qualifiers
    if (funcTypeSymbol.getConstType())
    {
        functionSignature += L" const";
    }
    if (funcTypeSymbol.getVolatileType())
    {
        functionSignature += L" volatile";
    }
    // TODO: What does unaligned mean in this context?

    return L"std::function<" + functionSignature + L">";
}

std::wstring resolveTypeName(const Symbol& symbol)
{
    const auto symTag = symbol.getSymTag();

    if (SymTagData == symTag)
    {
        throw std::invalid_argument("Invalid usage! Resolution of type names is "
                                    "invalid for struct members! Try resolving the type name of the "
                                    "/type/ of the member instead.");
    }
    if (SymTagFunctionArgType == symTag)
    {
        throw std::invalid_argument("Invalid usage! Resolution of type names is "
                                    "invalid for function arguments! Try resolving the type name of the "
                                    "/type/ of the argument instead.");
    }

    switch (symTag)
    {
    case SymTagBaseType:
    {
        return resolveBaseTypeName(symbol);
    }
    case SymTagPointerType:
    {
        if (SymTagFunctionType == symbol.getType().getSymTag())
        {
            // Pointers to functions are treated differently since a pointer-to function signature/std::function is odd.
            return resolveFunctionTypeName(symbol.getType(), false);
        }
        return resolveTypeName(symbol.getType()) + L"*";
    }
    case SymTagArrayType:
    {
        const auto elementType  = symbol.getType();
        const auto elementCount = symbol.getCount();
        return L"std::array<" + resolveTypeName(elementType) + L", " + std::to_wstring(elementCount) + L">";
    }
    case SymTagTypedef:
    {
        const auto underlyingType = symbol.getType();
        return resolveTypeName(underlyingType);
    }
    case SymTagUDT:
    case SymTagEnum:
    {
        if (!isSymbolUnnamed(symbol))
        {
            const auto typeName = symbol.getName();
            return typeName;
        }
        // Unnamed symbol.
        // Unfortunately, we cannot always inline the struct, as in cases of std::array<T>, T may not be an anonymous struct.
        // This is a very odd edge case I have only seen once with `_POP_POWER_ACTION` from NTDLL.
        // We will simple enter a buffer which will take up the same amount of space.
        if (LocationType::LocIsBitField == symbol.getLocationType())
        {
            // In case of bitfields, the length is in bits. I do not want to deal with this.
            throw UnimplementedException("Unnamed bitfields as nested types are not supported!");
        }
        const auto length = symbol.getLength();
        return L"/* Unnamed struct */ std::array<char, " + std::to_wstring(length) + L">";
    }
    case SymTagFunctionType:
    {
        const FunctionType funcTypeSymbol = static_cast<const FunctionType&>(symbol);
        return resolveFunctionTypeName(funcTypeSymbol, true);
    }
    default:
        throw std::invalid_argument("Unrecognized SymTag!");
    }
}

std::wstring resolveBaseTypeName(const Symbol& symbol)
{
    try
    {
        return resolveBaseTypeNameWithLength(symbol.getBaseType(), getLength(symbol));
    }
    catch (const DiaComException&)
    {
        return resolveBasicTypeName(symbol.getBaseType());
    }
}
}  // namespace dia
