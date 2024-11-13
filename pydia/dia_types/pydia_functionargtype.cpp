#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_exceptions.h"
#include "pydia_functionargtype.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include <SymbolTypes/DiaFunctionArgType.h>

TRIVIAL_INIT_DEINIT(FunctionArgType);


// Python method table for dia::FunctionArgType
static PyMethodDef PyDiaFunctionArgType_methods[] = {
    PyDiaSymbolMethodEntry_getModifierValues,



    {"get_class_parent", (PyCFunction)PyDiaSymbol_getClassParent, METH_NOARGS, "Get the class parent of the function argument."},
    {"get_class_parent_id", (PyCFunction)PyDiaSymbol_getClassParentId, METH_NOARGS, "Get the class parent ID of the function argument."},
    {"get_lexical_parent", (PyCFunction)PyDiaSymbol_getLexicalParent, METH_NOARGS, "Get the lexical parent of the function argument."},
    {"get_lexical_parent_id", (PyCFunction)PyDiaSymbol_getLexicalParentId, METH_NOARGS, "Get the lexical parent ID of the function argument."},
    {"get_sym_index_id", (PyCFunction)PyDiaSymbol_getSymIndexId, METH_NOARGS, "Get the symbol index ID of the function argument."},
    {"get_sym_tag", (PyCFunction)PyDiaSymbol_getSymTag, METH_NOARGS, "Get the symbol tag of the function argument."},
    {"get_type", (PyCFunction)PyDiaSymbol_getType, METH_NOARGS, "Get the type of the function argument."},
    {"get_type_id", (PyCFunction)PyDiaSymbol_getTypeId, METH_NOARGS, "Get the type ID of the function argument."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define the Python DiaEnum type object

PYDIA_SYMBOL_TYPE_DEFINITION(FunctionArgType, PyDiaFunctionArgType_methods);
TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(FunctionArgType);
