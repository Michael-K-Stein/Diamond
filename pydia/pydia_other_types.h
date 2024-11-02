#pragma once
#include <Python.h>
//
#include <SymbolTypes/DiaArray.h>
#include <SymbolTypes/DiaBaseType.h>
#include <SymbolTypes/DiaData.h>
#include <SymbolTypes/DiaExe.h>
#include <SymbolTypes/DiaFunction.h>
#include <SymbolTypes/DiaFunctionArgType.h>
#include <SymbolTypes/DiaFunctionType.h>
#include <SymbolTypes/DiaNull.h>
#include <SymbolTypes/DiaPointer.h>
#include <SymbolTypes/DiaTypedef.h>
#include <SymbolTypes/DiaUdt.h>
//
#include "dia_types/pydia_datasource.h"
#include "pydia_symbol.h"

#define XFOR_TRIVIAL_PYDIA_CLASSES(opperation)                                                                                                       \
    opperation(Exe);                                                                                                                                 \
    opperation(Function);                                                                                                                            \
    opperation(FunctionType);                                                                                                                        \
    opperation(FunctionArgType);                                                                                                                     \
    opperation(Null);                                                                                                                                \
    opperation(Typedef);

#define __TRIVIAL_PYDIA_TYPE_WRAPPER_DEFINITION(className)                                                                                           \
    typedef struct                                                                                                                                   \
    {                                                                                                                                                \
        PyObject_HEAD;                                                                                                                               \
        dia::##className* dia##className;                                                                                                            \
        PYDIA_DERIVED_SYMBOL_ADDITIONAL_MEMBERS;                                                                                                     \
    } PyDia##className;                                                                                                                              \
    extern PyTypeObject PyDia##className##_Type;

XFOR_TRIVIAL_PYDIA_CLASSES(__TRIVIAL_PYDIA_TYPE_WRAPPER_DEFINITION);
