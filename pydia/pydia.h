#pragma once
#include "pydia_classes.h"
#include <Python.h>

#define __DEFINE_EXTERN_PYDIA_CLASS(className) extern PyTypeObject PyDia##className##_Type;
XFOR_EACH_PYDIA_CLASS(__DEFINE_EXTERN_PYDIA_CLASS);

PyMODINIT_FUNC PyInit_pydia(void);
