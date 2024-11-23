#pragma once
#include <stdint.h>

#define TRIVIAL_CONVERT(fromType, toType)                                                                                                            \
    toType(const fromType& other)                                                                                                                    \
        : fromType{other} {};                                                                                                                        \
    toType operator=(const fromType& other)                                                                                                          \
    {                                                                                                                                                \
        fromType::operator=(other);                                                                                                                  \
        return *this;                                                                                                                                \
    }                                                                                                                                                \
    toType(fromType&& other) noexcept                                                                                                                \
        : fromType{other} {};                                                                                                                        \
    toType operator=(fromType&& other) noexcept                                                                                                      \
    {                                                                                                                                                \
        fromType::operator=(std::move(other));                                                                                                       \
        return *this;                                                                                                                                \
    }
#define USING_BASE_OPERATORS(baseType)                                                                                                               \
    using baseType::operator==;                                                                                                                      \
    using baseType::operator!=;                                                                                                                      \
    using baseType::operator!;                                                                                                                       \
    using baseType::operator<;                                                                                                                       \
    using baseType::operator<=;                                                                                                                      \
    using baseType::operator>;                                                                                                                       \
    using baseType::operator>=;

#define XFOR_DIA_SYMBOL_TYPE(opperation)                                                                                                             \
    opperation(Symbol);                                                                                                                              \
    opperation(Null);                                                                                                                                \
    opperation(Exe);                                                                                                                                 \
    opperation(Compiland);                                                                                                                           \
    opperation(CompilandDetails);                                                                                                                    \
    opperation(CompilandEnv);                                                                                                                        \
    opperation(Function);                                                                                                                            \
    opperation(Block);                                                                                                                               \
    opperation(Data);                                                                                                                                \
    opperation(Annotation);                                                                                                                          \
    opperation(Label);                                                                                                                               \
    opperation(PublicSymbol);                                                                                                                        \
    opperation(Udt);                                                                                                                                 \
    opperation(Enum);                                                                                                                                \
    opperation(FunctionType);                                                                                                                        \
    opperation(Pointer);                                                                                                                             \
    opperation(Array);                                                                                                                               \
    opperation(BaseType);                                                                                                                            \
    opperation(Typedef);                                                                                                                             \
    opperation(BaseClass);                                                                                                                           \
    opperation(Friend);                                                                                                                              \
    opperation(FunctionArgType);                                                                                                                     \
    opperation(FuncDebugStart);                                                                                                                      \
    opperation(FuncDebugEnd);                                                                                                                        \
    opperation(UsingNamespace);                                                                                                                      \
    opperation(VTableShape);                                                                                                                         \
    opperation(VTable);                                                                                                                              \
    opperation(Custom);                                                                                                                              \
    opperation(Thunk);                                                                                                                               \
    opperation(CustomType);                                                                                                                          \
    opperation(ManagedType);                                                                                                                         \
    opperation(Dimension);                                                                                                                           \
    opperation(CallSite);                                                                                                                            \
    opperation(InlineSite);                                                                                                                          \
    opperation(BaseInterface);                                                                                                                       \
    opperation(VectorType);                                                                                                                          \
    opperation(MatrixType);                                                                                                                          \
    opperation(HLSLType);                                                                                                                            \
    opperation(Caller);                                                                                                                              \
    opperation(Callee);                                                                                                                              \
    opperation(Export);                                                                                                                              \
    opperation(HeapAllocationSite);                                                                                                                  \
    opperation(CoffGroup);                                                                                                                           \
    opperation(Inlinee);                                                                                                                             \
    opperation(TaggedUnionCase);

namespace dia
{
#define __FORWARD_DECLARE_DIA_TYPE_CLASS(className) class className;
XFOR_DIA_SYMBOL_TYPE(__FORWARD_DECLARE_DIA_TYPE_CLASS);

// Enumeration for function call type
enum class CvCall : uint8_t
{
    NearC      = CV_CALL_NEAR_C,       // near right to left push, caller pops stack
    FarC       = CV_CALL_FAR_C,        // far right to left push, caller pops stack
    NearPascal = CV_CALL_NEAR_PASCAL,  // near left to right push, callee pops stack
    FarPascal  = CV_CALL_FAR_PASCAL,   // far left to right push, callee pops stack
    NearFast   = CV_CALL_NEAR_FAST,    // near left to right push with regs, callee pops stack
    FarFast    = CV_CALL_FAR_FAST,     // far left to right push with regs, callee pops stack
    Skipped    = CV_CALL_SKIPPED,      // skipped (unused) call index
    NearStd    = CV_CALL_NEAR_STD,     // near standard call
    FarStd     = CV_CALL_FAR_STD,      // far standard call
    NearSys    = CV_CALL_NEAR_SYS,     // near sys call
    FarSys     = CV_CALL_FAR_SYS,      // far sys call
    ThisCall   = CV_CALL_THISCALL,     // this call (this passed in register)
    MipsCall   = CV_CALL_MIPSCALL,     // Mips call
    Generic    = CV_CALL_GENERIC,      // Generic call sequence
    AlphaCall  = CV_CALL_ALPHACALL,    // Alpha call
    PpcCall    = CV_CALL_PPCCALL,      // PPC call
    ShCall     = CV_CALL_SHCALL,       // Hitachi SuperH call
    ArmCall    = CV_CALL_ARMCALL,      // ARM call
    Am33Call   = CV_CALL_AM33CALL,     // AM33 call
    TriCall    = CV_CALL_TRICALL,      // TriCore Call
    Sh5Call    = CV_CALL_SH5CALL,      // Hitachi SuperH-5 call
    M32rCall   = CV_CALL_M32RCALL,     // M32R Call
    ClrCall    = CV_CALL_CLRCALL,      // CLR call
    Inline     = CV_CALL_INLINE,       // Marker for routines always inlined
    NearVector = CV_CALL_NEAR_VECTOR,  // near left to right push with regs, callee pops stack
    Swift      = CV_CALL_SWIFT,        // Swift calling convention
    Reserved   = CV_CALL_RESERVED      // first unused call enumeration
};


}  // namespace dia

#define XBY_SYMBOL_TYPE_T(symbol, typeNameSymbol, operation)                                                                                         \
    do                                                                                                                                               \
    {                                                                                                                                                \
        switch (symbol.getSymTag())                                                                                                                  \
        {                                                                                                                                            \
        case SymTagNull:                                                                                                                             \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Null;                                                                                                        \
            operation(*reinterpret_cast<const dia::Null*>(&symbol));                                                                                 \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagArrayType:                                                                                                                        \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Array;                                                                                                       \
            operation(*reinterpret_cast<const dia::Array*>(&symbol));                                                                                \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagPointerType:                                                                                                                      \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Pointer;                                                                                                     \
            operation(*reinterpret_cast<const dia::Pointer*>(&symbol));                                                                              \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagUDT:                                                                                                                              \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Udt;                                                                                                         \
            operation(*reinterpret_cast<const dia::Udt*>(&symbol));                                                                                  \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagFunction:                                                                                                                         \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Function;                                                                                                    \
            operation(*reinterpret_cast<const dia::Function*>(&symbol));                                                                             \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagFunctionType:                                                                                                                     \
        {                                                                                                                                            \
            using typeNameSymbol = dia::FunctionType;                                                                                                \
            operation(*reinterpret_cast<const dia::FunctionType*>(&symbol));                                                                         \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagFunctionArgType:                                                                                                                  \
        {                                                                                                                                            \
            using typeNameSymbol = dia::FunctionArgType;                                                                                             \
            operation(*reinterpret_cast<const dia::FunctionArgType*>(&symbol));                                                                      \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagExe:                                                                                                                              \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Exe;                                                                                                         \
            operation(*reinterpret_cast<const dia::Exe*>(&symbol));                                                                                  \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagData:                                                                                                                             \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Data;                                                                                                        \
            operation(*reinterpret_cast<const dia::Data*>(&symbol));                                                                                 \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagBaseType:                                                                                                                         \
        {                                                                                                                                            \
            using typeNameSymbol = dia::BaseType;                                                                                                    \
            operation(*reinterpret_cast<const dia::BaseType*>(&symbol));                                                                             \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagCompiland:                                                                                                                        \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Compiland;                                                                                                   \
            operation(*reinterpret_cast<const dia::Compiland*>(&symbol));                                                                            \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagCompilandDetails:                                                                                                                 \
        {                                                                                                                                            \
            using typeNameSymbol = dia::CompilandDetails;                                                                                            \
            operation(*reinterpret_cast<const dia::CompilandDetails*>(&symbol));                                                                     \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagCompilandEnv:                                                                                                                     \
        {                                                                                                                                            \
            using typeNameSymbol = dia::CompilandEnv;                                                                                                \
            operation(*reinterpret_cast<const dia::CompilandEnv*>(&symbol));                                                                         \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagLabel:                                                                                                                            \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Label;                                                                                                       \
            operation(*reinterpret_cast<const dia::Label*>(&symbol));                                                                                \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagEnum:                                                                                                                             \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Enum;                                                                                                        \
            operation(*reinterpret_cast<const dia::Enum*>(&symbol));                                                                                 \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagTypedef:                                                                                                                          \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Typedef;                                                                                                     \
            operation(*reinterpret_cast<const dia::Typedef*>(&symbol));                                                                              \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagBaseClass:                                                                                                                        \
        {                                                                                                                                            \
            using typeNameSymbol = dia::BaseClass;                                                                                                   \
            operation(*reinterpret_cast<const dia::BaseClass*>(&symbol));                                                                            \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagFriend:                                                                                                                           \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Friend;                                                                                                      \
            operation(*reinterpret_cast<const dia::Friend*>(&symbol));                                                                               \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagAnnotation:                                                                                                                       \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Annotation;                                                                                                  \
            operation(*reinterpret_cast<const dia::Annotation*>(&symbol));                                                                           \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagPublicSymbol:                                                                                                                     \
        {                                                                                                                                            \
            using typeNameSymbol = dia::PublicSymbol;                                                                                                \
            operation(*reinterpret_cast<const dia::PublicSymbol*>(&symbol));                                                                         \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagCustom:                                                                                                                           \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Custom;                                                                                                      \
            operation(*reinterpret_cast<const dia::Custom*>(&symbol));                                                                               \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagThunk:                                                                                                                            \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Thunk;                                                                                                       \
            operation(*reinterpret_cast<const dia::Thunk*>(&symbol));                                                                                \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagCustomType:                                                                                                                       \
        {                                                                                                                                            \
            using typeNameSymbol = dia::CustomType;                                                                                                  \
            operation(*reinterpret_cast<const dia::CustomType*>(&symbol));                                                                           \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagManagedType:                                                                                                                      \
        {                                                                                                                                            \
            using typeNameSymbol = dia::ManagedType;                                                                                                 \
            operation(*reinterpret_cast<const dia::ManagedType*>(&symbol));                                                                          \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagDimension:                                                                                                                        \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Dimension;                                                                                                   \
            operation(*reinterpret_cast<const dia::Dimension*>(&symbol));                                                                            \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagCallSite:                                                                                                                         \
        {                                                                                                                                            \
            using typeNameSymbol = dia::CallSite;                                                                                                    \
            operation(*reinterpret_cast<const dia::CallSite*>(&symbol));                                                                             \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagInlineSite:                                                                                                                       \
        {                                                                                                                                            \
            using typeNameSymbol = dia::InlineSite;                                                                                                  \
            operation(*reinterpret_cast<const dia::InlineSite*>(&symbol));                                                                           \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagBaseInterface:                                                                                                                    \
        {                                                                                                                                            \
            using typeNameSymbol = dia::BaseInterface;                                                                                               \
            operation(*reinterpret_cast<const dia::BaseInterface*>(&symbol));                                                                        \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagVectorType:                                                                                                                       \
        {                                                                                                                                            \
            using typeNameSymbol = dia::VectorType;                                                                                                  \
            operation(*reinterpret_cast<const dia::VectorType*>(&symbol));                                                                           \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagMatrixType:                                                                                                                       \
        {                                                                                                                                            \
            using typeNameSymbol = dia::MatrixType;                                                                                                  \
            operation(*reinterpret_cast<const dia::MatrixType*>(&symbol));                                                                           \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagHLSLType:                                                                                                                         \
        {                                                                                                                                            \
            using typeNameSymbol = dia::HLSLType;                                                                                                    \
            operation(*reinterpret_cast<const dia::HLSLType*>(&symbol));                                                                             \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagCaller:                                                                                                                           \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Caller;                                                                                                      \
            operation(*reinterpret_cast<const dia::Caller*>(&symbol));                                                                               \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagCallee:                                                                                                                           \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Callee;                                                                                                      \
            operation(*reinterpret_cast<const dia::Callee*>(&symbol));                                                                               \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagExport:                                                                                                                           \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Export;                                                                                                      \
            operation(*reinterpret_cast<const dia::Export*>(&symbol));                                                                               \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagHeapAllocationSite:                                                                                                               \
        {                                                                                                                                            \
            using typeNameSymbol = dia::HeapAllocationSite;                                                                                          \
            operation(*reinterpret_cast<const dia::HeapAllocationSite*>(&symbol));                                                                   \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagCoffGroup:                                                                                                                        \
        {                                                                                                                                            \
            using typeNameSymbol = dia::CoffGroup;                                                                                                   \
            operation(*reinterpret_cast<const dia::CoffGroup*>(&symbol));                                                                            \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagInlinee:                                                                                                                          \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Inlinee;                                                                                                     \
            operation(*reinterpret_cast<const dia::Inlinee*>(&symbol));                                                                              \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        case SymTagTaggedUnionCase:                                                                                                                  \
        {                                                                                                                                            \
            using typeNameSymbol = dia::TaggedUnionCase;                                                                                             \
            operation(*reinterpret_cast<const dia::TaggedUnionCase*>(&symbol));                                                                      \
            break;                                                                                                                                   \
        }                                                                                                                                            \
                                                                                                                                                     \
        default:                                                                                                                                     \
        {                                                                                                                                            \
            printf("%d\n", symbol.getSymTag());                                                                                                      \
            _ASSERT_EXPR(false, L"Invalid SymTag!");                                                                                                 \
            throw std::runtime_error("Invalid SymTag!");                                                                                             \
        }                                                                                                                                            \
        }                                                                                                                                            \
    } while (0)
