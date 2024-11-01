#pragma once
#include <Python.h>
//
#include "pydia_symbol.h"
//
#include <SymbolTypes/DiaBaseType.h>

// Define the Python DiaBaseType object
typedef struct
{
    PyObject_HEAD dia::BaseType* diaBaseType;  // Pointer to the C++ DiaBaseType object
} PyDiaBaseType;

extern PyTypeObject PyDiaBaseType_Type;
