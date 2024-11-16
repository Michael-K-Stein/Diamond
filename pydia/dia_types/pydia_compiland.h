#pragma once
#include <Python.h>
//
#include "pydia_symbol.h"
//
#include <DiaSymbol.h>

// Define the Python DiaCompiland object
typedef struct
{
    PyObject_HEAD;
    dia::Compiland* diaCompiland;  // Pointer to the C++ DiaCompilandType object
    PYDIA_DERIVED_SYMBOL_ADDITIONAL_MEMBERS;
} PyDiaCompiland;

extern PyTypeObject PyDiaCompiland_Type;
