#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else

static PyObject* PyDiaError;
static int pydia_initialize_pydiaerror(PyObject* module)
{
    PyDiaError = PyErr_NewException("pydia.error", NULL, NULL);
    Py_XINCREF(PyDiaError);
    if (PyModule_AddObject(module, "error", PyDiaError) < 0)
    {
        Py_XDECREF(PyDiaError);
        Py_CLEAR(PyDiaError);
        Py_DECREF(module);
        return -1;
    }
    return 0;
}
