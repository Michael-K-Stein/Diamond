#include "pch.h"
//
#include "DiaHashing.h"


#define GET_ATTRIBUTE_OR_DEFAULT(_symbol, attribute)                                                                                                 \
    (                                                                                                                                                \
        [](const auto& symbol)                                                                                                                       \
        {                                                                                                                                            \
            try                                                                                                                                      \
            {                                                                                                                                        \
                return symbol.##attribute##();                                                                                                       \
            }                                                                                                                                        \
            catch (const dia::InvalidUsageException&)                                                                                                \
            {                                                                                                                                        \
                return decltype(symbol.##attribute##()){};                                                                                           \
            }                                                                                                                                        \
        })(_symbol)

#define GET_CLASS_PARENT_OR_EMPTY(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getClassParent)
#define GET_CLASS_PARENT_ID_OR_ZERO(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getClassParentId)
#define GET_TOKEN_OR_ZERO(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getToken)
#define GET_SLOT_OR_ZERO(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getSlot)
#define GET_LENGTH_OR_ZERO(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getLength)
#define GET_SPLITTED_OR_FALSE(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getIsSplitted)
#define GET_AGGREGATED_OR_FALSE(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getIsAggregated)
#define GET_COMPILER_GENERATED_OR_FALSE(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getCompilerGenerated)
#define GET_BIT_POSITION_OR_ZERO(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getBitPosition)
#define GET_RANK_OR_ZERO(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getRank)
#define GET_VTABLE_SHARE_OR_EMPTY(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getVirtualTableShape)
#define GET_THIS_ADJUST_OR_ZERO(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getThisAdjust)
#define GET_OBJECT_POINTER_TYPE_OR_EMPTY(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getObjectPointerType)
#define GET_OFFSET_OR_ZERO(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getOffset)
#define GET_ACCESS_OR_NONE(_symbol) GET_ATTRIBUTE_OR_DEFAULT(_symbol, getAccess)

namespace std
{


size_t hash<dia::Enum>::operator()(const dia::Enum& v) const
{
    size_t calculatedHash = 0;
    hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), v.getBaseType(), GET_CLASS_PARENT_ID_OR_ZERO(v), v.getConstructor(),
                 v.getConstType(), v.getHasAssignmentOperator(), v.getHasCastOperator(), v.getHasNestedTypes(), v.getLength(), v.getName(),
                 v.getNested(), v.getOverloadedOperator(), v.getPacked(), v.getScoped(), v.getUnalignedType(), v.getVolatileType());
    return calculatedHash;
}

size_t hash<dia::Udt>::operator()(const dia::Udt& v) const
{
    size_t calculatedHash = 0;
    hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), GET_CLASS_PARENT_ID_OR_ZERO(v), v.getConstructor(), v.getConstType(),
                 v.getHasAssignmentOperator(), v.getHasCastOperator(), v.getHasNestedTypes(), GET_LENGTH_OR_ZERO(v), v.getName(), v.getNested(),
                 v.getOverloadedOperator(), v.getPacked(), v.getScoped(), v.getUdtKind(), v.getUnalignedType(), GET_VTABLE_SHARE_OR_EMPTY(v),
                 v.getVolatileType());

#if 0
        // This causes infinite recursion
        const dia::Symbol& s = *reinterpret_cast<const dia::Symbol*>(&v);
        for (const auto& member : dia::enumerate<dia::Data>(s, SymTagData))
        {
            hash_combine(calculatedHash, member.calcHash());
        }
#endif

    return calculatedHash;
}

size_t hash<dia::Data>::operator()(const dia::Data& v) const
{
    size_t calculatedHash = 0;
    hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), GET_ACCESS_OR_NONE(v), GET_BIT_POSITION_OR_ZERO(v),
                 GET_CLASS_PARENT_OR_EMPTY(v), GET_COMPILER_GENERATED_OR_FALSE(v), v.getConstType(), v.getDataKind(), GET_AGGREGATED_OR_FALSE(v),
                 GET_SPLITTED_OR_FALSE(v), GET_LENGTH_OR_ZERO(v), v.getLocationType(), v.getName(), GET_OFFSET_OR_ZERO(v), GET_SLOT_OR_ZERO(v),
                 v.getSymTag(), GET_TOKEN_OR_ZERO(v), v.getType(), v.getUnalignedType(), v.getVolatileType());

    return calculatedHash;
}

size_t hash<dia::Function>::operator()(const dia::Function& v) const
{
    size_t calculatedHash = 0;
    hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), v.getAccess(), v.getAddressSection(), v.getClassParent(),
                 v.getConstType(), v.getCustomCallingConvention(), v.getFarReturn(), v.getHasAlloca(), v.getHasEH(), v.getHasEHa(), v.getHasInlAsm(),
                 v.getHasLongJump(), v.getHasSecurityChecks(), v.getHasSEH(), v.getHasSetJump(), v.getInlSpec(), v.getInterruptReturn(), v.getIntro(),
                 v.getIsNaked(), v.getIsStatic(), v.getLength(), v.getLocationType(), v.getName(), v.getNoInline(), v.getNoReturn(),
                 v.getNoStackOrdering(), v.getNotReached(), v.getOptimizedCodeDebugInfo(), v.getPure(), GET_TOKEN_OR_ZERO(v), v.getType(),
                 v.getUnalignedType(), v.getUndecoratedName(), v.getVirtual(), v.getVirtualAddress(), v.getVolatileType());

    return calculatedHash;
}

size_t hash<dia::FunctionType>::operator()(const dia::FunctionType& v) const
{
    size_t calculatedHash = 0;
    hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), v.getCallingConvention(), v.getConstType(), v.getCount(),
                 GET_OBJECT_POINTER_TYPE_OR_EMPTY(v), GET_THIS_ADJUST_OR_ZERO(v), v.getUnalignedType(), v.getVolatileType());
    for (const auto& param : v)
    {
        hash_combine(calculatedHash, hash<dia::FunctionArgType>()(param));
    }

    return calculatedHash;
}

size_t hash<dia::Array>::operator()(const dia::Array& v) const
{
    size_t calculatedHash = 0;
    hash_combine(calculatedHash, std::wstring(dia::symTagToName(v.getSymTag())), v.getArrayIndexType(), v.getConstType(), v.getCount(),
                 v.getLength() /* Length should be well defined for arrays */, v.getLexicalParentId(), GET_RANK_OR_ZERO(v), v.getUnalignedType(),
                 v.getVolatileType());
    return calculatedHash;
}

size_t hash<dia::Annotation>::operator()(const dia::Annotation& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::BaseClass>::operator()(const dia::BaseClass& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::BaseInterface>::operator()(const dia::BaseInterface& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::Callee>::operator()(const dia::Callee& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::Caller>::operator()(const dia::Caller& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::CallSite>::operator()(const dia::CallSite& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::CoffGroup>::operator()(const dia::CoffGroup& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::Compiland>::operator()(const dia::Compiland& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::CompilandDetails>::operator()(const dia::CompilandDetails& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::CompilandEnv>::operator()(const dia::CompilandEnv& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::Custom>::operator()(const dia::Custom& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::CustomType>::operator()(const dia::CustomType& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::Dimension>::operator()(const dia::Dimension& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::Export>::operator()(const dia::Export& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::Friend>::operator()(const dia::Friend& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::HeapAllocationSite>::operator()(const dia::HeapAllocationSite& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::HLSLType>::operator()(const dia::HLSLType& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::Inlinee>::operator()(const dia::Inlinee& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::InlineSite>::operator()(const dia::InlineSite& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::Label>::operator()(const dia::Label& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::ManagedType>::operator()(const dia::ManagedType& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::MatrixType>::operator()(const dia::MatrixType& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::PublicSymbol>::operator()(const dia::PublicSymbol& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::TaggedUnionCase>::operator()(const dia::TaggedUnionCase& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::Thunk>::operator()(const dia::Thunk& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::Typedef>::operator()(const dia::Typedef& v) const { throw std::runtime_error("Not implemented!"); }

size_t hash<dia::VectorType>::operator()(const dia::VectorType& v) const { throw std::runtime_error("Not implemented!"); }

}  // namespace std

namespace dia
{
size_t Data::calcHash() const { return std::hash<dia::Data>()(*this); }

size_t Udt::calcHash() const { return std::hash<dia::Udt>()(*this); }
}  // namespace dia
