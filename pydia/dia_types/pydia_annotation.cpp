#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_annotation.h"
#include "pydia_exceptions.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include <SymbolTypes/DiaAnnotation.h>

TRIVIAL_INIT_DEINIT(Annotation);

static PyMethodDef PyDiaAnnotation_methods[] = {
    PyDiaSymbolMethodEntry_getAddressOffset,
    PyDiaSymbolMethodEntry_getAddressSection,
    PyDiaSymbolMethodEntry_getDataKind,
    PyDiaSymbolMethodEntry_getRelativeVirtualAddress,
    PyDiaSymbolMethodEntry_getSymIndexId,
    PyDiaSymbolMethodEntry_getSymTag,
    PyDiaSymbolMethodEntry_getValue,
    PyDiaSymbolMethodEntry_getVirtualAddress,
    {NULL, NULL, 0, NULL},  // Sentinel
};

PYDIA_SYMBOL_TYPE_DEFINITION(Annotation, PyDiaAnnotation_methods);
TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(Annotation);
