#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>
//
#include "dia_types/pydia_datasource.h"
#include "pydia_exceptions.h"

#define TRIVIAL_INIT_DEINIT_CUSTOM_FIELD(diaName, fieldName)                                                                                         \
    static void PyDia##diaName##_dealloc(PyDia##diaName* self)                                                                                       \
    {                                                                                                                                                \
        if (self->dia##fieldName)                                                                                                                    \
        {                                                                                                                                            \
            delete self->dia##fieldName;                                                                                                             \
        }                                                                                                                                            \
        Py_TYPE(self)->tp_free((PyObject*)self);                                                                                                     \
    }                                                                                                                                                \
                                                                                                                                                     \
    static int PyDia##diaName##_init(PyDia##diaName* self, PyObject* args, PyObject* kwds)                                                           \
    {                                                                                                                                                \
        const auto unsafeInit =                                                                                                                      \
            [&]() -> int { /* Check if the function was called with 0 or 2 arguments*/                                                               \
                           if (0 == PyTuple_Size(args))                                                                                              \
                           {                                                                                                                         \
                               /* No arguments : use default constructor*/                                                                           \
                               self->dia##fieldName = new (std::nothrow) dia::##fieldName();                                                         \
                           }                                                                                                                         \
                           else if (2 == PyTuple_Size(args))                                                                                         \
                           {                                                                                                                         \
                               /* Expecting 2 arguments : dataSource and index */                                                                    \
                               PyObject* arg1              = PyTuple_GetItem(args, 0);                                                               \
                               PyObject* arg2              = PyTuple_GetItem(args, 1);                                                               \
                                                                                                                                                     \
                               PyDiaDataSource* dataSource = PyDiaDataSource_FromInitializerList(arg1);                                              \
                               if (!dataSource)                                                                                                      \
                               {                                                                                                                     \
                                   PyErr_SetString(PyExc_TypeError, "First argument must be deducible to a DataSource.");                            \
                                   return -1;                                                                                                        \
                               }                                                                                                                     \
                                                                                                                                                     \
                               const auto symbolHash = PyLong_AsSize_t(arg2);                                                                        \
                               if (symbolHash == -1 && PyErr_Occurred())                                                                             \
                               {                                                                                                                     \
                                   PyErr_SetString(PyExc_TypeError, "Second argument must be an integer.");                                          \
                                   return -1;                                                                                                        \
                               }                                                                                                                     \
                                                                                                                                                     \
                               /* Create the data object with dataSource and index */                                                                \
                               _ASSERT_EXPR(nullptr != dataSource->diaDataSource, L"DataSource must have a valid internal state!");                  \
                               self->dia##fieldName = new (std::nothrow) dia::##fieldName(dataSource->diaDataSource->getSymbolByHash(symbolHash));   \
                               if (!!self->dia##fieldName)                                                                                           \
                               {                                                                                                                     \
                                   Py_INCREF(dataSource);                                                                                            \
                                   self->dataSource = dataSource;                                                                                    \
                               }                                                                                                                     \
                           }                                                                                                                         \
                           else                                                                                                                      \
                           {                                                                                                                         \
                               PyErr_SetString(PyExc_TypeError, "PyDia" #diaName "_init() expects 0 or 2 arguments.");                               \
                               return -1;                                                                                                            \
                           }                                                                                                                         \
                           return 0;                                                                                                                 \
        };                                                                                                                                           \
                                                                                                                                                     \
        int retVal = -1;                                                                                                                             \
        PYDIA_SAFE_TRY_EXCEPT({ retVal = unsafeInit(); },                                                                                            \
                              {                                                                                                                      \
                                  PyErr_SetString(PyDiaError, e.what());                                                                             \
                                  return -1;                                                                                                         \
                              });                                                                                                                    \
        if (0 > retVal)                                                                                                                              \
        {                                                                                                                                            \
            return retVal;                                                                                                                           \
        }                                                                                                                                            \
                                                                                                                                                     \
        /* Check if allocation succeeded */                                                                                                          \
        if (!self->dia##fieldName)                                                                                                                   \
        {                                                                                                                                            \
            PyErr_SetString(PyExc_MemoryError, "Failed to create " #diaName " object.");                                                             \
            return -1;                                                                                                                               \
        }                                                                                                                                            \
                                                                                                                                                     \
        return 0;                                                                                                                                    \
    }

#define TRIVIAL_INIT_DEINIT(diaName) TRIVIAL_INIT_DEINIT_CUSTOM_FIELD(diaName, diaName)

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
