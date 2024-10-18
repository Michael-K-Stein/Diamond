#pragma once
#include <DiaSymbol.h>
#include <Python.h>

// Define the Python DiaSymbol object
typedef struct
{
    PyObject_HEAD dia::Symbol* diaSymbol; // Pointer to the C++ DiaSymbol object
} PyDiaSymbol;
extern PyTypeObject PyDiaSymbolType;