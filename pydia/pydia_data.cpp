#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_data.h"
#include "pydia_exceptions.h"
#include "pydia_trivial_init.h"

// C++ DiaSymbolMaster imports
#include "SymbolTypes/DiaData.h"
#include "pydia_wrapping_types.h"
#include <pydia_helper_routines.h>


static PyObject* PyDiaData_getName(PyDiaData* self);
static PyObject* PyDiaData_getValue(PyDiaData* self);

TRIVIAL_INIT_DEINIT(Data);

// Python method table for dia::Data
static PyMethodDef PyDiaData_methods[] = {
    {"get_name", (PyCFunction)PyDiaData_getName, METH_NOARGS, "Get the name of the data field."},
    {"get_value", (PyCFunction)PyDiaData_getValue, METH_NOARGS, "Get the value of the data field."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define the Python DiaData type object
PyTypeObject PyDiaData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0) "pydia.Data", /* tp_name */
    sizeof(PyDiaData),                           /* tp_basicsize */
    0,                                           /* tp_itemsize */
    (destructor)PyDiaData_dealloc,               /* tp_dealloc */
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
    "Data object",                               /* tp_doc */
    0,                                           /* tp_traverse */
    0,                                           /* tp_clear */
    0,                                           /* tp_richcompare */
    0,                                           /* tp_weaklistoffset */
    0,                                           /* tp_iter */
    0,                                           /* tp_iternext */
    PyDiaData_methods,                           /* tp_methods */
    0,                                           /* tp_members */
    0,                                           /* tp_getset */
    0,                                           /* tp_base */
    0,                                           /* tp_dict */
    0,                                           /* tp_descr_get */
    0,                                           /* tp_descr_set */
    0,                                           /* tp_dictoffset */
    (initproc)PyDiaData_init,                    /* tp_init */
    0,                                           /* tp_alloc */
    PyType_GenericNew,                           /* tp_new */
};

// Method: PyDiaData_getName
static PyObject* PyDiaData_getName(PyDiaData* self)
{
    try
    {
        // Get the name as a std::string and convert to a Python string
        const std::wstring name = self->diaData->getName();
        return PyUnicode_FromWideChar(name.c_str(), name.length());
    }
    catch (const std::exception& e)
    {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return NULL;
    }
    Py_UNREACHABLE();
}

// Method: PyDiaData_getValue
static PyObject* PyDiaData_getValue(PyDiaData* self)
{
    try
    {
        // Get the value from diaData and convert it to an appropriate Python object
        const auto value           = self->diaData->getValue();
        const auto variantPyObject = VariantToPyObject(value);
        return variantPyObject;
    }
    catch (const std::exception& e)
    {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return NULL;
    }
    Py_UNREACHABLE();
}
