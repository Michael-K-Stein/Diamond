#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_exceptions.h"
#include "pydia_helper_routines.h"
#include "pydia_pointer.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include <SymbolTypes/DiaPointer.h>

TRIVIAL_INIT_DEINIT(Pointer);


// Python method table for dia::Pointer
static PyMethodDef PyDiaPointer_methods[] = {
    PyDiaSymbolMethodEntry_getModifierValues,


    {"is_const", (PyCFunction)PyDiaSymbol_isConst, METH_NOARGS, "Check if the data is const-qualified."},
    {"is_reference", (PyCFunction)PyDiaSymbol_isReference, METH_NOARGS, "Check if the pointer is a reference."},
    {"is_rvalue_reference", (PyCFunction)PyDiaSymbol_isRValueReference, METH_NOARGS, "Check if the pointer is an r-value reference."},
    {"is_unaligned", (PyCFunction)PyDiaSymbol_isUnaligned, METH_NOARGS, "Check if the data is unaligned."},
    {"is_volatile", (PyCFunction)PyDiaSymbol_isVolatile, METH_NOARGS, "Check if the data is volatile-qualified."},
    {"get_length", (PyCFunction)PyDiaSymbol_getLength, METH_NOARGS, "Get the length of the pointer."},
    {"get_lexical_parent", (PyCFunction)PyDiaSymbol_getLexicalParent, METH_NOARGS, "Get the lexical parent of the pointer."},
    {"get_lexical_parent_id", (PyCFunction)PyDiaSymbol_getLexicalParentId, METH_NOARGS, "Get the lexical parent ID of the pointer."},
    {"get_sym_index_id", (PyCFunction)PyDiaSymbol_getSymIndexId, METH_NOARGS, "Get the symbol index ID of the pointer."},
    {"get_sym_tag", (PyCFunction)PyDiaSymbol_getSymTag, METH_NOARGS, "Get the symbol tag of the pointer."},
    {"get_type", (PyCFunction)PyDiaSymbol_getType, METH_NOARGS, "Get the type of the pointer."},
    {"get_type_id", (PyCFunction)PyDiaSymbol_getTypeId, METH_NOARGS, "Get the type ID of the pointer."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define the Python DiaFunction type object
PYDIA_SYMBOL_TYPE_DEFINITION(Pointer, PyDiaPointer_methods);
TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(Pointer);
