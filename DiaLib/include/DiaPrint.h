#pragma once
#include "DiaTypeResolution.h"
#include "SymbolTypes/DiaSymbolPrint.h"
#include <ostream>
#include <type_traits>

static std::wostream& operator<<(std::wostream& os, const enum SymTagEnum& v)
{
    os << dia::symTagToName(v);
    return os;
}

static std::wostream& operator<<(std::wostream& os, const enum LocationType& v)
{
    os << dia::locationTypeToName(v);
    return os;
}

std::wostream& operator<<(std::wostream& os, const dia::Null& v);
std::wostream& operator<<(std::wostream& os, const dia::Data& v);
std::wostream& operator<<(std::wostream& os, const dia::Udt& v);
std::wostream& operator<<(std::wostream& os, const dia::Enum& v);
std::wostream& operator<<(std::wostream& os, const dia::BaseType& v);
std::wostream& operator<<(std::wostream& os, const dia::Annotation& v);
std::wostream& operator<<(std::wostream& os, const dia::BaseClass& v);
std::wostream& operator<<(std::wostream& os, const dia::BaseInterface& v);
std::wostream& operator<<(std::wostream& os, const dia::Callee& v);
std::wostream& operator<<(std::wostream& os, const dia::Caller& v);
std::wostream& operator<<(std::wostream& os, const dia::CallSite& v);
std::wostream& operator<<(std::wostream& os, const dia::CoffGroup& v);
std::wostream& operator<<(std::wostream& os, const dia::Compiland& v);
std::wostream& operator<<(std::wostream& os, const dia::CompilandDetails& v);
std::wostream& operator<<(std::wostream& os, const dia::CompilandEnv& v);
std::wostream& operator<<(std::wostream& os, const dia::Custom& v);
std::wostream& operator<<(std::wostream& os, const dia::CustomType& v);
std::wostream& operator<<(std::wostream& os, const dia::Dimension& v);
std::wostream& operator<<(std::wostream& os, const dia::Exe& v);
std::wostream& operator<<(std::wostream& os, const dia::Export& v);
std::wostream& operator<<(std::wostream& os, const dia::Friend& v);
std::wostream& operator<<(std::wostream& os, const dia::HeapAllocationSite& v);
std::wostream& operator<<(std::wostream& os, const dia::HLSLType& v);
std::wostream& operator<<(std::wostream& os, const dia::Inlinee& v);
std::wostream& operator<<(std::wostream& os, const dia::InlineSite& v);
std::wostream& operator<<(std::wostream& os, const dia::Label& v);
std::wostream& operator<<(std::wostream& os, const dia::ManagedType& v);
std::wostream& operator<<(std::wostream& os, const dia::MatrixType& v);
std::wostream& operator<<(std::wostream& os, const dia::PublicSymbol& v);
std::wostream& operator<<(std::wostream& os, const dia::TaggedUnionCase& v);
std::wostream& operator<<(std::wostream& os, const dia::Thunk& v);
std::wostream& operator<<(std::wostream& os, const dia::Typedef& v);
std::wostream& operator<<(std::wostream& os, const dia::VectorType& v);

namespace std
{
template <>
struct hash<dia::Enum>
{
    size_t operator()(const dia::Enum& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::Annotation>
{
    size_t operator()(const dia::Annotation& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::BaseClass>
{
    size_t operator()(const dia::BaseClass& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::BaseInterface>
{
    size_t operator()(const dia::BaseInterface& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::Callee>
{
    size_t operator()(const dia::Callee& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::Caller>
{
    size_t operator()(const dia::Caller& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::CallSite>
{
    size_t operator()(const dia::CallSite& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::CoffGroup>
{
    size_t operator()(const dia::CoffGroup& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::Compiland>
{
    size_t operator()(const dia::Compiland& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::CompilandDetails>
{
    size_t operator()(const dia::CompilandDetails& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::CompilandEnv>
{
    size_t operator()(const dia::CompilandEnv& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::Custom>
{
    size_t operator()(const dia::Custom& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::CustomType>
{
    size_t operator()(const dia::CustomType& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::Dimension>
{
    size_t operator()(const dia::Dimension& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::Export>
{
    size_t operator()(const dia::Export& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::Friend>
{
    size_t operator()(const dia::Friend& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::HeapAllocationSite>
{
    size_t operator()(const dia::HeapAllocationSite& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::HLSLType>
{
    size_t operator()(const dia::HLSLType& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::Inlinee>
{
    size_t operator()(const dia::Inlinee& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::InlineSite>
{
    size_t operator()(const dia::InlineSite& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::Label>
{
    size_t operator()(const dia::Label& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::ManagedType>
{
    size_t operator()(const dia::ManagedType& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::MatrixType>
{
    size_t operator()(const dia::MatrixType& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::PublicSymbol>
{
    size_t operator()(const dia::PublicSymbol& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::TaggedUnionCase>
{
    size_t operator()(const dia::TaggedUnionCase& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::Thunk>
{
    size_t operator()(const dia::Thunk& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::Typedef>
{
    size_t operator()(const dia::Typedef& v) const { throw std::runtime_error("Not implemented!"); }
};

template <>
struct hash<dia::VectorType>
{
    size_t operator()(const dia::VectorType& v) const { throw std::runtime_error("Not implemented!"); }
};
}  // namespace std
