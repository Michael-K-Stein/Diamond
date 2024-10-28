#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_exceptions.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_udt.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include "DiaUserDefinedTypeWrapper.h"
#include "SymbolTypes/DiaUdt.h"

static void PyDiaUdt_dealloc(PyDiaUdt* self)
{
    if (self->diaUdt)
    {
        delete self->diaUdt;
    }
    _Py_TYPE(((PyObject*)((self))))->tp_free((PyObject*)self);
}

static int PyDiaUdt_init(PyDiaUdt* self, PyObject* args, PyObject* kwds)
{
    self->diaUdt = new (std::nothrow) dia::UserDefinedType();
    if (!self->diaUdt)
    {
        PyErr_SetString(PyExc_MemoryError, "Failed to create Udt object.");
        return -1;
    }
    return 0;
};

// Python method table for dia::Udt
static PyMethodDef PyDiaUdt_methods[] = {
    {"get_name", (PyCFunction)PyDiaSymbol_getName, METH_NOARGS, "Get the name of the UDT."},
    {"get_value", (PyCFunction)PyDiaSymbol_getValue, METH_NOARGS, "Get the value of the UDT."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define the Python DiaData type object
PyTypeObject PyDiaUdt_Type = {
    PyVarObject_HEAD_INIT(NULL, 0) "pydia.Udt", /* tp_name */
    sizeof(PyDiaUdt),                           /* tp_basicsize */
    0,                                          /* tp_itemsize */
    (destructor)PyDiaUdt_dealloc,               /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_as_async */
    0,                                          /* tp_repr */
    0,                                          /* tp_as_number */
    0,                                          /* tp_as_sequence */
    0,                                          /* tp_as_mapping */
    (hashfunc)PyDiaSymbol_hash,                 /* tp_hash  */
    0,                                          /* tp_call */
    0,                                          /* tp_str */
    0,                                          /* tp_getattro */
    0,                                          /* tp_setattro */
    0,                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                         /* tp_flags */
    "UserDefinedType object",                   /* tp_doc */
    0,                                          /* tp_traverse */
    0,                                          /* tp_clear */
    (richcmpfunc)PyDiaSymbol_richcompare,       /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    PyDiaUdt_methods,                           /* tp_methods */
    0,                                          /* tp_members */
    0,                                          /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    (initproc)PyDiaUdt_init,                    /* tp_init */
    0,                                          /* tp_alloc */
    PyType_GenericNew,                          /* tp_new */
};
