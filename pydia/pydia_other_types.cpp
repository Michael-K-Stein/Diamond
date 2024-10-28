#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_exceptions.h"
#include "pydia_other_types.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"


#define __TRIVIAL_PYDIA_SYMBOL_TYPE_DEFINITION(className) PYDIA_SYMBOL_TYPE_DEFINITION(className, 0)
#define __TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(className)                                                                                           \
    PyObject* PyDia##className##_From##className##Symbol(dia::##className&& symbol)                                                                  \
    {                                                                                                                                                \
        PyDia##className* pySymbol = PyObject_New(PyDia##className, &PyDia##className##_Type);                                                       \
        if (!pySymbol)                                                                                                                               \
        {                                                                                                                                            \
            PyErr_SetString(PyExc_MemoryError, "Failed to create Dia" #className " object.");                                                        \
            return NULL;                                                                                                                             \
        }                                                                                                                                            \
                                                                                                                                                     \
        pySymbol->dia##className = new (std::nothrow) dia::##className(symbol);                                                                      \
                                                                                                                                                     \
        Py_INCREF(pySymbol);                                                                                                                         \
        return reinterpret_cast<PyObject*>(pySymbol);                                                                                                \
    }


XFOR_TRIVIAL_PYDIA_CLASSES(TRIVIAL_INIT_DEINIT);
XFOR_TRIVIAL_PYDIA_CLASSES(__TRIVIAL_PYDIA_SYMBOL_TYPE_DEFINITION);
XFOR_TRIVIAL_PYDIA_CLASSES(__TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION);
