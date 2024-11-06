#pragma once
#include <Python.h>
//
#include "pydia_symbol.h"
//
#include <SymbolTypes/DiaFunction.h>

// Define the Python DiaFunction object
typedef struct
{
    PyObject_HEAD;
    dia::Function* diaFunction;  // Pointer to the C++ DiaFunction object
    PYDIA_DERIVED_SYMBOL_ADDITIONAL_MEMBERS;
} PyDiaFunction;

extern PyTypeObject PyDiaFunction_Type;
