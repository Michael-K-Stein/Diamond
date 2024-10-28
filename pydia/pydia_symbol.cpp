#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_exceptions.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include "DiaSymbol.h"
#include "DiaUserDefinedTypeWrapper.h"

#define PYDIA_ASSERT_SYMBOL_POINTERS(__self)                                                                                                         \
    do                                                                                                                                               \
    {                                                                                                                                                \
        _ASSERT(nullptr != __self);                                                                                                                  \
        _ASSERT(nullptr != __self->diaSymbol);                                                                                                       \
    } while (0)

PyObject* PyDiaSymbol_FromSymbol(dia::Symbol&& symbol)
{
    // Create a new PyDiaData object
    PyDiaSymbol* pySymbol = PyObject_New(PyDiaSymbol, &PyDiaSymbol_Type);
    if (!pySymbol)
    {
        PyErr_SetString(PyExc_MemoryError, "Failed to create DiaSymbol object.");
        return NULL;
    }

    // Initialize the PyDiaData object with the corresponding dia::Data object
    pySymbol->diaSymbol = new (std::nothrow) dia::Symbol(symbol);

    Py_INCREF(pySymbol);
    return reinterpret_cast<PyObject*>(pySymbol);
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

Py_hash_t PyDiaSymbol_hash(PyObject* self)
{
    _ASSERT(nullptr != self);
    dia::Symbol* selfSymbol = reinterpret_cast<PyDiaSymbol*>(self)->diaSymbol;
    _ASSERT(nullptr != selfSymbol);
    return static_cast<Py_hash_t>(selfSymbol->calcHash());
}

TRIVIAL_INIT_DEINIT(Symbol);
PYDIA_SYMBOL_TYPE_DEFINITION(Symbol, 0);

// Method: PyDiaSymbol_getClassParent
PyObject* PyDiaSymbol_getClassParent(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        auto classParent = self->diaSymbol->getClassParent();
        return PyDiaSymbol_FromSymbol(std::move(classParent));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getClassParentId
PyObject* PyDiaSymbol_getClassParentId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD classParentId = self->diaSymbol->getClassParentId();
        return PyLong_FromUnsignedLong(classParentId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_access
PyObject* PyDiaSymbol_getAccess(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
        // Call getArrayIndexType and wrap the returned Symbol in a new PyDiaSymbol
        dia::Symbol arrayIndexType = self->diaSymbol->getArrayIndexType();
        return PyDiaSymbol_FromSymbol(std::move(arrayIndexType));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getArrayIndexTypeId
PyObject* PyDiaSymbol_getArrayIndexTypeId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
        // Call getBaseSymbol and wrap the returned Symbol in a new PyDiaSymbol
        dia::Symbol baseSymbol = self->diaSymbol->getBaseSymbol();
        return PyDiaSymbol_FromSymbol(std::move(baseSymbol));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getBaseSymbolId
PyObject* PyDiaSymbol_getBaseSymbolId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
        // Call getBaseType and convert to Python integer (representing the enum BasicType)
        const BasicType baseType = self->diaSymbol->getBaseType();
        // Static assert to assure that this static_cast is valid
        static_assert(sizeof(baseType) <= sizeof(unsigned long));
        return PyLong_FromUnsignedLong(static_cast<unsigned long>(baseType));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getBindId
PyObject* PyDiaSymbol_getBindId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
        // Call getCoffGroup and wrap the returned Symbol in a new PyDiaSymbol
        dia::Symbol coffGroup = self->diaSymbol->getCoffGroup();
        return PyDiaSymbol_FromSymbol(std::move(coffGroup));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isCompilerGenerated
PyObject* PyDiaSymbol_isCompilerGenerated(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
        // Call getCompilerName and convert to Python string
        const BstrWrapper compilerName = self->diaSymbol->getCompilerName();
        return BstrWrapperToPyObject(compilerName);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_const_type
PyObject* PyDiaSymbol_isConst(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
        // Call getContainer and wrap the returned Symbol in a new PyDiaSymbol
        dia::Symbol container = self->diaSymbol->getContainer();
        return PyDiaSymbol_FromSymbol(std::move(container));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getCount
PyObject* PyDiaSymbol_getCount(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
        // Call getCustomCallingConvention and convert to Python boolean
        const bool customCallingConvention = self->diaSymbol->getCustomCallingConvention();
        return PyBool_FromLong(customCallingConvention);
    });
    Py_UNREACHABLE();
}

#if 0
// The DiaLib version of this is not implemented either :(

// Method: PyDiaSymbol_data_bytes
PyObject* PyDiaSymbol_data_bytes(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
        // Call getGuid and convert to Python string (UUID)
        const GUID guid = self->diaSymbol->getGuid();
        char guidString[37];
        snprintf(guidString, sizeof(guidString), "%08lX-%04X-%04X-%04X-%012llX", guid.Data1, guid.Data2, guid.Data3,
                 (guid.Data4[0] << 8) | guid.Data4[1], *(reinterpret_cast<const ULONGLONG*>(&guid.Data4[2])));
        return PyUnicode_FromString(guidString);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasAlloca
PyObject* PyDiaSymbol_hasAlloca(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hasAssignmentOperator = self->diaSymbol->getHasAssignmentOperator();
        return PyBool_FromLong(hasAssignmentOperator);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasCastOperator
PyObject* PyDiaSymbol_hasCastOperator(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hasCastOperator = self->diaSymbol->getHasCastOperator();
        return PyBool_FromLong(hasCastOperator);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasControlFlowCheck
PyObject* PyDiaSymbol_hasControlFlowCheck(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hasControlFlowCheck = self->diaSymbol->getHasControlFlowCheck();
        return PyBool_FromLong(hasControlFlowCheck);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasDebugInfo
PyObject* PyDiaSymbol_hasDebugInfo(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hasDebugInfo = self->diaSymbol->getHasDebugInfo();
        return PyBool_FromLong(hasDebugInfo);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasEh
PyObject* PyDiaSymbol_hasEh(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hasEH = self->diaSymbol->getHasEH();
        return PyBool_FromLong(hasEH);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasEha
PyObject* PyDiaSymbol_hasEha(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hasEHa = self->diaSymbol->getHasEHa();
        return PyBool_FromLong(hasEHa);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasInlineAsm
PyObject* PyDiaSymbol_hasInlineAsm(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hasInlAsm = self->diaSymbol->getHasInlAsm();
        return PyBool_FromLong(hasInlAsm);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasLongJump
PyObject* PyDiaSymbol_hasLongJump(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hasLongJump = self->diaSymbol->getHasLongJump();
        return PyBool_FromLong(hasLongJump);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasManagedCode
PyObject* PyDiaSymbol_hasManagedCode(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hasManagedCode = self->diaSymbol->getHasManagedCode();
        return PyBool_FromLong(hasManagedCode);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasNestedTypes
PyObject* PyDiaSymbol_hasNestedTypes(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hasNestedTypes = self->diaSymbol->getHasNestedTypes();
        return PyBool_FromLong(hasNestedTypes);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasSeh
PyObject* PyDiaSymbol_hasSeh(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hasSEH = self->diaSymbol->getHasSEH();
        return PyBool_FromLong(hasSEH);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasSecurityChecks
PyObject* PyDiaSymbol_hasSecurityChecks(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hasSecurityChecks = self->diaSymbol->getHasSecurityChecks();
        return PyBool_FromLong(hasSecurityChecks);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasSetJump
PyObject* PyDiaSymbol_hasSetJump(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hasSetJump = self->diaSymbol->getHasSetJump();
        return PyBool_FromLong(hasSetJump);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasValidPgoCounts
PyObject* PyDiaSymbol_hasValidPgoCounts(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hasValidPGOCounts = self->diaSymbol->getHasValidPGOCounts();
        return PyBool_FromLong(hasValidPGOCounts);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getHfaDouble
PyObject* PyDiaSymbol_getHfaDouble(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hfaDouble = self->diaSymbol->getHfaDouble();
        return PyBool_FromLong(hfaDouble);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getHfaFloat
PyObject* PyDiaSymbol_getHfaFloat(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool hfaFloat = self->diaSymbol->getHfaFloat();
        return PyBool_FromLong(hfaFloat);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getIndirectVirtualBaseClass
PyObject* PyDiaSymbol_getIndirectVirtualBaseClass(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool indirectVirtualBaseClass = self->diaSymbol->getIndirectVirtualBaseClass();
        return PyBool_FromLong(indirectVirtualBaseClass);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getInlSpec
PyObject* PyDiaSymbol_getInlSpec(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool inlSpec = self->diaSymbol->getInlSpec();
        return PyBool_FromLong(inlSpec);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasInterruptReturn
PyObject* PyDiaSymbol_hasInterruptReturn(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool interruptReturn = self->diaSymbol->getInterruptReturn();
        return PyBool_FromLong(interruptReturn);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isIntrinsic
PyObject* PyDiaSymbol_isIntrinsic(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool intrinsic = self->diaSymbol->getIntrinsic();
        return PyBool_FromLong(intrinsic);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isIntro
PyObject* PyDiaSymbol_isIntro(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool intro = self->diaSymbol->getIntro();
        return PyBool_FromLong(intro);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_accelerator_group_shared_local
PyObject* PyDiaSymbol_is_accelerator_group_shared_local(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isAcceleratorGroupSharedLocal = self->diaSymbol->getIsAcceleratorGroupSharedLocal();
        return PyBool_FromLong(isAcceleratorGroupSharedLocal);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_accelerator_pointer_tag_live_range
PyObject* PyDiaSymbol_is_accelerator_pointer_tag_live_range(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isAcceleratorPointerTagLiveRange = self->diaSymbol->getIsAcceleratorPointerTagLiveRange();
        return PyBool_FromLong(isAcceleratorPointerTagLiveRange);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_accelerator_stub_function
PyObject* PyDiaSymbol_is_accelerator_stub_function(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isAcceleratorStubFunction = self->diaSymbol->getIsAcceleratorStubFunction();
        return PyBool_FromLong(isAcceleratorStubFunction);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_aggregated
PyObject* PyDiaSymbol_is_aggregated(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isAggregated = self->diaSymbol->getIsAggregated();
        return PyBool_FromLong(isAggregated);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_ctypes
PyObject* PyDiaSymbol_is_ctypes(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isCTypes = self->diaSymbol->getIsCTypes();
        return PyBool_FromLong(isCTypes);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_cvtcil
PyObject* PyDiaSymbol_is_cvtcil(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isCVTCIL = self->diaSymbol->getIsCVTCIL();
        return PyBool_FromLong(isCVTCIL);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_constructor_virtual_base
PyObject* PyDiaSymbol_is_constructor_virtual_base(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isConstructorVirtualBase = self->diaSymbol->getIsConstructorVirtualBase();
        return PyBool_FromLong(isConstructorVirtualBase);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_cxx_return_udt
PyObject* PyDiaSymbol_is_cxx_return_udt(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isCxxReturnUdt = self->diaSymbol->getIsCxxReturnUdt();
        return PyBool_FromLong(isCxxReturnUdt);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_data_aligned
PyObject* PyDiaSymbol_is_data_aligned(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isDataAligned = self->diaSymbol->getIsDataAligned();
        return PyBool_FromLong(isDataAligned);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_hlsl_data
PyObject* PyDiaSymbol_is_hlsl_data(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isHLSLData = self->diaSymbol->getIsHLSLData();
        return PyBool_FromLong(isHLSLData);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_hotpatchable
PyObject* PyDiaSymbol_is_hotpatchable(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isHotpatchable = self->diaSymbol->getIsHotpatchable();
        return PyBool_FromLong(isHotpatchable);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_interface_udt
PyObject* PyDiaSymbol_is_interface_udt(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isInterfaceUdt = self->diaSymbol->getIsInterfaceUdt();
        return PyBool_FromLong(isInterfaceUdt);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_ltcg
PyObject* PyDiaSymbol_is_ltcg(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isLTCG = self->diaSymbol->getIsLTCG();
        return PyBool_FromLong(isLTCG);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_location_control_flow_dependent
PyObject* PyDiaSymbol_is_location_control_flow_dependent(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isLocationControlFlowDependent = self->diaSymbol->getIsLocationControlFlowDependent();
        return PyBool_FromLong(isLocationControlFlowDependent);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_msil_netmodule
PyObject* PyDiaSymbol_is_msil_netmodule(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isMSILNetmodule = self->diaSymbol->getIsMSILNetmodule();
        return PyBool_FromLong(isMSILNetmodule);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_matrix_row_major
PyObject* PyDiaSymbol_is_matrix_row_major(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isMatrixRowMajor = self->diaSymbol->getIsMatrixRowMajor();
        return PyBool_FromLong(isMatrixRowMajor);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_multiple_inheritance
PyObject* PyDiaSymbol_is_multiple_inheritance(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isMultipleInheritance = self->diaSymbol->getIsMultipleInheritance();
        return PyBool_FromLong(isMultipleInheritance);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_naked
PyObject* PyDiaSymbol_is_naked(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isNaked = self->diaSymbol->getIsNaked();
        return PyBool_FromLong(isNaked);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_optimized_away
PyObject* PyDiaSymbol_is_optimized_away(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isOptimizedAway = self->diaSymbol->getIsOptimizedAway();
        return PyBool_FromLong(isOptimizedAway);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_optimized_for_speed
PyObject* PyDiaSymbol_is_optimized_for_speed(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isOptimizedForSpeed = self->diaSymbol->getIsOptimizedForSpeed();
        return PyBool_FromLong(isOptimizedForSpeed);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_pgo
PyObject* PyDiaSymbol_is_pgo(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isPGO = self->diaSymbol->getIsPGO();
        return PyBool_FromLong(isPGO);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_pointer_based_on_symbol_value
PyObject* PyDiaSymbol_is_pointer_based_on_symbol_value(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isPointerBasedOnSymbolValue = self->diaSymbol->getIsPointerBasedOnSymbolValue();
        return PyBool_FromLong(isPointerBasedOnSymbolValue);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_pointer_to_data_member
PyObject* PyDiaSymbol_is_pointer_to_data_member(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isPointerToDataMember = self->diaSymbol->getIsPointerToDataMember();
        return PyBool_FromLong(isPointerToDataMember);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_pointer_to_member_function
PyObject* PyDiaSymbol_is_pointer_to_member_function(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isPointerToMemberFunction = self->diaSymbol->getIsPointerToMemberFunction();
        return PyBool_FromLong(isPointerToMemberFunction);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_ref_udt
PyObject* PyDiaSymbol_is_ref_udt(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isRefUdt = self->diaSymbol->getIsRefUdt();
        return PyBool_FromLong(isRefUdt);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_return_value
PyObject* PyDiaSymbol_is_return_value(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isReturnValue = self->diaSymbol->getIsReturnValue();
        return PyBool_FromLong(isReturnValue);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_safe_buffers
PyObject* PyDiaSymbol_is_safe_buffers(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isSafeBuffers = self->diaSymbol->getIsSafeBuffers();
        return PyBool_FromLong(isSafeBuffers);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_sdl
PyObject* PyDiaSymbol_is_sdl(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isSdl = self->diaSymbol->getIsSdl();
        return PyBool_FromLong(isSdl);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_single_inheritance
PyObject* PyDiaSymbol_is_single_inheritance(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isSingleInheritance = self->diaSymbol->getIsSingleInheritance();
        return PyBool_FromLong(isSingleInheritance);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isSplitted
PyObject* PyDiaSymbol_isSplitted(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isSplitted = self->diaSymbol->getIsSplitted();
        return PyBool_FromLong(isSplitted);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_static
PyObject* PyDiaSymbol_is_static(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isStatic = self->diaSymbol->getIsStatic();
        return PyBool_FromLong(isStatic);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_stripped
PyObject* PyDiaSymbol_is_stripped(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isStripped = self->diaSymbol->getIsStripped();
        return PyBool_FromLong(isStripped);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_value_udt
PyObject* PyDiaSymbol_is_value_udt(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isValueUdt = self->diaSymbol->getIsValueUdt();
        return PyBool_FromLong(isValueUdt);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_virtual_inheritance
PyObject* PyDiaSymbol_is_virtual_inheritance(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isVirtualInheritance = self->diaSymbol->getIsVirtualInheritance();
        return PyBool_FromLong(isVirtualInheritance);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_is_winrt_pointer
PyObject* PyDiaSymbol_is_winrt_pointer(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isWinRTPointer = self->diaSymbol->getIsWinRTPointer();
        return PyBool_FromLong(isWinRTPointer);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLanguage
PyObject* PyDiaSymbol_getLanguage(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD language = self->diaSymbol->getLanguage();
        return PyLong_FromUnsignedLong(language);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_length
PyObject* PyDiaSymbol_getLength(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONGLONG length = self->diaSymbol->getLength();
        return PyLong_FromUnsignedLongLong(length);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLexicalParent
PyObject* PyDiaSymbol_getLexicalParent(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        dia::Symbol lexicalParent = self->diaSymbol->getLexicalParent();
        return PyDiaSymbol_FromSymbol(std::move(lexicalParent));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLexicalParentId
PyObject* PyDiaSymbol_getLexicalParentId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD lexicalParentId = self->diaSymbol->getLexicalParentId();
        return PyLong_FromUnsignedLong(lexicalParentId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLibraryName
PyObject* PyDiaSymbol_getLibraryName(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const BstrWrapper libraryName = self->diaSymbol->getLibraryName();
        return BstrWrapperToPyObject(libraryName);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLiveRangeLength
PyObject* PyDiaSymbol_getLiveRangeLength(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONGLONG liveRangeLength = self->diaSymbol->getLiveRangeLength();
        return PyLong_FromUnsignedLongLong(liveRangeLength);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLiveRangeStartAddressOffset
PyObject* PyDiaSymbol_getLiveRangeStartAddressOffset(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG startAddressOffset = self->diaSymbol->getLiveRangeStartAddressOffset();
        return PyLong_FromUnsignedLong(startAddressOffset);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLiveRangeStartAddressSection
PyObject* PyDiaSymbol_getLiveRangeStartAddressSection(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD startAddressSection = self->diaSymbol->getLiveRangeStartAddressSection();
        return PyLong_FromUnsignedLong(startAddressSection);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLiveRangeStartRelativeVirtualAddress
PyObject* PyDiaSymbol_getLiveRangeStartRelativeVirtualAddress(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG startRelativeVirtualAddress = self->diaSymbol->getLiveRangeStartRelativeVirtualAddress();
        return PyLong_FromUnsignedLong(startRelativeVirtualAddress);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLocalBasePointerRegisterId
PyObject* PyDiaSymbol_getLocalBasePointerRegisterId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG localBasePointerRegisterId = self->diaSymbol->getLocalBasePointerRegisterId();
        return PyLong_FromUnsignedLong(localBasePointerRegisterId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLocationType
PyObject* PyDiaSymbol_getLocationType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const LocationType locationType = self->diaSymbol->getLocationType();
        return PyLong_FromUnsignedLong(static_cast<unsigned long>(locationType));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLowerBound
PyObject* PyDiaSymbol_getLowerBound(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        dia::Symbol lowerBound = self->diaSymbol->getLowerBound();
        return PyDiaSymbol_FromSymbol(std::move(lowerBound));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getLowerBoundId
PyObject* PyDiaSymbol_getLowerBoundId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD lowerBoundId = self->diaSymbol->getLowerBoundId();
        return PyLong_FromUnsignedLong(lowerBoundId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getMachineType
PyObject* PyDiaSymbol_getMachineType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD machineType = self->diaSymbol->getMachineType();
        return PyLong_FromUnsignedLong(machineType);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isManaged
PyObject* PyDiaSymbol_isManaged(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool managed = self->diaSymbol->getManaged();
        return PyBool_FromLong(managed);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getMemorySpaceKind
PyObject* PyDiaSymbol_getMemorySpaceKind(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG memorySpaceKind = self->diaSymbol->getMemorySpaceKind();
        return PyLong_FromUnsignedLong(memorySpaceKind);
    });
    Py_UNREACHABLE();
}

#if 0  // TODO: Implement dia::Symbol::getModifierValues()
// Method: PyDiaSymbol_getModifierValues 
PyObject* PyDiaSymbol_getModifierValues(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const std::vector<ULONG> modifierValues = self->diaSymbol->getModifierValues();
        PyObject* pyList                        = PyList_New(modifierValues.size());
        for (size_t i = 0; i < modifierValues.size(); ++i)
        {
            PyObject* pyValue = PyLong_FromUnsignedLong(modifierValues[i]);
            PyList_SetItem(pyList, i, pyValue);  // Steals reference to pyValue
        }
        return pyList;
    });
    Py_UNREACHABLE();
}
#endif

// Method: PyDiaSymbol_isMsil
PyObject* PyDiaSymbol_isMsil(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool msil = self->diaSymbol->getMsil();
        return PyBool_FromLong(msil);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_GetName
PyObject* PyDiaSymbol_getName(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const BstrWrapper name = self->diaSymbol->getName();
        return BstrWrapperToPyObject(name);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isNested
PyObject* PyDiaSymbol_isNested(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool nested = self->diaSymbol->getNested();
        return PyBool_FromLong(nested);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isNoInline
PyObject* PyDiaSymbol_isNoInline(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool noInline = self->diaSymbol->getNoInline();
        return PyBool_FromLong(noInline);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isNoNameExport
PyObject* PyDiaSymbol_isNoNameExport(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool noNameExport = self->diaSymbol->getNoNameExport();
        return PyBool_FromLong(noNameExport);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isNoReturn
PyObject* PyDiaSymbol_isNoReturn(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool noReturn = self->diaSymbol->getNoReturn();
        return PyBool_FromLong(noReturn);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasNoStackOrdering
PyObject* PyDiaSymbol_hasNoStackOrdering(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool noStackOrdering = self->diaSymbol->getNoStackOrdering();
        return PyBool_FromLong(noStackOrdering);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isNotReached
PyObject* PyDiaSymbol_isNotReached(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool notReached = self->diaSymbol->getNotReached();
        return PyBool_FromLong(notReached);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_number_of_accelerator_pointer_tags
PyObject* PyDiaSymbol_number_of_accelerator_pointer_tags(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG numTags = self->diaSymbol->getNumberOfAcceleratorPointerTags();
        return PyLong_FromUnsignedLong(numTags);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_number_of_columns
PyObject* PyDiaSymbol_number_of_columns(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG numColumns = self->diaSymbol->getNumberOfColumns();
        return PyLong_FromUnsignedLong(numColumns);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getNumberOfModifiers
PyObject* PyDiaSymbol_getNumberOfModifiers(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG numModifiers = self->diaSymbol->getNumberOfModifiers();
        return PyLong_FromUnsignedLong(numModifiers);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getNumberOfRegisterIndices
PyObject* PyDiaSymbol_getNumberOfRegisterIndices(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG numIndices = self->diaSymbol->getNumberOfRegisterIndices();
        return PyLong_FromUnsignedLong(numIndices);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getNumberOfRows
PyObject* PyDiaSymbol_getNumberOfRows(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
        const BstrWrapper objectFileName = self->diaSymbol->getObjectFileName();
        return BstrWrapperToPyObject(objectFileName);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getObjectPointerType
PyObject* PyDiaSymbol_getObjectPointerType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        dia::Symbol objectPointerType = self->diaSymbol->getObjectPointerType();
        return PyDiaSymbol_FromSymbol(std::move(objectPointerType));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getOemId
PyObject* PyDiaSymbol_getOemId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG oemId = self->diaSymbol->getOemId();
        return PyLong_FromUnsignedLong(oemId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getOemSymbolId
PyObject* PyDiaSymbol_getOemSymbolId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG oemSymbolId = self->diaSymbol->getOemSymbolId();
        return PyLong_FromUnsignedLong(oemSymbolId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getOffset
PyObject* PyDiaSymbol_getOffset(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const LONG offset = self->diaSymbol->getOffset();
        return PyLong_FromLong(offset);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getOffsetInUdt
PyObject* PyDiaSymbol_getOffsetInUdt(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG offsetInUdt = self->diaSymbol->getOffsetInUdt();
        return PyLong_FromUnsignedLong(offsetInUdt);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasOptimizedCodeDebugInfo
PyObject* PyDiaSymbol_hasOptimizedCodeDebugInfo(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool optimizedCodeDebugInfo = self->diaSymbol->getOptimizedCodeDebugInfo();
        return PyBool_FromLong(optimizedCodeDebugInfo);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getOrdinal
PyObject* PyDiaSymbol_getOrdinal(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD ordinal = self->diaSymbol->getOrdinal();
        return PyLong_FromUnsignedLong(ordinal);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasOverloadedOperator
PyObject* PyDiaSymbol_hasOverloadedOperator(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool overloadedOperator = self->diaSymbol->getOverloadedOperator();
        return PyBool_FromLong(overloadedOperator);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getPgoDynamicInstructionCount
PyObject* PyDiaSymbol_getPgoDynamicInstructionCount(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONGLONG pgoDynamicInstructionCount = self->diaSymbol->getPGODynamicInstructionCount();
        return PyLong_FromUnsignedLongLong(pgoDynamicInstructionCount);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_pgo_edge_count
PyObject* PyDiaSymbol_pgo_edge_count(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD pgoEdgeCount = self->diaSymbol->getPGOEdgeCount();
        return PyLong_FromUnsignedLong(pgoEdgeCount);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_pgo_entry_count
PyObject* PyDiaSymbol_pgo_entry_count(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD pgoEntryCount = self->diaSymbol->getPGOEntryCount();
        return PyLong_FromUnsignedLong(pgoEntryCount);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isPacked
PyObject* PyDiaSymbol_isPacked(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool packed = self->diaSymbol->getPacked();
        return PyBool_FromLong(packed);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_param_base_pointer_register_id
PyObject* PyDiaSymbol_param_base_pointer_register_id(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG paramBasePointerRegisterId = self->diaSymbol->getParamBasePointerRegisterId();
        return PyLong_FromUnsignedLong(paramBasePointerRegisterId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_phase_name
PyObject* PyDiaSymbol_phase_name(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const BstrWrapper phaseName = self->diaSymbol->getPhaseName();
        return BstrWrapperToPyObject(phaseName);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_platform
PyObject* PyDiaSymbol_platform(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG platform = self->diaSymbol->getPlatform();
        return PyLong_FromUnsignedLong(platform);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_private_export
PyObject* PyDiaSymbol_private_export(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool privateExport = self->diaSymbol->getPrivateExport();
        return PyBool_FromLong(privateExport);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_pure
PyObject* PyDiaSymbol_pure(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool pure = self->diaSymbol->getPure();
        return PyBool_FromLong(pure);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_r_value_reference
PyObject* PyDiaSymbol_r_value_reference(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool rValueReference = self->diaSymbol->getRValueReference();
        return PyBool_FromLong(rValueReference);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_rank
PyObject* PyDiaSymbol_rank(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD rank = self->diaSymbol->getRank();
        return PyLong_FromUnsignedLong(rank);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_reference
PyObject* PyDiaSymbol_reference(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool reference = self->diaSymbol->getReference();
        return PyBool_FromLong(reference);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_register_id
PyObject* PyDiaSymbol_register_id(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD registerId = self->diaSymbol->getRegisterId();
        return PyLong_FromUnsignedLong(registerId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getRegisterType
PyObject* PyDiaSymbol_getRegisterType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG registerType = self->diaSymbol->getRegisterType();
        return PyLong_FromUnsignedLong(registerType);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getRelativeVirtualAddress
PyObject* PyDiaSymbol_getRelativeVirtualAddress(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD relativeVirtualAddress = self->diaSymbol->getRelativeVirtualAddress();
        return PyLong_FromUnsignedLong(relativeVirtualAddress);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isRestrictedType
PyObject* PyDiaSymbol_isRestrictedType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool restrictedType = self->diaSymbol->getRestrictedType();
        return PyBool_FromLong(restrictedType);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSamplerSlot
PyObject* PyDiaSymbol_getSamplerSlot(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG samplerSlot = self->diaSymbol->getSamplerSlot();
        return PyLong_FromUnsignedLong(samplerSlot);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isSealed
PyObject* PyDiaSymbol_isSealed(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool sealed = self->diaSymbol->getSealed();
        return PyBool_FromLong(sealed);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSignature
PyObject* PyDiaSymbol_getSignature(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD signature = self->diaSymbol->getSignature();
        return PyLong_FromUnsignedLong(signature);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSizeInUdt
PyObject* PyDiaSymbol_getSizeInUdt(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG sizeInUdt = self->diaSymbol->getSizeInUdt();
        return PyLong_FromUnsignedLong(sizeInUdt);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSlot
PyObject* PyDiaSymbol_getSlot(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG slot = self->diaSymbol->getSlot();
        return PyLong_FromUnsignedLong(slot);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSourceFileName
PyObject* PyDiaSymbol_getSourceFileName(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const BstrWrapper sourceFileName = self->diaSymbol->getSourceFileName();
        return BstrWrapperToPyObject(sourceFileName);
    });
    Py_UNREACHABLE();
}

#if 0
// Looks complicated to implement, leaving this for now until I find a use for this method.

// Method: PyDiaSymbol_src_line_on_type_defn
PyObject* PyDiaSymbol_src_line_on_type_defn(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD staticSize = self->diaSymbol->getStaticSize();
        return PyLong_FromUnsignedLong(staticSize);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_hasStrictGsCheck
PyObject* PyDiaSymbol_hasStrictGsCheck(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool strictGSCheck = self->diaSymbol->getStrictGSCheck();
        return PyBool_FromLong(strictGSCheck);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getStride
PyObject* PyDiaSymbol_getStride(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG stride = self->diaSymbol->getStride();
        return PyLong_FromUnsignedLong(stride);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSubType
PyObject* PyDiaSymbol_getSubType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        dia::Symbol subType = self->diaSymbol->getSubType();
        return PyDiaSymbol_FromSymbol(std::move(subType));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSubTypeId
PyObject* PyDiaSymbol_getSubTypeId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG subTypeId = self->diaSymbol->getSubTypeId();
        return PyLong_FromUnsignedLong(subTypeId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_sym_index_id
PyObject* PyDiaSymbol_getSymIndexId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD symIndexId = self->diaSymbol->getSymIndexId();
        return PyLong_FromUnsignedLong(symIndexId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isScoped
PyObject* PyDiaSymbol_isScoped(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isScoped = self->diaSymbol->getScoped();
        return PyBool_FromLong(isScoped);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSymTag
PyObject* PyDiaSymbol_getSymTag(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const enum SymTagEnum symTag = self->diaSymbol->getSymTag();
        return PyLong_FromUnsignedLong(static_cast<unsigned long>(symTag));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getSymbolsFileName
PyObject* PyDiaSymbol_getSymbolsFileName(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const BstrWrapper symbolsFileName = self->diaSymbol->getSymbolsFileName();
        return BstrWrapperToPyObject(symbolsFileName);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getTargetOffset
PyObject* PyDiaSymbol_getTargetOffset(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG targetOffset = self->diaSymbol->getTargetOffset();
        return PyLong_FromUnsignedLong(targetOffset);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_target_relative_virtual_address
PyObject* PyDiaSymbol_target_relative_virtual_address(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG targetRelativeVirtualAddress = self->diaSymbol->getTargetRelativeVirtualAddress();
        return PyLong_FromUnsignedLong(targetRelativeVirtualAddress);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_target_section
PyObject* PyDiaSymbol_target_section(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD targetSection = self->diaSymbol->getTargetSection();
        return PyLong_FromUnsignedLong(targetSection);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_target_virtual_address
PyObject* PyDiaSymbol_target_virtual_address(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONGLONG targetVirtualAddress = self->diaSymbol->getTargetVirtualAddress();
        return PyLong_FromUnsignedLongLong(targetVirtualAddress);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_texture_slot
PyObject* PyDiaSymbol_texture_slot(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG textureSlot = self->diaSymbol->getTextureSlot();
        return PyLong_FromUnsignedLong(textureSlot);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_this_adjust
PyObject* PyDiaSymbol_this_adjust(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const LONG thisAdjust = self->diaSymbol->getThisAdjust();
        return PyLong_FromLong(thisAdjust);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getThunkOrdinal
PyObject* PyDiaSymbol_getThunkOrdinal(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG thunkOrdinal = self->diaSymbol->getThunkOrdinal();
        return PyLong_FromUnsignedLong(thunkOrdinal);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getTimeStamp
PyObject* PyDiaSymbol_getTimeStamp(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG timeStamp = self->diaSymbol->getTimeStamp();
        return PyLong_FromUnsignedLong(timeStamp);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getToken
PyObject* PyDiaSymbol_getToken(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG token = self->diaSymbol->getToken();
        return PyLong_FromUnsignedLong(token);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getType
PyObject* PyDiaSymbol_getType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        dia::Symbol type = self->diaSymbol->getType();
        return PyDiaSymbol_FromSymbol(std::move(type));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getTypeId
PyObject* PyDiaSymbol_getTypeId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD typeId = self->diaSymbol->getTypeId();
        return PyLong_FromUnsignedLong(typeId);
    });
    Py_UNREACHABLE();
}

PyObject* PyDiaSymbol_getUdtKind(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);

    auto safeExecution = [&]() -> PyObject*
    {
        const enum UdtKind udtKind = self->diaSymbol->getUdtKind();

        // Convert the enum value to a string key directly using predefined names
        static const char* udtKindKeys[] = {"Struct", "Class", "Union", "Interface", "TaggedUnion"};

        // Ensure the enum value is within range and return the corresponding dictionary entry
        if (0 < udtKind || udtKind >= sizeof(udtKindKeys) / sizeof(udtKindKeys[0]))
        {
            // Out of range: set ValueError if enum value is unknown
            PyErr_SetString(PyExc_ValueError, "Unknown UdtKind value.");
            return NULL;
        }

        PyObject* udtKindObj = PyDict_GetItemString(getDiaUdtKindEnumWrappings(), udtKindKeys[udtKind]);
        Py_XINCREF(udtKindObj);  // Increase reference count to return a new reference
        return udtKindObj;
    };

    PYDIA_SAFE_TRY_EXCEPT({ return safeExecution(); });
    Py_UNREACHABLE();
}


#if 0  // TODO: Requires dia::Symbol function implementations!
// Method: PyDiaSymbol_getTypeIds
PyObject* PyDiaSymbol_getTypeIds(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
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
    PYDIA_SAFE_TRY_EXCEPT({
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

// Method: PyDiaSymbol_uav_slot
PyObject* PyDiaSymbol_uav_slot(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG uavSlot = self->diaSymbol->getUavSlot();
        return PyLong_FromUnsignedLong(uavSlot);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_udt_kind
PyObject* PyDiaSymbol_udt_kind(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const UdtKind udtKind = self->diaSymbol->getUdtKind();
        return PyLong_FromUnsignedLong(static_cast<unsigned long>(udtKind));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isUnaligned
PyObject* PyDiaSymbol_isUnaligned(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool unalignedType = self->diaSymbol->getUnalignedType();
        return PyBool_FromLong(unalignedType);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_undecorated_name
PyObject* PyDiaSymbol_undecorated_name(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const BstrWrapper undecoratedName = self->diaSymbol->getUndecoratedName();
        return BstrWrapperToPyObject(undecoratedName);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_undecorated_name_ex
PyObject* PyDiaSymbol_undecorated_name_ex(const PyDiaSymbol* self, DWORD options)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const BstrWrapper undecoratedNameEx = self->diaSymbol->getUndecoratedNameEx(options);
        return BstrWrapperToPyObject(undecoratedNameEx);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_unmodified_type
PyObject* PyDiaSymbol_unmodified_type(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        dia::Symbol unmodifiedType = self->diaSymbol->getUnmodifiedType();
        return PyDiaSymbol_FromSymbol(std::move(unmodifiedType));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_unmodified_type_id
PyObject* PyDiaSymbol_unmodified_type_id(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONG unmodifiedTypeId = self->diaSymbol->getUnmodifiedTypeId();
        return PyLong_FromUnsignedLong(unmodifiedTypeId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_unused
PyObject* PyDiaSymbol_unused(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const BstrWrapper unused = self->diaSymbol->getUnused();
        return BstrWrapperToPyObject(unused);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_upper_bound
PyObject* PyDiaSymbol_upper_bound(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        dia::Symbol upperBound = self->diaSymbol->getUpperBound();
        return PyDiaSymbol_FromSymbol(std::move(upperBound));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_upper_bound_id
PyObject* PyDiaSymbol_upper_bound_id(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD upperBoundId = self->diaSymbol->getUpperBoundId();
        return PyLong_FromUnsignedLong(upperBoundId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getValue
PyObject* PyDiaSymbol_getValue(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        // Get the value from diaData and convert it to an appropriate Python object
        const auto value           = self->diaSymbol->getValue();
        const auto variantPyObject = VariantToPyObject(value);
        return variantPyObject;
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isVirtual
PyObject* PyDiaSymbol_isVirtual(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isVirtual = self->diaSymbol->getVirtual();
        return PyBool_FromLong(isVirtual);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualAddress
PyObject* PyDiaSymbol_getVirtualAddress(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const ULONGLONG virtualAddress = self->diaSymbol->getVirtualAddress();
        return PyLong_FromUnsignedLongLong(virtualAddress);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualBaseClass
PyObject* PyDiaSymbol_getVirtualBaseClass(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isVirtualBaseClass = self->diaSymbol->getVirtualBaseClass();
        return PyBool_FromLong(isVirtualBaseClass);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualBaseDispIndex
PyObject* PyDiaSymbol_getVirtualBaseDispIndex(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD virtualBaseDispIndex = self->diaSymbol->getVirtualBaseDispIndex();
        return PyLong_FromUnsignedLong(virtualBaseDispIndex);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualBaseOffset
PyObject* PyDiaSymbol_getVirtualBaseOffset(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD virtualBaseOffset = self->diaSymbol->getVirtualBaseOffset();
        return PyLong_FromUnsignedLong(virtualBaseOffset);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualBasePointerOffset
PyObject* PyDiaSymbol_getVirtualBasePointerOffset(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const LONG virtualBasePointerOffset = self->diaSymbol->getVirtualBasePointerOffset();
        return PyLong_FromLong(virtualBasePointerOffset);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualBaseTableType
PyObject* PyDiaSymbol_getVirtualBaseTableType(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        dia::Symbol virtualBaseTableType = self->diaSymbol->getVirtualBaseTableType();
        return PyDiaSymbol_FromSymbol(std::move(virtualBaseTableType));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualTableShape
PyObject* PyDiaSymbol_getVirtualTableShape(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        dia::Symbol virtualTableShape = self->diaSymbol->getVirtualTableShape();
        return PyDiaSymbol_FromSymbol(std::move(virtualTableShape));
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_getVirtualTableShapeId
PyObject* PyDiaSymbol_getVirtualTableShapeId(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const DWORD virtualTableShapeId = self->diaSymbol->getVirtualTableShapeId();
        return PyLong_FromUnsignedLong(virtualTableShapeId);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_isVolatile
PyObject* PyDiaSymbol_isVolatile(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool isVolatileType = self->diaSymbol->getVolatileType();
        return PyBool_FromLong(isVolatileType);
    });
    Py_UNREACHABLE();
}

// Method: PyDiaSymbol_wasInlined
PyObject* PyDiaSymbol_wasInlined(const PyDiaSymbol* self)
{
    PYDIA_ASSERT_SYMBOL_POINTERS(self);
    PYDIA_SAFE_TRY_EXCEPT({
        const bool wasInlined = self->diaSymbol->getWasInlined();
        return PyBool_FromLong(wasInlined);
    });
    Py_UNREACHABLE();
}
