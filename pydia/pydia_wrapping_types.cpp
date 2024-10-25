#include "pydia_wrapping_types.h"

PyObject* g_diaBasicTypeEnumWrappings = NULL;

PyObject* getDiaBasicTypeEnumWrappings() { return g_diaBasicTypeEnumWrappings; }

static PyObject* createDiaBasicTypeEnumWrappings(PyObject* module)
{
    if (NULL != g_diaBasicTypeEnumWrappings)
    {
        // Avoid duplicate initialization
        return NULL;
    }

    // Create a dictionary for BasicType constants
    g_diaBasicTypeEnumWrappings = PyDict_New();
    if (g_diaBasicTypeEnumWrappings == NULL)
    {
        return NULL;
    }

    // Add BasicType constants to the dictionary
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "NoType", PyLong_FromLong(0));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Void", PyLong_FromLong(1));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Char", PyLong_FromLong(2));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "WChar", PyLong_FromLong(3));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Int", PyLong_FromLong(6));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "UInt", PyLong_FromLong(7));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Float", PyLong_FromLong(8));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "BCD", PyLong_FromLong(9));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Bool", PyLong_FromLong(10));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Long", PyLong_FromLong(13));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "ULong", PyLong_FromLong(14));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Currency", PyLong_FromLong(25));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Date", PyLong_FromLong(26));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Variant", PyLong_FromLong(27));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Complex", PyLong_FromLong(28));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Bit", PyLong_FromLong(29));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "BSTR", PyLong_FromLong(30));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Hresult", PyLong_FromLong(31));
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Char16", PyLong_FromLong(32));  // char16_t
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Char32", PyLong_FromLong(33));  // char32_t
    PyDict_SetItemString(g_diaBasicTypeEnumWrappings, "Char8", PyLong_FromLong(34));   // char8_t

    // Set the BasicType dictionary as an attribute of the main module
    PyModule_AddObject(module, "BasicType", g_diaBasicTypeEnumWrappings);

    return module;
}

PyObject* createDiaEnumWrappings(PyObject* module)
{
    if (NULL == createDiaBasicTypeEnumWrappings(module))
    {
        return NULL;
    }

    return module;
}
