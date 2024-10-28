#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_data.h"
#include "pydia_exceptions.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include "SymbolTypes/DiaData.h"

TRIVIAL_INIT_DEINIT(Data);

// Python method table for dia::Data
static PyMethodDef PyDiaData_methods[] = {
    {"get_name", (PyCFunction)PyDiaSymbol_getName, METH_NOARGS, "Get the name of the data field."},
    {"get_value", (PyCFunction)PyDiaSymbol_getValue, METH_NOARGS, "Get the value of the data field."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

PYDIA_SYMBOL_TYPE_DEFINITION(Data, PyDiaData_methods);

PyObject* PyDiaData_FromDataSymbol(dia::Data&& symbol)
{
    // Create a new PyDiaData object
    PyDiaData* pySymbol = PyObject_New(PyDiaData, &PyDiaData_Type);
    if (!pySymbol)
    {
        PyErr_SetString(PyExc_MemoryError, "Failed to create DiaSymbol object.");
        return NULL;
    }

    // Initialize the PyDiaData object with the corresponding dia::Data object
    pySymbol->diaData = new (std::nothrow) dia::Data(symbol);

    Py_INCREF(pySymbol);
    return reinterpret_cast<PyObject*>(pySymbol);
}
