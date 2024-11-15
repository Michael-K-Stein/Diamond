#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_data.h"
#include "pydia_exceptions.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include "SymbolTypes/DiaData.h"

TRIVIAL_INIT_DEINIT(Data);

static PyMethodDef PyDiaData_methods[] = {
    PyDiaSymbolMethodEntry_getAccess,
    PyDiaSymbolMethodEntry_getAddressOffset,
    PyDiaSymbolMethodEntry_getAddressSection,
    PyDiaSymbolMethodEntry_isAddressTaken,
    PyDiaSymbolMethodEntry_getBitPosition,
    PyDiaSymbolMethodEntry_getClassParent,
    PyDiaSymbolMethodEntry_getClassParentId,
    PyDiaSymbolMethodEntry_isCompilerGenerated,
    PyDiaSymbolMethodEntry_isConst,
    PyDiaSymbolMethodEntry_getDataKind,
    PyDiaSymbolMethodEntry_isAggregated,
    PyDiaSymbolMethodEntry_isSplitted,
    PyDiaSymbolMethodEntry_getLength,
    PyDiaSymbolMethodEntry_getLexicalParent,
    PyDiaSymbolMethodEntry_getLexicalParentId,
    PyDiaSymbolMethodEntry_getLocationType,
    PyDiaSymbolMethodEntry_getName,
    PyDiaSymbolMethodEntry_getOffset,
    PyDiaSymbolMethodEntry_getRegisterId,
    PyDiaSymbolMethodEntry_getRelativeVirtualAddress,
    PyDiaSymbolMethodEntry_getSlot,
    PyDiaSymbolMethodEntry_getSymIndexId,
    PyDiaSymbolMethodEntry_getSymTag,
    PyDiaSymbolMethodEntry_getToken,
    PyDiaSymbolMethodEntry_getType,
    PyDiaSymbolMethodEntry_getTypeId,
    PyDiaSymbolMethodEntry_isUnaligned,
    PyDiaSymbolMethodEntry_getValue,
    PyDiaSymbolMethodEntry_getVirtualAddress,
    PyDiaSymbolMethodEntry_isVolatile,
    {NULL, NULL, 0, NULL}  // Sentinel
};

PYDIA_SYMBOL_TYPE_DEFINITION(Data, PyDiaData_methods);
TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(Data);
