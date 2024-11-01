#pragma once
#include <Python.h>
//
#include "pydia_symbol.h"
//
#include <SymbolTypes/DiaArray.h>

// Define the Python DiaArray object
typedef struct
{
    PyObject_HEAD dia::Array* diaArray;  // Array to the C++ DiaArray object
} PyDiaArray;

extern PyTypeObject PyDiaArray_Type;
