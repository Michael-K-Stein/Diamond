#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_all_types.h"
#include "pydia_datasource.h"
#include "pydia_enum.h"
#include "pydia_exceptions.h"
#include "pydia_other_types.h"
#include "pydia_symbol.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_typedef.h"
#include "pydia_udts.h"

// C++ DiaSymbolMaster imports
#include "DiaDataSource.h"
#include <pydia_helper_routines.h>

static PyObject* PyDiaDataSource_loadDataFromPdb(PyDiaDataSource* self, PyObject* args);
static PyObject* PyDiaDataSource_getExports(PyDiaDataSource* self, PyObject* args);
static PyObject* PyDiaDataSource_getExportedFunctions(PyDiaDataSource* self);
static PyObject* PyDiaDataSource_getEnum(PyDiaDataSource* self, PyObject* args);
static PyObject* PyDiaDataSource_getStruct(PyDiaDataSource* self, PyObject* args);
static PyObject* PyDiaDataSource_getTypedefs(PyDiaDataSource* self);

static void PyDiaDataSource_dealloc(PyDiaDataSource* self)
{
    if (self->diaDataSource)
    {
        delete self->diaDataSource;
    }
    _Py_TYPE(((PyObject*)((self))))->tp_free((PyObject*)self);
}

// Updated initialization function
static int PyDiaDataSource_init(PyDiaDataSource* self, PyObject* args, PyObject* kwds)
{
    dia::DataSource* tempDataSource = nullptr;  // Temporary pointer

    const auto unsafeInit           = [&]() -> int
    {
        try
        {
            // Check if we have any arguments
            if (PyTuple_Size(args) == 0)
            {
                // Use the default constructor
                tempDataSource = new (std::nothrow) dia::DataSource();
            }
            else if (PyTuple_Size(args) == 1)
            {
                // Handle the first argument as filePath
                tempDataSource = new (std::nothrow) dia::DataSource(PyObjectToAnyString(PyTuple_GetItem(args, 0)));
            }
            else if (PyTuple_Size(args) == 2)
            {
                // Handle the first argument as filePath and the second as symstoreDirectory
                tempDataSource =
                    new (std::nothrow) dia::DataSource(PyObjectToAnyString(PyTuple_GetItem(args, 0)), PyObjectToAnyString(PyTuple_GetItem(args, 1)));
            }
            else
            {
                // Too many arguments
                PyErr_SetString(PyExc_TypeError, "Invalid number of arguments for DataSource constructor.");
                return -1;
            }
        }
        catch (const dia::InvalidFileFormatException& e)
        {
            PyErr_SetString(PyDiaError, e.what());
            return -1;
        }
        return 0;
    };

    int retVal = -1;
    PYDIA_SAFE_TRY_EXCEPT({ retVal = unsafeInit(); },
                          {
                              PyErr_SetString(PyDiaError, e.what());
                              return -1;
                          });
    if (0 > retVal)
    {
        return retVal;
    }

    // Check if the DataSource was created successfully
    if (!tempDataSource)
    {
        PyErr_SetString(PyExc_MemoryError, "Failed to create DataSource object with provided arguments.");
        return -1;
    }

    // Assign the created DataSource to the member variable
    self->diaDataSource = tempDataSource;

    return 0;
}

// Python method table for DiaDataSource
static PyMethodDef PyDiaDataSource_methods[] = {
    {"load_data_from_pdb", (PyCFunction)PyDiaDataSource_loadDataFromPdb, METH_VARARGS, "Load data from a PDB file."},
    {"get_functions", (PyCFunction)PyDiaDataSource_getExportedFunctions, METH_NOARGS, "Get exported functions."},
    {"get_exports", (PyCFunction)PyDiaDataSource_getExports, METH_VARARGS, "Get all exports."},
    {"get_enum", (PyCFunction)PyDiaDataSource_getEnum, METH_VARARGS, "Get enum by name."},
    {"get_struct", (PyCFunction)PyDiaDataSource_getStruct, METH_VARARGS, "Get struct by name."},
    {"get_typedefs", (PyCFunction)PyDiaDataSource_getTypedefs, METH_NOARGS, "Get all typedefs."},
    {NULL, NULL, 0, NULL},
};

// Define the Python DiaDataSource type object
PyTypeObject PyDiaDataSource_Type = {
    PyVarObject_HEAD_INIT(NULL, 0) "pydia.DataSource", /* tp_name */
    sizeof(PyDiaDataSource),                           /* tp_basicsize */
    0,                                                 /* tp_itemsize */
    (destructor)PyDiaDataSource_dealloc,               /* tp_dealloc */
    0,                                                 /* tp_print */
    0,                                                 /* tp_getattr */
    0,                                                 /* tp_setattr */
    0,                                                 /* tp_as_async */
    0,                                                 /* tp_repr */
    0,                                                 /* tp_as_number */
    0,                                                 /* tp_as_sequence */
    0,                                                 /* tp_as_mapping */
    0,                                                 /* tp_hash  */
    0,                                                 /* tp_call */
    0,                                                 /* tp_str */
    0,                                                 /* tp_getattro */
    0,                                                 /* tp_setattro */
    0,                                                 /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                                /* tp_flags */
    "DataSource object",                               /* tp_doc */
    0,                                                 /* tp_traverse */
    0,                                                 /* tp_clear */
    0,                                                 /* tp_richcompare */
    0,                                                 /* tp_weaklistoffset */
    0,                                                 /* tp_iter */
    0,                                                 /* tp_iternext */
    PyDiaDataSource_methods,                           /* tp_methods */
    0,                                                 /* tp_members */
    0,                                                 /* tp_getset */
    0,                                                 /* tp_base */
    0,                                                 /* tp_dict */
    0,                                                 /* tp_descr_get */
    0,                                                 /* tp_descr_set */
    0,                                                 /* tp_dictoffset */
    (initproc)PyDiaDataSource_init,                    /* tp_init */
    0,                                                 /* tp_alloc */
    PyType_GenericNew,                                 /* tp_new */
};

// Method: loadDataFromPdb
static PyObject* PyDiaDataSource_loadDataFromPdb(PyDiaDataSource* self, PyObject* args)
{
    // The lifetime of thie PyObject is guaranteed by the "args"
    PyObject* pyFilePath = NULL;

    // Parse the argument as a Python object (string or bytes)
    if (!PyArg_ParseTuple(args, "O", &pyFilePath))
    {
        return NULL;  // If parsing fails, return NULL (error already set)
    }

    try
    {
        // PyObjectToAnyString creates a new copy of the string which is C++ memory managed
        self->diaDataSource->loadDataFromPdb(PyObjectToAnyString(pyFilePath));
    }
    catch (const dia::InvalidUsageException& e)
    {
        PyErr_SetString(PyDiaInvalidUsageError, e.what());
        return NULL;
    }

    // Return self for method chaining
    Py_INCREF(self);
    return (PyObject*)self;
}

// Method: getExportedFunctions
static PyObject* PyDiaDataSource_getExportedFunctions(PyDiaDataSource* self)
{
    std::vector<dia::Function> functions{};
    try
    {
        functions = self->diaDataSource->getFunctions();
    }
    catch (const std::exception& e)
    {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return NULL;
    }

    PyObject* resultList = PyList_New(functions.size());
    if (!resultList) return NULL;

    for (size_t i = 0; i < functions.size(); ++i)
    {
        PyObject* functionStr = PyUnicode_FromWideChar(functions[i].getName().c_str(), functions[i].getName().length());
        if (!functionStr)
        {
            Py_DECREF(resultList);
            return NULL;
        }
        PyList_SET_ITEM(resultList, i, functionStr);
    }

    return resultList;
}

static PyObject* PyDiaDataSource_getExports(PyDiaDataSource* self, PyObject* args)
{
    int symTagInt;
    if (!PyArg_ParseTuple(args, "i", &symTagInt))
    {
        PyErr_SetString(PyExc_ValueError, "Expected an integer for the SymTagEnum.");
        return NULL;
    }

    enum SymTagEnum symTag           = static_cast<enum SymTagEnum>(symTagInt);
    std::vector<dia::Symbol> exports = self->diaDataSource->getSymbols(symTag);

    PyObject* resultList             = PyList_New(exports.size());
    if (!resultList)
    {
        return NULL;  // Return NULL on failure
    }

    for (size_t i = 0; i < exports.size(); ++i)
    {

        PyObject* sym = PyDiaSymbol_FromSymbol(std::move(exports[i]), self);
        if (!sym)
        {
            Py_DECREF(resultList);  // Clean up the result list
            return NULL;            // Return NULL on failure
        }

        // Set the item in the list, transferring ownership
        if (0 > PyList_SetItem(resultList, i, sym))
        {
            Py_DECREF(sym);
            Py_DECREF(resultList);  // Clean up the result list
            return NULL;            // Return NULL on failure
        }
    }

    return resultList;
}

static PyObject* PyDiaDataSource_getEnum(PyDiaDataSource* self, PyObject* args)
{
    // The PyObject argument for enum name
    PyObject* pyEnumName = NULL;

    // Parse the argument as a Python object (expected string or bytes)
    if (!PyArg_ParseTuple(args, "O", &pyEnumName))
    {
        return NULL;  // If parsing fails, return NULL (error already set)
    }

    // Try to retrieve the enum using the provided name
    try
    {
        const auto& enumSymbol = self->diaDataSource->getEnum(PyObjectToAnyString(pyEnumName));

        // Allocate a new PyDiaEnum object
        PyDiaEnum* pyEnum = PyObject_New(PyDiaEnum, &PyDiaEnum_Type);
        if (!pyEnum)
        {
            PyErr_SetString(PyExc_MemoryError, "Failed to create DiaEnum object.");
            return NULL;
        }

        // Initialize the PyDiaEnum object with the dia::Enum object
        pyEnum->diaEnum = new (std::nothrow) dia::Enum(enumSymbol);
        if (!pyEnum->diaEnum)
        {
            PyErr_SetString(PyExc_MemoryError, "Failed to allocate memory for DiaEnum.");
            Py_DECREF(pyEnum);  // Release allocated PyDiaEnum object
            return NULL;
        }

        return (PyObject*)pyEnum;
    }
    catch (const dia::SymbolNotFoundException& e)
    {
        PyErr_SetString(PyExc_ValueError, e.what());
        return NULL;
    }
    catch (const std::bad_alloc&)
    {
        PyErr_SetString(PyExc_MemoryError, "Memory allocation failed for DiaEnum.");
        return NULL;
    }
}

static PyObject* PyDiaDataSource_getStruct(PyDiaDataSource* self, PyObject* args)
{
    _ASSERT(self);
    _ASSERT(self->diaDataSource);

    // The PyObject argument for struct name
    PyObject* pyStructName = NULL;

    // Parse the argument as a Python object (expected string or bytes)
    if (!PyArg_ParseTuple(args, "O", &pyStructName))
    {
        return NULL;  // If parsing fails, return NULL (error already set)
    }

    // Try to retrieve the struct using the provided name
    try
    {
        auto structSymbol = self->diaDataSource->getStruct(PyObjectToAnyString(pyStructName));
        _ASSERT(NULL != &structSymbol);
        return PyDiaUdt_FromSymbol(std::move(static_cast<dia::Symbol&>(structSymbol)), self);
    }
    catch (const dia::SymbolNotFoundException& e)
    {
        PyErr_SetString(PyExc_ValueError, e.what());
        return NULL;
    }
    catch (const std::bad_alloc&)
    {
        PyErr_SetString(PyExc_MemoryError, "Memory allocation failed for DiaStruct.");
        return NULL;
    }
}

static PyObject* PyDiaDataSource_getTypedefs(PyDiaDataSource* self)
{
    const auto unsafeFunc = [&]() -> PyObject*
    {
        auto typedefs        = self->diaDataSource->getTypedefs();

        PyObject* resultList = PyList_New(typedefs.size());
        if (!resultList)
        {
            PyErr_SetString(PyExc_MemoryError, "Memory allocation failed for typedefs list.");
            return NULL;  // Return NULL on failure
        }

        for (size_t i = 0; i < typedefs.size(); ++i)
        {
            PyDiaTypedef* sym = reinterpret_cast<PyDiaTypedef*>(PyDiaTypedef_FromTypedefSymbol(std::move(typedefs[i]), self));

            // Set the item in the list, transferring ownership
            if (PyList_SetItem(resultList, i, reinterpret_cast<PyObject*>(sym)) < 0)
            {
                Py_DECREF(resultList);  // Clean up the result list
                return NULL;            // Return NULL on failure
            }
        }

        return resultList;
    };

    PYDIA_SAFE_TRY({ return unsafeFunc(); });
    Py_UNREACHABLE();
}

PyDiaDataSource* PyDiaDataSource_FromInitializerList(PyObject* initializerList)
{
    if (PyObject_IsInstance(initializerList, (PyObject*)&PyDiaDataSource_Type))
    {
        return (PyDiaDataSource*)initializerList;
    }

    if (PyUnicode_Check(initializerList))
    {
        // Create a new PyDiaDataSource object using tp_new
        PyDiaDataSource* dataSourceObj = (PyDiaDataSource*)PyDiaDataSource_Type.tp_new(&PyDiaDataSource_Type, NULL, NULL);
        if (!dataSourceObj)
        {
            PyErr_SetString(PyExc_MemoryError, "Failed to allocate memory for new PyDiaDataSource object.");
            return NULL;
        }

        PyObject* pyTupleOfString = PyTuple_Pack(1, initializerList);
        if (!pyTupleOfString)
        {
            Py_DECREF(dataSourceObj);  // Clean up if initialization fails
            return NULL;
        }

        // Initialize the PyDiaDataSource object with the string data source
        if (0 > PyDiaDataSource_init(dataSourceObj, pyTupleOfString, NULL))
        {
            Py_DECREF(dataSourceObj);  // Clean up if initialization fails
            return NULL;
        }

        return dataSourceObj;
    }

    PyErr_SetString(PyExc_TypeError, "A DataSource object cannot be deduced from the given parameters.");
    return NULL;
}
