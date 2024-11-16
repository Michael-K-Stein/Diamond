#pragma once
#include <Python.h>
//
#include "pydia_symbol.h"
//
#include <SymbolTypes/DiaAnnotation.h>

// Define the Python DiaAnnotation object
typedef struct
{
    PyObject_HEAD;
    dia::Annotation* diaAnnotation;  // Pointer to the C++ DiaAnnotation object
    PYDIA_DERIVED_SYMBOL_ADDITIONAL_MEMBERS;
} PyDiaAnnotation;

extern PyTypeObject PyDiaAnnotation_Type;
