#pragma once
#include <Python.h>

#include <DiaSymbolFuncs.h>

PyObject* createDiaEnumWrappings(PyObject* module);

PyObject* PyDiaBasicType_FromBasicType(enum BasicType basicType);
PyObject* PyDiaCallingConvention_FromCallingConvention(dia::CvCall callingConvention);
PyObject* PyDiaAccessModifier_FromAccessModifier(enum AccessModifier v);
PyObject* PyDiaUdtKind_FromUdtKind(enum UdtKind v);
PyObject* PyDiaDataKind_FromDataKind(enum DataKind v);
PyObject* PyDiaLocationType_FromLocationType(enum LocationType v);
PyObject* PyDiaStorageModifier_FromStorageModifier(dia::StorageModifier v);
