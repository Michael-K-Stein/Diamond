#include "pydia_exceptions.h"

PyObject* PyDiaError = NULL;

#define __DEFINE_TRIVIAL_PYDIA_ERROR(pureName) PyObject* PyDia##pureName##Error = NULL;
XFOR_TRIVIAL_PYDIA_ERRORS(__DEFINE_TRIVIAL_PYDIA_ERROR);

static int initialize_pydiaerror(PyObject* module);
static int initialize_trivial_pydiaerrors(PyObject* module);

int pydia_initialize_pydiaerrors(PyObject* module)
{
    if (0 > initialize_pydiaerror(module))
    {
        return -1;
    }
    if (0 > initialize_trivial_pydiaerrors(module))
    {
        return -1;
    }
    return 0;
}

static int initialize_pydiaerror(PyObject* module)
{
    PyDiaError = PyErr_NewException("pydia.Error", NULL, NULL);
    if (!PyDiaError)
    {
        return -1;
    }
    Py_XINCREF(PyDiaError);
    if (PyModule_AddObject(module, "Error", PyDiaError) < 0)
    {
        Py_XDECREF(PyDiaError);
        Py_CLEAR(PyDiaError);
        Py_DECREF(module);
        return -1;
    }
    return 0;
}

static int initialize_trivial_pydiaerrors(PyObject* module)
{
#define __INITIALIZE_TRIVIAL_PYDIA_ERROR(pureName)                                                                                                   \
    do                                                                                                                                               \
    {                                                                                                                                                \
        PyDia##pureName##Error = PyErr_NewException("pydia." #pureName, PyDiaError, NULL);                                                           \
        if (!(PyDia##pureName##Error))                                                                                                               \
        {                                                                                                                                            \
            return -1;                                                                                                                               \
        }                                                                                                                                            \
        Py_XINCREF((PyDia##pureName##Error));                                                                                                        \
        if (0 > PyModule_AddObject(module, #pureName, (PyDia##pureName##Error)))                                                                     \
        {                                                                                                                                            \
            Py_XDECREF((PyDia##pureName##Error));                                                                                                    \
            Py_CLEAR((PyDia##pureName##Error));                                                                                                      \
            Py_DECREF(module);                                                                                                                       \
            return -1;                                                                                                                               \
        }                                                                                                                                            \
    } while (0)

    XFOR_TRIVIAL_PYDIA_ERRORS(__INITIALIZE_TRIVIAL_PYDIA_ERROR);
    return 0;
}