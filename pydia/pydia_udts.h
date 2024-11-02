#pragma once
#include <Python.h>
//
#include "pydia_register_classes.h"
//
#include <DiaUserDefinedTypeWrapper.h>

// In DIA2 SDK terms, Structs, Classes, Unions, Interfaces, and TaggedUnions are all UDTs (User Defined Types).
// Since the underlying DiaLib wrapper also does not distinguish between the five, we will use Python's incredible RTTI capabilities to implement the
// difrentation here. Why implement it at all you may ask? An average user actually DOES care whether something is a struct or a union, even if the
// 0's and 1's are the same.

#define XFOR_EACH_UDT_KIND(opperation)                                                                                                               \
    opperation(Struct);                                                                                                                              \
    opperation(Class);                                                                                                                               \
    opperation(Union);                                                                                                                               \
    opperation(Interface);                                                                                                                           \
    opperation(TaggedUnion);

typedef struct
{
    PyObject_HEAD;
    dia::UserDefinedType* diaUserDefinedType;  // Pointer to the C++ UserDefinedType object
    PYDIA_DERIVED_SYMBOL_ADDITIONAL_MEMBERS;
} PyDiaUdt_Abstract;

#define __TYPEDEF_UDT(udtName) typedef PyDiaUdt_Abstract PyDia##udtName;
XFOR_EACH_UDT_KIND(__TYPEDEF_UDT);

#define __EXTERN_DEF_UDT_TYPE_OBJECT(udtName) extern PyTypeObject PyDia##udtName##_Type;
XFOR_EACH_UDT_KIND(__EXTERN_DEF_UDT_TYPE_OBJECT);

PyObject* registerUdtPyClasses(PyObject* module);
REGISTER_PYCLASS_REGISTRATION_FUNCTION(registerUdtPyClasses)

PyObject* PyDiaUdt_FromSymbol(dia::Symbol&& symbol, PyDiaDataSource* dataSource);
