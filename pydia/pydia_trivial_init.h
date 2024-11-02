#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

#define TRIVIAL_INIT_DEINIT(diaName)                                                                                                                 \
    static void PyDia##diaName##_dealloc(PyDia##diaName* self)                                                                                       \
    {                                                                                                                                                \
        if (self->dia##diaName)                                                                                                                      \
        {                                                                                                                                            \
            delete self->dia##diaName;                                                                                                               \
        }                                                                                                                                            \
        Py_TYPE(self)->tp_free((PyObject*)self);                                                                                                     \
    }                                                                                                                                                \
                                                                                                                                                     \
    static int PyDia##diaName##_init(PyDia##diaName* self, PyObject* args, PyObject* kwds)                                                           \
    {                                                                                                                                                \
        self->dia##diaName = new (std::nothrow) dia::##diaName();                                                                                    \
        if (!self->dia##diaName)                                                                                                                     \
        {                                                                                                                                            \
            PyErr_SetString(PyExc_MemoryError, "Failed to create " #diaName "object.");                                                              \
            return -1;                                                                                                                               \
        }                                                                                                                                            \
        return 0;                                                                                                                                    \
    }

#define TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(className)                                                                                             \
    PyObject* PyDia##className##_From##className##Symbol(dia::##className&& symbol, PyDiaDataSource* dataSource)                                     \
    {                                                                                                                                                \
        PyDia##className* pySymbol = PyObject_New(PyDia##className, &PyDia##className##_Type);                                                       \
        if (!pySymbol)                                                                                                                               \
        {                                                                                                                                            \
            PyErr_SetString(PyExc_MemoryError, "Failed to create Dia" #className " object.");                                                        \
            return NULL;                                                                                                                             \
        }                                                                                                                                            \
                                                                                                                                                     \
        pySymbol->dia##className = new (std::nothrow) dia::##className(symbol);                                                                      \
        if (!(pySymbol->dia##className))                                                                                                             \
        {                                                                                                                                            \
            PyErr_SetString(PyExc_MemoryError, "Failed to create Dia" #className "'s internal state.");                                              \
            return NULL;                                                                                                                             \
        }                                                                                                                                            \
                                                                                                                                                     \
        Py_INCREF(dataSource);                                                                                                                       \
        pySymbol->dataSource = dataSource;                                                                                                           \
                                                                                                                                                     \
        Py_INCREF(pySymbol);                                                                                                                         \
        return reinterpret_cast<PyObject*>(pySymbol);                                                                                                \
    }
