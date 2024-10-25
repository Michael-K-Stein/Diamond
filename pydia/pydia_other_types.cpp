#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_exceptions.h"
#include "pydia_other_types.h"
#include "pydia_trivial_init.h"


#define __TRIVIAL_PYDIA_TYPE_DEFINITION(className)                                                                                                   \
    PyTypeObject PyDia##className##_Type = {                                                                                                         \
        PyVarObject_HEAD_INIT(NULL, 0) "pydia." #className, /* tp_name */                                                                            \
        sizeof(PyDia##className),                           /* tp_basicsize */                                                                       \
        0,                                                  /* tp_itemsize */                                                                        \
        (destructor)PyDia##className##_dealloc,             /* tp_dealloc */                                                                         \
        0,                                                  /* tp_print */                                                                           \
        0,                                                  /* tp_getattr */                                                                         \
        0,                                                  /* tp_setattr */                                                                         \
        0,                                                  /* tp_as_async */                                                                        \
        0,                                                  /* tp_repr */                                                                            \
        0,                                                  /* tp_as_number */                                                                       \
        0,                                                  /* tp_as_sequence */                                                                     \
        0,                                                  /* tp_as_mapping */                                                                      \
        0,                                                  /* tp_hash  */                                                                           \
        0,                                                  /* tp_call */                                                                            \
        0,                                                  /* tp_str */                                                                             \
        0,                                                  /* tp_getattro */                                                                        \
        0,                                                  /* tp_setattro */                                                                        \
        0,                                                  /* tp_as_buffer */                                                                       \
        Py_TPFLAGS_DEFAULT,                                 /* tp_flags */                                                                           \
        #className " object",                               /* tp_doc */                                                                             \
        0,                                                  /* tp_traverse */                                                                        \
        0,                                                  /* tp_clear */                                                                           \
        0,                                                  /* tp_richcompare */                                                                     \
        0,                                                  /* tp_weaklistoffset */                                                                  \
        0,                                                  /* tp_iter */                                                                            \
        0,                                                  /* tp_iternext */                                                                        \
        0,                                                  /* tp_methods */                                                                         \
        0,                                                  /* tp_members */                                                                         \
        0,                                                  /* tp_getset */                                                                          \
        0,                                                  /* tp_base */                                                                            \
        0,                                                  /* tp_dict */                                                                            \
        0,                                                  /* tp_descr_get */                                                                       \
        0,                                                  /* tp_descr_set */                                                                       \
        0,                                                  /* tp_dictoffset */                                                                      \
        (initproc)PyDia##className##_init,                  /* tp_init */                                                                            \
        0,                                                  /* tp_alloc */                                                                           \
        PyType_GenericNew,                                  /* tp_new */                                                                             \
    };


XFOR_TRIVIAL_PYDIA_CLASSES(TRIVIAL_INIT_DEINIT);
XFOR_TRIVIAL_PYDIA_CLASSES(__TRIVIAL_PYDIA_TYPE_DEFINITION);
