#pragma once
#include <Python.h>
//
#include "pydia_symbol.h"
//
#include <SymbolTypes/DiaEnum.h>

// Define the Python DiaEnumType object
typedef struct
{
    PyObject_HEAD;
    dia::Enum* diaEnum;  // Pointer to the C++ DiaEnumType object
    PYDIA_DERIVED_SYMBOL_ADDITIONAL_MEMBERS;
} PyDiaEnum;

extern PyTypeObject PyDiaEnum_Type;
