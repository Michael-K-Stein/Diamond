#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_data.h"
#include "pydia_enum.h"
#include "pydia_exceptions.h"
#include "pydia_generators.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_udts.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include <DiaUserDefinedTypeWrapper.h>


static PyObject* PyDiaUdt_Abstract_enumerateMembers(PyDiaUdt_Abstract* self);

#define __INIT_DEINIT_UDT(udtName)                                                                                                                   \
    static void PyDia##udtName##_dealloc(PyDia##udtName* self)                                                                                       \
    {                                                                                                                                                \
        if (self->diaUserDefinedType)                                                                                                                \
        {                                                                                                                                            \
            delete self->diaUserDefinedType;                                                                                                         \
        }                                                                                                                                            \
        Py_TYPE(self)->tp_free((PyObject*)self);                                                                                                     \
    }                                                                                                                                                \
                                                                                                                                                     \
    static int PyDia##udtName##_init(PyDia##udtName* self, PyObject* args, PyObject* kwds)                                                           \
    {                                                                                                                                                \
        self->diaUserDefinedType = new (std::nothrow) dia::UserDefinedType();                                                                        \
        if (!self->diaUserDefinedType)                                                                                                               \
        {                                                                                                                                            \
            PyErr_SetString(PyExc_MemoryError, "Failed to create " #udtName "object.");                                                              \
            return -1;                                                                                                                               \
        }                                                                                                                                            \
        return 0;                                                                                                                                    \
    }

XFOR_EACH_UDT_KIND(__INIT_DEINIT_UDT);

static PyMethodDef PyDiaUdt_Abstract_methods[] = {
    {"has_assignment_operator", (PyCFunction)PyDiaSymbol_hasAssignmentOperator, METH_NOARGS, "Check if the UDT has an assignment operator."},
    {"has_cast_operator", (PyCFunction)PyDiaSymbol_hasCastOperator, METH_NOARGS, "Check if the UDT has a cast operator."},
    {"has_constructor", (PyCFunction)PyDiaSymbol_hasConstructor, METH_NOARGS, "Retrieve the constructor of the UDT."},
    {"has_nested_types", (PyCFunction)PyDiaSymbol_hasNestedTypes, METH_NOARGS, "Check if the UDT has nested types."},
    {"has_overloaded_operator", (PyCFunction)PyDiaSymbol_hasOverloadedOperator, METH_NOARGS, "Check if the UDT has an overloaded operator."},
    {"is_const", (PyCFunction)PyDiaSymbol_isConst, METH_NOARGS, "Check if the UDT is const-qualified."},
    {"is_nested", (PyCFunction)PyDiaSymbol_isNested, METH_NOARGS, "Check if the UDT is nested."},
    {"is_packed", (PyCFunction)PyDiaSymbol_isPacked, METH_NOARGS, "Check if the UDT is packed."},
    {"is_scoped", (PyCFunction)PyDiaSymbol_isScoped, METH_NOARGS, "Check if the UDT is scoped."},
    {"is_unaligned", (PyCFunction)PyDiaSymbol_isUnaligned, METH_NOARGS, "Check if the UDT is unaligned."},
    {"is_volatile", (PyCFunction)PyDiaSymbol_isVolatile, METH_NOARGS, "Check if the UDT is volatile-qualified."},
    {"get_class_parent", (PyCFunction)PyDiaSymbol_getClassParent, METH_NOARGS, "Get the class in which this UDT declaration resides."},
    {"get_class_parent_id", (PyCFunction)PyDiaSymbol_getClassParentId, METH_NOARGS, "Get the class parent ID of the UDT."},
    {"get_length", (PyCFunction)PyDiaSymbol_getLength, METH_NOARGS, "Get the length of the UDT."},
    {"get_lexical_parent", (PyCFunction)PyDiaSymbol_getLexicalParent, METH_NOARGS, "Get the lexical parent of the UDT."},
    {"get_lexical_parent_id", (PyCFunction)PyDiaSymbol_getLexicalParentId, METH_NOARGS, "Get the lexical parent ID of the UDT."},
    {"get_name", (PyCFunction)PyDiaSymbol_getName, METH_NOARGS, "Get the name of the UDT."},
    {"get_sym_index_id", (PyCFunction)PyDiaSymbol_getSymIndexId, METH_NOARGS, "Get the symbol index ID of the UDT."},
    {"get_sym_tag", (PyCFunction)PyDiaSymbol_getSymTag, METH_NOARGS, "Get the symbol tag of the UDT."},
    {"get_udt_kind", (PyCFunction)PyDiaSymbol_getUdtKind, METH_NOARGS, "Get the kind of UDT."},
    {"get_virtual_table_shape", (PyCFunction)PyDiaSymbol_getVirtualTableShape, METH_NOARGS, "Get the virtual table shape of the UDT."},
    {"get_virtual_table_shape_id", (PyCFunction)PyDiaSymbol_getVirtualTableShapeId, METH_NOARGS, "Get the virtual table shape ID of the UDT."},

    {"enumerate_members", (PyCFunction)PyDiaUdt_Abstract_enumerateMembers, METH_NOARGS, "Iterate over all members (fields) of the UDT."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define the Python DiaEnum type object

#define __DEFINE_UDT_TYPE(udtName) PYDIA_SYMBOL_TYPE_DEFINITION(udtName, PyDiaUdt_Abstract_methods);
XFOR_EACH_UDT_KIND(__DEFINE_UDT_TYPE);

static PyObject* PyDiaUdt_Abstract_enumerateMembers(PyDiaUdt_Abstract* self)
{
    _ASSERT(NULL != self);
    _ASSERT(NULL != self->diaUserDefinedType);

    auto safeExecution = [&]() -> PyObject*
    {
        auto rawEnumerator = self->diaUserDefinedType->enumerateMembers();
        PyDiaDataGenerator* generator =
            (PyDiaDataGenerator*)PyDiaSymbolGenerator_create<dia::UserDefinedType, dia::Data>(self->diaUserDefinedType, std::move(rawEnumerator));
        if (!generator)
        {
            PyErr_SetString(PyExc_RuntimeError, "Failed to create generator.");
            return NULL;  // Failed to allocate generator
        }

        return (PyObject*)generator;
    };

    PYDIA_SAFE_TRY({ return safeExecution(); });
    Py_UNREACHABLE();
}

PyObject* registerUdtPyClasses(PyObject* module)
{
    if (!module)
    {
        return NULL;
    }
    XFOR_EACH_UDT_KIND(__REGISTER_PYDIA_CLASS);
    return module;
}

PyObject* PyDiaUdt_FromSymbol(dia::Symbol&& symbol)
{
    PyObject* pySymbol = NULL;
    switch (symbol.getUdtKind())
    {
    case UdtStruct:
    {

        auto pyStruct = PyObject_New(PyDiaStruct, &PyDiaStruct_Type);
        if (!pyStruct)
        {
            PyErr_SetString(PyExc_MemoryError, "Failed to create DiaStruct object.");
            return NULL;
        }
        pyStruct->diaUserDefinedType = new (std::nothrow) dia::Struct(static_cast<dia::Struct&>(symbol));
        pySymbol                     = reinterpret_cast<PyObject*>(pyStruct);
        break;
    }
    case UdtClass:
    {

        auto pyClass = PyObject_New(PyDiaClass, &PyDiaClass_Type);
        if (!pyClass)
        {
            PyErr_SetString(PyExc_MemoryError, "Failed to create DiaClass object.");
            return NULL;
        }
        pyClass->diaUserDefinedType = new (std::nothrow) dia::Class(static_cast<dia::Class&>(symbol));
        pySymbol                    = reinterpret_cast<PyObject*>(pyClass);
        break;
    }
    case UdtUnion:
    {

        auto pyUnion = PyObject_New(PyDiaUnion, &PyDiaUnion_Type);
        if (!pyUnion)
        {
            PyErr_SetString(PyExc_MemoryError, "Failed to create DiaUnion object.");
            return NULL;
        }
        pyUnion->diaUserDefinedType = new (std::nothrow) dia::Union(static_cast<dia::Union&>(symbol));
        pySymbol                    = reinterpret_cast<PyObject*>(pyUnion);
        break;
    }
    case UdtInterface:
    {

        auto pyInterface = PyObject_New(PyDiaInterface, &PyDiaInterface_Type);
        if (!pyInterface)
        {
            PyErr_SetString(PyExc_MemoryError, "Failed to create DiaInterface object.");
            return NULL;
        }
        pyInterface->diaUserDefinedType = new (std::nothrow) dia::Interface(static_cast<dia::Interface&>(symbol));
        pySymbol                        = reinterpret_cast<PyObject*>(pyInterface);
        break;
    }
    case UdtTaggedUnion:
    {
        auto pyTaggedUnion = PyObject_New(PyDiaTaggedUnion, &PyDiaTaggedUnion_Type);
        if (!pyTaggedUnion)
        {
            PyErr_SetString(PyExc_MemoryError, "Failed to create DiaTaggedUnion object.");
            return NULL;
        }
        pyTaggedUnion->diaUserDefinedType = new (std::nothrow) dia::TaggedUnion(static_cast<dia::TaggedUnion&>(symbol));
        pySymbol                          = reinterpret_cast<PyObject*>(pyTaggedUnion);
        break;
    }
    default:
        Py_UNREACHABLE();
        break;
    }

    if (!pySymbol)
    {
        PyErr_SetString(PyExc_MemoryError, "Failed to create specific UDTs object.");
        return NULL;
    }

    if (NULL == reinterpret_cast<PyDiaUdt_Abstract*>(pySymbol)->diaUserDefinedType)
    {
        PyErr_SetString(PyExc_MemoryError, "Failed to allocate specific UDT's internal state.");
        return NULL;
    }

    return pySymbol;
}
