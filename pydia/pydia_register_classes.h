#pragma once
#include "pydia.h"

#define XFOR_EACH_PYDIA_CLASS(opperation)                                      \
    opperation(DataSource);                                                    \
    opperation(Symbol);

static PyObject* registerPydiaClasses(PyObject* module)
{
#define REGISTER_PYDIA_CLASS(className)                                        \
    do                                                                         \
    {                                                                          \
        if (PyType_Ready(&(PyDia##className##Type)) < 0)                       \
        {                                                                      \
            return NULL;                                                       \
        }                                                                      \
        Py_INCREF(&(PyDia##className##Type));                                  \
        PyModule_AddObject(module, #className,                                 \
                           (PyObject*)&(PyDia##className##Type));              \
    } while (0)

    XFOR_EACH_PYDIA_CLASS(REGISTER_PYDIA_CLASS)
    return module;
}
