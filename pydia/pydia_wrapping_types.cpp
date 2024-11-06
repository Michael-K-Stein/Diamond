#include "pydia_wrapping_types.h"
#include <DiaSymbolFuncs.h>
#include <DiaTypeResolution.h>
#include <cvconst.h>
#include <pydia_exceptions.h>

PyObject* g_diaBasicTypeEnumWrappings         = NULL;
PyObject* g_diaLocationTypeEnumWrappings      = NULL;
PyObject* g_diaDataKindEnumWrappings          = NULL;
PyObject* g_diaUdtKindEnumWrappings           = NULL;
PyObject* g_diaAccessModifierEnumWrappings    = NULL;
PyObject* g_diaCallingConventionEnumWrappings = NULL;

PyObject* getDiaBasicTypeEnumWrappings() { return g_diaBasicTypeEnumWrappings; }

using EnumWrapperGetterFunction = PyObject* (*)();

template <typename EnumT>
static PyObject* PyDiaEnumObject_FromEnumValue(EnumWrapperGetterFunction getterFunction, const EnumT& enumValue)
{
    auto safeExecution = [&]() -> PyObject*
    {
        PyObject* enumEntryInstance = PyObject_CallFunction(getterFunction(), "(i)", enumValue);

        Py_XINCREF(enumEntryInstance);  // Increase reference count to return a new reference
        return enumEntryInstance;
    };

    PYDIA_SAFE_TRY({ return safeExecution(); });
    Py_UNREACHABLE();
}

PyObject* PyDiaBasicType_FromBasicType(enum BasicType basicType) { return PyDiaEnumObject_FromEnumValue(getDiaBasicTypeEnumWrappings, basicType); }

static PyObject* getDiaLocationTypeEnumWrappings() { return g_diaLocationTypeEnumWrappings; }

PyObject* PyDiaLocationType_FromLocationType(enum LocationType v) { return PyDiaEnumObject_FromEnumValue(getDiaLocationTypeEnumWrappings, v); }

static PyObject* getDiaDataKindEnumWrappings() { return g_diaDataKindEnumWrappings; }

PyObject* PyDiaDataKind_FromDataKind(enum DataKind v) { return PyDiaEnumObject_FromEnumValue(getDiaDataKindEnumWrappings, v); }

static PyObject* getDiaUdtKindEnumWrappings() { return g_diaUdtKindEnumWrappings; }

PyObject* PyDiaUdtKind_FromUdtKind(enum UdtKind v) { return PyDiaEnumObject_FromEnumValue(getDiaUdtKindEnumWrappings, v); }

static PyObject* getDiaAccessModifierEnumWrappings() { return g_diaAccessModifierEnumWrappings; }

PyObject* PyDiaAccessModifier_FromAccessModifier(enum AccessModifier v)
{
    return PyDiaEnumObject_FromEnumValue(getDiaAccessModifierEnumWrappings, v);
}

static PyObject* getDiaCallingConventionEnumWrappings() { return g_diaCallingConventionEnumWrappings; }

PyObject* PyDiaCallingConvention_FromCallingConvention(dia::CvCall callingConvention)
{
    return PyDiaEnumObject_FromEnumValue(getDiaCallingConventionEnumWrappings, callingConvention);
}

static PyObject* createEnumObject(PyObject* module, const char* name, std::initializer_list<std::pair<const char*, int>> items)
{
    PyObject* pyEnumDict = PyDict_New();
    if (!pyEnumDict)
    {
        return NULL;
    }

    for (auto& item : items)
    {
        PyDict_SetItemString(pyEnumDict, item.first, PyLong_FromLong(item.second));
    }

    PyObject* pyEnumModule = PyImport_ImportModule("enum");
    if (pyEnumModule == NULL)
    {
        Py_CLEAR(pyEnumDict);
    }

    PyObject* pyEnumType = PyObject_CallMethod(pyEnumModule, "IntEnum", "sO", name, pyEnumDict);

    Py_CLEAR(pyEnumDict);
    Py_CLEAR(pyEnumModule);

#if 0
    // Create a new PyTypeObject for the enum
    PyTypeObject* pyEnumType = (PyTypeObject*)PyType_Type.tp_alloc(&PyType_Type, 0);
    if (!pyEnumType)
    {
        Py_DECREF(pyEnumDict);
        return NULL;
    }

    pyEnumType->tp_name      = name;
    pyEnumType->tp_basicsize = sizeof(PyObject);
    pyEnumType->tp_flags     = Py_TPFLAGS_DEFAULT;
    pyEnumType->tp_dict      = pyEnumDict;

    // Finalize the type so it can be used as a proper Python object
    if (PyType_Ready(pyEnumType) < 0)
    {
        Py_DECREF(pyEnumDict);
        Py_DECREF(pyEnumType);
        return NULL;
    }
    Py_INCREF(pyEnumType);
#endif

    PyModule_AddObject(module, name, (PyObject*)pyEnumType);
    return (PyObject*)pyEnumType;
}

PyObject* createDiaEnumWrappings(PyObject* module)
{
    if (NULL ==
        (g_diaBasicTypeEnumWrappings = createEnumObject(
             module, "BasicType",
             {{"NoType", btNoType}, {"Void", btVoid},       {"Char", btChar},       {"WChar", btWChar}, {"Int", btInt},     {"UInt", btUInt},
              {"Float", btFloat},   {"BCD", btBCD},         {"Bool", btBool},       {"Long", btLong},   {"ULong", btULong}, {"Currency", btCurrency},
              {"Date", btDate},     {"Variant", btVariant}, {"Complex", btComplex}, {"Bit", btBit},     {"BSTR", btBSTR},   {"Hresult", btHresult},
              {"Char16", btChar16}, {"Char32", btChar32},   {"Char8", btChar8}})))
    {
        return NULL;
    }

    if (NULL == (g_diaLocationTypeEnumWrappings = createEnumObject(module, "LocationType",
                                                                   {{"Null", LocIsNull},
                                                                    {"Static", LocIsStatic},
                                                                    {"TLS", LocIsTLS},
                                                                    {"RegRel", LocIsRegRel},
                                                                    {"ThisRel", LocIsThisRel},
                                                                    {"Enregistered", LocIsEnregistered},
                                                                    {"BitField", LocIsBitField},
                                                                    {"Slot", LocIsSlot},
                                                                    {"IlRel", LocIsIlRel},
                                                                    {"MetaData", LocInMetaData},
                                                                    {"Constant", LocIsConstant},
                                                                    {"RegRelAliasIndir", LocIsRegRelAliasIndir},
                                                                    {"LocTypeMax", LocTypeMax}})))
    {
        return NULL;
    }


    if (NULL == (g_diaDataKindEnumWrappings = createEnumObject(module, "DataKind",
                                                               {{"Unknown", DataIsUnknown},
                                                                {"Local", DataIsLocal},
                                                                {"StaticLocal", DataIsStaticLocal},
                                                                {"Param", DataIsParam},
                                                                {"ObjectPtr", DataIsObjectPtr},
                                                                {"FileStatic", DataIsFileStatic},
                                                                {"Global", DataIsGlobal},
                                                                {"Member", DataIsMember},
                                                                {"StaticMember", DataIsStaticMember},
                                                                {"Constant", DataIsConstant}})))
    {
        return NULL;
    }

    if (NULL ==
        (g_diaUdtKindEnumWrappings = createEnumObject(
             module, "UdtKind",
             {{"Struct", UdtStruct}, {"Class", UdtClass}, {"Union", UdtUnion}, {"Interface", UdtInterface}, {"TaggedUnion", UdtTaggedUnion}})))
    {
        return NULL;
    }

    if (NULL == (g_diaAccessModifierEnumWrappings = createEnumObject(module, "AccessModifier",
                                                                     {{"Private", static_cast<int>(dia::AccessModifier::Private)},
                                                                      {"Public", static_cast<int>(dia::AccessModifier::Public)},
                                                                      {"Protected", static_cast<int>(dia::AccessModifier::Protected)}})))
    {
        return NULL;
    }

    return module;
}
