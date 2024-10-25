#pragma once
#include <DiaDataSource.h>
#include <Python.h>

// Define the Python DiaDataSource object
typedef struct
{
    PyObject_HEAD dia::DataSource* diaDataSource;  // Pointer to the C++ DiaDataSource object
} PyDiaDataSource;

extern PyTypeObject PyDiaDataSourceType;
