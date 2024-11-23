#include "pydia_module_methods.h"
#include <pydia_exceptions.h>
#include <pydia_helper_routines.h>

PyObject* PyDiaModule_resolveTypeName(PyObject* module, PyObject* args)
{
    PyObject* symbol = nullptr;

    // Parse the arguments and ensure the object is of the correct type
    if (!PyArg_ParseTuple(args, "O!", &PyDiaSymbol_Type, &symbol) || !symbol)
    {
        return nullptr;  // Parsing failed; raise an appropriate exception
    }

    const auto unsafeCode = [](const PyDiaSymbol* self) -> PyObject* { return PyObject_FromWstring(dia::resolveTypeName(*self->diaSymbol)); };
    PYDIA_SAFE_TRY({ return unsafeCode(reinterpret_cast<PyDiaSymbol*>(symbol)); });
    Py_UNREACHABLE();
}
