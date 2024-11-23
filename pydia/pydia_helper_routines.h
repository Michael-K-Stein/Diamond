#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>

// Windows includes
#include <oaidl.h>
#include <objbase.h>

#include <set>

// From C++ DiaLib
#include <AnyString.h>
#include <BstrWrapper.h>

// Pydia includes
#include "pydia_symbol.h"


// Helper function to convert Python string to AnyString

AnyString PyObjectToAnyString(PyObject* obj);
PyObject* PyObject_FromBstrWrapper(const BstrWrapper& bstrWrapper);
PyObject* PyObject_FromWstring(const std::wstring& string);
PyObject* PyObject_FromVariant(const VARIANT& variantValue);

template <typename T>
PyObject* PyObject_FromSymbolSet(const std::set<T>& s, PyDiaDataSource* dataSource)
{
    PyObject* pySet = PySet_New(NULL);
    if (NULL == pySet)
    {
        return NULL;  // PySet_New already sets an exception on failure
    }
    for (const auto& v : s)
    {
        dia::Symbol vCopy{v};
        PyObject* pyV = PyDiaSymbol_FromSymbol(std::move(vCopy), dataSource);

        if (NULL == pyV)
        {
            Py_DECREF(pySet);  // Cleanup before returning NULL
            return NULL;       // PyDiaSymbol_FromSymbol already sets an exception
        }
        if (0 > PySet_Add(pySet, pyV))
        {
            Py_DECREF(pyV);    // Decrement pyV before exiting
            Py_DECREF(pySet);  // Cleanup pySet before returning NULL
            return NULL;       // PySet_Add sets an exception on failure
        }
        Py_DECREF(pyV);  // PySet_Add increments the refcount; balance it here
    }
    return pySet;
}

void pydia_showDeprecationWarning(const char* warningMessage = "This function is deprecated and will be removed in a future release.");
