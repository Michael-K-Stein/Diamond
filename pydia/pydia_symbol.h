#pragma once
#include <Python.h>
//
#include <DiaSymbol.h>

// Define the Python DiaSymbolType object
// This is much much to permissive and abstract to expose to Python users.
// The PyDiaSymbol MUST be wrapped with user friendly and intuitive ad-hoc types.
typedef struct
{
    PyObject_HEAD dia::Symbol* diaSymbol;  // Pointer to the C++ DiaSymbolType object
} PyDiaSymbol;

extern PyTypeObject PyDiaSymbol_Type;
