#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h> // For CoInitialize
// Further PyDia headers
#include "pydia.h"
#include "pydia_exceptions.h"

typedef struct
{
    int Initialized;
} PyDiaModuleState;

static void pydia_cleanup(void* module);
static PyDiaModuleState* get_pydia_module_state(PyObject* module);

static PyDiaModuleState* get_pydia_module_state(PyObject* module)
{
    return (PyDiaModuleState*)PyModule_GetState(module);
}

static PyMethodDef PyDiaMethods[] = {
    //{"system", pydia_system, METH_VARARGS, "Execute a shell command."},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef pydiamodule = {
    PyModuleDef_HEAD_INIT,
    "pydia",                  /* name of module */
    NULL,                     /* module documentation, may be NULL */
    sizeof(PyDiaModuleState), /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
    PyDiaMethods,
    NULL,
    NULL,
    NULL,
    pydia_cleanup,
};

static void pydia_cleanup(void* module)
{
    PyDiaModuleState* moduleState = get_pydia_module_state((PyObject*)module);
    if (0 == moduleState->Initialized)
    {
        return;
    }

    CoUninitialize();
}

PyMODINIT_FUNC PyInit_pydia(void)
{
    PyObject* module = NULL;
    PyDiaModuleState* moduleState = NULL;
    HRESULT hresult = S_OK;

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

    if (0 > pydia_initialize_pydiaerror(module))
    {
        return NULL;
    }

    // Get the module state (assuming get_pydia_module_state is properly
    // defined)
    moduleState = get_pydia_module_state((PyObject*)module);
    if (moduleState == NULL)
    {
        PyErr_SetString(PyExc_RuntimeError, "Failed to allocate module state.");
        return NULL;
    }

    // Set the initialized state to false
    moduleState->Initialized = 0;

    // Initialize COM library
    hresult = CoInitialize(NULL);
    if (FAILED(hresult))
    {
        // Propagate HRESULT error to the Python caller
        PyErr_Format(PyExc_OSError,
                     "Failed to initialize COM library! HRESULT: 0x%08lX",
                     hresult);
        return NULL;
    }

    // Add the DiaDataSource type to the module
    if (PyType_Ready(&PyDiaDataSourceType) < 0)
    {
        return NULL;
    }
    Py_INCREF(&PyDiaDataSourceType);
    PyModule_AddObject(module, "DiaDataSource",
                       (PyObject*)&PyDiaDataSourceType);

    // Add the DiaSymbol type to the module
    if (PyType_Ready(&PyDiaSymbolType) < 0)
    {
        return NULL;
    }
    Py_INCREF(&PyDiaSymbolType);
    PyModule_AddObject(module, "Symbol", (PyObject*)&PyDiaSymbolType);

    // Mark the module as initialized
    moduleState->Initialized = 1;

    return module;
}
