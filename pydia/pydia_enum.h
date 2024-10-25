#pragma once
#include <Python.h>
#include <SymbolTypes/DiaEnum.h>

// Define the Python DiaEnumType object
typedef struct
{
    PyObject_HEAD dia::Enum* diaEnum;  // Pointer to the C++ DiaEnumType object
} PyDiaEnum;

extern PyTypeObject PyDiaEnum_Type;
