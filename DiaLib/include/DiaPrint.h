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
