#pragma once
#include "dia_types/pydia_datasource.h"
#include "pydia.h"
#include "pydia_classes.h"
#include "pydia_enum.h"
#include "pydia_other_types.h"

#define __REGISTER_PYDIA_CLASS(className)                                                                                                            \
    do                                                                                                                                               \
    {                                                                                                                                                \
        if (PyType_Ready(&(PyDia##className##_Type)) < 0)                                                                                            \
        {                                                                                                                                            \
            return NULL;                                                                                                                             \
        }                                                                                                                                            \
        Py_INCREF(&(PyDia##className##_Type));                                                                                                       \
        PyModule_AddObject(module, #className, (PyObject*)&(PyDia##className##_Type));                                                               \
    } while (0)

static PyObject* registerPydiaClasses(PyObject* module)
{
    XFOR_EACH_PYDIA_CLASS(__REGISTER_PYDIA_CLASS)
    return module;
}
