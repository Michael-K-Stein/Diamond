#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_exceptions.h"
#include "pydia_generators.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol.h"
#include "pydia_symbol_private.h"

// C++ DiaSymbolMaster imports
#include <DiaSymbolEnumerator.h>

#if 0
static void PyDiaSymbolGenerator_dealloc(PyDiaSymbolGenerator* self);

// Forward declaration of the generator iteration function
static PyObject* PyDiaSymbolGenerator_iter(PyDiaSymbolGenerator* self);
static PyObject* PyDiaSymbolGenerator_iternext(PyDiaSymbolGenerator* self);

PyTypeObject PyDiaSymbolGenerator_Type = {
    PyVarObject_HEAD_INIT(NULL, 0) "pydia.SymbolGenerator",        /* tp_name */
    sizeof(PyDiaSymbolGenerator),                                  /* tp_basicsize */
    0,                                                             /* tp_itemsize */
    (destructor)PyDiaSymbolGenerator_dealloc,                      /* tp_dealloc */
    0,                                                             /* tp_print */
    0,                                                             /* tp_getattr */
    0,                                                             /* tp_setattr */
    0,                                                             /* tp_as_async */
    0,                                                             /* tp_repr */
    0,                                                             /* tp_as_number */
    0,                                                             /* tp_as_sequence */
    0,                                                             /* tp_as_mapping */
    0,                                                             /* tp_hash  */
    0,                                                             /* tp_call */
    0,                                                             /* tp_str */
    0,                                                             /* tp_getattro */
    0,                                                             /* tp_setattro */
    0,                                                             /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                                            /* tp_flags */
    "Python wrapper for DiaLib Symbol enumerator",                 /* tp_doc */
    0,                                                             /* tp_traverse */
    0,                                                             /* tp_clear */
    0,                                                             /* tp_richcompare */
    0,                                                             /* tp_weaklistoffset */
    (getiterfunc)PyDiaSymbolGenerator_iter,                        /* tp_iter */
    (iternextfunc)PyDiaSymbolGenerator_iternext,                   /* tp_iternext */
    0,                                                             /* tp_methods */
    0,                                                             /* tp_members */
    0,                                                             /* tp_getset */
    0,                                                             /* tp_base */
    0,                                                             /* tp_dict */
    0,                                                             /* tp_descr_get */
    0,                                                             /* tp_descr_set */
    0,                                                             /* tp_dictoffset */
    0 /* This object should never be created by Python callers */, /* tp_init */
    0,                                                             /* tp_alloc */
    PyType_GenericNew,                                             /* tp_new */
};
#endif;