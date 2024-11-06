#pragma once
#include <Python.h>
//
#include "pydia_data.h"
#include "pydia_enum.h"
#include "pydia_other_types.h"
#include "pydia_udt.h"
#include "pydia_udts.h"


#define XFOR_ALL_PYDIA_CLASSES(opperation)                                                                                                           \
    opperation(Array);                                                                                                                               \
    opperation(Exe);                                                                                                                                 \
    opperation(Function);                                                                                                                            \
    opperation(FunctionType);                                                                                                                        \
    opperation(FunctionArgType);                                                                                                                     \
    opperation(Null);                                                                                                                                \
    opperation(Pointer);                                                                                                                             \
    opperation(Data);                                                                                                                                \
    opperation(Enum);                                                                                                                                \
    opperation(Udt);                                                                                                                                 \
    opperation(BaseType);                                                                                                                            \
    opperation(Typedef);                                                                                                                             \
    opperation(UserDefinedType);

// Forward decleration
template <typename K, typename T>
struct PyDiaAbstractGenerator;

#define DEFINE_ENUMERATOR(diaTypeName)                                                                                                               \
    using PyDia##diaTypeName##Generator = PyDiaAbstractGenerator<dia::Symbol, dia::##diaTypeName>;                                                   \
    extern PyTypeObject PyDia##diaTypeName##Generator_Type;

XFOR_ALL_PYDIA_CLASSES(DEFINE_ENUMERATOR);
XFOR_ALL_PYDIA_CLASSES(DECLARE_PYDIA_SYMBOL_FROM_SYMBOL_TRIVIAL_CONVERSION);
DEFINE_ENUMERATOR(Symbol);