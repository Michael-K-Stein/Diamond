#include "pydia_helper_routines.h"
#include "pydia_symbol.h"
#include <DiaSymbol.h>
#include <datetime.h>     // For PyDateTime_FromDateAndTime
#include <propvarutil.h>  // For VariantToDouble
#include <set>

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

PyObject* PyObject_FromBstrWrapper(const BstrWrapper& bstrWrapper) { return PyUnicode_FromWideChar(bstrWrapper.c_str(), bstrWrapper.length()); }

PyObject* PyObject_FromWstring(const std::wstring& string) { return PyUnicode_FromWideChar(string.c_str(), string.length()); }

PyObject* PyObject_FromVariant(const VARIANT& variantValue)
{
    switch (variantValue.vt)
    {
    case VT_I4:  // LONG
        return PyLong_FromLong(variantValue.lVal);

    case VT_I2:  // SHORT
        return PyLong_FromLong(variantValue.iVal);

    case VT_UI1:  // BYTE
        return PyLong_FromUnsignedLong(variantValue.bVal);

    case VT_I1:  // CHAR (signed byte)
        return PyLong_FromLong(variantValue.cVal);

    case VT_UI2:  // USHORT
        return PyLong_FromUnsignedLong(variantValue.uiVal);

    case VT_R4:  // FLOAT
        return PyFloat_FromDouble(static_cast<double>(variantValue.fltVal));

    case VT_R8:  // DOUBLE
        return PyFloat_FromDouble(variantValue.dblVal);

    case VT_BOOL:  // VARIANT_BOOL (True or False)
        return PyBool_FromLong(variantValue.boolVal != VARIANT_FALSE);

    case VT_BSTR:  // BSTR (string)
    {
        if (!variantValue.bstrVal)
        {
            Py_RETURN_NONE;  // Handle NULL BSTR as None
        }
        PyObject* pyStr = PyUnicode_FromWideChar(variantValue.bstrVal, SysStringLen(variantValue.bstrVal));
        SysFreeString(variantValue.bstrVal);  // Free the BSTR
        return pyStr;
    }

    case VT_I8:  // LONGLONG
        return PyLong_FromLongLong(variantValue.llVal);

    case VT_UI4:  // ULONG
        return PyLong_FromUnsignedLong(variantValue.ulVal);

    case VT_UI8:  // ULONGLONG
        return PyLong_FromUnsignedLongLong(variantValue.ullVal);

    case VT_INT:  // INT
        return PyLong_FromLong(variantValue.intVal);

    case VT_UINT:  // UINT
        return PyLong_FromUnsignedLong(variantValue.uintVal);

    case VT_DECIMAL:  // DECIMAL
    {
        double decimalValue;
        if (VariantToDouble(variantValue, &decimalValue) == S_OK)  // Convert DECIMAL to double
        {
            return PyFloat_FromDouble(decimalValue);
        }
        PyErr_SetString(PyExc_TypeError, "Failed to convert DECIMAL to double.");
        return NULL;
    }

    case VT_DATE:  // DATE (COM date type)
    {
        // Convert DATE (OLE Automation date) to Python datetime
        SYSTEMTIME sysTime;
        if (VariantTimeToSystemTime(variantValue.date, &sysTime))
        {
            return PyDateTime_FromDateAndTime(sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond,
                                              sysTime.wMilliseconds * 1000);
        }
        PyErr_SetString(PyExc_ValueError, "Invalid DATE value in VARIANT.");
        return NULL;
    }

    case VT_EMPTY:  // No value
    case VT_NULL:   // SQL-style NULL
        Py_RETURN_NONE;

    case VT_VARIANT | VT_BYREF:  // Reference to another VARIANT
        if (variantValue.pvarVal)
        {
            return PyObject_FromVariant(*variantValue.pvarVal);
        }
        Py_RETURN_NONE;

    case VT_ARRAY:  // SAFEARRAY
        PyErr_SetString(PyExc_NotImplementedError, "SAFEARRAY handling is not yet implemented.");
        return NULL;

    case VT_UNKNOWN:   // IUnknown pointer
    case VT_DISPATCH:  // IDispatch pointer
        PyErr_SetString(PyExc_NotImplementedError, "COM object handling is not yet implemented.");
        return NULL;

    default:
        PyErr_Format(PyExc_TypeError, "Unsupported data type '%hu' in VARIANT.", variantValue.vt);
        return NULL;
    }

    Py_UNREACHABLE();
}

void pydia_showDeprecationWarning(const char* warningMessage)
{
    if (PyErr_WarnEx(PyExc_DeprecationWarning, warningMessage, 1) < 0)
    {
        // Ignore error in raising warning
        return;
    }
}