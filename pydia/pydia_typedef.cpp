#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_exceptions.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_typedef.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include <SymbolTypes/DiaTypedef.h>

TRIVIAL_INIT_DEINIT(Typedef);

static PyMethodDef PyDiaTypedef_methods[] = {
    PyDiaSymbolMethodEntry_getBaseType,
    PyDiaSymbolMethodEntry_getClassParent,
    PyDiaSymbolMethodEntry_getClassParentId,
    PyDiaSymbolMethodEntry_hasConstructor,
    PyDiaSymbolMethodEntry_isConst,
    PyDiaSymbolMethodEntry_hasAssignmentOperator,
    PyDiaSymbolMethodEntry_hasCastOperator,
    PyDiaSymbolMethodEntry_hasNestedTypes,
    PyDiaSymbolMethodEntry_getLength,
    PyDiaSymbolMethodEntry_getLexicalParent,
    PyDiaSymbolMethodEntry_getLexicalParentId,
    PyDiaSymbolMethodEntry_getName,
    PyDiaSymbolMethodEntry_isNested,
    PyDiaSymbolMethodEntry_hasOverloadedOperator,
    PyDiaSymbolMethodEntry_isPacked,
    PyDiaSymbolMethodEntry_isReference,
    PyDiaSymbolMethodEntry_isScoped,
    PyDiaSymbolMethodEntry_getSymIndexId,
    PyDiaSymbolMethodEntry_getSymTag,
    PyDiaSymbolMethodEntry_getType,
    PyDiaSymbolMethodEntry_getTypeId,
    PyDiaSymbolMethodEntry_getUdtKind,
    PyDiaSymbolMethodEntry_isUnaligned,
    PyDiaSymbolMethodEntry_getVirtualTableShape,
    PyDiaSymbolMethodEntry_getVirtualTableShapeId,
    PyDiaSymbolMethodEntry_isVolatile,
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define the Python DiaEnum type object
PYDIA_SYMBOL_TYPE_DEFINITION(Typedef, PyDiaTypedef_methods);
TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(Typedef);
