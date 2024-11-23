#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>  // For CoInitialize
// Further PyDia headers
#include "pydia.h"
#include "pydia_exceptions.h"
#include "pydia_module_methods.h"
#include "pydia_register_classes.h"
#include "pydia_wrapping_types.h"

typedef struct
{
    BOOLEAN Initialized;
} PyDiaModuleState;

static void pydia_cleanup(PyObject* module);
static PyDiaModuleState* pydia_getModuleState(PyObject* module);

static PyMethodDef PyDiaMethods[] = {
    PyDiaModuleMethodEntry_resolveTypeName,

    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef pydiamodule = {
    PyModuleDef_HEAD_INIT,
    "pydia",                  /* name of module */
    NULL,                     /* module documentation, may be NULL */
    sizeof(PyDiaModuleState), /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    PyDiaMethods,
    NULL,
    NULL,
    NULL,
    (freefunc)pydia_cleanup,
};

static void pydia_cleanup(PyObject* module)
{
    const auto moduleState = pydia_getModuleState(module);
    if (0 == moduleState->Initialized)
    {
        return;
    }

    CoUninitialize();
}

static PyDiaModuleState* pydia_getModuleState(PyObject* module) { return (PyDiaModuleState*)PyModule_GetState(module); }

PyMODINIT_FUNC PyInit_pydia(void)
{
    PyObject* module              = NULL;
    PyDiaModuleState* moduleState = NULL;
    HRESULT hresult               = S_OK;

    // Avoid multiple initializations
    static volatile short passed = 0;
    if (TRUE == InterlockedCompareExchange16(&passed, TRUE, FALSE))
    {
        Py_RETURN_NONE;
    }

    // Create the Python module
    module = PyModule_Create(&pydiamodule);
    if (NULL == module)
    {
        return NULL;
    }

    moduleState = pydia_getModuleState(module);
    if (NULL == moduleState)
    {
        PyErr_SetString(PyExc_RuntimeError, "Failed to allocate module state.");
        return NULL;
    }

    // Set the initialized state to false
    moduleState->Initialized = FALSE;

    // Initialize COM library
    hresult = CoInitialize(NULL);
    if (FAILED(hresult))
    {
        // Propagate HRESULT error to the Python caller
        PyErr_Format(PyExc_OSError, "Failed to initialize COM library! HRESULT: 0x%08lX", hresult);
        return NULL;
    }

    if (NULL == pydia_initializeErrors(module))
    {
        return NULL;
    }

    if (NULL == pydia_createDiaEnumWrappings(module))
    {
        return NULL;
    }

    if (NULL == pydia_registerClasses(module))
    {
        return NULL;
    }

    // Mark the module as initialized
    moduleState->Initialized = TRUE;

    return module;
}
