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
PyObject* PyObject_FromWstring(const std::wstring& string);
PyObject* PyObject_FromVariant(const VARIANT& variantValue);
void pydia_showDeprecationWarning(const char* warningMessage = "This function is deprecated and will be removed in a future release.");
