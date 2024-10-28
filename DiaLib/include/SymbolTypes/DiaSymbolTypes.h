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

namespace dia
{
class Symbol;
class Null;
class Exe;
class Compiland;
class CompilandDetails;
class CompilandEnv;
class Function;
class Block;
class Data;
class Annotation;
class Label;
class PublicSymbol;
class Udt;
class Enum;
class FunctionType;
class Pointer;
class Array;
class BaseType;
class Typedef;
class BaseClass;
class Friend;
class FunctionArgType;
class FuncDebugStart;
class FuncDebugEnd;
class UsingNamespace;
class VTableShape;
class VTable;
class Custom;
class Thunk;
class CustomType;
class ManagedType;
class Dimension;
class CallSite;
class InlineSite;
class BaseInterface;
class VectorType;
class MatrixType;
class HLSLType;
class Caller;
class Callee;
class Export;
class HeapAllocationSite;
class CoffGroup;
class Inlinee;
class TaggedUnionCase;

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
        /* case SymTagExe:                                                                                                                           \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Exe;                                                                                                         \
            operation(*reinterpret_cast<const dia::Exe*>(&symbol));                                                                                  \
            break;                                                                                                                                   \
        }    */                                                                                                                                      \
        case SymTagData:                                                                                                                             \
        {                                                                                                                                            \
            using typeNameSymbol = dia::Data;                                                                                                        \
            operation(*reinterpret_cast<const dia::Data*>(&symbol));                                                                                 \
            break;                                                                                                                                   \
        }                                                                                                                                            \
        /*TODO: IMPLEMENT !! */ case SymTagBaseType:                                                                                                 \
            using typeNameSymbol = dia::BaseType;                                                                                                    \
            operation(*reinterpret_cast<const dia::BaseType*>(&symbol));                                                                             \
            break;                                                                                                                                   \
        default:                                                                                                                                     \
        {                                                                                                                                            \
            printf("%d\n", symbol.getSymTag());                                                                                                      \
            _ASSERT_EXPR(false, L"Invalid SymTag!");                                                                                                 \
            throw std::runtime_error("Invalid SymTag!");                                                                                             \
        }                                                                                                                                            \
        } /* End of switch statment */                                                                                                               \
    } while (0)
