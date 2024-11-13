#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_exceptions.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_typedef.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include <SymbolTypes/DiaTypedef.h>

TRIVIAL_INIT_DEINIT(Typedef);

// Python method table for dia::Typedef
static PyMethodDef PyDiaTypedef_methods[] = {
    PyDiaSymbolMethodEntry_getModifierValues,

    {"get_base_type", (PyCFunction)PyDiaSymbol_getBaseType, METH_NOARGS, "Get the base type of the typedef."},
    {"get_class_parent", (PyCFunction)PyDiaSymbol_getClassParent, METH_NOARGS, "Get the class parent of the typedef."},
    {"get_class_parent_id", (PyCFunction)PyDiaSymbol_getClassParentId, METH_NOARGS, "Get the class parent ID of the typedef."},
    {"get_constructor", (PyCFunction)PyDiaSymbol_hasConstructor, METH_NOARGS, "Get the constructor of the typedef."},
    {"get_const_type", (PyCFunction)PyDiaSymbol_isConst, METH_NOARGS, "Check if the typedef is const-qualified."},
    {"has_assignment_operator", (PyCFunction)PyDiaSymbol_hasAssignmentOperator, METH_NOARGS, "Check if the typedef has an assignment operator."},
    {"has_cast_operator", (PyCFunction)PyDiaSymbol_hasCastOperator, METH_NOARGS, "Check if the typedef has a cast operator."},
    {"has_nested_types", (PyCFunction)PyDiaSymbol_hasNestedTypes, METH_NOARGS, "Check if the typedef has nested types."},
    {"get_length", (PyCFunction)PyDiaSymbol_getLength, METH_NOARGS, "Get the length of the typedef."},
    {"get_lexical_parent", (PyCFunction)PyDiaSymbol_getLexicalParent, METH_NOARGS, "Get the lexical parent of the typedef."},
    {"get_lexical_parent_id", (PyCFunction)PyDiaSymbol_getLexicalParentId, METH_NOARGS, "Get the lexical parent ID of the typedef."},
    {"get_name", (PyCFunction)PyDiaSymbol_getName, METH_NOARGS, "Get the name of the typedef."},
    {"get_nested", (PyCFunction)PyDiaSymbol_isNested, METH_NOARGS, "Get the nested symbol of the typedef."},
    {"get_overloaded_operator", (PyCFunction)PyDiaSymbol_hasOverloadedOperator, METH_NOARGS, "Get the overloaded operator for the typedef."},
    {"is_packed", (PyCFunction)PyDiaSymbol_isPacked, METH_NOARGS, "Check if the typedef is packed."},
    {"is_reference", (PyCFunction)PyDiaSymbol_isReference, METH_NOARGS, "Check if the typedef is a reference."},
    {"is_scoped", (PyCFunction)PyDiaSymbol_isScoped, METH_NOARGS, "Check if the typedef is scoped."},
    {"get_sym_index_id", (PyCFunction)PyDiaSymbol_getSymIndexId, METH_NOARGS, "Get the symbol index ID of the typedef."},
    {"get_sym_tag", (PyCFunction)PyDiaSymbol_getSymTag, METH_NOARGS, "Get the symbol tag of the typedef."},
    {"get_type", (PyCFunction)PyDiaSymbol_getType, METH_NOARGS, "Get the type of the typedef."},
    {"get_type_id", (PyCFunction)PyDiaSymbol_getTypeId, METH_NOARGS, "Get the type ID of the typedef."},
    {"get_udt_kind", (PyCFunction)PyDiaSymbol_getUdtKind, METH_NOARGS, "Get the UDT kind of the typedef."},
    {"is_unaligned", (PyCFunction)PyDiaSymbol_isUnaligned, METH_NOARGS, "Check if the typedef is unaligned."},
    {"get_virtual_table_shape", (PyCFunction)PyDiaSymbol_getVirtualTableShape, METH_NOARGS, "Get the virtual table shape of the typedef."},
    {"get_virtual_table_shape_id", (PyCFunction)PyDiaSymbol_getVirtualTableShapeId, METH_NOARGS, "Get the virtual table shape ID of the typedef."},
    {"is_volatile", (PyCFunction)PyDiaSymbol_isVolatile, METH_NOARGS, "Check if the typedef is volatile-qualified."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define the Python DiaEnum type object

PYDIA_SYMBOL_TYPE_DEFINITION(Typedef, PyDiaTypedef_methods);

TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(Typedef);
