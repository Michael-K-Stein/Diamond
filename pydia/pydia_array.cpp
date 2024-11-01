#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_array.h"
#include "pydia_exceptions.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include <SymbolTypes/DiaArray.h>

TRIVIAL_INIT_DEINIT(Array);


// Python method table for dia::Array
static PyMethodDef PyDiaArray_methods[] = {
    {"is_const", (PyCFunction)PyDiaSymbol_isConst, METH_NOARGS, "Check if the data is const-qualified."},
    {"is_unaligned", (PyCFunction)PyDiaSymbol_isUnaligned, METH_NOARGS, "Check if the data is unaligned."},
    {"is_volatile", (PyCFunction)PyDiaSymbol_isVolatile, METH_NOARGS, "Check if the data is volatile-qualified."},
    {"get_index_type", (PyCFunction)PyDiaSymbol_getArrayIndexType, METH_NOARGS, "Get the type of the index of the array."},
    {"get_index_type_id", (PyCFunction)PyDiaSymbol_getArrayIndexTypeId, METH_NOARGS, "Get the id of type of the index of the array."},
    {"get_length", (PyCFunction)PyDiaSymbol_getLength, METH_NOARGS, "Get the suze, in bytes, of the array."},
    {"get_count", (PyCFunction)PyDiaSymbol_getCount, METH_NOARGS, "Get the number of elements in the array."},
    {"get_lexical_parent", (PyCFunction)PyDiaSymbol_getLexicalParent, METH_NOARGS, "Get the lexical parent of the array."},
    {"get_lexical_parent_id", (PyCFunction)PyDiaSymbol_getLexicalParentId, METH_NOARGS, "Get the lexical parent ID of the array."},
    {"get_rank", (PyCFunction)PyDiaSymbol_getRank, METH_NOARGS, "Get the rank of a FORTRAN multidimensional array."},
    {"get_sym_index_id", (PyCFunction)PyDiaSymbol_getSymIndexId, METH_NOARGS, "Get the symbol index ID of the array."},
    {"get_sym_tag", (PyCFunction)PyDiaSymbol_getSymTag, METH_NOARGS, "Get the symbol tag of the array."},
    {"get_type", (PyCFunction)PyDiaSymbol_getType, METH_NOARGS, "Get the type of the array."},
    {"get_type_id", (PyCFunction)PyDiaSymbol_getTypeId, METH_NOARGS, "Get the type ID of the array."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define the Python DiaEnum type object

PYDIA_SYMBOL_TYPE_DEFINITION(Array, PyDiaArray_methods);

TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(Array);
