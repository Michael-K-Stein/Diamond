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

PyObject* BstrWrapperToPyObject(const BstrWrapper& bstrWrapper);

PyObject* VariantToPyObject(const VARIANT& variantValue);
