#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_data.h"
#include "pydia_enum.h"
#include "pydia_exceptions.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include "SymbolTypes/DiaEnum.h"

static PyObject* PyDiaEnum_getValues(PyDiaEnum* self);

TRIVIAL_INIT_DEINIT(Enum);

// Python method table for dia::Enum
static PyMethodDef PyDiaEnum_methods[] = {
    PyDiaSymbolMethodEntry_getBaseType,
    PyDiaSymbolMethodEntry_getName,
    PyDiaSymbolMethodEntry_getClassParent,
    PyDiaSymbolMethodEntry_getClassParentId,
    PyDiaSymbolMethodEntry_hasConstructor,
    PyDiaSymbolMethodEntry_hasAssignmentOperator,
    PyDiaSymbolMethodEntry_hasCastOperator,
    PyDiaSymbolMethodEntry_hasNestedTypes,
    PyDiaSymbolMethodEntry_getLength,
    PyDiaSymbolMethodEntry_getLexicalParent,
    PyDiaSymbolMethodEntry_getLexicalParentId,
    PyDiaSymbolMethodEntry_isNested,
    PyDiaSymbolMethodEntry_hasOverloadedOperator,
    PyDiaSymbolMethodEntry_isConst,
    PyDiaSymbolMethodEntry_isPacked,
    PyDiaSymbolMethodEntry_isScoped,
    PyDiaSymbolMethodEntry_isUnaligned,
    PyDiaSymbolMethodEntry_isVolatile,
    PyDiaSymbolMethodEntry_getSymIndexId,
    PyDiaSymbolMethodEntry_getSymTag,
    PyDiaSymbolMethodEntry_getType,
    PyDiaSymbolMethodEntry_getTypeId,

    {"get_values", (PyCFunction)PyDiaEnum_getValues, METH_NOARGS, "Get the values associated with the enum."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define the Python DiaEnum type object

PYDIA_SYMBOL_TYPE_DEFINITION(Enum, PyDiaEnum_methods);
TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(Enum);

// TODO: This can probably be made generic for all "data child" enumerations


static PyObject* PyDiaEnum_getValues(PyDiaEnum* self)
{
    _ASSERT(NULL != self);
    _ASSERT(NULL != self->diaEnum);

    auto safeExecution = [&]() -> PyObject*
    {
        auto rawEnumerator            = self->diaEnum->getValues();
        PyDiaDataGenerator* generator = (PyDiaDataGenerator*)PyDiaSymbolGenerator_create<PyDiaEnum, dia::Data>(self, std::move(rawEnumerator));
        if (!generator)
        {
            PyErr_SetString(PyExc_RuntimeError, "Failed to create generator.");
            return NULL;  // Failed to allocate generator
        }

        return (PyObject*)generator;
    };

    PYDIA_SAFE_TRY({ return safeExecution(); });
    Py_UNREACHABLE();
}
