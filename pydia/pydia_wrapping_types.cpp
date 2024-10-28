#include "pydia_wrapping_types.h"

PyObject* g_diaBasicTypeEnumWrappings    = NULL;
PyObject* g_diaLocationTypeEnumWrappings = NULL;
PyObject* g_diaDataKindEnumWrappings     = NULL;
PyObject* g_diaUdtKindEnumWrappings      = NULL;

PyObject* getDiaBasicTypeEnumWrappings() { return g_diaBasicTypeEnumWrappings; }

PyObject* getDiaLocationTypeEnumWrappings() { return g_diaLocationTypeEnumWrappings; }

PyObject* getDiaDataKindEnumWrappings() { return g_diaDataKindEnumWrappings; }

PyObject* getDiaUdtKindEnumWrappings() { return g_diaUdtKindEnumWrappings; }

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

static PyObject* createDiaLocationTypeEnumWrappings(PyObject* module)
{
    if (g_diaLocationTypeEnumWrappings != NULL) return NULL;

    g_diaLocationTypeEnumWrappings = PyDict_New();
    if (g_diaLocationTypeEnumWrappings == NULL) return NULL;

    // Add LocationType constants to the dictionary
    PyDict_SetItemString(g_diaLocationTypeEnumWrappings, "Null", PyLong_FromLong(0));
    PyDict_SetItemString(g_diaLocationTypeEnumWrappings, "Static", PyLong_FromLong(1));
    PyDict_SetItemString(g_diaLocationTypeEnumWrappings, "TLS", PyLong_FromLong(2));
    PyDict_SetItemString(g_diaLocationTypeEnumWrappings, "RegRel", PyLong_FromLong(3));
    PyDict_SetItemString(g_diaLocationTypeEnumWrappings, "ThisRel", PyLong_FromLong(4));
    PyDict_SetItemString(g_diaLocationTypeEnumWrappings, "Enregistered", PyLong_FromLong(5));
    PyDict_SetItemString(g_diaLocationTypeEnumWrappings, "BitField", PyLong_FromLong(6));
    PyDict_SetItemString(g_diaLocationTypeEnumWrappings, "Slot", PyLong_FromLong(7));
    PyDict_SetItemString(g_diaLocationTypeEnumWrappings, "IlRel", PyLong_FromLong(8));
    PyDict_SetItemString(g_diaLocationTypeEnumWrappings, "MetaData", PyLong_FromLong(9));
    PyDict_SetItemString(g_diaLocationTypeEnumWrappings, "Constant", PyLong_FromLong(10));
    PyDict_SetItemString(g_diaLocationTypeEnumWrappings, "RegRelAliasIndir", PyLong_FromLong(11));
    PyDict_SetItemString(g_diaLocationTypeEnumWrappings, "LocTypeMax", PyLong_FromLong(12));  // TODO: Do we really need this?

    PyModule_AddObject(module, "LocationType", g_diaLocationTypeEnumWrappings);
    return module;
}

static PyObject* createDiaDataKindEnumWrappings(PyObject* module)
{
    if (g_diaDataKindEnumWrappings != NULL) return NULL;

    g_diaDataKindEnumWrappings = PyDict_New();
    if (g_diaDataKindEnumWrappings == NULL) return NULL;

    // Add DataKind constants to the dictionary
    PyDict_SetItemString(g_diaDataKindEnumWrappings, "Unknown", PyLong_FromLong(0));
    PyDict_SetItemString(g_diaDataKindEnumWrappings, "Local", PyLong_FromLong(1));
    PyDict_SetItemString(g_diaDataKindEnumWrappings, "StaticLocal", PyLong_FromLong(2));
    PyDict_SetItemString(g_diaDataKindEnumWrappings, "Param", PyLong_FromLong(3));
    PyDict_SetItemString(g_diaDataKindEnumWrappings, "ObjectPtr", PyLong_FromLong(4));
    PyDict_SetItemString(g_diaDataKindEnumWrappings, "FileStatic", PyLong_FromLong(5));
    PyDict_SetItemString(g_diaDataKindEnumWrappings, "Global", PyLong_FromLong(6));
    PyDict_SetItemString(g_diaDataKindEnumWrappings, "Member", PyLong_FromLong(7));
    PyDict_SetItemString(g_diaDataKindEnumWrappings, "StaticMember", PyLong_FromLong(8));
    PyDict_SetItemString(g_diaDataKindEnumWrappings, "Constant", PyLong_FromLong(9));

    PyModule_AddObject(module, "DataKind", g_diaDataKindEnumWrappings);
    return module;
}

static PyObject* createDiaUdtKindEnumWrappings(PyObject* module)
{
    if (g_diaUdtKindEnumWrappings != NULL) return NULL;

    g_diaUdtKindEnumWrappings = PyDict_New();
    if (g_diaUdtKindEnumWrappings == NULL) return NULL;

    // Add UdtKind constants to the dictionary
    PyDict_SetItemString(g_diaUdtKindEnumWrappings, "Struct", PyLong_FromLong(0));
    PyDict_SetItemString(g_diaUdtKindEnumWrappings, "Class", PyLong_FromLong(1));
    PyDict_SetItemString(g_diaUdtKindEnumWrappings, "Union", PyLong_FromLong(2));
    PyDict_SetItemString(g_diaUdtKindEnumWrappings, "Interface", PyLong_FromLong(3));
    PyDict_SetItemString(g_diaUdtKindEnumWrappings, "TaggedUnion", PyLong_FromLong(4));

    PyModule_AddObject(module, "UdtKind", g_diaUdtKindEnumWrappings);
    return module;
}

PyObject* createDiaEnumWrappings(PyObject* module)
{
    if (createDiaBasicTypeEnumWrappings(module) == NULL || createDiaLocationTypeEnumWrappings(module) == NULL ||
        createDiaDataKindEnumWrappings(module) == NULL || createDiaUdtKindEnumWrappings(module) == NULL)
    {
        return NULL;
    }

    return module;
}
