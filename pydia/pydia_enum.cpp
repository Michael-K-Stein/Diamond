#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_enum.h"
#include "pydia_exceptions.h"
#include "pydia_trivial_init.h"

// C++ DiaSymbolMaster imports
#include "SymbolTypes/DiaEnum.h"
#include "pydia_wrapping_types.h"


static PyObject* PyDiaEnum_getBaseType(PyDiaEnum* self);
// static PyObject* PyDiaEnum_getClassParent(PyDiaEnum* self);

TRIVIAL_INIT_DEINIT(Enum);
// Python method table for dia::Enum
static PyMethodDef PyDiaEnum_methods[] = {
    {"get_base_type", (PyCFunction)PyDiaEnum_getBaseType, METH_NOARGS, "Get BasicType of the enum."},
#if 0
    {"get_class_parent", (PyCFunction)PyDiaEnum_getClassParent, METH_NOARGS, "Get class in which this enum declaration resides."},
    {"get_class_parent_id", (PyCFunction)PyDiaEnum_getClassParentId, METH_NOARGS, "Get the class parent ID of the enum."},
    {"has_constructor", (PyCFunction)PyDiaEnum_getConstructor, METH_NOARGS, "Check if the enum has a constructor."},
    {"is_const", (PyCFunction)PyDiaEnum_getConstType, METH_NOARGS, "Check if the enum is const-qualified."},
    {"has_assignment_operator", (PyCFunction)PyDiaEnum_getHasAssignmentOperator, METH_NOARGS, "Check if the enum has an assignment operator."},
    {"has_cast_operator", (PyCFunction)PyDiaEnum_getHasCastOperator, METH_NOARGS, "Check if the enum has a cast operator."},
    {"has_nested_types", (PyCFunction)PyDiaEnum_getHasNestedTypes, METH_NOARGS, "Check if the enum has nested types."},
    {"get_length", (PyCFunction)PyDiaEnum_getLength, METH_NOARGS, "Get the length of the enum."},
    {"get_lexical_parent", (PyCFunction)PyDiaEnum_getLexicalParent, METH_NOARGS, "Get the lexical parent of the enum."},
    {"get_lexical_parent_id", (PyCFunction)PyDiaEnum_getLexicalParentId, METH_NOARGS, "Get the lexical parent ID of the enum."},
    {"get_name", (PyCFunction)PyDiaEnum_getName, METH_NOARGS, "Get the name of the enum."},
    {"get_nested", (PyCFunction)PyDiaEnum_getNested, METH_NOARGS, "Get nested types within the enum."},
    {"has_overloaded_operator", (PyCFunction)PyDiaEnum_getOverloadedOperator, METH_NOARGS, "Check if the enum has an overloaded operator."},
    {"is_packed", (PyCFunction)PyDiaEnum_getPacked, METH_NOARGS, "Check if the enum is packed."},
    {"is_scoped", (PyCFunction)PyDiaEnum_getScoped, METH_NOARGS, "Check if the enum is scoped."},
    {"get_sym_index_id", (PyCFunction)PyDiaEnum_getSymIndexId, METH_NOARGS, "Get the symbol index ID of the enum."},
    {"get_sym_tag", (PyCFunction)PyDiaEnum_getSymTag, METH_NOARGS, "Get the symbol tag of the enum."},
    {"get_type", (PyCFunction)PyDiaEnum_getType, METH_NOARGS, "Get the type of the enum."},
    {"get_type_id", (PyCFunction)PyDiaEnum_getTypeId, METH_NOARGS, "Get the type ID of the enum."},
    {"is_unaligned", (PyCFunction)PyDiaEnum_getUnalignedType, METH_NOARGS, "Check if the enum is unaligned."},
    {"is_volatile", (PyCFunction)PyDiaEnum_getVolatileType, METH_NOARGS, "Check if the enum is volatile-qualified."},
    {"get_values", (PyCFunction)PyDiaEnum_getValues, METH_NOARGS, "Get the values associated with the enum."},
#endif
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define the Python DiaEnum type object
PyTypeObject PyDiaEnum_Type = {
    PyVarObject_HEAD_INIT(NULL, 0) "pydia.Enum", /* tp_name */
    sizeof(PyDiaEnum),                           /* tp_basicsize */
    0,                                           /* tp_itemsize */
    (destructor)PyDiaEnum_dealloc,               /* tp_dealloc */
    0,                                           /* tp_print */
    0,                                           /* tp_getattr */
    0,                                           /* tp_setattr */
    0,                                           /* tp_as_async */
    0,                                           /* tp_repr */
    0,                                           /* tp_as_number */
    0,                                           /* tp_as_sequence */
    0,                                           /* tp_as_mapping */
    0,                                           /* tp_hash  */
    0,                                           /* tp_call */
    0,                                           /* tp_str */
    0,                                           /* tp_getattro */
    0,                                           /* tp_setattro */
    0,                                           /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                          /* tp_flags */
    "Enum object",                               /* tp_doc */
    0,                                           /* tp_traverse */
    0,                                           /* tp_clear */
    0,                                           /* tp_richcompare */
    0,                                           /* tp_weaklistoffset */
    0,                                           /* tp_iter */
    0,                                           /* tp_iternext */
    PyDiaEnum_methods,                           /* tp_methods */
    0,                                           /* tp_members */
    0,                                           /* tp_getset */
    0,                                           /* tp_base */
    0,                                           /* tp_dict */
    0,                                           /* tp_descr_get */
    0,                                           /* tp_descr_set */
    0,                                           /* tp_dictoffset */
    (initproc)PyDiaEnum_init,                    /* tp_init */
    0,                                           /* tp_alloc */
    PyType_GenericNew,                           /* tp_new */
};

// Method: getBaseType
static PyObject* PyDiaEnum_getBaseType(PyDiaEnum* self)
{
    const auto basicType = self->diaEnum->getBaseType();

    // Access the BasicType dictionary from the module
    PyObject* basicTypeDict = getDiaBasicTypeEnumWrappings();
    if (!basicTypeDict)
    {
        PyErr_SetString(PyExc_RuntimeError, "BasicType dictionary not found.");
        return NULL;
    }

    // Convert the basicType integer to a Python integer
    PyObject* key = PyLong_FromLong(basicType);
    if (!key)
    {
        PyErr_SetString(PyExc_RuntimeError, "Failed to convert BasicType to PyLong.");
        return NULL;
    }

    // Get the name of the basicType from the dictionary
    PyObject* result = PyDict_GetItem(basicTypeDict, key);
    Py_DECREF(key);  // Decrease ref count for the key as it is no longer needed

    if (!result)
    {
        PyErr_SetString(PyExc_KeyError, "BasicType key not found in dictionary.");
        return NULL;
    }

    Py_INCREF(result);  // Increment ref count for result as it will be returned
    return result;
}

//
// static PyObject* PyDiaEnum_getClassParent(PyDiaEnum* self)
//{
//    const auto classParent = self->diaEnum->getClassParent();
//
//
//
//    return classParent;
//};
//}