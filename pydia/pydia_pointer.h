#pragma once
#include <Python.h>
//
#include "pydia_symbol.h"
//
#include <SymbolTypes/DiaPointer.h>

// Define the Python DiaPointer object
typedef struct
{
    PyObject_HEAD;
    dia::Pointer* diaPointer;  // Pointer to the C++ DiaPointer object
    PYDIA_DERIVED_SYMBOL_ADDITIONAL_MEMBERS;
} PyDiaPointer;

extern PyTypeObject PyDiaPointer_Type;
