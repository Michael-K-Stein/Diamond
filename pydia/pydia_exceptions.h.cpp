#include "pydia_exceptions.h"

PyObject* PyDiaError = NULL;

#define __DEFINE_TRIVIAL_PYDIA_ERROR(pureName) PyObject* PyDia##pureName##Error = NULL;
XFOR_TRIVIAL_PYDIA_ERRORS(__DEFINE_TRIVIAL_PYDIA_ERROR);

static PyObject* pydia_initializeBaseError(PyObject* module);
static PyObject* pydia_initializeTrivialErrors(PyObject* module);

PyObject* pydia_initializeErrors(PyObject* module)
{
    if (NULL == pydia_initializeBaseError(module))
    {
        return NULL;
    }
    if (NULL == pydia_initializeTrivialErrors(module))
    {
        return NULL;
    }
    return module;
}

static PyObject* pydia_initializeBaseError(PyObject* module)
{
    PyDiaError = PyErr_NewException("pydia.Error", NULL, NULL);
    if (!PyDiaError)
    {
        return NULL;
    }
    Py_XINCREF(PyDiaError);
    if (PyModule_AddObject(module, "Error", PyDiaError) < 0)
    {
        Py_XDECREF(PyDiaError);
        Py_CLEAR(PyDiaError);
        Py_DECREF(module);
        return NULL;
    }
    return module;
}

static PyObject* pydia_initializeTrivialErrors(PyObject* module)
{
#define __INITIALIZE_TRIVIAL_PYDIA_ERROR(pureName)                                                                                                   \
    do                                                                                                                                               \
    {                                                                                                                                                \
        PyDia##pureName##Error = PyErr_NewException("pydia." #pureName, PyDiaError, NULL);                                                           \
        if (!(PyDia##pureName##Error))                                                                                                               \
        {                                                                                                                                            \
            return NULL;                                                                                                                             \
        }                                                                                                                                            \
        Py_XINCREF((PyDia##pureName##Error));                                                                                                        \
        if (0 > PyModule_AddObject(module, #pureName, (PyDia##pureName##Error)))                                                                     \
        {                                                                                                                                            \
            Py_XDECREF((PyDia##pureName##Error));                                                                                                    \
            Py_CLEAR((PyDia##pureName##Error));                                                                                                      \
            Py_DECREF(module);                                                                                                                       \
            return NULL;                                                                                                                             \
        }                                                                                                                                            \
    } while (0)

    XFOR_TRIVIAL_PYDIA_ERRORS(__INITIALIZE_TRIVIAL_PYDIA_ERROR);
    return module;
}