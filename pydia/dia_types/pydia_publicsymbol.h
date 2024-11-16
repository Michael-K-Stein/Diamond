#pragma once
#include <Python.h>
//
#include "pydia_symbol.h"
//
#include <SymbolTypes/DiaPublicSymbol.h>

// Define the Python DiaPublicSymbol object
typedef struct
{
    PyObject_HEAD;
    dia::PublicSymbol* diaPublicSymbol;  // Pointer to the C++ DiaPublicSymbol object
    PYDIA_DERIVED_SYMBOL_ADDITIONAL_MEMBERS;
} PyDiaPublicSymbol;

extern PyTypeObject PyDiaPublicSymbol_Type;
