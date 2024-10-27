#pragma once
#include <Python.h>
// We will explicitly use the UDT wrapper instead of dia::Udt, since dia::Udt is too abstract over structs & unions.
#include <DiaUserDefinedTypeWrapper.h>

// Define the Python DiaStructType object
typedef struct
{
    PyObject_HEAD dia::UserDefinedType* diaUdt;
} PyDiaUdt;

extern PyTypeObject PyDiaUdt_Type;
