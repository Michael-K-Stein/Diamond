#pragma once
#include <Python.h>
//
#include "pydia_generators.h"
#include <SymbolTypes/DiaData.h>

// Define the Python DiaDataType object
typedef struct
{
    PyObject_HEAD dia::Data* diaData;  // Pointer to the C++ DiaDataType object
} PyDiaData;

extern PyTypeObject PyDiaData_Type;
