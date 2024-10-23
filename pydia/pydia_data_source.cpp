#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_exceptions.h"
#include "pydia_symbol.h"

// C++ DiaSymbolMaster imports
#include "DiaDataSource.h"

// Define the Python DiaDataSource object
typedef struct
{
    PyObject_HEAD dia::DiaDataSource*
        diaDataSource; // Pointer to the C++ DiaDataSource object
} PyDiaDataSource;

static PyObject* PyDiaDataSource_loadDataFromPdb(PyDiaDataSource* self,
                                                 PyObject* args);
static PyObject* PyDiaDataSource_getExports(PyDiaDataSource* self,
                                            PyObject* args);
static PyObject* PyDiaDataSource_getExportedFunctions(PyDiaDataSource* self);

// Deallocate method (destructor)
static void PyDiaDataSource_dealloc(PyDiaDataSource* self)
{
    if (self->diaDataSource)
    {
        delete self->diaDataSource;
    }
    Py_TYPE(self)->tp_free((PyObject*)self);
}

// __init__ method (constructor)
static int PyDiaDataSource_init(PyDiaDataSource* self, PyObject* args,
                                PyObject* kwds)
{
    self->diaDataSource = new dia::DiaDataSource();
    if (!self->diaDataSource)
    {
        PyErr_SetString(PyExc_MemoryError,
                        "Failed to create DiaDataSource object.");
        return -1;
    }
    return 0;
}

// Python method table for DiaDataSource
static PyMethodDef PyDiaDataSource_methods[] = {
    {"loadDataFromPdb", (PyCFunction)PyDiaDataSource_loadDataFromPdb,
     METH_VARARGS, "Load data from a PDB file"},

    {"getFunctions", (PyCFunction)PyDiaDataSource_getExportedFunctions,
     METH_NOARGS, "Get exported functions"},

    {"getSymbols", (PyCFunction)PyDiaDataSource_getExports, METH_VARARGS,
     "Get all exports"},

    {NULL, NULL, 0, NULL}};

// Define the Python DiaDataSource type object
PyTypeObject PyDiaDataSourceType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pydia.DiaDataSource", /* tp_name */
    sizeof(PyDiaDataSource),                              /* tp_basicsize */
    0,                                                    /* tp_itemsize */
    (destructor)PyDiaDataSource_dealloc,                  /* tp_dealloc */
    0,                                                    /* tp_print */
    0,                                                    /* tp_getattr */
    0,                                                    /* tp_setattr */
    0,                                                    /* tp_as_async */
    0,                                                    /* tp_repr */
    0,                                                    /* tp_as_number */
    0,                                                    /* tp_as_sequence */
    0,                                                    /* tp_as_mapping */
    0,                                                    /* tp_hash  */
    0,                                                    /* tp_call */
    0,                                                    /* tp_str */
    0,                                                    /* tp_getattro */
    0,                                                    /* tp_setattro */
    0,                                                    /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                                   /* tp_flags */
    "DiaDataSource object",                               /* tp_doc */
    0,                                                    /* tp_traverse */
    0,                                                    /* tp_clear */
    0,                                                    /* tp_richcompare */
    0,                              /* tp_weaklistoffset */
    0,                              /* tp_iter */
    0,                              /* tp_iternext */
    PyDiaDataSource_methods,        /* tp_methods */
    0,                              /* tp_members */
    0,                              /* tp_getset */
    0,                              /* tp_base */
    0,                              /* tp_dict */
    0,                              /* tp_descr_get */
    0,                              /* tp_descr_set */
    0,                              /* tp_dictoffset */
    (initproc)PyDiaDataSource_init, /* tp_init */
    0,                              /* tp_alloc */
    PyType_GenericNew,              /* tp_new */
};

// Method: loadDataFromPdb
static PyObject* PyDiaDataSource_loadDataFromPdb(PyDiaDataSource* self,
                                                 PyObject* args)
{
    PyObject* pyFilePath = NULL;

    // Parse the argument as a Python object (string or bytes)
    if (!PyArg_ParseTuple(args, "O", &pyFilePath))
    {
        return NULL; // If parsing fails, return NULL (error already set)
    }

    // Variable to hold the converted wide-char path
    const wchar_t* pdbFilePath = NULL;

    // Check if the object is a Unicode string (str in Python)
    if (PyUnicode_Check(pyFilePath))
    {
        // Convert Unicode string (PyUnicodeObject) to a wchar_t*
        pdbFilePath = PyUnicode_AsWideCharString(pyFilePath, NULL);
        if (!pdbFilePath)
        {
            PyErr_SetString(
                PyExc_ValueError,
                "Failed to convert Unicode string to wide character.");
            return NULL;
        }
    }
    // Check if the object is a bytes string
    else if (PyBytes_Check(pyFilePath))
    {
        // Convert bytes to a C string (char*)
        const char* bytesFilePath = PyBytes_AsString(pyFilePath);
        if (!bytesFilePath)
        {
            PyErr_SetString(PyExc_ValueError,
                            "Failed to convert bytes to string.");
            return NULL;
        }
        // Convert char* to wchar_t* using MultiByteToWideChar
        int len = MultiByteToWideChar(CP_UTF8, 0, bytesFilePath, -1, NULL, 0);
        if (len <= 0)
        {
            PyErr_SetString(PyExc_ValueError,
                            "Failed to convert bytes to wide character.");
            return NULL;
        }

        wchar_t* widePath = (wchar_t*)PyMem_Malloc(len * sizeof(wchar_t));
        if (!widePath)
        {
            PyErr_SetString(
                PyExc_MemoryError,
                "Failed to allocate memory for wide character conversion.");
            return NULL;
        }
        MultiByteToWideChar(CP_UTF8, 0, bytesFilePath, -1, widePath, len);
        pdbFilePath = widePath; // Use the newly converted wchar_t* path
    }
    else
    {
        PyErr_SetString(
            PyExc_TypeError,
            "Expected a string or bytes object for the PDB file path.");
        return NULL;
    }

    try
    {
        // Call the C++ method with the wide-char path
        self->diaDataSource->loadDataFromPdb(std::wstring(pdbFilePath));
    }
    catch (const std::exception& e)
    {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        if (pdbFilePath && !PyUnicode_Check(pyFilePath))
        {
            PyMem_Free(
                (void*)pdbFilePath); // Free memory for widePath if converted
        }
        return NULL;
    }

    if (pdbFilePath && !PyUnicode_Check(pyFilePath))
    {
        PyMem_Free((void*)pdbFilePath); // Free memory for widePath if converted
    }

    // Return self for method chaining
    Py_INCREF(self);
    return (PyObject*)self;
}

// Method: getExportedFunctions
static PyObject* PyDiaDataSource_getExportedFunctions(PyDiaDataSource* self)
{
    std::vector<dia::Symbol> functions{};
    try
    {
        functions = self->diaDataSource->getFunctions();
    }
    catch (const std::exception& e)
    {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return NULL;
    }

    PyObject* resultList = PyList_New(functions.size());
    if (!resultList)
        return NULL;

    for (size_t i = 0; i < functions.size(); ++i)
    {
        PyObject* functionStr = PyUnicode_FromWideChar(
            functions[i].getName().c_str(), functions[i].getName().length());
        if (!functionStr)
        {
            Py_DECREF(resultList);
            return NULL;
        }
        PyList_SET_ITEM(resultList, i, functionStr);
    }

    return resultList;
}

static PyObject* PyDiaDataSource_getExports(PyDiaDataSource* self,
                                            PyObject* args)
{
    int symTagInt;
    if (!PyArg_ParseTuple(args, "i", &symTagInt))
    {
        PyErr_SetString(PyExc_ValueError,
                        "Expected an integer for the SymTagEnum.");
        return NULL;
    }

    enum SymTagEnum symTag = static_cast<enum SymTagEnum>(symTagInt);
    std::vector<dia::Symbol> exports = self->diaDataSource->getSymbols(symTag);

    PyObject* resultList = PyList_New(exports.size());
    if (!resultList)
    {
        return NULL; // Return NULL on failure
    }

    for (size_t i = 0; i < exports.size(); ++i)
    {
        PyDiaSymbol* sym = PyObject_New(PyDiaSymbol, &PyDiaSymbolType);
        if (!sym)
        {
            Py_DECREF(resultList); // Clean up the result list
            return NULL;           // Return NULL on failure
        }
        sym->diaSymbol = new dia::Symbol(exports[i]);

        // Set the item in the list, transferring ownership
        if (PyList_SetItem(resultList, i, reinterpret_cast<PyObject*>(sym)) < 0)
        {
            delete sym->diaSymbol; // Clean up
            delete sym;            // Clean up
            Py_DECREF(resultList); // Clean up the result list
            return NULL;           // Return NULL on failure
        }
    }

    return resultList;
}
