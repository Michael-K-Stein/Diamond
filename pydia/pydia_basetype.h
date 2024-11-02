#pragma once
#include <Python.h>
//
#include "pydia_symbol.h"
//
#include <SymbolTypes/DiaBaseType.h>

// Define the Python DiaBaseType object
typedef struct
{
    PyObject_HEAD;
    dia::BaseType* diaBaseType;  // Pointer to the C++ DiaBaseType object
    PYDIA_DERIVED_SYMBOL_ADDITIONAL_MEMBERS;
} PyDiaBaseType;

extern PyTypeObject PyDiaBaseType_Type;
