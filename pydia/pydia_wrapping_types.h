#pragma once
#include <Python.h>

PyObject* createDiaEnumWrappings(PyObject* module);

PyObject* getDiaBasicTypeEnumWrappings();
PyObject* getDiaLocationTypeEnumWrappings();
PyObject* getDiaDataKindEnumWrappings();
PyObject* getDiaUdtKindEnumWrappings();
PyObject* getDiaAccessModifierEnumWrappings();
