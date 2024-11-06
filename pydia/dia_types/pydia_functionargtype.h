#pragma once
#include <Python.h>
//
#include "pydia_symbol.h"
//
#include <SymbolTypes/DiaFunctionArgType.h>

// Define the Python DiaFunctionArgType object
typedef struct
{
    PyObject_HEAD;
    dia::FunctionArgType* diaFunctionArgType;  // Pointer to the C++ DiaFunctionArgType object
    PYDIA_DERIVED_SYMBOL_ADDITIONAL_MEMBERS;
} PyDiaFunctionArgType;

extern PyTypeObject PyDiaFunctionArgType_Type;
