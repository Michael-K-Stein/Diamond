#pragma once
#include <Python.h>

// pydia includes
#include "pydia_all_types.h"
#include "pydia_symbol.h"

// DiaLib includes
#include <DiaSymbolEnumerator.h>

//
//// Forward declerations
// template <typename K, typename T>
// static inline void PyDiaSymbolGenerator_dealloc(PyDiaAbstractGenerator<K, T>* self);
// template <typename K, typename T>
// static inline PyObject* PyDiaSymbolGenerator_iter(PyDiaAbstractGenerator<K, T>* self);
// template <typename K, typename T>
// static inline PyObject* PyDiaSymbolGenerator_iternext(PyDiaAbstractGenerator<K, T>* self);

// A generator (the Python thing) for instances
template <typename K, typename T>
struct PyDiaAbstractGenerator
{
    PyObject_HEAD const K* parent;
    dia::DiaSymbolEnumerator<T>* enumerator;
    dia::DiaSymbolEnumerator<T>::Iterator* iterator;
};

template <typename K, typename T>
static inline void PyDiaSymbolGenerator_dealloc(PyDiaAbstractGenerator<K, T>* self)
{
    if (self->enumerator)
    {
        delete self->enumerator;
    }
    Py_TYPE(self)->tp_free((PyObject*)self);
}

template <typename K, typename T>
static inline PyObject* PyDiaSymbolGenerator_iter(PyDiaAbstractGenerator<K, T>* self)
{
    _ASSERT(NULL != self);
    if (NULL == self->parent)
    {
        PyErr_SetString(PyExc_RuntimeError, "Attempted to iterate on a SymbolGenerator object before initializing its parent symbol.");
        return NULL;
    }
    if (NULL == self->enumerator)
    {
        PyErr_SetString(PyExc_RuntimeError, "Attempted to iterate on a SymbolGenerator object before initializing its internal enumerator.");
        return NULL;
    }
    if (NULL == self->iterator)
    {
        PyErr_SetString(PyExc_RuntimeError, "Attempted to iterate on a SymbolGenerator object before initializing its internal iterator.");
        return NULL;
    }

    Py_INCREF(self);         // Increment reference count for generator object
    return (PyObject*)self;  // Return self as an iterator
}

template <typename K, typename T>
static inline PyObject* PyDiaSymbolGenerator_iternext(PyDiaAbstractGenerator<K, T>* self)
{
    // Inside "self" we have a pointer to an iterator instance
    auto& iteratorPointer = self->iterator;
    if (NULL == iteratorPointer)
    {
        PyErr_SetString(PyExc_RuntimeError, "Attempted to iterate on a SymbolGenerator object before initializing its internal iterator.");
        return NULL;
    }

    // Actual iterator instance
    auto& iterator         = *iteratorPointer;

    auto capturedIteration = iterator++;
    if (self->enumerator->end() == capturedIteration)
    {
        PyErr_SetNone(PyExc_StopIteration);  // Raise StopIteration pseudo-exception
        return NULL;
    }

    auto& currentItem = *capturedIteration;
    _ASSERT(NULL != &currentItem);

    return PyDiaSymbol_FromSymbol(std::move(currentItem));
}

template <typename K, typename T>
PyTypeObject PyDiaAbstractGenerator_Type = {
    PyVarObject_HEAD_INIT(NULL, 0) "pydia.SymbolAbstractGenerator",   /* tp_name */
    sizeof(PyDiaAbstractGenerator<T, K>),                             /* tp_basicsize */
    0,                                                                /* tp_itemsize */
    (destructor)PyDiaSymbolGenerator_dealloc<T, K>,                   /* tp_dealloc */
    0,                                                                /* tp_print */
    0,                                                                /* tp_getattr */
    0,                                                                /* tp_setattr */
    0,                                                                /* tp_as_async */
    0,                                                                /* tp_repr */
    0,                                                                /* tp_as_number */
    0,                                                                /* tp_as_sequence */
    0,                                                                /* tp_as_mapping */
    0,                                                                /* tp_hash  */
    0,                                                                /* tp_call */
    0,                                                                /* tp_str */
    0,                                                                /* tp_getattro */
    0,                                                                /* tp_setattro */
    0,                                                                /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                                               /* tp_flags */
    "Python wrapper for DiaLib Symbol enumerator (abstract version)", /* tp_doc */
    0,                                                                /* tp_traverse */
    0,                                                                /* tp_clear */
    0,                                                                /* tp_richcompare */
    0,                                                                /* tp_weaklistoffset */
    (getiterfunc)PyDiaSymbolGenerator_iter<T, K>,                     /* tp_iter */
    (iternextfunc)PyDiaSymbolGenerator_iternext<T, K>,                /* tp_iternext */
    0,                                                                /* tp_methods */
    0,                                                                /* tp_members */
    0,                                                                /* tp_getset */
    0,                                                                /* tp_base */
    0,                                                                /* tp_dict */
    0,                                                                /* tp_descr_get */
    0,                                                                /* tp_descr_set */
    0,                                                                /* tp_dictoffset */
    0 /* This object should never be created by Python callers */,    /* tp_init */
    PyType_GenericAlloc,                                              /* tp_alloc */
    PyType_GenericNew,                                                /* tp_new */
};

// Generic enumerator for implementations
DEFINE_ENUMERATOR(Symbol);

// Allocates a new SymbolGenerator. For use by internal methods which return a generator
template <typename K, typename T>
PyDiaAbstractGenerator<K, T>* PyDiaSymbolGenerator_create(const K* parent, dia::DiaSymbolEnumerator<T>&& enumerator)
{
    auto& generatorType                = PyDiaAbstractGenerator_Type<T, K>;
    PyDiaAbstractGenerator<K, T>* self = (PyDiaAbstractGenerator<K, T>*)generatorType.tp_alloc(&generatorType, 0);
    if (!self)
    {
        PyErr_SetString(PyExc_MemoryError, "Failed to allocate SymbolGenerator object.");
        return NULL;
    }

    self->parent     = parent;
    self->enumerator = new (std::nothrow) dia::DiaSymbolEnumerator<T>(std::move(enumerator));
    if (!self->enumerator)
    {
        PyErr_SetString(PyExc_MemoryError, "Failed to allocate SymbolGenerator object's internal enumerator.");
        return NULL;
    }
    self->iterator = new (std::nothrow) dia::DiaSymbolEnumerator<T>::Iterator();
    if (!self->iterator)
    {
        PyErr_SetString(PyExc_MemoryError, "Failed to allocate SymbolGenerator object's internal iterator.");
        return NULL;
    }
    // Set the internal iterator to the enumeration beginning
    // TODO: This looks super fishy
    *self->iterator = std::move(self->enumerator->begin());

    return self;
}
