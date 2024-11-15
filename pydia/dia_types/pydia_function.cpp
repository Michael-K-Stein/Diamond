#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_exceptions.h"
#include "pydia_function.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include <SymbolTypes/DiaFunction.h>

TRIVIAL_INIT_DEINIT(Function);

static PyMethodDef PyDiaFunction_methods[] = {
    PyDiaSymbolMethodEntry_getAccess,
    PyDiaSymbolMethodEntry_getAddressOffset,
    PyDiaSymbolMethodEntry_getAddressSection,
    PyDiaSymbolMethodEntry_getClassParent,
    PyDiaSymbolMethodEntry_getClassParentId,
    PyDiaSymbolMethodEntry_hasCustomCallingConvention,
    PyDiaSymbolMethodEntry_hasAlloca,
    PyDiaSymbolMethodEntry_hasEh,
    PyDiaSymbolMethodEntry_hasEha,
    PyDiaSymbolMethodEntry_hasInlineAsm,
    PyDiaSymbolMethodEntry_hasLongJump,
    PyDiaSymbolMethodEntry_hasSecurityChecks,
    PyDiaSymbolMethodEntry_hasSeh,
    PyDiaSymbolMethodEntry_hasSetJump,
    PyDiaSymbolMethodEntry_hasInlineSpecifier,
    PyDiaSymbolMethodEntry_hasNoStackOrdering,
    PyDiaSymbolMethodEntry_hasOptimizedCodeDebugInfo,
    PyDiaSymbolMethodEntry_hasInterruptReturn,
    PyDiaSymbolMethodEntry_isFarReturn,
    PyDiaSymbolMethodEntry_isConst,
    PyDiaSymbolMethodEntry_isUnaligned,
    PyDiaSymbolMethodEntry_isNaked,
    PyDiaSymbolMethodEntry_isStatic,
    PyDiaSymbolMethodEntry_isNotReached,
    PyDiaSymbolMethodEntry_isVirtual,
    PyDiaSymbolMethodEntry_isVolatile,
    PyDiaSymbolMethodEntry_isNoInline,
    PyDiaSymbolMethodEntry_isNoReturn,
    PyDiaSymbolMethodEntry_isIntro,
    PyDiaSymbolMethodEntry_getLength,
    PyDiaSymbolMethodEntry_getLexicalParent,
    PyDiaSymbolMethodEntry_getLexicalParentId,
    PyDiaSymbolMethodEntry_getLocationType,
    PyDiaSymbolMethodEntry_getName,
    PyDiaSymbolMethodEntry_getRelativeVirtualAddress,
    PyDiaSymbolMethodEntry_getSymIndexId,
    PyDiaSymbolMethodEntry_getSymTag,
    PyDiaSymbolMethodEntry_getToken,
    PyDiaSymbolMethodEntry_getType,
    PyDiaSymbolMethodEntry_getTypeId,
    PyDiaSymbolMethodEntry_getUndecoratedName,
    PyDiaSymbolMethodEntry_getUndecoratedNameEx,
    PyDiaSymbolMethodEntry_getVirtualAddress,
    PyDiaSymbolMethodEntry_getVirtualBaseOffset,
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define the Python DiaFunction type object
PYDIA_SYMBOL_TYPE_DEFINITION(Function, PyDiaFunction_methods);
TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(Function);
