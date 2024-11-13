#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_exceptions.h"
#include "pydia_functiontype.h"
#include "pydia_generators.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include <SymbolTypes/DiaFunctionType.h>

TRIVIAL_INIT_DEINIT(FunctionType);

static PyObject* PyDiaFunctionType_enumerateParameters(PyDiaFunctionType* self);

// Python method table for dia::FunctionType
static PyMethodDef PyDiaFunctionType_methods[] = {
    PyDiaSymbolMethodEntry_getModifierValues,


    {"get_lexical_parent", (PyCFunction)PyDiaSymbol_getLexicalParent, METH_NOARGS, "Get the lexical parent of the symbol."},
    {"get_lexical_parent_id", (PyCFunction)PyDiaSymbol_getLexicalParentId, METH_NOARGS, "Get the lexical parent ID of the symbol."},

    {"get_sym_index_id", (PyCFunction)PyDiaSymbol_getSymIndexId, METH_NOARGS, "Get the symbol index ID of the symbol."},
    {"get_sym_tag", (PyCFunction)PyDiaSymbol_getSymTag, METH_NOARGS, "Get the symbol tag of the symbol."},

    {"is_unaligned", (PyCFunction)PyDiaSymbol_isUnaligned, METH_NOARGS, "Check if the data is unaligned."},
    {"is_volatile", (PyCFunction)PyDiaSymbol_isVolatile, METH_NOARGS, "Check if the data is volatile-qualified."},

    {"get_calling_convention", (PyCFunction)PyDiaSymbol_getCallingConvention, METH_NOARGS, "Get the calling convention of the function type."},

    {"get_class_parent", (PyCFunction)PyDiaSymbol_getClassParent, METH_NOARGS, "Get the class parent of the function type."},
    {"get_class_parent_id", (PyCFunction)PyDiaSymbol_getClassParentId, METH_NOARGS, "Get the class parent ID of the function type."},

    {"get_count", (PyCFunction)PyDiaSymbol_getCount, METH_NOARGS, "Get the count of elements associated with the function type."},
    {"get_object_pointer_type", (PyCFunction)PyDiaSymbol_getObjectPointerType, METH_NOARGS,
     "Get the object pointer type associated with the function type."},

    {"get_this_adjust", (PyCFunction)PyDiaSymbol_getThisAdjust, METH_NOARGS, "Get the 'this' pointer adjustment value for the function type."},

    {"get_type", (PyCFunction)PyDiaSymbol_getType, METH_NOARGS, "Get the type of the function type."},
    {"get_type_id", (PyCFunction)PyDiaSymbol_getTypeId, METH_NOARGS, "Get the type ID of the function type."},

    {"enumerate_parameters", (PyCFunction)PyDiaFunctionType_enumerateParameters, METH_NOARGS, "Enumerate the parameters of the function type."},
    {NULL, NULL, 0, NULL}  // Sentinel
};


// Define the Python DiaEnum type object

PYDIA_SYMBOL_TYPE_DEFINITION(FunctionType, PyDiaFunctionType_methods);
TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(FunctionType);

static PyObject* PyDiaFunctionType_enumerateParameters(PyDiaFunctionType* self)
{
    auto rawEnumerator = self->diaFunctionType->enumerateParameters();
    PyDiaDataGenerator* generator =
        (PyDiaDataGenerator*)PyDiaSymbolGenerator_create<PyDiaFunctionType, dia::FunctionArgType>(self, std::move(rawEnumerator));
    if (!generator)
    {
        PyErr_SetString(PyExc_RuntimeError, "Failed to create generator.");
        return NULL;  // Failed to allocate generator
    }

    return (PyObject*)generator;
}
