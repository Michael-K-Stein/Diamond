#include "pydia_symbol.h"
#include "DiaSymbol.h"
#include <Python.h>

// Method definitions
static PyObject* PyDiaSymbol_getName(PyDiaSymbol* self, PyObject*);
static PyObject* PyDiaSymbol_getOffset(PyDiaSymbol* self, PyObject*);
static PyObject* PyDiaSymbol_getType(PyDiaSymbol* self, PyObject*);
static PyObject* PyDiaSymbol_getTypeName(PyDiaSymbol* self, PyObject*);
static PyObject* PyDiaSymbol_getSymTag(PyDiaSymbol* self, PyObject*);
static PyObject* PyDiaSymbol_getBaseType(PyDiaSymbol* self, PyObject*);
static PyObject* PyDiaSymbol_getCount(PyDiaSymbol* self, PyObject*);
static PyObject* PyDiaSymbol_getLocationType(PyDiaSymbol* self, PyObject*);
static PyObject* PyDiaSymbol_getBitPosition(PyDiaSymbol* self, PyObject*);
static PyObject* PyDiaSymbol_getLength(PyDiaSymbol* self, PyObject*);
static PyObject* PyDiaSymbol_isVolatile(PyDiaSymbol* self, PyObject*);
static PyObject* PyDiaSymbol_isArray(PyDiaSymbol* self, PyObject*);
static PyObject* PyDiaSymbol_isPointer(PyDiaSymbol* self, PyObject*);

// Method definitions struct
static PyMethodDef PyDiaSymbol_methods[] = {
    {"getName", (PyCFunction)PyDiaSymbol_getName, METH_NOARGS,
     "Get the name of the symbol."},
    {"getOffset", (PyCFunction)PyDiaSymbol_getOffset, METH_NOARGS,
     "Get the offset of the symbol."},
    {"getType", (PyCFunction)PyDiaSymbol_getType, METH_NOARGS,
     "Get the type of the symbol."},
    {"getTypeName", (PyCFunction)PyDiaSymbol_getTypeName, METH_NOARGS,
     "Get the type name of the symbol."},
    {"getSymTag", (PyCFunction)PyDiaSymbol_getSymTag, METH_NOARGS,
     "Get the SymTag of the symbol."},
    {"getBaseType", (PyCFunction)PyDiaSymbol_getBaseType, METH_NOARGS,
     "Get the base type of the symbol."},
    {"getCount", (PyCFunction)PyDiaSymbol_getCount, METH_NOARGS,
     "Get the count of the symbol."},
    {"getLocationType", (PyCFunction)PyDiaSymbol_getLocationType, METH_NOARGS,
     "Get the location type of the symbol."},
    {"getBitPosition", (PyCFunction)PyDiaSymbol_getBitPosition, METH_NOARGS,
     "Get the bit position of the symbol."},
    {"getLength", (PyCFunction)PyDiaSymbol_getLength, METH_NOARGS,
     "Get the length of the symbol."},
    {"isVolatile", (PyCFunction)PyDiaSymbol_isVolatile, METH_NOARGS,
     "Check if the symbol is volatile."},
    {"isArray", (PyCFunction)PyDiaSymbol_isArray, METH_NOARGS,
     "Check if the symbol is an array."},
    {"isPointer", (PyCFunction)PyDiaSymbol_isPointer, METH_NOARGS,
     "Check if the symbol is a pointer."},
    {NULL, NULL, 0, NULL} // Sentinel
};

// Deallocate method (destructor)
static void PyDiaSymbol_dealloc(PyDiaSymbol* self)
{
    if (self->diaSymbol)
    {
        delete self->diaSymbol;
    }
    Py_TYPE(self)->tp_free((PyObject*)self);
}

// __init__ method (constructor)
static int PyDiaSymbol_init(PyDiaSymbol* self, PyObject* args, PyObject* kwds)
{
    self->diaSymbol = new dia::Symbol();
    if (!self->diaSymbol)
    {
        PyErr_SetString(PyExc_MemoryError,
                        "Failed to create DiaSymbol object.");
        return -1;
    }
    return 0;
}

// Type object
PyTypeObject PyDiaSymbolType = {
    PyVarObject_HEAD_INIT(NULL, 0) "pydia.Symbol", // tp_name
    sizeof(PyDiaSymbol),                           // tp_basicsize
    0,                                             // tp_itemsize
    (destructor)PyDiaSymbol_dealloc,               // tp_dealloc
    0,                                             // tp_print
    0,                                             // tp_getattr
    0,                                             // tp_setattr
    0,                                             // tp_compare
    0,                                             // tp_repr
    0,                                             // tp_as_number
    0,                                             // tp_as_sequence
    0,                                             // tp_as_mapping
    0,                                             // tp_hash
    0,                                             // tp_call
    0,                                             // tp_str
    0,                                             // tp_getattro
    0,                                             // tp_setattro
    0,                                             // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                            // tp_flags
    "Symbol objects",                              // tp_doc
    0,                                             // tp_traverse
    0,                                             // tp_clear
    0,                                             // tp_richcompare
    0,                                             // tp_weaklistoffset
    0,                                             // tp_iter
    0,                                             // tp_iternext
    PyDiaSymbol_methods,                           // tp_methods
    0,                                             // tp_members
    0,                                             // tp_getset
    0,                                             // tp_base
    0,                                             // tp_dict
    0,                                             // tp_descr_get
    0,                                             // tp_descr_set
    0,                                             // tp_dictoffset
    0,                                             // tp_init
    0,                                             // tp_alloc
    0,                                             // tp_new
    0,                                             // tp_free
    0,                                             // tp_is_gc
    0,                                             // tp_bases
    0,                                             // tp_mro
    0,                                             // tp_cache
    0,                                             // tp_subclasses
    0,                                             // tp_weaklist
    0,                                             // tp_del
    0,                                             // tp_version_tag
};

// Define the methods
static PyObject* PyDiaSymbol_getName(PyDiaSymbol* self, PyObject*)
{
    dia::Symbol* symbol = reinterpret_cast<dia::Symbol*>(self->diaSymbol);
    std::wstring name = symbol->getName();
    return PyUnicode_FromWideChar(name.c_str(), name.length());
}

static PyObject* PyDiaSymbol_getOffset(PyDiaSymbol* self, PyObject*)
{
    dia::Symbol* symbol = reinterpret_cast<dia::Symbol*>(self->diaSymbol);
    LONG offset = symbol->getOffset();
    return PyLong_FromLong(offset);
}

static PyObject* PyDiaSymbol_getType(PyDiaSymbol* self, PyObject*)
{
    dia::Symbol* symbol = reinterpret_cast<dia::Symbol*>(self->diaSymbol);
    const auto& symbolType = symbol->getType();

    PyDiaSymbol* sym = PyObject_New(PyDiaSymbol, &PyDiaSymbolType);
    if (!sym)
    {
        return PyErr_NoMemory();
    }
    sym->diaSymbol = new dia::Symbol(symbolType);

    return reinterpret_cast<PyObject*>(sym);
}

static PyObject* PyDiaSymbol_getTypeName(PyDiaSymbol* self, PyObject*)
{
    dia::Symbol* symbol = reinterpret_cast<dia::Symbol*>(self->diaSymbol);
    std::wstring typeName = symbol->getTypeName();
    return PyUnicode_FromWideChar(typeName.c_str(), typeName.length());
}

static PyObject* PyDiaSymbol_getSymTag(PyDiaSymbol* self, PyObject*)
{
    dia::Symbol* symbol = reinterpret_cast<dia::Symbol*>(self->diaSymbol);
    enum SymTagEnum symTag = symbol->getSymTag();
    return PyLong_FromLong(static_cast<long>(symTag));
}

static PyObject* PyDiaSymbol_getBaseType(PyDiaSymbol* self, PyObject*)
{
    dia::Symbol* symbol = reinterpret_cast<dia::Symbol*>(self->diaSymbol);
    DWORD baseType = symbol->getBaseType();
    return PyLong_FromUnsignedLong(baseType);
}

static PyObject* PyDiaSymbol_getCount(PyDiaSymbol* self, PyObject*)
{
    dia::Symbol* symbol = reinterpret_cast<dia::Symbol*>(self->diaSymbol);
    DWORD count = symbol->getCount();
    return PyLong_FromUnsignedLong(count);
}

static PyObject* PyDiaSymbol_getLocationType(PyDiaSymbol* self, PyObject*)
{
    dia::Symbol* symbol = reinterpret_cast<dia::Symbol*>(self->diaSymbol);
    enum LocationType locationType = symbol->getLocationType();
    return PyLong_FromLong(static_cast<long>(locationType));
}

static PyObject* PyDiaSymbol_getBitPosition(PyDiaSymbol* self, PyObject*)
{
    dia::Symbol* symbol = reinterpret_cast<dia::Symbol*>(self->diaSymbol);
    DWORD bitPosition = symbol->getBitPosition();
    return PyLong_FromUnsignedLong(bitPosition);
}

static PyObject* PyDiaSymbol_getLength(PyDiaSymbol* self, PyObject*)
{
    dia::Symbol* symbol = reinterpret_cast<dia::Symbol*>(self->diaSymbol);
    ULONGLONG length = symbol->getLength();
    return PyLong_FromUnsignedLongLong(length);
}

static PyObject* PyDiaSymbol_isVolatile(PyDiaSymbol* self, PyObject*)
{
    dia::Symbol* symbol = reinterpret_cast<dia::Symbol*>(self->diaSymbol);
    bool volatileFlag = symbol->isVolatile();
    return PyBool_FromLong(static_cast<long>(volatileFlag));
}

static PyObject* PyDiaSymbol_isArray(PyDiaSymbol* self, PyObject*)
{
    dia::Symbol* symbol = reinterpret_cast<dia::Symbol*>(self->diaSymbol);
    bool isArray = symbol->isArray();
    return PyBool_FromLong(static_cast<long>(isArray));
}

static PyObject* PyDiaSymbol_isPointer(PyDiaSymbol* self, PyObject*)
{
    dia::Symbol* symbol = reinterpret_cast<dia::Symbol*>(self->diaSymbol);
    bool isPointer = symbol->isPointer();
    return PyBool_FromLong(static_cast<long>(isPointer));
}
