#pragma once
#include <Python.h>
//
#include "pydia_symbol.h"
//
#include <SymbolTypes/DiaFunctionType.h>

// Define the Python DiaFunctionType object
typedef struct
{
    PyObject_HEAD;
    dia::FunctionType* diaFunctionType;  // Pointer to the C++ DiaFunctionType object
    PYDIA_DERIVED_SYMBOL_ADDITIONAL_MEMBERS;
} PyDiaFunctionType;

extern PyTypeObject PyDiaFunctionType_Type;
