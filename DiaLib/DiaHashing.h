#pragma once
#include "Exceptions.h"
#include "HashUtils.h"
#include "SymbolTypes/DiaAnnotation.h"
#include "SymbolTypes/DiaArray.h"
#include "SymbolTypes/DiaData.h"
#include "SymbolTypes/DiaEnum.h"
#include "SymbolTypes/DiaFunction.h"
#include "SymbolTypes/DiaFunctionArgType.h"
#include "SymbolTypes/DiaFunctionType.h"
#include "SymbolTypes/DiaSymbolTypes.h"
#include "SymbolTypes/DiaUDT.h"

namespace std
{

template <>
struct hash<VARIANT>
{
    size_t operator()(const VARIANT& v) const;
};

template <>
struct hash<dia::Enum>
{
    size_t operator()(const dia::Enum& v) const;
};

template <>
struct hash<dia::Udt>
{
    size_t operator()(const dia::Udt& v) const;
};

template <>
struct hash<dia::Data>
{
    size_t operator()(const dia::Data& v) const;
};

template <>
struct hash<dia::Function>
{
    size_t operator()(const dia::Function& v) const;
};

template <>
struct hash<dia::FunctionType>
{
    size_t operator()(const dia::FunctionType& v) const;
};

template <>
struct hash<dia::Array>
{
    size_t operator()(const dia::Array& v) const;
};

template <>
struct hash<dia::Annotation>
{
    size_t operator()(const dia::Annotation& v) const;
};

template <>
struct hash<dia::BaseClass>
{
    size_t operator()(const dia::BaseClass& v) const;
};

template <>
struct hash<dia::BaseInterface>
{
    size_t operator()(const dia::BaseInterface& v) const;
};

template <>
struct hash<dia::Callee>
{
    size_t operator()(const dia::Callee& v) const;
};

template <>
struct hash<dia::Caller>
{
    size_t operator()(const dia::Caller& v) const;
};

template <>
struct hash<dia::CallSite>
{
    size_t operator()(const dia::CallSite& v) const;
};

template <>
struct hash<dia::CoffGroup>
{
    size_t operator()(const dia::CoffGroup& v) const;
};

template <>
struct hash<dia::Compiland>
{
    size_t operator()(const dia::Compiland& v) const;
};

template <>
struct hash<dia::CompilandDetails>
{
    size_t operator()(const dia::CompilandDetails& v) const;
};

template <>
struct hash<dia::CompilandEnv>
{
    size_t operator()(const dia::CompilandEnv& v) const;
};

template <>
struct hash<dia::Custom>
{
    size_t operator()(const dia::Custom& v) const;
};

template <>
struct hash<dia::CustomType>
{
    size_t operator()(const dia::CustomType& v) const;
};

template <>
struct hash<dia::Dimension>
{
    size_t operator()(const dia::Dimension& v) const;
};

template <>
struct hash<dia::Export>
{
    size_t operator()(const dia::Export& v) const;
};

template <>
struct hash<dia::Friend>
{
    size_t operator()(const dia::Friend& v) const;
};

template <>
struct hash<dia::HeapAllocationSite>
{
    size_t operator()(const dia::HeapAllocationSite& v) const;
};

template <>
struct hash<dia::HLSLType>
{
    size_t operator()(const dia::HLSLType& v) const;
};

template <>
struct hash<dia::Inlinee>
{
    size_t operator()(const dia::Inlinee& v) const;
};

template <>
struct hash<dia::InlineSite>
{
    size_t operator()(const dia::InlineSite& v) const;
};

template <>
struct hash<dia::Label>
{
    size_t operator()(const dia::Label& v) const;
};

template <>
struct hash<dia::ManagedType>
{
    size_t operator()(const dia::ManagedType& v) const;
};

template <>
struct hash<dia::MatrixType>
{
    size_t operator()(const dia::MatrixType& v) const;
};

template <>
struct hash<dia::PublicSymbol>
{
    size_t operator()(const dia::PublicSymbol& v) const;
};

template <>
struct hash<dia::TaggedUnionCase>
{
    size_t operator()(const dia::TaggedUnionCase& v) const;
};

template <>
struct hash<dia::Thunk>
{
    size_t operator()(const dia::Thunk& v) const;
};

template <>
struct hash<dia::Typedef>
{
    size_t operator()(const dia::Typedef& v) const;
};

template <>
struct hash<dia::VectorType>
{
    size_t operator()(const dia::VectorType& v) const;
};
}  // namespace std
