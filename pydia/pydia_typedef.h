#pragma once
#include <Python.h>
//
#include "pydia_symbol.h"
//
#include <SymbolTypes/DiaTypedef.h>

// Define the Python DiaTypedef object
typedef struct
{
    PyObject_HEAD;
    dia::Typedef* diaTypedef;  // Typedef to the C++ DiaTypedef object
    PYDIA_DERIVED_SYMBOL_ADDITIONAL_MEMBERS;
} PyDiaTypedef;

extern PyTypeObject PyDiaTypedef_Type;
