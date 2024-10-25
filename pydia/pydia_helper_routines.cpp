#include "pydia_helper_routines.h"

// Helper function to convert Python string to std::wstring
AnyString PyObjectToAnyString(PyObject* obj)
{
    if (PyUnicode_Check(obj))
    {
        Py_ssize_t size           = 0;
        const wchar_t* unicodeStr = PyUnicode_AsWideCharString(obj, &size);
        if (!unicodeStr)
        {
            PyErr_SetString(PyExc_ValueError, "Failed to convert Unicode string to wide character.");
            return {};
        }
        std::wstring result(unicodeStr, size);
        PyMem_Free((void*)unicodeStr);
        return result;
    }
    else if (PyBytes_Check(obj))
    {
        // Convert bytes to a C string (char*)
        const char* bytesString = PyBytes_AsString(obj);
        if (!bytesString)
        {
            PyErr_SetString(PyExc_ValueError, "Failed to convert bytes to string.");
            return {};
        }
        // Convert char* to wchar_t* using MultiByteToWideChar
        int len = MultiByteToWideChar(CP_UTF8, 0, bytesString, -1, NULL, 0);
        if (len <= 0)
        {
            PyErr_SetString(PyExc_ValueError, "Failed to convert bytes to wide character.");
            return {};
        }

        wchar_t* widePath = (wchar_t*)PyMem_Malloc(len * sizeof(wchar_t));
        if (!widePath)
        {
            PyErr_SetString(PyExc_MemoryError, "Failed to allocate memory for wide character conversion.");
            return {};
        }
        int len2 = MultiByteToWideChar(CP_UTF8, 0, bytesString, -1, widePath, len);
        _ASSERT(len == len2);
        return AnyString{widePath};
    }

    PyErr_SetString(PyExc_TypeError, "Invalid string!");
    return {};
}

PyObject* BstrWrapperToPyObject(const BstrWrapper& bstrWrapper) { return PyUnicode_FromWideChar(bstrWrapper.c_str(), bstrWrapper.length()); }
