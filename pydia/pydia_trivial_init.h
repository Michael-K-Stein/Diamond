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