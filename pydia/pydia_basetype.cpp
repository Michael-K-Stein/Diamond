#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_basetype.h"
#include "pydia_exceptions.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include <SymbolTypes/DiaBaseType.h>

TRIVIAL_INIT_DEINIT(BaseType);


// Python method table for dia::BaseType
static PyMethodDef PyDiaBaseType_methods[] = {
    PyDiaSymbolMethodEntry_getModifierValues,




    {"get_base_type", (PyCFunction)PyDiaSymbol_getBaseType, METH_NOARGS, "Get BasicType of the base type."},
    {"get_length", (PyCFunction)PyDiaSymbol_getLength, METH_NOARGS, "Get the length of the base type."},
    {"get_lexical_parent", (PyCFunction)PyDiaSymbol_getLexicalParent, METH_NOARGS, "Get the lexical parent of the base type."},
    {"get_lexical_parent_id", (PyCFunction)PyDiaSymbol_getLexicalParentId, METH_NOARGS, "Get the lexical parent ID of the base type."},
    {"get_sym_index_id", (PyCFunction)PyDiaSymbol_getSymIndexId, METH_NOARGS, "Get the symbol index ID of the base type."},
    {"get_sym_tag", (PyCFunction)PyDiaSymbol_getSymTag, METH_NOARGS, "Get the symbol tag of the base type."},
    {"is_unaligned", (PyCFunction)PyDiaSymbol_isUnaligned, METH_NOARGS, "Check if the data is unaligned."},
    {"is_const", (PyCFunction)PyDiaSymbol_isConst, METH_NOARGS, "Check if the data is const-qualified."},
    {"is_volatile", (PyCFunction)PyDiaSymbol_isVolatile, METH_NOARGS, "Check if the data is volatile-qualified."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define the Python DiaEnum type object

PYDIA_SYMBOL_TYPE_DEFINITION(BaseType, PyDiaBaseType_methods);
TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(BaseType);
