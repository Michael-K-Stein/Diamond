#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
//
#include <pydia_symbol.h>


PyObject* PyDiaModule_resolveTypeName(PyObject* module, PyObject* args);
static PyMethodDef PyDiaModuleMethodEntry_resolveTypeName = {
    "resolve_type_name", (PyCFunction)PyDiaModule_resolveTypeName, METH_VARARGS,
    "Returns a C-style name as closely resembling the source code of the Symbol as possible."};
