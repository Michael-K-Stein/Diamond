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
    PyDiaSymbolMethodEntry_getModifierValues,



    {"get_base_type", (PyCFunction)PyDiaSymbol_getBaseType, METH_NOARGS, "Get BasicType of the enum."},
    {"get_name", (PyCFunction)PyDiaSymbol_getName, METH_NOARGS, "Get the name of the enum."},
    {"get_class_parent", (PyCFunction)PyDiaSymbol_getClassParent, METH_NOARGS, "Get class in which this enum declaration resides."},
    {"get_class_parent_id", (PyCFunction)PyDiaSymbol_getClassParentId, METH_NOARGS, "Get the class parent ID of the enum."},
    {"has_constructor", (PyCFunction)PyDiaSymbol_hasConstructor, METH_NOARGS, "Check if the enum has a constructor."},
    {"has_assignment_operator", (PyCFunction)PyDiaSymbol_hasAssignmentOperator, METH_NOARGS, "Check if the enum has an assignment operator."},
    {"has_cast_operator", (PyCFunction)PyDiaSymbol_hasCastOperator, METH_NOARGS, "Check if the enum has a cast operator."},
    {"has_nested_types", (PyCFunction)PyDiaSymbol_hasNestedTypes, METH_NOARGS, "Check if the enum has nested types."},
    {"get_length", (PyCFunction)PyDiaSymbol_getLength, METH_NOARGS, "Get the length of the enum."},
    {"get_lexical_parent", (PyCFunction)PyDiaSymbol_getLexicalParent, METH_NOARGS, "Get the lexical parent of the enum."},
    {"get_lexical_parent_id", (PyCFunction)PyDiaSymbol_getLexicalParentId, METH_NOARGS, "Get the lexical parent ID of the enum."},
    {"is_nested", (PyCFunction)PyDiaSymbol_isNested, METH_NOARGS, "Get nested types within the enum."},
    {"has_overloaded_operator", (PyCFunction)PyDiaSymbol_hasOverloadedOperator, METH_NOARGS, "Check if the enum has an overloaded operator."},
    {"is_const", (PyCFunction)PyDiaSymbol_isConst, METH_NOARGS, "Check if the enum is const-qualified."},
    {"is_packed", (PyCFunction)PyDiaSymbol_isPacked, METH_NOARGS, "Check if the enum is packed."},
    {"is_scoped", (PyCFunction)PyDiaSymbol_isScoped, METH_NOARGS, "Check if the enum is scoped."},
    {"is_unaligned", (PyCFunction)PyDiaSymbol_isUnaligned, METH_NOARGS, "Check if the enum is unaligned."},
    {"is_volatile", (PyCFunction)PyDiaSymbol_isVolatile, METH_NOARGS, "Check if the enum is volatile-qualified."},
    {"get_sym_index_id", (PyCFunction)PyDiaSymbol_getSymIndexId, METH_NOARGS, "Get the symbol index ID of the enum."},
    {"get_sym_tag", (PyCFunction)PyDiaSymbol_getSymTag, METH_NOARGS, "Get the symbol tag of the enum."},
    {"get_type", (PyCFunction)PyDiaSymbol_getType, METH_NOARGS, "Get the type of the enum."},
    {"get_type_id", (PyCFunction)PyDiaSymbol_getTypeId, METH_NOARGS, "Get the type ID of the enum."},
    {"get_values", (PyCFunction)PyDiaEnum_getValues, METH_NOARGS, "Get the values associated with the enum."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define the Python DiaEnum type object

PYDIA_SYMBOL_TYPE_DEFINITION(Enum, PyDiaEnum_methods);
TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(Enum);

static PyObject* PyDiaEnum_getValues(PyDiaEnum* self)
{
    try
    {
        // Retrieve the enumeration values
        const auto enumValues = self->diaEnum->getValues();

        // Create a new Python list to hold the enum values
        PyObject* pyList = PyList_New(enumValues.size());
        if (!pyList)
        {
            PyErr_SetString(PyExc_MemoryError, "Failed to create list for enum values.");
            return NULL;
        }

        // Populate the Python list with PyDiaData objects
        for (size_t i = 0; i < enumValues.size(); ++i)
        {
            const dia::Data& value = enumValues[i];

            // Create a new PyDiaData object
            PyDiaData* pyData = PyObject_New(PyDiaData, &PyDiaData_Type);
            if (!pyData)
            {
                Py_DECREF(pyList);
                PyErr_SetString(PyExc_MemoryError, "Failed to create DiaData object.");
                return NULL;
            }

            // Initialize the PyDiaData object with the corresponding dia::Data object
            pyData->diaData = new dia::Data(value);

            // Set the PyDiaData object in the list
            PyList_SET_ITEM(pyList, i, reinterpret_cast<PyObject*>(pyData));
            // Reference Management: PyList_SET_ITEM steals the reference to pyData, so no Py_DECREF for pyData is necessary after insertion.
        }

        return pyList;
    }
    catch (const std::exception& e)
    {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return NULL;
    }
    Py_UNREACHABLE();
}
