#pragma once
#include <Python.h>
//
#include <DiaSymbol.h>

// Define the Python DiaSymbolType object
// This is much much to permissive and abstract to expose to Python users.
// The PyDiaSymbol MUST be wrapped with user friendly and intuitive ad-hoc types.
typedef struct
{
    PyObject_HEAD dia::Symbol* diaSymbol;  // Pointer to the C++ DiaSymbolType object
} PyDiaSymbol;

extern PyTypeObject PyDiaSymbol_Type;

PyObject* PyDiaSymbol_FromSymbol(dia::Symbol&& symbol);

// Auto decleration of trivial conversions like PyDiaSymbol_FromSymbol for all types
#define DECLARE_PYDIA_SYMBOL_FROM_SYMBOL_TRIVIAL_CONVERSION(diaTypeName)                                                                             \
    PyObject* PyDia##diaTypeName##_From##diaTypeName##Symbol(dia::##diaTypeName&& symbol);                                                           \
    static inline PyObject* PyDiaSymbol_FromSymbol(dia::##diaTypeName&& symbol)                                                                      \
    {                                                                                                                                                \
        return PyDia##diaTypeName##_From##diaTypeName##Symbol(std::move(symbol));                                                                    \
    }
