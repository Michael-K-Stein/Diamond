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
static PyObject* PyDiaDataSource_getSymbols(PyDiaDataSource* self, PyObject* args);

static PyObject* PyDiaDataSource_getFunction(PyDiaDataSource* self, PyObject* args);
static PyObject* PyDiaDataSource_getFunctions(PyDiaDataSource* self);

static PyObject* PyDiaDataSource_getEnum(PyDiaDataSource* self, PyObject* args);
static PyObject* PyDiaDataSource_getEnums(PyDiaDataSource* self);

static PyObject* PyDiaDataSource_getStruct(PyDiaDataSource* self, PyObject* args);
static PyObject* PyDiaDataSource_getUserDefinedTypes(PyDiaDataSource* self);

static PyObject* PyDiaDataSource_getTypedef(PyDiaDataSource* self, PyObject* args);
static PyObject* PyDiaDataSource_getTypedefs(PyDiaDataSource* self);

static void PyDiaDataSource_dealloc(PyDiaDataSource* self)
{
    if (self->diaDataSource)
    {
        delete self->diaDataSource;
    }
    Py_TYPE(((PyObject*)((self))))->tp_free((PyObject*)self);
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
                PyErr_SetString(PyExc_TypeError, "DataSource requires at least one argument.");
                return -1;
#if 0  // Haven't found a valid use case for this...
       // Use the default constructor
                tempDataSource = new (std::nothrow) dia::DataSource();
#endif
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

    auto capturedGlobalScope{tempDataSource->getGlobalScope()};
    auto tempGlobalScope = PyDiaSymbol_FromSymbol(std::move(capturedGlobalScope), self);
    // Check if the DataSource was created successfully
    if (!tempGlobalScope)
    {
        if (tempDataSource)
        {
            delete tempDataSource;
        }
        PyErr_SetString(PyExc_MemoryError, "Failed to create DataSource object with provided arguments.");
        return -1;
    }

    // Assign the created DataSource to the member variable
    self->diaDataSource  = tempDataSource;
    tempDataSource       = nullptr;
    self->diaGlobalScope = (PyDiaSymbol*)tempGlobalScope;
    tempGlobalScope      = nullptr;

    return 0;
}

// Python method table for DiaDataSource
static PyMethodDef PyDiaDataSource_methods[] = {
    {"load_data_from_pdb", (PyCFunction)PyDiaDataSource_loadDataFromPdb, METH_VARARGS, "Load data from a PDB file."},

    {"get_symbols", (PyCFunction)PyDiaDataSource_getSymbols, METH_VARARGS, "Get all symbols of specified type."},

    {"get_function", (PyCFunction)PyDiaDataSource_getFunction, METH_VARARGS, "Get function by name."},
    {"get_functions", (PyCFunction)PyDiaDataSource_getFunctions, METH_NOARGS, "Get functions."},

    {"get_enum", (PyCFunction)PyDiaDataSource_getEnum, METH_VARARGS, "Get enum by name."},
    {"get_enums", (PyCFunction)PyDiaDataSource_getEnums, METH_NOARGS, "Get all enums."},

    {"get_struct", (PyCFunction)PyDiaDataSource_getStruct, METH_VARARGS, "Get struct by name."},

    {"get_user_defined_types", (PyCFunction)PyDiaDataSource_getUserDefinedTypes, METH_NOARGS,
     "Get all user defined types (structs, unions, classes, interfaces, ...)."},

    {"get_typedef", (PyCFunction)PyDiaDataSource_getTypedef, METH_VARARGS, "Get typedef by name."},
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

template <typename T>
static PyObject* getSymbolByName(PyDiaDataSource* self,
                                 PyObject* args,
                                 std::function<T(const AnyString&)> getter,
                                 std::function<PyObject*(T&&, PyDiaDataSource*)> transformer)
{
    // The PyObject argument for symbol name
    PyObject* pySymbolName = NULL;

    // Parse the argument as a Python object (expected string or bytes)
    if (!PyArg_ParseTuple(args, "O", &pySymbolName))
    {
        return NULL;  // If parsing fails, return NULL (error already set)
    }

    // Try to retrieve the smbol using the provided name
    try
    {
        auto cSymbol = getter(PyObjectToAnyString(pySymbolName));
        return transformer(std::move(cSymbol), self);
    }
    catch (const dia::SymbolNotFoundException& e)
    {
        PyErr_SetString(PyExc_ValueError, e.what());
        return NULL;
    }
    catch (const std::runtime_error& e)
    {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return NULL;
    }
    catch (const std::bad_alloc&)
    {
        PyErr_SetString(PyExc_MemoryError, "Memory allocation failed.");
        return NULL;
    }
    Py_UNREACHABLE();
}

template <typename EntryT>
static PyObject* getSymbolsEnumeration(PyDiaDataSource* self, dia::DiaSymbolEnumerator<EntryT>&& rawEnumeration)
{
    auto safeExecution = [&]() -> PyObject*
    {
        dia::DiaSymbolEnumerator<EntryT> rawEnumerator = rawEnumeration;
        PyDiaDataGenerator* generator =
            (PyDiaDataGenerator*)PyDiaSymbolGenerator_create<PyDiaSymbol, EntryT>(self->diaGlobalScope, std::move(rawEnumerator));
        if (!generator)
        {
            PyErr_SetString(PyExc_RuntimeError, "Failed to create generator.");
            return NULL;  // Failed to allocate generator
        }

        return (PyObject*)generator;
    };

    PYDIA_SAFE_TRY({ return safeExecution(); });
    Py_UNREACHABLE();
}

static PyObject* PyDiaDataSource_getFunction(PyDiaDataSource* self, PyObject* args)
{
    using T                                       = dia::Function;
    std::function<T(const AnyString&)> getterFunc = std::bind(&dia::DataSource::getFunction, self->diaDataSource, std::placeholders::_1);
    std::function<PyObject*(T&&, PyDiaDataSource*)> transformer = PyDiaFunction_FromFunctionSymbol;
    return getSymbolByName(self, args, getterFunc, transformer);
}

static PyObject* PyDiaDataSource_getFunctions(PyDiaDataSource* self) { return getSymbolsEnumeration(self, self->diaDataSource->getFunctions()); }

static PyObject* PyDiaDataSource_getSymbols(PyDiaDataSource* self, PyObject* args)
{
    int symTagInt = 0;
    if (!PyArg_ParseTuple(args, "i", &symTagInt))
    {
        PyErr_SetString(PyExc_ValueError, "Expected an integer for the SymTagEnum.");
        return NULL;
    }

    auto safeExecution = [&]() -> PyObject*
    {
        enum SymTagEnum symTag = static_cast<enum SymTagEnum>(symTagInt);
        auto rawEnumerator     = self->diaDataSource->getSymbols(symTag);

        PyDiaDataGenerator* generator =
            (PyDiaDataGenerator*)PyDiaSymbolGenerator_create<PyDiaSymbol, dia::Symbol>(self->diaGlobalScope, std::move(rawEnumerator));
        if (!generator)
        {
            PyErr_SetString(PyExc_RuntimeError, "Failed to create generator.");
            return NULL;  // Failed to allocate generator
        }

        return (PyObject*)generator;
    };

    PYDIA_SAFE_TRY({ return safeExecution(); });
    Py_UNREACHABLE();
}

static PyObject* PyDiaDataSource_getEnum(PyDiaDataSource* self, PyObject* args)
{

    using T                                                     = dia::Enum;
    std::function<T(const AnyString&)> getterFunc               = std::bind(&dia::DataSource::getEnum, self->diaDataSource, std::placeholders::_1);
    std::function<PyObject*(T&&, PyDiaDataSource*)> transformer = PyDiaEnum_FromEnumSymbol;
    return getSymbolByName(self, args, getterFunc, transformer);
}

static PyObject* PyDiaDataSource_getEnums(PyDiaDataSource* self) { return getSymbolsEnumeration(self, self->diaDataSource->getEnums()); }

static PyObject* PyDiaDataSource_getStruct(PyDiaDataSource* self, PyObject* args)
{
    using T                                                     = dia::Struct;
    std::function<T(const AnyString&)> getterFunc               = std::bind(&dia::DataSource::getStruct, self->diaDataSource, std::placeholders::_1);
    std::function<PyObject*(T&&, PyDiaDataSource*)> transformer = PyDiaUdt_FromSymbol;
    return getSymbolByName(self, args, getterFunc, transformer);
}

static PyObject* PyDiaDataSource_getUserDefinedTypes(PyDiaDataSource* self)
{
    return getSymbolsEnumeration(self, self->diaDataSource->getUserDefinedTypes());
}

static PyObject* PyDiaDataSource_getTypedef(PyDiaDataSource* self, PyObject* args)
{
    using T                                                     = dia::Typedef;
    std::function<T(const AnyString&)> getterFunc               = std::bind(&dia::DataSource::getTypedef, self->diaDataSource, std::placeholders::_1);
    std::function<PyObject*(T&&, PyDiaDataSource*)> transformer = PyDiaTypedef_FromTypedefSymbol;
    return getSymbolByName(self, args, getterFunc, transformer);
}

static PyObject* PyDiaDataSource_getTypedefs(PyDiaDataSource* self) { return getSymbolsEnumeration(self, self->diaDataSource->getTypedefs()); }

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
