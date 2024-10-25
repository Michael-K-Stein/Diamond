#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else


#define XFOR_TRIVIAL_PYDIA_ERRORS(opperation)                                                                                                        \
    opperation(InvalidUsage);                                                                                                                        \
    opperation(NotFound);

#define __DECLARE_TRIVIAL_PYDIA_ERROR(pureName) extern PyObject* PyDia##pureName##Error;


extern PyObject* PyDiaError;
XFOR_TRIVIAL_PYDIA_ERRORS(__DECLARE_TRIVIAL_PYDIA_ERROR);

int pydia_initialize_pydiaerrors(PyObject* module);
