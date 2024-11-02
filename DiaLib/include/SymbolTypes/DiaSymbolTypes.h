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
    NearC      = 0x00,  // near right to left push, caller pops stack
    FarC       = 0x01,  // far right to left push, caller pops stack
    NearPascal = 0x02,  // near left to right push, callee pops stack
    FarPascal  = 0x03,  // far left to right push, callee pops stack
    NearFast   = 0x04,  // near left to right push with regs, callee pops stack
    FarFast    = 0x05,  // far left to right push with regs, callee pops stack
    Skipped    = 0x06,  // skipped (unused) call index
    NearStd    = 0x07,  // near standard call
    FarStd     = 0x08,  // far standard call
    NearSys    = 0x09,  // near sys call
    FarSys     = 0x0a,  // far sys call
    ThisCall   = 0x0b,  // this call (this passed in register)
    MipsCall   = 0x0c,  // Mips call
    Generic    = 0x0d,  // Generic call sequence
    AlphaCall  = 0x0e,  // Alpha call
    PpcCall    = 0x0f,  // PPC call
    ShCall     = 0x10,  // Hitachi SuperH call
    ArmCall    = 0x11,  // ARM call
    Am33Call   = 0x12,  // AM33 call
    TriCall    = 0x13,  // TriCore Call
    Sh5Call    = 0x14,  // Hitachi SuperH-5 call
    M32rCall   = 0x15,  // M32R Call
    ClrCall    = 0x16,  // CLR call
    Inline     = 0x17,  // Marker for routines always inlined and thus lacking a
                        // convention
    NearVector = 0x18,  // near left to right push with regs, callee pops stack
    Swift      = 0x19,  // Swift calling convention
    Reserved   = 0x20   // first unused call enumeration
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
