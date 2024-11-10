#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>

// Windows includes
#include <oaidl.h>
#include <objbase.h>

// From C++ DiaLib
#include <AnyString.h>
#include <BstrWrapper.h>

// Helper function to convert Python string to AnyString

AnyString PyObjectToAnyString(PyObject* obj);

PyObject* PyObject_FromBstrWrapper(const BstrWrapper& bstrWrapper);

PyObject* PyObject_FromVariant(const VARIANT& variantValue);
