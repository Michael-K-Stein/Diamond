#pragma once
#include <Python.h>
#include <SymbolTypes/DiaArray.h>
#include <SymbolTypes/DiaData.h>
#include <SymbolTypes/DiaExe.h>
#include <SymbolTypes/DiaFunction.h>
#include <SymbolTypes/DiaFunctionArgType.h>
#include <SymbolTypes/DiaFunctionType.h>
#include <SymbolTypes/DiaNull.h>
#include <SymbolTypes/DiaPointer.h>
#include <SymbolTypes/DiaUdt.h>

#define XFOR_TRIVIAL_PYDIA_CLASSES(opperation)                                                                                                       \
    opperation(Array);                                                                                                                               \
    opperation(Exe);                                                                                                                                 \
    opperation(Function);                                                                                                                            \
    opperation(FunctionType);                                                                                                                        \
    opperation(FunctionArgType);                                                                                                                     \
    opperation(Null);                                                                                                                                \
    opperation(Pointer);                                                                                                                             \
    opperation(Udt);

#define __TRIVIAL_PYDIA_TYPE_WRAPPER_DEFINITION(className)                                                                                           \
    typedef struct                                                                                                                                   \
    {                                                                                                                                                \
        PyObject_HEAD dia::##className* dia##className;                                                                                              \
    } PyDia##className;                                                                                                                              \
    extern PyTypeObject PyDia##className##_Type;

XFOR_TRIVIAL_PYDIA_CLASSES(__TRIVIAL_PYDIA_TYPE_WRAPPER_DEFINITION);
