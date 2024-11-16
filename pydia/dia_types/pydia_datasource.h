#pragma once
#include <DiaDataSource.h>
#include <Python.h>

// Forward decleration
struct PyDiaSymbol_s;

// Define the Python DiaDataSource object
typedef struct
{
    PyObject_HEAD;
    dia::DataSource* diaDataSource;  // Pointer to the C++ DiaDataSource object
    PyDiaSymbol_s* diaGlobalScope;   // Pointer to the Python Symbol which is the global scope of the data source
} PyDiaDataSource;

extern PyTypeObject PyDiaDataSource_Type;

PyDiaDataSource* PyDiaDataSource_FromInitializerList(PyObject* initializerList);
