#pragma once

#define TRIVIAL_CONVERT(fromType, toType)                                      \
    toType(const fromType& other) : fromType{other} {};                        \
    toType operator=(const fromType& other)                                    \
    {                                                                          \
        fromType::operator=(other);                                            \
        return *this;                                                          \
    }                                                                          \
    toType(fromType&& other) noexcept : fromType{other} {};                    \
    toType operator=(fromType&& other) noexcept                                \
    {                                                                          \
        fromType::operator=(std::move(other));                                 \
        return *this;                                                          \
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
class PointerType;
class ArrayType;
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
} // namespace dia

#define XBY_SYMBOL_TYPE_T(symbol, typeNameSymbol, operation)                   \
    do                                                                         \
    {                                                                          \
        switch (symbol.getSymTag())                                            \
        {                                                                      \
        case SymTagNull:                                                       \
        {                                                                      \
            using typeNameSymbol = dia::Null;                                  \
            operation(*reinterpret_cast<const dia::Null*>(&symbol));           \
            break;                                                             \
        }                                                                      \
        case SymTagArrayType:                                                  \
        {                                                                      \
            using typeNameSymbol = dia::ArrayType;                             \
            operation(*reinterpret_cast<const dia::ArrayType*>(&symbol));      \
            break;                                                             \
        }                                                                      \
        case SymTagPointerType:                                                \
        {                                                                      \
            using typeNameSymbol = dia::PointerType;                           \
            operation(*reinterpret_cast<const dia::PointerType*>(&symbol));    \
            break;                                                             \
        }                                                                      \
        case SymTagUDT:                                                        \
        {                                                                      \
            using typeNameSymbol = dia::Udt;                                   \
            operation(*reinterpret_cast<const dia::Udt*>(&symbol));            \
            break;                                                             \
        }                                                                      \
        case SymTagFunction:                                                   \
        {                                                                      \
            using typeNameSymbol = dia::Function;                              \
            operation(*reinterpret_cast<const dia::Function*>(&symbol));       \
            break;                                                             \
        }                                                                      \
        /* case SymTagExe:                                                     \
        {                                                                      \
            using typeNameSymbol = dia::Exe;                                   \
            operation(*reinterpret_cast<const dia::Exe*>(&symbol));            \
            break;                                                             \
        }    */                                                                \
        case SymTagData:                                                       \
        {                                                                      \
            using typeNameSymbol = dia::Data;                                  \
            operation(*reinterpret_cast<const dia::Data*>(&symbol));           \
            break;                                                             \
        }                                                                      \
        default:                                                               \
        {                                                                      \
            throw std::runtime_error("Invalid SymTag!");                       \
        }                                                                      \
        } /* End of switch statment */                                         \
    } while (0)
