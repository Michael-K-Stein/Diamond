#pragma once
#include "BstrWrapper.h"
#include "ComWrapper.h"
#include "DiaSymbolFuncs.h"
#include "Exceptions.h"
#include "HashUtils.h"
#include <atlbase.h>
#include <dia2.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Forward decleration for tests
namespace CTests
{
class FindStructs;
};

namespace dia
{

// Forward decleration
class Symbol;
class DataMember;
class DataSource;

template <typename T>
class DiaSymbolEnumerator;

template <typename T>
DiaSymbolEnumerator<T> enumerate(const Symbol& parentSymbol, enum SymTagEnum symTag, LPCOLESTR name, DWORD compareFlags);

// General template declaration (forward declaration)
template <typename T>
/// @brief Stream to os the modifiers "const", "volatile", etc... if relevant.
/// @param os The stream to work on.
/// @param v The symbol to check.
/// @return The stream, with modifiers written as needed.
std::wostream& streamSymbolTypeModifiers(std::wostream& os, const T& v);

std::string convertGuidToString(const GUID& guid);

// Derived Types
class UserDefinedType;

class Symbol : public ComWrapper<IDiaSymbol>
{
public:
    Symbol() = default;
    // Copy semantics
    Symbol(const Symbol& other);
    Symbol& operator=(const Symbol& other);
    // Move semantics
    Symbol(Symbol&& other) noexcept;
    Symbol& operator=(Symbol&& other) noexcept;

    using ComWrapper::ComWrapper;
    using ComWrapper::makeFromRaw;
    using ComWrapper::operator!;
    using ComWrapper::operator=;

    using ComWrapper::get;

    /// @brief Get a human readable representation of this symbol and its type -
    /// stiving to be as similar to the original source code as possible.
    /// @return A string as closely resembling the source code this symbol
    /// refers to as possible.
    std::wstring getTypeName() const { return resolveTypeName(*this); }

    // DIA functions which are valid for ALL symbol types
    auto getSymTag() const { return dia::getSymTag(*this); }

    auto getSymIndexId() const { return dia::getSymIndexId(*this); }

    // Quick type checking functions

    /// @brief Analogous to getVolatileType.
    /// @return TRUE if the symbol is marked as volatile, FALSE otherwise.
    bool isVolatile() const;
    bool isArray() const;
    bool isPointer() const;
    bool isUserDefinedType() const;

    // Utility functions
    /// @brief Returns a unique identifier for this symbol's instance
    /// @return A unique identifier.
    /// @note Multiple instance of dia::Symbol referencing the same underlyind
    /// Debug Symbol (IDiaSymbol) will have the same UID.
    auto getUid() const { return getSymIndexId(); }

    /// @brief Calculate a hash representing the content of the symbol. The hash
    /// of a symbol is independant from its UID, and will be identical across
    /// versions of the same binary - given that the symbol has not changed.
    /// @return 64-bit hash value.
    size_t calcHash() const;

    bool operator==(const Symbol& other) const;
    bool operator!=(const Symbol& other) const;
    bool operator<(const Symbol& other) const;
    bool operator<=(const Symbol& other) const;
    bool operator>(const Symbol& other) const;
    bool operator>=(const Symbol& other) const;

#ifndef Py_PYTHON_H
    // In Python builds, we are going to allow the CPython code free access to the member functions, since the "wrapping" will actually be done in the
    // CPython extension.
protected:
#endif

    auto getType() const { return dia::getType(*this); }

    auto getName() const { return dia::getName(*this); }

#if 0
    // Not yet implemented!
    auto findChildren() const { return dia::findChildren(*this); }
    auto findChildrenEx() const { return dia::findChildrenEx(*this); }
#endif
    auto findInputAssemblyFile() const { return dia::findInputAssemblyFile(*this); }
#if 0
    auto getAcceleratorPointerTags() const
    {
        return dia::getAcceleratorPointerTags(*this);
    }
#endif
    auto getAccess() const { return dia::getAccess(*this); }

    auto getAddressOffset() const { return dia::getAddressOffset(*this); }

    auto getAddressSection() const { return dia::getAddressSection(*this); }

    auto getAddressTaken() const { return dia::getAddressTaken(*this); }

    auto getAge() const { return dia::getAge(*this); }

    auto getArrayIndexType() const { return dia::getArrayIndexType(*this); }

    auto getArrayIndexTypeId() const { return dia::getArrayIndexTypeId(*this); }

    auto getBaseSymbol() const { return dia::getBaseSymbol(*this); }

    auto getBaseSymbolId() const { return dia::getBaseSymbolId(*this); }

    auto getBitField() const { return dia::getBitField(*this); }

    auto getBindSpace() const { return dia::getBindSpace(*this); }

    auto getBitPosition() const { return dia::getBitPosition(*this); }

    auto getBitSize() const { return dia::getBitSize(*this); }

    auto getBuiltInKind() const { return dia::getBuiltInKind(*this); }

    auto getCallingConvention() const { return dia::getCallingConvention(*this); }

    auto getCharacteristics() const { return dia::getCharacteristics(*this); }

    auto getClassParent() const { return dia::getClassParent(*this); }

    auto getCode() const { return dia::getCode(*this); }

    auto getCoffGroup() const { return dia::getCoffGroup(*this); }

    auto getCompilerGenerated() const { return dia::getCompilerGenerated(*this); }

    auto getConstantExport() const { return dia::getConstantExport(*this); }

    auto getDataExport() const { return dia::getDataExport(*this); }

    auto getDataKind() const { return dia::getDataKind(*this); }

    auto getExceptionHandlerAddressOffset() const { return dia::getExceptionHandlerAddressOffset(*this); }

    auto getExceptionHandlerAddressSection() const { return dia::getExceptionHandlerAddressSection(*this); }

    auto getExceptionHandlerRelativeVirtualAddress() const { return dia::getExceptionHandlerRelativeVirtualAddress(*this); }

    auto getExceptionHandlerVirtualAddress() const { return dia::getExceptionHandlerVirtualAddress(*this); }

    auto getExportHasExplicitlyAssignedOrdinal() const { return dia::getExportHasExplicitlyAssignedOrdinal(*this); }

    auto getExportIsForwarder() const { return dia::getExportIsForwarder(*this); }

    auto getFinalLiveStaticSize() const { return dia::getFinalLiveStaticSize(*this); }

    auto getFrameSize() const { return dia::getFrameSize(*this); }

    auto getFunction() const { return dia::getFunction(*this); }

    auto getHasControlFlowCheck() const { return dia::getHasControlFlowCheck(*this); }

    auto getHasValidPGOCounts() const { return dia::getHasValidPGOCounts(*this); }

    auto getIsOptimizedForSpeed() const { return dia::getIsOptimizedForSpeed(*this); }

    auto getIsPGO() const { return dia::getIsPGO(*this); }

    auto getLength() const { return dia::getLength(*this); }

    auto getLexicalParent() const { return dia::getLexicalParent(*this); }

    auto getLocationType() const { return dia::getLocationType(*this); }

    auto getLowerBound() const { return dia::getLowerBound(*this); }

    auto getLowerBoundId() const { return dia::getLowerBoundId(*this); }

    auto getManaged() const { return dia::getManaged(*this); }

    auto getMsil() const { return dia::getMsil(*this); }

    auto getNoNameExport() const { return dia::getNoNameExport(*this); }

    auto getOffset() const { return dia::getOffset(*this); }

    auto getOrdinal() const { return dia::getOrdinal(*this); }

    auto getPGODynamicInstructionCount() const { return dia::getPGODynamicInstructionCount(*this); }

    auto getPGOEdgeCount() const { return dia::getPGOEdgeCount(*this); }

    auto getPGOEntryCount() const { return dia::getPGOEntryCount(*this); }

    auto getPhaseName() const { return dia::getPhaseName(*this); }

    auto getPrivateExport() const { return dia::getPrivateExport(*this); }

    auto getRank() const { return dia::getRank(*this); }

    auto getRegisterId() const { return dia::getRegisterId(*this); }

    auto getRelativeVirtualAddress() const { return dia::getRelativeVirtualAddress(*this); }

    auto getSignature() const { return dia::getSignature(*this); }

    auto getStaticSize() const { return dia::getStaticSize(*this); }

    auto getTypeId() const { return dia::getTypeId(*this); }

    auto getUndecoratedName() const { return dia::getUndecoratedName(*this); }

    auto getUpperBound() const { return dia::getUpperBound(*this); }

    auto getUpperBoundId() const { return dia::getUpperBoundId(*this); }

    auto getVirtualAddress() const { return dia::getVirtualAddress(*this); }

    auto getVirtualBaseDispIndex() const { return dia::getVirtualBaseDispIndex(*this); }

    auto getVirtualTableShape() const { return dia::getVirtualTableShape(*this); }

    auto getVirtualTableShapeId() const { return dia::getVirtualTableShapeId(*this); }

    auto getSrcLineOnTypeDefn() const { return dia::getSrcLineOnTypeDefn(*this); }

    auto getRValueReference() const { return dia::getRValueReference(*this); }

    auto getBackEndBuild() const { return dia::getBackEndBuild(*this); }

    auto getBackEndMajor() const { return dia::getBackEndMajor(*this); }

    auto getBackEndMinor() const { return dia::getBackEndMinor(*this); }

    auto getBackEndQFE() const { return dia::getBackEndQFE(*this); }

    auto getBaseDataOffset() const { return dia::getBaseDataOffset(*this); }

    auto getBaseDataSlot() const { return dia::getBaseDataSlot(*this); }

    auto getBaseType() const { return dia::getBaseType(*this); }

    auto getBindID() const { return dia::getBindID(*this); }

    auto getBindSlot() const { return dia::getBindSlot(*this); }

    auto getClassParentId() const { return dia::getClassParentId(*this); }

    auto getCompilerName() const { return dia::getCompilerName(*this); }

    auto getConstType() const { return dia::getConstType(*this); }

    auto getConstructor() const { return dia::getConstructor(*this); }

    auto getContainer() const { return dia::getContainer(*this); }

    auto getCount() const { return dia::getCount(*this); }

    auto getCountLiveRanges() const { return dia::getCountLiveRanges(*this); }

    auto getCustomCallingConvention() const { return dia::getCustomCallingConvention(*this); }

    // auto getDataBytes() const { return dia::getDataBytes(*this); }
    auto getEditAndContinueEnabled() const { return dia::getEditAndContinueEnabled(*this); }

    auto getFarReturn() const { return dia::getFarReturn(*this); }

    auto getFramePointerPresent() const { return dia::getFramePointerPresent(*this); }

    auto getFrontEndBuild() const { return dia::getFrontEndBuild(*this); }

    auto getFrontEndMajor() const { return dia::getFrontEndMajor(*this); }

    auto getFrontEndMinor() const { return dia::getFrontEndMinor(*this); }

    auto getFrontEndQFE() const { return dia::getFrontEndQFE(*this); }

    auto getGuid() const { return dia::getGuid(*this); }

    auto getHasAlloca() const { return dia::getHasAlloca(*this); }

    auto getHasAssignmentOperator() const { return dia::getHasAssignmentOperator(*this); }

    auto getHasCastOperator() const { return dia::getHasCastOperator(*this); }

    auto getHasDebugInfo() const { return dia::getHasDebugInfo(*this); }

    auto getHasEH() const { return dia::getHasEH(*this); }

    auto getHasEHa() const { return dia::getHasEHa(*this); }

    auto getHasInlAsm() const { return dia::getHasInlAsm(*this); }

    auto getHasLongJump() const { return dia::getHasLongJump(*this); }

    auto getHasManagedCode() const { return dia::getHasManagedCode(*this); }

    auto getHasNestedTypes() const { return dia::getHasNestedTypes(*this); }

    auto getHasSEH() const { return dia::getHasSEH(*this); }

    auto getHasSecurityChecks() const { return dia::getHasSecurityChecks(*this); }

    auto getHasSetJump() const { return dia::getHasSetJump(*this); }

    auto getHfaDouble() const { return dia::getHfaDouble(*this); }

    auto getHfaFloat() const { return dia::getHfaFloat(*this); }

    auto getIndirectVirtualBaseClass() const { return dia::getIndirectVirtualBaseClass(*this); }

    auto getInlSpec() const { return dia::getInlSpec(*this); }

    auto getInterruptReturn() const { return dia::getInterruptReturn(*this); }

    auto getIntrinsic() const { return dia::getIntrinsic(*this); }

    auto getIntro() const { return dia::getIntro(*this); }

    auto getIsAcceleratorGroupSharedLocal() const { return dia::getIsAcceleratorGroupSharedLocal(*this); }

    auto getIsAcceleratorPointerTagLiveRange() const { return dia::getIsAcceleratorPointerTagLiveRange(*this); }

    auto getIsAcceleratorStubFunction() const { return dia::getIsAcceleratorStubFunction(*this); }

    auto getIsAggregated() const { return dia::getIsAggregated(*this); }

    auto getIsCTypes() const { return dia::getIsCTypes(*this); }

    auto getIsCVTCIL() const { return dia::getIsCVTCIL(*this); }

    auto getIsConstructorVirtualBase() const { return dia::getIsConstructorVirtualBase(*this); }

    auto getIsCxxReturnUdt() const { return dia::getIsCxxReturnUdt(*this); }

    auto getIsDataAligned() const { return dia::getIsDataAligned(*this); }

    auto getIsHLSLData() const { return dia::getIsHLSLData(*this); }

    auto getIsHotpatchable() const { return dia::getIsHotpatchable(*this); }

    auto getIsInterfaceUdt() const { return dia::getIsInterfaceUdt(*this); }

    auto getIsLTCG() const { return dia::getIsLTCG(*this); }

    auto getIsLocationControlFlowDependent() const { return dia::getIsLocationControlFlowDependent(*this); }

    auto getIsMSILNetmodule() const { return dia::getIsMSILNetmodule(*this); }

    auto getIsMatrixRowMajor() const { return dia::getIsMatrixRowMajor(*this); }

    auto getIsMultipleInheritance() const { return dia::getIsMultipleInheritance(*this); }

    auto getIsNaked() const { return dia::getIsNaked(*this); }

    auto getIsOptimizedAway() const { return dia::getIsOptimizedAway(*this); }

    auto getIsPointerBasedOnSymbolValue() const { return dia::getIsPointerBasedOnSymbolValue(*this); }

    auto getIsPointerToDataMember() const { return dia::getIsPointerToDataMember(*this); }

    auto getIsPointerToMemberFunction() const { return dia::getIsPointerToMemberFunction(*this); }

    auto getIsRefUdt() const { return dia::getIsRefUdt(*this); }

    auto getIsReturnValue() const { return dia::getIsReturnValue(*this); }

    auto getIsSafeBuffers() const { return dia::getIsSafeBuffers(*this); }

    auto getIsSdl() const { return dia::getIsSdl(*this); }

    auto getIsSingleInheritance() const { return dia::getIsSingleInheritance(*this); }

    auto getIsSplitted() const { return dia::getIsSplitted(*this); }

    auto getIsStatic() const { return dia::getIsStatic(*this); }

    auto getIsStripped() const { return dia::getIsStripped(*this); }

    auto getIsValueUdt() const { return dia::getIsValueUdt(*this); }

    auto getIsVirtualInheritance() const { return dia::getIsVirtualInheritance(*this); }

    auto getIsWinRTPointer() const { return dia::getIsWinRTPointer(*this); }

    auto getLanguage() const { return dia::getLanguage(*this); }

    auto getLexicalParentId() const { return dia::getLexicalParentId(*this); }

    auto getLibraryName() const { return dia::getLibraryName(*this); }

    auto getLiveRangeLength() const { return dia::getLiveRangeLength(*this); }

    auto getLiveRangeStartAddressOffset() const { return dia::getLiveRangeStartAddressOffset(*this); }

    auto getLiveRangeStartAddressSection() const { return dia::getLiveRangeStartAddressSection(*this); }

    auto getLiveRangeStartRelativeVirtualAddress() const { return dia::getLiveRangeStartRelativeVirtualAddress(*this); }

    auto getLocalBasePointerRegisterId() const { return dia::getLocalBasePointerRegisterId(*this); }

    auto getMachineType() const { return dia::getMachineType(*this); }

    auto getMemorySpaceKind() const { return dia::getMemorySpaceKind(*this); }

    auto getModifierValues() const { return dia::getModifierValues(*this); }

    auto getNested() const { return dia::getNested(*this); }

    auto getNoInline() const { return dia::getNoInline(*this); }

    auto getNoReturn() const { return dia::getNoReturn(*this); }

    auto getNoStackOrdering() const { return dia::getNoStackOrdering(*this); }

    auto getNotReached() const { return dia::getNotReached(*this); }

    auto getNumberOfAcceleratorPointerTags() const { return dia::getNumberOfAcceleratorPointerTags(*this); }

    auto getNumberOfColumns() const { return dia::getNumberOfColumns(*this); }

    auto getNumberOfModifiers() const { return dia::getNumberOfModifiers(*this); }

    auto getNumberOfRegisterIndices() const { return dia::getNumberOfRegisterIndices(*this); }

    auto getNumberOfRows() const { return dia::getNumberOfRows(*this); }

    auto getNumericProperties() const { return dia::getNumericProperties(*this); }

    auto getObjectFileName() const { return dia::getObjectFileName(*this); }

    auto getObjectPointerType() const { return dia::getObjectPointerType(*this); }

    auto getOemId() const { return dia::getOemId(*this); }

    auto getOemSymbolId() const { return dia::getOemSymbolId(*this); }

    auto getOffsetInUdt() const { return dia::getOffsetInUdt(*this); }

    auto getOptimizedCodeDebugInfo() const { return dia::getOptimizedCodeDebugInfo(*this); }

    auto getOverloadedOperator() const { return dia::getOverloadedOperator(*this); }

    auto getPacked() const { return dia::getPacked(*this); }

    auto getParamBasePointerRegisterId() const { return dia::getParamBasePointerRegisterId(*this); }

    auto getPlatform() const { return dia::getPlatform(*this); }

    auto getPure() const { return dia::getPure(*this); }

    auto getReference() const { return dia::getReference(*this); }

    auto getRegisterType() const { return dia::getRegisterType(*this); }

    auto getRestrictedType() const { return dia::getRestrictedType(*this); }

    auto getSamplerSlot() const { return dia::getSamplerSlot(*this); }

    auto getScoped() const { return dia::getScoped(*this); }

    auto getSealed() const { return dia::getSealed(*this); }

    auto getSizeInUdt() const { return dia::getSizeInUdt(*this); }

    auto getSlot() const { return dia::getSlot(*this); }

    auto getSourceFileName() const { return dia::getSourceFileName(*this); }

    auto getStrictGSCheck() const { return dia::getStrictGSCheck(*this); }

    auto getStride() const { return dia::getStride(*this); }

    auto getSubType() const { return dia::getSubType(*this); }

    auto getSubTypeId() const { return dia::getSubTypeId(*this); }

    auto getSymbolsFileName() const { return dia::getSymbolsFileName(*this); }

    auto getTargetOffset() const { return dia::getTargetOffset(*this); }

    auto getTargetRelativeVirtualAddress() const { return dia::getTargetRelativeVirtualAddress(*this); }

    auto getTargetSection() const { return dia::getTargetSection(*this); }

    auto getTargetVirtualAddress() const { return dia::getTargetVirtualAddress(*this); }

    auto getTextureSlot() const { return dia::getTextureSlot(*this); }

    auto getThisAdjust() const { return dia::getThisAdjust(*this); }

    auto getThunkOrdinal() const { return dia::getThunkOrdinal(*this); }

    auto getTimeStamp() const { return dia::getTimeStamp(*this); }

    auto getToken() const { return dia::getToken(*this); }

    auto getTypeIds() const { return dia::getTypeIds(*this); }

    auto getTypes() const { return dia::getTypes(*this); }

    auto getUavSlot() const { return dia::getUavSlot(*this); }

    auto getUdtKind() const { return dia::getUdtKind(*this); }

    auto getUnalignedType() const { return dia::getUnalignedType(*this); }

    auto getUndecoratedNameEx(DWORD options) const { return dia::getUndecoratedNameEx(*this, options); }

    auto getUnmodifiedType() const { return dia::getUnmodifiedType(*this); }

    auto getUnmodifiedTypeId() const { return dia::getUnmodifiedTypeId(*this); }

    auto getUnused() const { return dia::getUnused(*this); }

    auto getValue() const { return dia::getValue(*this); }

    auto getVirtual() const { return dia::getVirtual(*this); }

    auto getVirtualBaseClass() const { return dia::getVirtualBaseClass(*this); }

    auto getVirtualBaseOffset() const { return dia::getVirtualBaseOffset(*this); }

    auto getVirtualBasePointerOffset() const { return dia::getVirtualBasePointerOffset(*this); }

    auto getVirtualBaseTableType() const { return dia::getVirtualBaseTableType(*this); }

    auto getVolatileType() const { return dia::getVolatileType(*this); }

    auto getWasInlined() const { return dia::getWasInlined(*this); }

    // Implicit conversion operators
#define __DECLARE_AND_DEFINE_IMPLICIT_CAST_OPERATIONS(className)                                                                                     \
    operator className&() { return reinterpret_cast<className&>(*this); }                                                                            \
    operator className&&()& { return reinterpret_cast<className&&>(static_cast<Symbol&&>(*this)); }                                                  \
    operator className&&()&& { return reinterpret_cast<className&&>(*this); }
    XFOR_DIA_SYMBOL_TYPE(__DECLARE_AND_DEFINE_IMPLICIT_CAST_OPERATIONS);

    __DECLARE_AND_DEFINE_IMPLICIT_CAST_OPERATIONS(UserDefinedType);

private:
    using SymbolEnum = DiaSymbolEnumerator<Symbol>;
    using LineEnum   = DiaSymbolEnumerator<Symbol>;  // TODO: Should be
                                                     // DiaSymbolEnumerator<dia::Line>

    friend DiaSymbolEnumerator<Symbol> enumerate<Symbol>(const Symbol& parentSymbol, enum SymTagEnum symTag, LPCOLESTR name, DWORD compareFlags);
    friend DiaSymbolEnumerator<DataMember>
    enumerate<DataMember>(const Symbol& parentSymbol, enum SymTagEnum symTag, LPCOLESTR name, DWORD compareFlags);
    friend ::std::wstring resolveTypeName(const Symbol& symbol);
    friend ::std::wstring resolveBaseTypeName(const Symbol& symbol);
    friend class DataSource;

    template <typename T>
    friend std::wostream& streamSymbolTypeModifiers(std::wostream& os, const T& v);

    template <typename ContainerT>
    friend std::set<Symbol> queryDependencies(const ContainerT& symbol);

    friend bool isSymbolUnnamed(const Symbol& symbol);

    // For tests
    friend class CTests::FindStructs;
};

static bool isSymbolUnnamed(const Symbol& symbol)
{
    const auto& symbolName        = symbol.getName();
    const wchar_t unnamedPrefix[] = L"<unnamed-";
    return 0 == wcsncmp(symbolName.c_str(), unnamedPrefix, (sizeof(unnamedPrefix) / sizeof(unnamedPrefix[0]) - 1));
}

template <typename ContainerT>
std::set<Symbol> queryDependencies(const ContainerT& symbol);
// Explicit instantiation declarations (restrict instantiation to these types).
extern template std::set<Symbol> queryDependencies<FunctionType>(const FunctionType& symbols);
extern template std::set<Symbol> queryDependencies<UserDefinedType>(const UserDefinedType& symbols);

template <typename ToTypeT>
std::vector<ToTypeT> convertSymbolVector(const std::vector<Symbol>& v)
{
    std::vector<ToTypeT> out{};
    std::transform(v.begin(), v.end(), std::back_inserter(out), [](const dia::Symbol& x) { return static_cast<const ToTypeT&>(x); });
    return out;
}

template <typename ToTypeT>
std::vector<ToTypeT> convertSymbolVector(std::vector<Symbol>&& v)
{
    std::vector<ToTypeT> out{};
    std::transform(v.begin(), v.end(), std::back_inserter(out), [](const dia::Symbol& x) { return static_cast<const ToTypeT&>(x); });
    return out;
}

// Specialized template for types derived from Symbol
template <typename T>
std::wostream& streamSymbolTypeModifiers(std::wostream& os, const T& v)
{
    static_assert(std::is_base_of<Symbol, T>::value, "T must be a class derived from dia::Symbol !");
    return streamSymbolTypeModifiers(os, reinterpret_cast<const Symbol&>(v));
}

template <>
std::wostream& streamSymbolTypeModifiers(std::wostream& os, const Symbol& v);

class Array;
template <>
std::wostream& streamSymbolTypeModifiers(std::wostream& os, const Array& v);

}  // namespace dia

std::wostream& operator<<(std::wostream& os, const dia::Symbol& v);
std::wostream& operator<<(std::wostream& os, const enum SymTagEnum& v);
std::wostream& operator<<(std::wostream& os, const enum LocationType& v);

namespace std
{
template <>
struct hash<dia::Symbol>
{
    size_t operator()(const dia::Symbol& diaSymbol) const { return diaSymbol.calcHash(); }
};
}  // namespace std
