#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_data.h"
#include "pydia_exceptions.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include <DiaSymbol.h>
#include <DiaUserDefinedTypeWrapper.h>
#include <SymbolTypes/DiaArray.h>
#include <SymbolTypes/DiaBaseType.h>
#include <set>

#define PYDIA_ASSERT_SYMBOL_POINTERS(__self)                                                                                                         \
    do                                                                                                                                               \
    {                                                                                                                                                \
        _ASSERT_EXPR(nullptr != __self, L"Self must not be null!");                                                                                  \
        _ASSERT_EXPR(nullptr != __self->diaSymbol, L"Internal symbol must not be null!");                                                            \
        _ASSERT_EXPR(nullptr != __self->dataSource, L"Internal dataSource pointer can never be null!");                                              \
    } while (0)
#define PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE(unsafeCode)                                                                                 \
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE(                                                                                                             \
        unsafeCode, { return PyBool_FromLong(false); }, PYDIA_SAFE_TRIVIAL_ERROR_HANDLER())

static PyObject* PyDiaRawSymbol_FromSymbol(dia::Symbol&& symbol, PyDiaDataSource* dataSource)
{
    PyDiaSymbol* pySymbol = PyObject_New(PyDiaSymbol, &PyDiaSymbol_Type);
    if (!pySymbol)
    {
        PyErr_SetString(PyExc_MemoryError, "Failed to create DiaSymbol object.");
        return NULL;
    }

    pySymbol->diaSymbol = new (std::nothrow) dia::Symbol(symbol);
    if (!(pySymbol->diaSymbol))
    {
        PyErr_SetString(PyExc_MemoryError, "Failed to create DiaSymbol's internal state.");
        return NULL;
    }

    Py_INCREF(dataSource);
    pySymbol->dataSource = dataSource;

    Py_INCREF(pySymbol);
    return reinterpret_cast<PyObject*>(pySymbol);
}

PyObject* PyDiaSymbol_FromSymbol(dia::Symbol&& symbol, PyDiaDataSource* dataSource)
{
    // Create a new PyDiaData object
    _ASSERT_EXPR(nullptr != dataSource, L"Cannot initialize a PyDiaSymbol without a dataSource!");

    const auto symTag  = symbol.getSymTag();

    PyObject* pySymbol = NULL;
    switch (symTag)
    {
    case SymTagNull:
        pySymbol = PyDiaNull_FromNullSymbol(std::move(symbol), dataSource);
        break;
    case SymTagExe:
        pySymbol = PyDiaExe_FromExeSymbol(std::move(symbol), dataSource);
        break;
    case SymTagData:
        pySymbol = PyDiaData_FromDataSymbol(std::move(symbol), dataSource);
        break;
    case SymTagEnum:
        pySymbol = PyDiaEnum_FromEnumSymbol(std::move(symbol), dataSource);
        break;
    case SymTagUDT:
        pySymbol = PyDiaUdt_FromSymbol(std::move(symbol), dataSource);
        break;
    case SymTagFunction:
        pySymbol = PyDiaFunction_FromFunctionSymbol(std::move(symbol), dataSource);
        break;
    case SymTagFunctionType:
        pySymbol = PyDiaFunctionType_FromFunctionTypeSymbol(std::move(symbol), dataSource);
        break;
    case SymTagFunctionArgType:
        pySymbol = PyDiaFunctionArgType_FromFunctionArgTypeSymbol(std::move(symbol), dataSource);
        break;
    case SymTagPointerType:
        pySymbol = PyDiaPointer_FromPointerSymbol(std::move(symbol), dataSource);
        break;
    case SymTagArrayType:
        pySymbol = PyDiaArray_FromArraySymbol(std::move(symbol), dataSource);
        break;
    case SymTagBaseType:
        pySymbol = PyDiaBaseType_FromBaseTypeSymbol(std::move(symbol), dataSource);
        break;
    case SymTagTypedef:
        pySymbol = PyDiaTypedef_FromTypedefSymbol(std::move(symbol), dataSource);
        break;
    case SymTagCompiland:
        pySymbol = PyDiaCompiland_FromCompilandSymbol(std::move(symbol), dataSource);
        break;
    default:
    case SymTagAnnotation:
        pySymbol = PyDiaAnnotation_FromAnnotationSymbol(std::move(symbol), dataSource);
        break;
    case SymTagPublicSymbol:
        pySymbol = PyDiaPublicSymbol_FromPublicSymbolSymbol(std::move(symbol), dataSource);
        break;
#ifdef _DEBUG
        pySymbol = PyDiaRawSymbol_FromSymbol(std::move(symbol), dataSource);
#else
        return PyErr_Format(PyExc_TypeError, "Unrecognized SymTag \"%lu\".", static_cast<unsigned long>(symTag));
#endif
        break;
    }

    if (!pySymbol)
    {
        PyErr_SetString(PyExc_MemoryError, "Failed to create symbol object.");
        return NULL;
    }

    Py_INCREF(pySymbol);
    return pySymbol;
}

PyObject* PyDiaSymbol_richcompare(PyObject* self, PyObject* other, int op)
{
    if (!PyObject_TypeCheck(other, &PyDiaSymbol_Type))
    {
        Py_RETURN_NOTIMPLEMENTED;
    }

    _ASSERT(nullptr != self);
    _ASSERT(nullptr != other);

    const dia::Symbol* selfSymbol  = reinterpret_cast<PyDiaSymbol*>(self)->diaSymbol;
    const dia::Symbol* otherSymbol = reinterpret_cast<PyDiaSymbol*>(other)->diaSymbol;

    _ASSERT(nullptr != selfSymbol);
    _ASSERT(nullptr != otherSymbol);

    bool result = false;
    switch (op)
    {
    case Py_EQ:
        result = *selfSymbol == *otherSymbol;
        break;
    case Py_NE:
        result = *selfSymbol != *otherSymbol;
        break;
    case Py_LT:
        result = *selfSymbol < *otherSymbol;
        break;
    case Py_LE:
        result = *selfSymbol <= *otherSymbol;
        break;
    case Py_GT:
        result = *selfSymbol > *otherSymbol;
        break;
    case Py_GE:
        result = *selfSymbol >= *otherSymbol;
        break;
    default:
        Py_UNREACHABLE();
    }

    if (result)
    {
        Py_RETURN_TRUE;
    }
    else
    {
        Py_RETURN_FALSE;
    }
}

PyObject* PyDiaSymbol_repr(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    auto safeExecution = [&]() -> PyObject*
    {
        _ASSERT_EXPR(nullptr != self->dataSource->diaDataSource, L"Internal data source raw pointer must be initialized!");
        const std::wstring dataSource = self->dataSource->diaDataSource->getLoadedPdbFile();
        const auto hash               = self->diaSymbol->calcHash();

        return PyUnicode_FromFormat("%T(R'%U', 0x%.16llX)", self, PyObject_FromWstring(dataSource), hash);
    };
    PYDIA_SAFE_TRY({ return safeExecution(); });
}

Py_hash_t PyDiaSymbol_hash(PyObject* self)
{
    _ASSERT_EXPR(nullptr != self, L"Self must not be null when hashing!");
    dia::Symbol* selfSymbol = reinterpret_cast<PyDiaSymbol*>(self)->diaSymbol;
    _ASSERT_EXPR(nullptr != selfSymbol, L"Self->diaSymbol must not be null when hashing!");
    PYDIA_SAFE_TRY_EXCEPT({ return static_cast<Py_hash_t>(selfSymbol->calcHash()); }, { Py_UNREACHABLE(); });
    Py_UNREACHABLE();
}

static void PyDiaSymbol_dealloc(PyDiaSymbol* self)
{
    _ASSERT(nullptr != self);
    if (self->diaSymbol)
    {
        delete self->diaSymbol;
    }
    if (self->dataSource)
    {
        const auto dataSource = self->dataSource;
        self->dataSource      = nullptr;
        Py_DECREF(dataSource);
    }
    if (Py_TYPE(((PyObject*)((self))))->tp_free)
    {
        Py_TYPE(((PyObject*)((self))))->tp_free((PyObject*)self);
    }
}

static int PyDiaSymbol_init(PyDiaSymbol* self, PyObject* args, PyObject* kwds)
{
    self->diaSymbol = new (std::nothrow) dia::Symbol();
    if (!self->diaSymbol)
    {
        PyErr_SetString(PyExc_MemoryError, "Failed to create Symbol object.");
        return -1;
    }
    return 0;
};

static PyMethodDef PyDiaSymbol_methods[] = {
    PyDiaSymbolMethodEntry_getAccess,
    PyDiaSymbolMethodEntry_getSymIndexId,
    PyDiaSymbolMethodEntry_isScoped,
    PyDiaSymbolMethodEntry_getClassParent,
    PyDiaSymbolMethodEntry_getClassParentId,
    PyDiaSymbolMethodEntry_isVolatile,
    PyDiaSymbolMethodEntry_getLength,
    PyDiaSymbolMethodEntry_isAddressTaken,
    PyDiaSymbolMethodEntry_getAge,
    PyDiaSymbolMethodEntry_getArrayIndexType,
    PyDiaSymbolMethodEntry_getArrayIndexTypeId,
    PyDiaSymbolMethodEntry_getBackendBuild,
    PyDiaSymbolMethodEntry_getBackendMajor,
    PyDiaSymbolMethodEntry_getBackendMinor,
    PyDiaSymbolMethodEntry_getBackendQfe,
    PyDiaSymbolMethodEntry_getBaseDataOffset,
    PyDiaSymbolMethodEntry_getBaseDataSlot,
    PyDiaSymbolMethodEntry_getBaseSymbol,
    PyDiaSymbolMethodEntry_getBaseSymbolId,
    PyDiaSymbolMethodEntry_getBaseType,
    PyDiaSymbolMethodEntry_getBitPosition,
    PyDiaSymbolMethodEntry_getBindId,
    PyDiaSymbolMethodEntry_getBindSlot,
    PyDiaSymbolMethodEntry_isCode,
    PyDiaSymbolMethodEntry_getCoffGroup,
    PyDiaSymbolMethodEntry_isCompilerGenerated,
    PyDiaSymbolMethodEntry_getCompilerName,
    PyDiaSymbolMethodEntry_isConst,
    PyDiaSymbolMethodEntry_isConstantExport,
    PyDiaSymbolMethodEntry_hasConstructor,
    PyDiaSymbolMethodEntry_getCount,
    PyDiaSymbolMethodEntry_getCountLiveRanges,
    PyDiaSymbolMethodEntry_hasCustomCallingConvention,
    PyDiaSymbolMethodEntry_getCallingConvention,
#if 0  // TODO: Implement
    PyDiaSymbolMethodEntry_getSrcLineOnTypeDefn,
    PyDiaSymbolMethodEntry_getDataBytes,
#endif
    PyDiaSymbolMethodEntry_isDataExport,
    PyDiaSymbolMethodEntry_getDataKind,
    PyDiaSymbolMethodEntry_isEditAndContinueEnabled,
    PyDiaSymbolMethodEntry_getExceptionHandlerAddressOffset,
    PyDiaSymbolMethodEntry_getExceptionHandlerAddressSection,
    PyDiaSymbolMethodEntry_getExceptionHandlerRelativeVirtualAddress,
    PyDiaSymbolMethodEntry_getExceptionHandlerVirtualAddress,
    PyDiaSymbolMethodEntry_isExportWithExplicitOrdinal,
    PyDiaSymbolMethodEntry_isExportForwarder,
    PyDiaSymbolMethodEntry_isFarReturn,
    PyDiaSymbolMethodEntry_getFinalLiveStaticSize,
    PyDiaSymbolMethodEntry_isFramePointerPresent,
    PyDiaSymbolMethodEntry_getFrameSize,
    PyDiaSymbolMethodEntry_getFrontEndBuild,
    PyDiaSymbolMethodEntry_getFrontEndMajor,
    PyDiaSymbolMethodEntry_getFrontEndMinor,
    PyDiaSymbolMethodEntry_getFrontEndQfe,
    PyDiaSymbolMethodEntry_isFunction,
    PyDiaSymbolMethodEntry_getGuid,
    PyDiaSymbolMethodEntry_hasAlloca,
    PyDiaSymbolMethodEntry_hasAssignmentOperator,
    PyDiaSymbolMethodEntry_hasCastOperator,
    PyDiaSymbolMethodEntry_hasControlFlowCheck,
    PyDiaSymbolMethodEntry_hasDebugInfo,
    PyDiaSymbolMethodEntry_hasEh,
    PyDiaSymbolMethodEntry_hasEha,
    PyDiaSymbolMethodEntry_hasInlineAsm,
    PyDiaSymbolMethodEntry_hasLongJump,
    PyDiaSymbolMethodEntry_hasManagedCode,
    PyDiaSymbolMethodEntry_hasNestedTypes,
    PyDiaSymbolMethodEntry_hasSeh,
    PyDiaSymbolMethodEntry_hasSecurityChecks,
    PyDiaSymbolMethodEntry_hasSetJump,
    PyDiaSymbolMethodEntry_hasValidPgoCounts,
    PyDiaSymbolMethodEntry_getHfaDouble,
    PyDiaSymbolMethodEntry_getHfaFloat,
    PyDiaSymbolMethodEntry_getIndirectVirtualBaseClass,
    PyDiaSymbolMethodEntry_hasInlineSpecifier,
    PyDiaSymbolMethodEntry_hasInterruptReturn,
    PyDiaSymbolMethodEntry_isIntrinsic,
    PyDiaSymbolMethodEntry_isIntro,
    PyDiaSymbolMethodEntry_isAggregated,
    PyDiaSymbolMethodEntry_isCtypes,
    PyDiaSymbolMethodEntry_isConstructorVirtualBase,
    PyDiaSymbolMethodEntry_isCxxReturnUdt,
    PyDiaSymbolMethodEntry_isDataAligned,
    PyDiaSymbolMethodEntry_isHlslData,
    PyDiaSymbolMethodEntry_isMultipleInheritance,
    PyDiaSymbolMethodEntry_isNaked,
    PyDiaSymbolMethodEntry_isOptimizedAway,
    PyDiaSymbolMethodEntry_isOptimizedForSpeed,
    PyDiaSymbolMethodEntry_isPgo,
    PyDiaSymbolMethodEntry_isPointerToDataMember,
    PyDiaSymbolMethodEntry_isSingleInheritance,
    PyDiaSymbolMethodEntry_isSplitted,
    PyDiaSymbolMethodEntry_isStatic,
    PyDiaSymbolMethodEntry_isStripped,
    PyDiaSymbolMethodEntry_getLanguage,
    PyDiaSymbolMethodEntry_getLexicalParent,
    PyDiaSymbolMethodEntry_getLexicalParentId,
    PyDiaSymbolMethodEntry_getLibraryName,
    PyDiaSymbolMethodEntry_getLiveRangeLength,
    PyDiaSymbolMethodEntry_getLiveRangeStartAddressOffset,
    PyDiaSymbolMethodEntry_getLiveRangeStartAddressSection,
    PyDiaSymbolMethodEntry_getLiveRangeStartRelativeVirtualAddress,
    PyDiaSymbolMethodEntry_getLocalBasePointerRegisterId,
    PyDiaSymbolMethodEntry_getLocationType,
    PyDiaSymbolMethodEntry_getLowerBound,
    PyDiaSymbolMethodEntry_getLowerBoundId,
    PyDiaSymbolMethodEntry_getMachineType,
    PyDiaSymbolMethodEntry_isManaged,
    PyDiaSymbolMethodEntry_getMemorySpaceKind,
    PyDiaSymbolMethodEntry_getModifierValues,
    PyDiaSymbolMethodEntry_isMsil,
    PyDiaSymbolMethodEntry_getName,
    PyDiaSymbolMethodEntry_isNested,
    PyDiaSymbolMethodEntry_isNoInline,
    PyDiaSymbolMethodEntry_isNoNameExport,
    PyDiaSymbolMethodEntry_isNoReturn,
    PyDiaSymbolMethodEntry_hasNoStackOrdering,
    PyDiaSymbolMethodEntry_isNotReached,
    PyDiaSymbolMethodEntry_getNumberOfModifiers,
    PyDiaSymbolMethodEntry_getNumberOfRegisterIndices,
    PyDiaSymbolMethodEntry_getObjectFileName,
    PyDiaSymbolMethodEntry_getObjectPointerType,
    PyDiaSymbolMethodEntry_getOemId,
    PyDiaSymbolMethodEntry_getOemSymbolId,
    PyDiaSymbolMethodEntry_getOffset,
    PyDiaSymbolMethodEntry_getOffsetInUdt,
    PyDiaSymbolMethodEntry_hasOptimizedCodeDebugInfo,
    PyDiaSymbolMethodEntry_getOrdinal,
    PyDiaSymbolMethodEntry_hasOverloadedOperator,
    PyDiaSymbolMethodEntry_getPgoDynamicInstructionCount,
    PyDiaSymbolMethodEntry_isPacked,
    PyDiaSymbolMethodEntry_isPure,
    PyDiaSymbolMethodEntry_getNumberOfRows,
    PyDiaSymbolMethodEntry_isRValueReference,
    PyDiaSymbolMethodEntry_getRank,
    PyDiaSymbolMethodEntry_isReference,
    PyDiaSymbolMethodEntry_getRegisterType,
    PyDiaSymbolMethodEntry_getRelativeVirtualAddress,
    PyDiaSymbolMethodEntry_isRestrictedType,
    PyDiaSymbolMethodEntry_getSamplerSlot,
    PyDiaSymbolMethodEntry_isSealed,
    PyDiaSymbolMethodEntry_getSignature,
    PyDiaSymbolMethodEntry_getSizeInUdt,
    PyDiaSymbolMethodEntry_getSlot,
    PyDiaSymbolMethodEntry_getSourceFileName,
    PyDiaSymbolMethodEntry_getStaticSize,
    PyDiaSymbolMethodEntry_hasStrictGsCheck,
    PyDiaSymbolMethodEntry_getStride,
    PyDiaSymbolMethodEntry_getSubType,
    PyDiaSymbolMethodEntry_getSubTypeId,
    PyDiaSymbolMethodEntry_getSymTag,
    PyDiaSymbolMethodEntry_getSymbolsFileName,
    PyDiaSymbolMethodEntry_getTargetOffset,
    PyDiaSymbolMethodEntry_getThisAdjust,
    PyDiaSymbolMethodEntry_getThunkOrdinal,
    PyDiaSymbolMethodEntry_getTimeStamp,
    PyDiaSymbolMethodEntry_getToken,
    PyDiaSymbolMethodEntry_getType,
    PyDiaSymbolMethodEntry_getTypeId,
#if 0  // TODO: Implement
    PyDiaSymbolMethodEntry_getTypeIds,
    PyDiaSymbolMethodEntry_getTypes,
#endif
    PyDiaSymbolMethodEntry_isUnaligned,
    PyDiaSymbolMethodEntry_getUndecoratedName,
    PyDiaSymbolMethodEntry_getUndecoratedNameEx,
    PyDiaSymbolMethodEntry_getUnmodifiedType,
    PyDiaSymbolMethodEntry_isUnused,
    PyDiaSymbolMethodEntry_getValue,
    PyDiaSymbolMethodEntry_isVirtual,
    PyDiaSymbolMethodEntry_getVirtualAddress,
    PyDiaSymbolMethodEntry_getVirtualBaseClass,
    PyDiaSymbolMethodEntry_getVirtualBaseDispIndex,
    PyDiaSymbolMethodEntry_getVirtualBaseOffset,
    PyDiaSymbolMethodEntry_getVirtualBasePointerOffset,
    PyDiaSymbolMethodEntry_getVirtualBaseTableType,
    PyDiaSymbolMethodEntry_getVirtualTableShape,
    PyDiaSymbolMethodEntry_getVirtualTableShapeId,
    PyDiaSymbolMethodEntry_getAddressOffset,
    PyDiaSymbolMethodEntry_getAddressSection,
    PyDiaSymbolMethodEntry_wasInlined,
    PyDiaSymbolMethodEntry_getPgoEdgeCount,
    PyDiaSymbolMethodEntry_getPgoEntryCount,
    PyDiaSymbolMethodEntry_getParamBasePointerRegisterId,
    PyDiaSymbolMethodEntry_getPhaseName,
    PyDiaSymbolMethodEntry_getPlatform,
    PyDiaSymbolMethodEntry_getRegisterId,
    PyDiaSymbolMethodEntry_getTargetRelativeVirtualAddress,
    PyDiaSymbolMethodEntry_getTargetSection,
    PyDiaSymbolMethodEntry_getTargetVirtualAddress,
    PyDiaSymbolMethodEntry_getTextureSlot,
    PyDiaSymbolMethodEntry_getUdtKind,
    PyDiaSymbolMethodEntry_getUpperBound,
    PyDiaSymbolMethodEntry_getUpperBoundId,
    {NULL, NULL, 0, NULL}  // Sentinel
};

#ifdef _DEBUG
// Allow complete and unmonitored usage of the DiaLib private symbol functions in debug mode.
PYDIA_SYMBOL_TYPE_DEFINITION_WITH_BASE(Symbol, PyDiaSymbol_methods, 0);
#else
// In release mode, users should never directly access DiaLib methods without pydia checking that the type is valid.
PYDIA_SYMBOL_TYPE_DEFINITION_WITH_BASE(Symbol, 0, 0);
#endif

// Method: PyDiaSymbol_getClassParent
PyObject* PyDiaSymbol_getClassParent(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        auto classParent = self->diaSymbol->getClassParent();
        return PyDiaSymbol_FromSymbol(std::move(classParent), self->dataSource);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getClassParentId
PyObject* PyDiaSymbol_getClassParentId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD classParentId = self->diaSymbol->getClassParentId();
        return PyLong_FromUnsignedLong(classParentId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_access
PyObject* PyDiaSymbol_getAccess(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getAccess and convert result to Python integer
        const dia::AccessModifier accessModifiers = self->diaSymbol->getAccess();
        _ASSERT(sizeof(accessModifiers) == sizeof(DWORD));
        return PyLong_FromUnsignedLong(static_cast<long>(accessModifiers));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getAddressOffset
PyObject* PyDiaSymbol_getAddressOffset(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getAddressOffset and convert to Python integer
        const DWORD offset = self->diaSymbol->getAddressOffset();
        return PyLong_FromUnsignedLong(offset);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getAddressSection
PyObject* PyDiaSymbol_getAddressSection(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getAddressSection and convert to Python integer
        const DWORD section = self->diaSymbol->getAddressSection();
        return PyLong_FromUnsignedLong(section);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isAddressTaken
PyObject* PyDiaSymbol_isAddressTaken(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getAddressTaken and convert to Python boolean
        const bool addressTaken = self->diaSymbol->getAddressTaken();
        return PyBool_FromLong(addressTaken);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getAge
PyObject* PyDiaSymbol_getAge(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getAge and convert to Python integer
        const DWORD age = self->diaSymbol->getAge();
        return PyLong_FromUnsignedLong(age);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getArrayIndexType
PyObject* PyDiaSymbol_getArrayIndexType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getArrayIndexType and wrap the returned Symbol in a new PyDiaSymbol
        dia::Symbol arrayIndexType = self->diaSymbol->getArrayIndexType();
        return PyDiaSymbol_FromSymbol(std::move(arrayIndexType), self->dataSource);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getArrayIndexTypeId
PyObject* PyDiaSymbol_getArrayIndexTypeId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getArrayIndexTypeId and convert to Python integer
        const DWORD typeId = self->diaSymbol->getArrayIndexTypeId();
        return PyLong_FromUnsignedLong(typeId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getBackendBuild
PyObject* PyDiaSymbol_getBackendBuild(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getBackEndBuild and convert to Python integer
        const DWORD build = self->diaSymbol->getBackEndBuild();
        return PyLong_FromUnsignedLong(build);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getBackendMajor
PyObject* PyDiaSymbol_getBackendMajor(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getBackEndMajor and convert to Python integer
        const DWORD major = self->diaSymbol->getBackEndMajor();
        return PyLong_FromUnsignedLong(major);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getBackendMinor
PyObject* PyDiaSymbol_getBackendMinor(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getBackEndMinor and convert to Python integer
        const DWORD minor = self->diaSymbol->getBackEndMinor();
        return PyLong_FromUnsignedLong(minor);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getBackendQfe
PyObject* PyDiaSymbol_getBackendQfe(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getBackEndQFE and convert to Python integer
        const DWORD qfe = self->diaSymbol->getBackEndQFE();
        return PyLong_FromUnsignedLong(qfe);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getBaseDataOffset
PyObject* PyDiaSymbol_getBaseDataOffset(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getBaseDataOffset and convert to Python integer
        const DWORD offset = self->diaSymbol->getBaseDataOffset();
        return PyLong_FromUnsignedLong(offset);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getBaseDataSlot
PyObject* PyDiaSymbol_getBaseDataSlot(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getBaseDataSlot and convert to Python integer
        const DWORD slot = self->diaSymbol->getBaseDataSlot();
        return PyLong_FromUnsignedLong(slot);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getBaseSymbol
PyObject* PyDiaSymbol_getBaseSymbol(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getBaseSymbol and wrap the returned Symbol in a new PyDiaSymbol
        dia::Symbol baseSymbol = self->diaSymbol->getBaseSymbol();
        return PyDiaSymbol_FromSymbol(std::move(baseSymbol), self->dataSource);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getBaseSymbolId
PyObject* PyDiaSymbol_getBaseSymbolId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getBaseSymbolId and convert to Python integer
        const DWORD symbolId = self->diaSymbol->getBaseSymbolId();
        return PyLong_FromUnsignedLong(symbolId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getBaseType
PyObject* PyDiaSymbol_getBaseType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getBaseType and convert to Python integer (representing the enum BasicType)
        const BasicType baseType = self->diaSymbol->getBaseType();
        // Static assert to assure that this static_cast is valid
        static_assert(sizeof(baseType) <= sizeof(unsigned long));
        return PyDiaBasicType_FromBasicType(baseType);
    });
    Py_UNREACHABLE();
}

PyObject* PyDiaSymbol_getBitPosition(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getBitPosition and convert to Python integer
        const DWORD bitPosition = self->diaSymbol->getBitPosition();
        return PyLong_FromUnsignedLong(bitPosition);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getBindId
PyObject* PyDiaSymbol_getBindId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getBindID and convert to Python integer
        const DWORD bindId = self->diaSymbol->getBindID();
        return PyLong_FromUnsignedLong(bindId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getBindSlot
PyObject* PyDiaSymbol_getBindSlot(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getBindSlot and convert to Python integer
        const DWORD slot = self->diaSymbol->getBindSlot();
        return PyLong_FromUnsignedLong(slot);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isCode
PyObject* PyDiaSymbol_isCode(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getCode and convert to Python boolean
        const bool isCode = self->diaSymbol->getCode();
        return PyBool_FromLong(isCode);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getCoffGroup
PyObject* PyDiaSymbol_getCoffGroup(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getCoffGroup and wrap the returned Symbol in a new PyDiaSymbol
        dia::Symbol coffGroup = self->diaSymbol->getCoffGroup();
        return PyDiaSymbol_FromSymbol(std::move(coffGroup), self->dataSource);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isCompilerGenerated
PyObject* PyDiaSymbol_isCompilerGenerated(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getCompilerGenerated and convert to Python boolean
        const bool compilerGenerated = self->diaSymbol->getCompilerGenerated();
        return PyBool_FromLong(compilerGenerated);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getCompilerName
PyObject* PyDiaSymbol_getCompilerName(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getCompilerName and convert to Python string
        const BstrWrapper compilerName = self->diaSymbol->getCompilerName();
        return PyObject_FromBstrWrapper(compilerName);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_const_type
PyObject* PyDiaSymbol_isConst(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getConstType and convert to Python boolean
        const bool constType = self->diaSymbol->getConstType();
        return PyBool_FromLong(constType);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_constant_export
PyObject* PyDiaSymbol_isConstantExport(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getConstantExport and convert to Python boolean
        const bool constantExport = self->diaSymbol->getConstantExport();
        return PyBool_FromLong(constantExport);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_constructor
PyObject* PyDiaSymbol_hasConstructor(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getConstructor and convert to Python boolean
        const bool constructor = self->diaSymbol->getConstructor();
        return PyBool_FromLong(constructor);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getContainer
PyObject* PyDiaSymbol_getContainer(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getContainer and wrap the returned Symbol in a new PyDiaSymbol
        dia::Symbol container = self->diaSymbol->getContainer();
        return PyDiaSymbol_FromSymbol(std::move(container), self->dataSource);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getCount
PyObject* PyDiaSymbol_getCount(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getCount and convert to Python integer
        const DWORD count = self->diaSymbol->getCount();
        return PyLong_FromUnsignedLong(count);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getCountLiveRanges
PyObject* PyDiaSymbol_getCountLiveRanges(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getCountLiveRanges and convert to Python integer
        const DWORD countLiveRanges = self->diaSymbol->getCountLiveRanges();
        return PyLong_FromUnsignedLong(countLiveRanges);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasCustomCallingConvention
PyObject* PyDiaSymbol_hasCustomCallingConvention(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getCustomCallingConvention and convert to Python boolean
        const bool customCallingConvention = self->diaSymbol->getCustomCallingConvention();
        return PyBool_FromLong(customCallingConvention);
    });
    Py_UNREACHABLE();
}

PyObject* PyDiaSymbol_getCallingConvention(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const auto callingConvention = self->diaSymbol->getCallingConvention();
        return PyDiaCallingConvention_FromCallingConvention(callingConvention);
    });
    Py_UNREACHABLE();
}

#if 0
// The DiaLib version of this is not implemented either :(

// Method: PyDiaSymbol_getDataBytes
PyObject* PyDiaSymbol_getDataBytes(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getDataBytes and convert the result to a Python bytes object
        const DataBytes dataBytes = self->diaSymbol->getDataBytes();
        return PyBytes_FromStringAndSize(dataBytes.data(), dataBytes.size());
    });
    Py_UNREACHABLE();
}
#endif

// Method: PyDiaSymbol_isDataExport
PyObject* PyDiaSymbol_isDataExport(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getDataExport and convert to Python boolean
        const bool dataExport = self->diaSymbol->getDataExport();
        return PyBool_FromLong(dataExport);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getDataKind
PyObject* PyDiaSymbol_getDataKind(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getDataKind and convert to Python integer (representing the enum DataKind)
        const DataKind dataKind = self->diaSymbol->getDataKind();
        return PyLong_FromLong(static_cast<long>(dataKind));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isEditAndContinueEnabled
PyObject* PyDiaSymbol_isEditAndContinueEnabled(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getEditAndContinueEnabled and convert to Python boolean
        const bool editAndContinueEnabled = self->diaSymbol->getEditAndContinueEnabled();
        return PyBool_FromLong(editAndContinueEnabled);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getExceptionHandlerAddressOffset
PyObject* PyDiaSymbol_getExceptionHandlerAddressOffset(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getExceptionHandlerAddressOffset and convert to Python integer
        const DWORD addressOffset = self->diaSymbol->getExceptionHandlerAddressOffset();
        return PyLong_FromUnsignedLong(addressOffset);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getExceptionHandlerAddressSection
PyObject* PyDiaSymbol_getExceptionHandlerAddressSection(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getExceptionHandlerAddressSection and convert to Python integer
        const DWORD addressSection = self->diaSymbol->getExceptionHandlerAddressSection();
        return PyLong_FromUnsignedLong(addressSection);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getExceptionHandlerRelativeVirtualAddress
PyObject* PyDiaSymbol_getExceptionHandlerRelativeVirtualAddress(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getExceptionHandlerRelativeVirtualAddress and convert to Python integer
        const DWORD relativeVirtualAddress = self->diaSymbol->getExceptionHandlerRelativeVirtualAddress();
        return PyLong_FromUnsignedLong(relativeVirtualAddress);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getExceptionHandlerVirtualAddress
PyObject* PyDiaSymbol_getExceptionHandlerVirtualAddress(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getExceptionHandlerVirtualAddress and convert to Python integer
        const ULONGLONG virtualAddress = self->diaSymbol->getExceptionHandlerVirtualAddress();
        return PyLong_FromUnsignedLongLong(virtualAddress);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isExportWithExplicitOrdinal
PyObject* PyDiaSymbol_isExportWithExplicitOrdinal(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getExportHasExplicitlyAssignedOrdinal and convert to Python boolean
        const bool hasExplicitOrdinal = self->diaSymbol->getExportHasExplicitlyAssignedOrdinal();
        return PyBool_FromLong(hasExplicitOrdinal);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isExportForwarder
PyObject* PyDiaSymbol_isExportForwarder(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getExportIsForwarder and convert to Python boolean
        const bool isForwarder = self->diaSymbol->getExportIsForwarder();
        return PyBool_FromLong(isForwarder);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isFarReturn
PyObject* PyDiaSymbol_isFarReturn(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getFarReturn and convert to Python boolean
        const bool farReturn = self->diaSymbol->getFarReturn();
        return PyBool_FromLong(farReturn);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getFinalLiveStaticSize
PyObject* PyDiaSymbol_getFinalLiveStaticSize(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getFinalLiveStaticSize and convert to Python integer
        const DWORD finalLiveStaticSize = self->diaSymbol->getFinalLiveStaticSize();
        return PyLong_FromUnsignedLong(finalLiveStaticSize);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isFramePointerPresent
PyObject* PyDiaSymbol_isFramePointerPresent(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getFramePointerPresent and convert to Python boolean
        const bool framePointerPresent = self->diaSymbol->getFramePointerPresent();
        return PyBool_FromLong(framePointerPresent);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getFrameSize
PyObject* PyDiaSymbol_getFrameSize(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getFrameSize and convert to Python integer
        const DWORD frameSize = self->diaSymbol->getFrameSize();
        return PyLong_FromUnsignedLong(frameSize);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getFrontEndBuild
PyObject* PyDiaSymbol_getFrontEndBuild(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getFrontEndBuild and convert to Python integer
        const DWORD frontEndBuild = self->diaSymbol->getFrontEndBuild();
        return PyLong_FromUnsignedLong(frontEndBuild);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getFrontEndMajor
PyObject* PyDiaSymbol_getFrontEndMajor(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getFrontEndMajor and convert to Python integer
        const DWORD frontEndMajor = self->diaSymbol->getFrontEndMajor();
        return PyLong_FromUnsignedLong(frontEndMajor);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getFrontEndMinor
PyObject* PyDiaSymbol_getFrontEndMinor(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getFrontEndMinor and convert to Python integer
        const DWORD frontEndMinor = self->diaSymbol->getFrontEndMinor();
        return PyLong_FromUnsignedLong(frontEndMinor);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getFrontEndQfe
PyObject* PyDiaSymbol_getFrontEndQfe(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getFrontEndQFE and convert to Python integer
        const DWORD frontEndQFE = self->diaSymbol->getFrontEndQFE();
        return PyLong_FromUnsignedLong(frontEndQFE);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isFunction
PyObject* PyDiaSymbol_isFunction(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getFunction and convert to Python boolean
        const bool isFunction = self->diaSymbol->getFunction();
        return PyBool_FromLong(isFunction);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getGuid
PyObject* PyDiaSymbol_getGuid(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Call getGuid and convert to Python string (UUID)
        const GUID guid       = self->diaSymbol->getGuid();
        const auto guidString = dia::convertGuidToString(guid);
        return PyUnicode_FromString(guidString.c_str());
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasAlloca
PyObject* PyDiaSymbol_hasAlloca(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        // Call getHasAlloca and convert to Python boolean
        const bool hasAlloca = self->diaSymbol->getHasAlloca();
        return PyBool_FromLong(hasAlloca);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasAssignmentOperator
PyObject* PyDiaSymbol_hasAssignmentOperator(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hasAssignmentOperator = self->diaSymbol->getHasAssignmentOperator();
        return PyBool_FromLong(hasAssignmentOperator);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasCastOperator
PyObject* PyDiaSymbol_hasCastOperator(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hasCastOperator = self->diaSymbol->getHasCastOperator();
        return PyBool_FromLong(hasCastOperator);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasControlFlowCheck
PyObject* PyDiaSymbol_hasControlFlowCheck(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hasControlFlowCheck = self->diaSymbol->getHasControlFlowCheck();
        return PyBool_FromLong(hasControlFlowCheck);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasDebugInfo
PyObject* PyDiaSymbol_hasDebugInfo(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hasDebugInfo = self->diaSymbol->getHasDebugInfo();
        return PyBool_FromLong(hasDebugInfo);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasEh
PyObject* PyDiaSymbol_hasEh(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hasEH = self->diaSymbol->getHasEH();
        return PyBool_FromLong(hasEH);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasEha
PyObject* PyDiaSymbol_hasEha(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hasEHa = self->diaSymbol->getHasEHa();
        return PyBool_FromLong(hasEHa);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasInlineAsm
PyObject* PyDiaSymbol_hasInlineAsm(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hasInlAsm = self->diaSymbol->getHasInlAsm();
        return PyBool_FromLong(hasInlAsm);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasLongJump
PyObject* PyDiaSymbol_hasLongJump(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hasLongJump = self->diaSymbol->getHasLongJump();
        return PyBool_FromLong(hasLongJump);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasManagedCode
PyObject* PyDiaSymbol_hasManagedCode(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hasManagedCode = self->diaSymbol->getHasManagedCode();
        return PyBool_FromLong(hasManagedCode);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasNestedTypes
PyObject* PyDiaSymbol_hasNestedTypes(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hasNestedTypes = self->diaSymbol->getHasNestedTypes();
        return PyBool_FromLong(hasNestedTypes);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasSeh
PyObject* PyDiaSymbol_hasSeh(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hasSEH = self->diaSymbol->getHasSEH();
        return PyBool_FromLong(hasSEH);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasSecurityChecks
PyObject* PyDiaSymbol_hasSecurityChecks(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hasSecurityChecks = self->diaSymbol->getHasSecurityChecks();
        return PyBool_FromLong(hasSecurityChecks);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasSetJump
PyObject* PyDiaSymbol_hasSetJump(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hasSetJump = self->diaSymbol->getHasSetJump();
        return PyBool_FromLong(hasSetJump);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasValidPgoCounts
PyObject* PyDiaSymbol_hasValidPgoCounts(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hasValidPGOCounts = self->diaSymbol->getHasValidPGOCounts();
        return PyBool_FromLong(hasValidPGOCounts);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getHfaDouble
PyObject* PyDiaSymbol_getHfaDouble(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hfaDouble = self->diaSymbol->getHfaDouble();
        return PyBool_FromLong(hfaDouble);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getHfaFloat
PyObject* PyDiaSymbol_getHfaFloat(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool hfaFloat = self->diaSymbol->getHfaFloat();
        return PyBool_FromLong(hfaFloat);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getIndirectVirtualBaseClass
PyObject* PyDiaSymbol_getIndirectVirtualBaseClass(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool indirectVirtualBaseClass = self->diaSymbol->getIndirectVirtualBaseClass();
        return PyBool_FromLong(indirectVirtualBaseClass);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasInlineSpecifier
PyObject* PyDiaSymbol_hasInlineSpecifier(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool inlSpec = self->diaSymbol->getInlSpec();
        return PyBool_FromLong(inlSpec);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasInterruptReturn
PyObject* PyDiaSymbol_hasInterruptReturn(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool interruptReturn = self->diaSymbol->getInterruptReturn();
        return PyBool_FromLong(interruptReturn);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isIntrinsic
PyObject* PyDiaSymbol_isIntrinsic(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool intrinsic = self->diaSymbol->getIntrinsic();
        return PyBool_FromLong(intrinsic);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isIntro
PyObject* PyDiaSymbol_isIntro(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool intro = self->diaSymbol->getIntro();
        return PyBool_FromLong(intro);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isAcceleratorGroupSharedLocal
PyObject* PyDiaSymbol_isAcceleratorGroupSharedLocal(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool isAcceleratorGroupSharedLocal = self->diaSymbol->getIsAcceleratorGroupSharedLocal();
        return PyBool_FromLong(isAcceleratorGroupSharedLocal);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isAcceleratorPointerTagLiveRange
PyObject* PyDiaSymbol_isAcceleratorPointerTagLiveRange(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool isAcceleratorPointerTagLiveRange = self->diaSymbol->getIsAcceleratorPointerTagLiveRange();
        return PyBool_FromLong(isAcceleratorPointerTagLiveRange);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isAcceleratorStubFunction
PyObject* PyDiaSymbol_isAcceleratorStubFunction(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool isAcceleratorStubFunction = self->diaSymbol->getIsAcceleratorStubFunction();
        return PyBool_FromLong(isAcceleratorStubFunction);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isAggregated
PyObject* PyDiaSymbol_isAggregated(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool isAggregated = self->diaSymbol->getIsAggregated();
        return PyBool_FromLong(isAggregated);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isCtypes
PyObject* PyDiaSymbol_isCtypes(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool isCTypes = self->diaSymbol->getIsCTypes();
        return PyBool_FromLong(isCTypes);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isConvertedCil
PyObject* PyDiaSymbol_isConvertedCil(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool isCVTCIL = self->diaSymbol->getIsCVTCIL();
        return PyBool_FromLong(isCVTCIL);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isConstructorVirtualBase
PyObject* PyDiaSymbol_isConstructorVirtualBase(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool isConstructorVirtualBase = self->diaSymbol->getIsConstructorVirtualBase();
        return PyBool_FromLong(isConstructorVirtualBase);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isCxxReturnUdt
PyObject* PyDiaSymbol_isCxxReturnUdt(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool isCxxReturnUdt = self->diaSymbol->getIsCxxReturnUdt();
        return PyBool_FromLong(isCxxReturnUdt);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isDataAligned
PyObject* PyDiaSymbol_isDataAligned(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool isDataAligned = self->diaSymbol->getIsDataAligned();
        return PyBool_FromLong(isDataAligned);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isHlslData
PyObject* PyDiaSymbol_isHlslData(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isHLSLData = self->diaSymbol->getIsHLSLData();
        return PyBool_FromLong(isHLSLData);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isHotpatchable
PyObject* PyDiaSymbol_isHotpatchable(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isHotpatchable = self->diaSymbol->getIsHotpatchable();
        return PyBool_FromLong(isHotpatchable);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isInterfaceUdt
PyObject* PyDiaSymbol_isInterfaceUdt(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isInterfaceUdt = self->diaSymbol->getIsInterfaceUdt();
        return PyBool_FromLong(isInterfaceUdt);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isLtcg
PyObject* PyDiaSymbol_isLtcg(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isLTCG = self->diaSymbol->getIsLTCG();
        return PyBool_FromLong(isLTCG);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isLocationControlFlowDependent
PyObject* PyDiaSymbol_isLocationControlFlowDependent(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isLocationControlFlowDependent = self->diaSymbol->getIsLocationControlFlowDependent();
        return PyBool_FromLong(isLocationControlFlowDependent);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isMsilNetmodule
PyObject* PyDiaSymbol_isMsilNetmodule(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isMSILNetmodule = self->diaSymbol->getIsMSILNetmodule();
        return PyBool_FromLong(isMSILNetmodule);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isMatrixRowMajor
PyObject* PyDiaSymbol_isMatrixRowMajor(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isMatrixRowMajor = self->diaSymbol->getIsMatrixRowMajor();
        return PyBool_FromLong(isMatrixRowMajor);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isMultipleInheritance
PyObject* PyDiaSymbol_isMultipleInheritance(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isMultipleInheritance = self->diaSymbol->getIsMultipleInheritance();
        return PyBool_FromLong(isMultipleInheritance);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isNaked
PyObject* PyDiaSymbol_isNaked(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isNaked = self->diaSymbol->getIsNaked();
        return PyBool_FromLong(isNaked);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isOptimizedAway
PyObject* PyDiaSymbol_isOptimizedAway(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isOptimizedAway = self->diaSymbol->getIsOptimizedAway();
        return PyBool_FromLong(isOptimizedAway);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isOptimizedForSpeed
PyObject* PyDiaSymbol_isOptimizedForSpeed(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isOptimizedForSpeed = self->diaSymbol->getIsOptimizedForSpeed();
        return PyBool_FromLong(isOptimizedForSpeed);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isPgo
PyObject* PyDiaSymbol_isPgo(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isPGO = self->diaSymbol->getIsPGO();
        return PyBool_FromLong(isPGO);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isPointerBasedOnSymbolValue
PyObject* PyDiaSymbol_isPointerBasedOnSymbolValue(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isPointerBasedOnSymbolValue = self->diaSymbol->getIsPointerBasedOnSymbolValue();
        return PyBool_FromLong(isPointerBasedOnSymbolValue);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isPointerToDataMember
PyObject* PyDiaSymbol_isPointerToDataMember(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isPointerToDataMember = self->diaSymbol->getIsPointerToDataMember();
        return PyBool_FromLong(isPointerToDataMember);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isPointerToMemberFunction
PyObject* PyDiaSymbol_isPointerToMemberFunction(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isPointerToMemberFunction = self->diaSymbol->getIsPointerToMemberFunction();
        return PyBool_FromLong(isPointerToMemberFunction);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isRefUdt
PyObject* PyDiaSymbol_isRefUdt(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isRefUdt = self->diaSymbol->getIsRefUdt();
        return PyBool_FromLong(isRefUdt);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isReturnValue
PyObject* PyDiaSymbol_isReturnValue(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isReturnValue = self->diaSymbol->getIsReturnValue();
        return PyBool_FromLong(isReturnValue);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isSafeBuffers
PyObject* PyDiaSymbol_isSafeBuffers(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isSafeBuffers = self->diaSymbol->getIsSafeBuffers();
        return PyBool_FromLong(isSafeBuffers);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isSdl
PyObject* PyDiaSymbol_isSdl(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isSdl = self->diaSymbol->getIsSdl();
        return PyBool_FromLong(isSdl);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isSingleInheritance
PyObject* PyDiaSymbol_isSingleInheritance(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isSingleInheritance = self->diaSymbol->getIsSingleInheritance();
        return PyBool_FromLong(isSingleInheritance);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isSplitted
PyObject* PyDiaSymbol_isSplitted(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isSplitted = self->diaSymbol->getIsSplitted();
        return PyBool_FromLong(isSplitted);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isStatic
PyObject* PyDiaSymbol_isStatic(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isStatic = self->diaSymbol->getIsStatic();
        return PyBool_FromLong(isStatic);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isStripped
PyObject* PyDiaSymbol_isStripped(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isStripped = self->diaSymbol->getIsStripped();
        return PyBool_FromLong(isStripped);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isValueUdt
PyObject* PyDiaSymbol_isValueUdt(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isValueUdt = self->diaSymbol->getIsValueUdt();
        return PyBool_FromLong(isValueUdt);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isVirtualInheritance
PyObject* PyDiaSymbol_isVirtualInheritance(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isVirtualInheritance = self->diaSymbol->getIsVirtualInheritance();
        return PyBool_FromLong(isVirtualInheritance);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isWinrtPointer
PyObject* PyDiaSymbol_isWinrtPointer(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool isWinRTPointer = self->diaSymbol->getIsWinRTPointer();
        return PyBool_FromLong(isWinRTPointer);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLanguage
PyObject* PyDiaSymbol_getLanguage(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD language = self->diaSymbol->getLanguage();
        return PyLong_FromUnsignedLong(language);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_length
PyObject* PyDiaSymbol_getLength(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONGLONG length = self->diaSymbol->getLength();
        return PyLong_FromUnsignedLongLong(length);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLexicalParent
PyObject* PyDiaSymbol_getLexicalParent(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        dia::Symbol lexicalParent = self->diaSymbol->getLexicalParent();
        return PyDiaSymbol_FromSymbol(std::move(lexicalParent), self->dataSource);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLexicalParentId
PyObject* PyDiaSymbol_getLexicalParentId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD lexicalParentId = self->diaSymbol->getLexicalParentId();
        return PyLong_FromUnsignedLong(lexicalParentId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLibraryName
PyObject* PyDiaSymbol_getLibraryName(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const BstrWrapper libraryName = self->diaSymbol->getLibraryName();
        return PyObject_FromBstrWrapper(libraryName);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLiveRangeLength
PyObject* PyDiaSymbol_getLiveRangeLength(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONGLONG liveRangeLength = self->diaSymbol->getLiveRangeLength();
        return PyLong_FromUnsignedLongLong(liveRangeLength);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLiveRangeStartAddressOffset
PyObject* PyDiaSymbol_getLiveRangeStartAddressOffset(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG startAddressOffset = self->diaSymbol->getLiveRangeStartAddressOffset();
        return PyLong_FromUnsignedLong(startAddressOffset);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLiveRangeStartAddressSection
PyObject* PyDiaSymbol_getLiveRangeStartAddressSection(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD startAddressSection = self->diaSymbol->getLiveRangeStartAddressSection();
        return PyLong_FromUnsignedLong(startAddressSection);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLiveRangeStartRelativeVirtualAddress
PyObject* PyDiaSymbol_getLiveRangeStartRelativeVirtualAddress(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG startRelativeVirtualAddress = self->diaSymbol->getLiveRangeStartRelativeVirtualAddress();
        return PyLong_FromUnsignedLong(startRelativeVirtualAddress);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLocalBasePointerRegisterId
PyObject* PyDiaSymbol_getLocalBasePointerRegisterId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG localBasePointerRegisterId = self->diaSymbol->getLocalBasePointerRegisterId();
        return PyLong_FromUnsignedLong(localBasePointerRegisterId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLocationType
PyObject* PyDiaSymbol_getLocationType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const auto locationType = self->diaSymbol->getLocationType();
        return PyDiaLocationType_FromLocationType(locationType);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLowerBound
PyObject* PyDiaSymbol_getLowerBound(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        dia::Symbol lowerBound = self->diaSymbol->getLowerBound();
        return PyDiaSymbol_FromSymbol(std::move(lowerBound), self->dataSource);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLowerBoundId
PyObject* PyDiaSymbol_getLowerBoundId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD lowerBoundId = self->diaSymbol->getLowerBoundId();
        return PyLong_FromUnsignedLong(lowerBoundId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getMachineType
PyObject* PyDiaSymbol_getMachineType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD machineType = self->diaSymbol->getMachineType();
        return PyLong_FromUnsignedLong(machineType);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isManaged
PyObject* PyDiaSymbol_isManaged(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool managed = self->diaSymbol->getManaged();
        return PyBool_FromLong(managed);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getMemorySpaceKind
PyObject* PyDiaSymbol_getMemorySpaceKind(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG memorySpaceKind = self->diaSymbol->getMemorySpaceKind();
        return PyLong_FromUnsignedLong(memorySpaceKind);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getModifierValues
PyObject* PyDiaSymbol_getModifierValues(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    pydia_showDeprecationWarning(
        "The newer DXC compiler no longer produces PDBs. The HLSL elements only have valid values on PDBs produced by the older fxc.exe compiler.\n"
        "Please use `is_const`, `is_unaligned`, `is_volatile` for C/C++ types instead.");
    PYDIA_SAFE_TRY({
        const std::set<dia::StorageModifier> modifierValues = self->diaSymbol->getModifierValues();
        PyObject* pyList                                    = PyTuple_New(modifierValues.size());
        Py_ssize_t index                                    = 0;
        for (const auto& modifier : modifierValues)
        {
            PyObject* pyValue = PyDiaStorageModifier_FromStorageModifier(modifier);
            PyTuple_SetItem(pyList, index, pyValue);
            ++index;
        }
        return pyList;
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isMsil
PyObject* PyDiaSymbol_isMsil(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool msil = self->diaSymbol->getMsil();
        return PyBool_FromLong(msil);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_GetName
PyObject* PyDiaSymbol_getName(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const BstrWrapper name = self->diaSymbol->getName();
        return PyObject_FromBstrWrapper(name);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isNested
PyObject* PyDiaSymbol_isNested(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool nested = self->diaSymbol->getNested();
        return PyBool_FromLong(nested);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isNoInline
PyObject* PyDiaSymbol_isNoInline(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const bool noInline = self->diaSymbol->getNoInline();
        return PyBool_FromLong(noInline);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isNoNameExport
PyObject* PyDiaSymbol_isNoNameExport(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool noNameExport = self->diaSymbol->getNoNameExport();
        return PyBool_FromLong(noNameExport);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isNoReturn
PyObject* PyDiaSymbol_isNoReturn(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool noReturn = self->diaSymbol->getNoReturn();
        return PyBool_FromLong(noReturn);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasNoStackOrdering
PyObject* PyDiaSymbol_hasNoStackOrdering(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool noStackOrdering = self->diaSymbol->getNoStackOrdering();
        return PyBool_FromLong(noStackOrdering);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isNotReached
PyObject* PyDiaSymbol_isNotReached(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool notReached = self->diaSymbol->getNotReached();
        return PyBool_FromLong(notReached);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getNumberOfAcceleratorPointerTags
PyObject* PyDiaSymbol_getNumberOfAcceleratorPointerTags(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG numTags = self->diaSymbol->getNumberOfAcceleratorPointerTags();
        return PyLong_FromUnsignedLong(numTags);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getNumberOfColumns
PyObject* PyDiaSymbol_getNumberOfColumns(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG numColumns = self->diaSymbol->getNumberOfColumns();
        return PyLong_FromUnsignedLong(numColumns);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getNumberOfModifiers
PyObject* PyDiaSymbol_getNumberOfModifiers(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    pydia_showDeprecationWarning(
        "The newer DXC compiler no longer produces PDBs. The HLSL elements only have valid values on PDBs produced by the older fxc.exe compiler.\n"
        "Please use `is_const`, `is_unaligned`, `is_volatile` for C/C++ types instead.");
    PYDIA_SAFE_TRY({
        const ULONG numModifiers = self->diaSymbol->getNumberOfModifiers();
        return PyLong_FromUnsignedLong(numModifiers);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getNumberOfRegisterIndices
PyObject* PyDiaSymbol_getNumberOfRegisterIndices(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG numIndices = self->diaSymbol->getNumberOfRegisterIndices();
        return PyLong_FromUnsignedLong(numIndices);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getNumberOfRows
PyObject* PyDiaSymbol_getNumberOfRows(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG numRows = self->diaSymbol->getNumberOfRows();
        return PyLong_FromUnsignedLong(numRows);
    });
    Py_UNREACHABLE();
}

#if 0
// Method: PyDiaSymbol_getNumericProperties
PyObject* PyDiaSymbol_getNumericProperties(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const std::vector<ULONG> numericProperties = self->diaSymbol->getNumericProperties();
        PyObject* pyList                           = PyList_New(numericProperties.size());
        for (size_t i = 0; i < numericProperties.size(); ++i)
        {
            PyObject* pyValue = PyLong_FromUnsignedLong(numericProperties[i]);
            PyList_SetItem(pyList, i, pyValue);  // Steals reference to pyValue
        }
        return pyList;
    });
    Py_UNREACHABLE();
}
#endif

// Method: PyDiaSymbol_getObjectFileName
PyObject* PyDiaSymbol_getObjectFileName(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const BstrWrapper objectFileName = self->diaSymbol->getObjectFileName();
        return PyObject_FromBstrWrapper(objectFileName);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getObjectPointerType
PyObject* PyDiaSymbol_getObjectPointerType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        dia::Symbol objectPointerType = self->diaSymbol->getObjectPointerType();
        return PyDiaSymbol_FromSymbol(std::move(objectPointerType), self->dataSource);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getOemId
PyObject* PyDiaSymbol_getOemId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG oemId = self->diaSymbol->getOemId();
        return PyLong_FromUnsignedLong(oemId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getOemSymbolId
PyObject* PyDiaSymbol_getOemSymbolId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG oemSymbolId = self->diaSymbol->getOemSymbolId();
        return PyLong_FromUnsignedLong(oemSymbolId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getOffset
PyObject* PyDiaSymbol_getOffset(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const LONG offset = self->diaSymbol->getOffset();
        return PyLong_FromLong(offset);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getOffsetInUdt
PyObject* PyDiaSymbol_getOffsetInUdt(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG offsetInUdt = self->diaSymbol->getOffsetInUdt();
        return PyLong_FromUnsignedLong(offsetInUdt);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasOptimizedCodeDebugInfo
PyObject* PyDiaSymbol_hasOptimizedCodeDebugInfo(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool optimizedCodeDebugInfo = self->diaSymbol->getOptimizedCodeDebugInfo();
        return PyBool_FromLong(optimizedCodeDebugInfo);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getOrdinal
PyObject* PyDiaSymbol_getOrdinal(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD ordinal = self->diaSymbol->getOrdinal();
        return PyLong_FromUnsignedLong(ordinal);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasOverloadedOperator
PyObject* PyDiaSymbol_hasOverloadedOperator(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool overloadedOperator = self->diaSymbol->getOverloadedOperator();
        return PyBool_FromLong(overloadedOperator);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getPgoDynamicInstructionCount
PyObject* PyDiaSymbol_getPgoDynamicInstructionCount(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONGLONG pgoDynamicInstructionCount = self->diaSymbol->getPGODynamicInstructionCount();
        return PyLong_FromUnsignedLongLong(pgoDynamicInstructionCount);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getPgoEdgeCount
PyObject* PyDiaSymbol_getPgoEdgeCount(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD pgoEdgeCount = self->diaSymbol->getPGOEdgeCount();
        return PyLong_FromUnsignedLong(pgoEdgeCount);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getPgoEntryCount
PyObject* PyDiaSymbol_getPgoEntryCount(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD pgoEntryCount = self->diaSymbol->getPGOEntryCount();
        return PyLong_FromUnsignedLong(pgoEntryCount);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isPacked
PyObject* PyDiaSymbol_isPacked(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool packed = self->diaSymbol->getPacked();
        return PyBool_FromLong(packed);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getParamBasePointerRegisterId
PyObject* PyDiaSymbol_getParamBasePointerRegisterId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG paramBasePointerRegisterId = self->diaSymbol->getParamBasePointerRegisterId();
        return PyLong_FromUnsignedLong(paramBasePointerRegisterId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getPhaseName
PyObject* PyDiaSymbol_getPhaseName(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const BstrWrapper phaseName = self->diaSymbol->getPhaseName();
        return PyObject_FromBstrWrapper(phaseName);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getPlatform
PyObject* PyDiaSymbol_getPlatform(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG platform = self->diaSymbol->getPlatform();
        return PyLong_FromUnsignedLong(platform);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isPrivateExport
PyObject* PyDiaSymbol_isPrivateExport(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool privateExport = self->diaSymbol->getPrivateExport();
        return PyBool_FromLong(privateExport);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isPure
PyObject* PyDiaSymbol_isPure(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool pure = self->diaSymbol->getPure();
        return PyBool_FromLong(pure);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isRValueReference
PyObject* PyDiaSymbol_isRValueReference(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool rValueReference = self->diaSymbol->getRValueReference();
        return PyBool_FromLong(rValueReference);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getRank
PyObject* PyDiaSymbol_getRank(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD rank = self->diaSymbol->getRank();
        return PyLong_FromUnsignedLong(rank);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isReference
PyObject* PyDiaSymbol_isReference(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool reference = self->diaSymbol->getReference();
        return PyBool_FromLong(reference);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getRegisterId
PyObject* PyDiaSymbol_getRegisterId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD registerId = self->diaSymbol->getRegisterId();
        return PyLong_FromUnsignedLong(registerId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getRegisterType
PyObject* PyDiaSymbol_getRegisterType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG registerType = self->diaSymbol->getRegisterType();
        return PyLong_FromUnsignedLong(registerType);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getRelativeVirtualAddress
PyObject* PyDiaSymbol_getRelativeVirtualAddress(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD relativeVirtualAddress = self->diaSymbol->getRelativeVirtualAddress();
        return PyLong_FromUnsignedLong(relativeVirtualAddress);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isRestrictedType
PyObject* PyDiaSymbol_isRestrictedType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool restrictedType = self->diaSymbol->getRestrictedType();
        return PyBool_FromLong(restrictedType);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSamplerSlot
PyObject* PyDiaSymbol_getSamplerSlot(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG samplerSlot = self->diaSymbol->getSamplerSlot();
        return PyLong_FromUnsignedLong(samplerSlot);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isSealed
PyObject* PyDiaSymbol_isSealed(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool isSealed = self->diaSymbol->getSealed();
        return PyBool_FromLong(isSealed);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSignature
PyObject* PyDiaSymbol_getSignature(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD signature = self->diaSymbol->getSignature();
        return PyLong_FromUnsignedLong(signature);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSizeInUdt
PyObject* PyDiaSymbol_getSizeInUdt(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG sizeInUdt = self->diaSymbol->getSizeInUdt();
        return PyLong_FromUnsignedLong(sizeInUdt);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSlot
PyObject* PyDiaSymbol_getSlot(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG slot = self->diaSymbol->getSlot();
        return PyLong_FromUnsignedLong(slot);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSourceFileName
PyObject* PyDiaSymbol_getSourceFileName(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const BstrWrapper sourceFileName = self->diaSymbol->getSourceFileName();
        return PyObject_FromBstrWrapper(sourceFileName);
    });
    Py_UNREACHABLE();
}

#if 0
// Looks complicated to implement, leaving this for now until I find a use for this method.

// Method: PyDiaSymbol_getSrcLineOnTypeDefn
PyObject* PyDiaSymbol_getSrcLineOnTypeDefn(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const IDiaLineNumber* srcLineOnTypeDefn = self->diaSymbol->getSrcLineOnTypeDefn();
        if (!srcLineOnTypeDefn)
        {
            Py_RETURN_NONE;  // or handle accordingly
        }
        // Assuming you have a method to wrap IDiaLineNumber, use it here
        return PyDiaLineNumber_FromIDiaLineNumber(srcLineOnTypeDefn);
    });
    Py_UNREACHABLE();
}
#endif

// Method: PyDiaSymbol_getStaticSize
PyObject* PyDiaSymbol_getStaticSize(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD staticSize = self->diaSymbol->getStaticSize();
        return PyLong_FromUnsignedLong(staticSize);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasStrictGsCheck
PyObject* PyDiaSymbol_hasStrictGsCheck(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool strictGSCheck = self->diaSymbol->getStrictGSCheck();
        return PyBool_FromLong(strictGSCheck);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getStride
PyObject* PyDiaSymbol_getStride(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG stride = self->diaSymbol->getStride();
        return PyLong_FromUnsignedLong(stride);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSubType
PyObject* PyDiaSymbol_getSubType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        dia::Symbol subType = self->diaSymbol->getSubType();
        return PyDiaSymbol_FromSymbol(std::move(subType), self->dataSource);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSubTypeId
PyObject* PyDiaSymbol_getSubTypeId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG subTypeId = self->diaSymbol->getSubTypeId();
        return PyLong_FromUnsignedLong(subTypeId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_sym_index_id
PyObject* PyDiaSymbol_getSymIndexId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD symIndexId = self->diaSymbol->getSymIndexId();
        return PyLong_FromUnsignedLong(symIndexId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isScoped
PyObject* PyDiaSymbol_isScoped(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool isScoped = self->diaSymbol->getScoped();
        return PyBool_FromLong(isScoped);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSymTag
PyObject* PyDiaSymbol_getSymTag(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const enum SymTagEnum symTag = self->diaSymbol->getSymTag();
        return PyLong_FromUnsignedLong(static_cast<unsigned long>(symTag));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSymbolsFileName
PyObject* PyDiaSymbol_getSymbolsFileName(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const BstrWrapper symbolsFileName = self->diaSymbol->getSymbolsFileName();
        return PyObject_FromBstrWrapper(symbolsFileName);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getTargetOffset
PyObject* PyDiaSymbol_getTargetOffset(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG targetOffset = self->diaSymbol->getTargetOffset();
        return PyLong_FromUnsignedLong(targetOffset);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getTargetRelativeVirtualAddress
PyObject* PyDiaSymbol_getTargetRelativeVirtualAddress(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG targetRelativeVirtualAddress = self->diaSymbol->getTargetRelativeVirtualAddress();
        return PyLong_FromUnsignedLong(targetRelativeVirtualAddress);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getTargetSection
PyObject* PyDiaSymbol_getTargetSection(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD targetSection = self->diaSymbol->getTargetSection();
        return PyLong_FromUnsignedLong(targetSection);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getTargetVirtualAddress
PyObject* PyDiaSymbol_getTargetVirtualAddress(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONGLONG targetVirtualAddress = self->diaSymbol->getTargetVirtualAddress();
        return PyLong_FromUnsignedLongLong(targetVirtualAddress);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getTextureSlot
PyObject* PyDiaSymbol_getTextureSlot(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG textureSlot = self->diaSymbol->getTextureSlot();
        return PyLong_FromUnsignedLong(textureSlot);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getThisAdjust
PyObject* PyDiaSymbol_getThisAdjust(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const LONG thisAdjust = self->diaSymbol->getThisAdjust();
        return PyLong_FromLong(thisAdjust);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getThunkOrdinal
PyObject* PyDiaSymbol_getThunkOrdinal(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG thunkOrdinal = self->diaSymbol->getThunkOrdinal();
        return PyLong_FromUnsignedLong(thunkOrdinal);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getTimeStamp
PyObject* PyDiaSymbol_getTimeStamp(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG timeStamp = self->diaSymbol->getTimeStamp();
        return PyLong_FromUnsignedLong(timeStamp);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getToken
PyObject* PyDiaSymbol_getToken(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG token = self->diaSymbol->getToken();
        return PyLong_FromUnsignedLong(token);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getType
PyObject* PyDiaSymbol_getType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        dia::Symbol type = self->diaSymbol->getType();
        return PyDiaSymbol_FromSymbol(std::move(type), self->dataSource);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getTypeId
PyObject* PyDiaSymbol_getTypeId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD typeId = self->diaSymbol->getTypeId();
        return PyLong_FromUnsignedLong(typeId);
    });
    Py_UNREACHABLE();
}

PyObject* PyDiaSymbol_getUdtKind(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);

    auto safeExecution = [&]() -> PyObject* { return PyDiaUdtKind_FromUdtKind(self->diaSymbol->getUdtKind()); };

    PYDIA_SAFE_TRY({ return safeExecution(); });
    Py_UNREACHABLE();
}


#if 0  // TODO: Requires dia::Symbol function implementations!
// Method: PyDiaSymbol_getTypeIds
PyObject* PyDiaSymbol_getTypeIds(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const std::vector<ULONG> typeIds = self->diaSymbol->getTypeIds();
        PyObject* result                 = PyList_New(typeIds.size());
        for (size_t i = 0; i < typeIds.size(); ++i)
        {
            PyList_SetItem(result, i, PyLong_FromUnsignedLong(typeIds[i]));
        }
        return result;
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getTypes
PyObject* PyDiaSymbol_getTypes(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const std::vector<ULONG> types = self->diaSymbol->getTypes();
        PyObject* result               = PyList_New(types.size());
        for (size_t i = 0; i < types.size(); ++i)
        {
            PyList_SetItem(result, i, PyLong_FromUnsignedLong(types[i]));
        }
        return result;
    });
    Py_UNREACHABLE();
}
#endif

// Method: PyDiaSymbol_getUavSlot
PyObject* PyDiaSymbol_getUavSlot(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG uavSlot = self->diaSymbol->getUavSlot();
        return PyLong_FromUnsignedLong(uavSlot);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isUnaligned
PyObject* PyDiaSymbol_isUnaligned(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool unalignedType = self->diaSymbol->getUnalignedType();
        return PyBool_FromLong(unalignedType);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getUndecoratedName
PyObject* PyDiaSymbol_getUndecoratedName(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const BstrWrapper undecoratedName = self->diaSymbol->getUndecoratedName();
        return PyObject_FromBstrWrapper(undecoratedName);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getUndecoratedNameEx
PyObject* PyDiaSymbol_getUndecoratedNameEx(const PyDiaSymbol* self, DWORD options)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const BstrWrapper undecoratedNameEx = self->diaSymbol->getUndecoratedNameEx(options);
        return PyObject_FromBstrWrapper(undecoratedNameEx);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getUnmodifiedType
PyObject* PyDiaSymbol_getUnmodifiedType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        dia::Symbol unmodifiedType = self->diaSymbol->getUnmodifiedType();
        return PyDiaSymbol_FromSymbol(std::move(unmodifiedType), self->dataSource);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getUnmodifiedTypeId
PyObject* PyDiaSymbol_getUnmodifiedTypeId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONG unmodifiedTypeId = self->diaSymbol->getUnmodifiedTypeId();
        return PyLong_FromUnsignedLong(unmodifiedTypeId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isUnused
PyObject* PyDiaSymbol_isUnused(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const BstrWrapper unused = self->diaSymbol->getUnused();
        return PyObject_FromBstrWrapper(unused);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getUpperBound
PyObject* PyDiaSymbol_getUpperBound(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        dia::Symbol upperBound = self->diaSymbol->getUpperBound();
        return PyDiaSymbol_FromSymbol(std::move(upperBound), self->dataSource);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getUpperBoundId
PyObject* PyDiaSymbol_getUpperBoundId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD upperBoundId = self->diaSymbol->getUpperBoundId();
        return PyLong_FromUnsignedLong(upperBoundId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getValue
PyObject* PyDiaSymbol_getValue(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        // Get the value from diaData and convert it to an appropriate Python object
        const auto value           = self->diaSymbol->getValue();
        const auto variantPyObject = PyObject_FromVariant(value);
        return variantPyObject;
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isVirtual
PyObject* PyDiaSymbol_isVirtual(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool isVirtual = self->diaSymbol->getVirtual();
        return PyBool_FromLong(isVirtual);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualAddress
PyObject* PyDiaSymbol_getVirtualAddress(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const ULONGLONG virtualAddress = self->diaSymbol->getVirtualAddress();
        return PyLong_FromUnsignedLongLong(virtualAddress);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualBaseClass
PyObject* PyDiaSymbol_getVirtualBaseClass(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool isVirtualBaseClass = self->diaSymbol->getVirtualBaseClass();
        return PyBool_FromLong(isVirtualBaseClass);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualBaseDispIndex
PyObject* PyDiaSymbol_getVirtualBaseDispIndex(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD virtualBaseDispIndex = self->diaSymbol->getVirtualBaseDispIndex();
        return PyLong_FromUnsignedLong(virtualBaseDispIndex);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualBaseOffset
PyObject* PyDiaSymbol_getVirtualBaseOffset(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD virtualBaseOffset = self->diaSymbol->getVirtualBaseOffset();
        return PyLong_FromUnsignedLong(virtualBaseOffset);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualBasePointerOffset
PyObject* PyDiaSymbol_getVirtualBasePointerOffset(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const LONG virtualBasePointerOffset = self->diaSymbol->getVirtualBasePointerOffset();
        return PyLong_FromLong(virtualBasePointerOffset);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualBaseTableType
PyObject* PyDiaSymbol_getVirtualBaseTableType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        dia::Symbol virtualBaseTableType = self->diaSymbol->getVirtualBaseTableType();
        return PyDiaSymbol_FromSymbol(std::move(virtualBaseTableType), self->dataSource);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualTableShape
PyObject* PyDiaSymbol_getVirtualTableShape(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        dia::Symbol virtualTableShape = self->diaSymbol->getVirtualTableShape();
        return PyDiaSymbol_FromSymbol(std::move(virtualTableShape), self->dataSource);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualTableShapeId
PyObject* PyDiaSymbol_getVirtualTableShapeId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY({
        const DWORD virtualTableShapeId = self->diaSymbol->getVirtualTableShapeId();
        return PyLong_FromUnsignedLong(virtualTableShapeId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isVolatile
PyObject* PyDiaSymbol_isVolatile(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool isVolatileType = self->diaSymbol->getVolatileType();
        return PyBool_FromLong(isVolatileType);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_wasInlined
PyObject* PyDiaSymbol_wasInlined(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT_NOT_AVAILABLE_RETURN_FALSE({
        const bool wasInlined = self->diaSymbol->getWasInlined();
        return PyBool_FromLong(wasInlined);
    });
    Py_UNREACHABLE();
}
