#pragma once
#include <Python.h>

#include <DiaSymbolFuncs.h>

/// @brief Initialize the C-Python wrapping Enums for the DIA SDK enums
/// @param module The pydia module
/// @return The same module on success, NULL on failure.
PyObject* pydia_createDiaEnumWrappings(PyObject* module);

PyObject* PyDiaSymTag_FromSymTag(enum SymTagEnum symTag);
PyObject* PyDiaBasicType_FromBasicType(enum BasicType basicType);
PyObject* PyDiaCallingConvention_FromCallingConvention(dia::CvCall callingConvention);
PyObject* PyDiaAccessModifier_FromAccessModifier(enum AccessModifier v);
PyObject* PyDiaUdtKind_FromUdtKind(enum UdtKind v);
PyObject* PyDiaDataKind_FromDataKind(enum DataKind v);
PyObject* PyDiaLocationType_FromLocationType(enum LocationType v);
PyObject* PyDiaStorageModifier_FromStorageModifier(dia::StorageModifier v);
