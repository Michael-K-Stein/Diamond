#include "DiaSymbolPrint.h"
#include "DiaArray.h"
#include "DiaFunction.h"
#include "DiaFunctionArgType.h"
#include "DiaFunctionType.h"
#include "DiaPointer.h"
#include "DiaSymbolTypes.h"
#include "UserDefinedType.h"
#include <ostream>

std::wstring
dia::callingConventionToString(const dia::CvCall& callingConvention)
{
    switch (callingConvention)
    {
    case dia::CvCall::NearC:
        return L"__cdecl";
    case dia::CvCall::FarC:
        return L"__far";
    case dia::CvCall::NearPascal:
        return L"__pascal";
    case dia::CvCall::FarPascal:
        return L"__far __pascal";
    case dia::CvCall::NearFast:
        return L"__fastcall";
    case dia::CvCall::FarFast:
        return L"__far __fastcall";
    case dia::CvCall::Skipped:
        return L"Skipped";
    case dia::CvCall::NearStd:
        return L"__stdcall";
    case dia::CvCall::FarStd:
        return L"__far __stdcall";
    case dia::CvCall::NearSys:
        return L"__syscall";
    case dia::CvCall::FarSys:
        return L"__far __syscall";
    case dia::CvCall::ThisCall:
        return L"__thiscall";
    case dia::CvCall::MipsCall:
        return L"Mips";
    case dia::CvCall::Generic:
        return L"Generic";
    case dia::CvCall::AlphaCall:
        return L"Alpha";
    case dia::CvCall::PpcCall:
        return L"PPC";
    case dia::CvCall::ShCall:
        return L"SH";
    case dia::CvCall::ArmCall:
        return L"ARM";
    case dia::CvCall::Am33Call:
        return L"AM33";
    case dia::CvCall::TriCall:
        return L"TriCore";
    case dia::CvCall::Sh5Call:
        return L"SH-5";
    case dia::CvCall::M32rCall:
        return L"M32R";
    case dia::CvCall::ClrCall:
        return L"CLR";
    case dia::CvCall::Inline:
        return L"inline";
    case dia::CvCall::NearVector:
        return L"Vectorcall";
    case dia::CvCall::Swift:
        return L"Swift";
    case dia::CvCall::Reserved:
        return L"Reserved";
    default:
        throw std::runtime_error("Unrecognized calling convention!");
    }
}

std::wostream& operator<<(std::wostream& os,
                          const dia::CvCall& callingConvention)
{
    os << callingConventionToString(callingConvention);
    return os;
}

std::wostream& operator<<(std::wostream& os, const dia::Function& func)
{
    const dia::FunctionType functionSignature{func.getType()};

    if (func.getIsStatic())
    {
        os << L"static ";
    }
    if (func.getInlSpec())
    {
        os << L"inline ";
    }
    if (func.getVirtual())
    {
        os << L"virtual ";
    }
    os << functionSignature.getCallingConvention() << L" ";
    os << func.getName() << L"(";

    if (!!functionSignature.getObjectPointerType())
    {
        os << functionSignature.getObjectPointerType() << L" this";
    }

    for (const auto& param : func.enumerateParameters())
    {
        os << param;
    }

    for (const auto& param : functionSignature.enumerateParameters())
    {
        os << param;
    }
    os << L")";
    if (func.getPure())
    {
        os << L" = 0";
    }
    os << L";";
    return os;
}

std::wostream& operator<<(std::wostream& os, const dia::FunctionType& funcType)
{
    os << funcType.getCallingConvention();
    return os;
}

std::wostream& operator<<(std::wostream& os, const dia::FunctionArgType& param)
{
    os << param.getType();
    return os;
}
std::wostream& operator<<(std::wostream& os, const dia::PointerType& pointer)
{
    os << pointer.getType() << L"*";
    return os;
}
std::wostream& operator<<(std::wostream& os, const dia::ArrayType& arr)
{
    streamSymbolTypeModifiers(os, arr);
    os << arr.getType() << L" " << arr.getType() << L"[" << arr.getCount()
       << L"]";
    return os;
}

std::wostream& operator<<(std::wostream& os, const dia::Null& null)
{
    throw std::runtime_error("Cannot stream dia::Null type!");
}

std::wostream& operator<<(std::wostream& os, const dia::Data& data)
{
    throw std::runtime_error("Calling unimplemented operator<<(Data) !");
}

std::wostream& operator<<(std::wostream& os, const dia::Exe& exe)
{
    throw std::runtime_error("Calling unimplemented operator<<(Exe) !");
}

std::wostream& operator<<(std::wostream& os, const dia::Udt& udt)
{
    os << dia::UserDefinedType{udt};
    return os;
}
