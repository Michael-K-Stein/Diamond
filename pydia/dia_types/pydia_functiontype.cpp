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
    PyDiaSymbolMethodEntry_getLexicalParent,
    PyDiaSymbolMethodEntry_getLexicalParentId,
    PyDiaSymbolMethodEntry_getSymIndexId,
    PyDiaSymbolMethodEntry_getSymTag,
    PyDiaSymbolMethodEntry_isUnaligned,
    PyDiaSymbolMethodEntry_isVolatile,
    PyDiaSymbolMethodEntry_getCallingConvention,
    PyDiaSymbolMethodEntry_getClassParent,
    PyDiaSymbolMethodEntry_getClassParentId,
    PyDiaSymbolMethodEntry_getCount,
    PyDiaSymbolMethodEntry_getObjectPointerType,
    PyDiaSymbolMethodEntry_getThisAdjust,
    PyDiaSymbolMethodEntry_getType,
    PyDiaSymbolMethodEntry_getTypeId,

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
