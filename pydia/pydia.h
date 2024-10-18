#pragma once
#include <Python.h>

extern PyTypeObject PyDiaDataSourceType;
extern PyTypeObject PyDiaSymbolType;

PyMODINIT_FUNC PyInit_pydia(void);
