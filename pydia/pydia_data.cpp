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
    {"get_access", (PyCFunction)PyDiaSymbol_getAccess, METH_NOARGS, "Get the access level of the data."},
    {"get_address_offset", (PyCFunction)PyDiaSymbol_getAddressOffset, METH_NOARGS, "Get the address offset of the data."},
    {"get_address_section", (PyCFunction)PyDiaSymbol_getAddressSection, METH_NOARGS, "Get the address section of the data."},
    {"is_address_taken", (PyCFunction)PyDiaSymbol_isAddressTaken, METH_NOARGS, "Check if the address is taken for the data."},
    {"get_bit_position", (PyCFunction)PyDiaSymbol_getBitPosition, METH_NOARGS, "Get the bit position of the data."},
    {"get_class_parent", (PyCFunction)PyDiaSymbol_getClassParent, METH_NOARGS, "Get the class in which this data resides."},
    {"get_class_parent_id", (PyCFunction)PyDiaSymbol_getClassParentId, METH_NOARGS, "Get the class parent ID of the data."},
    {"is_compiler_generated", (PyCFunction)PyDiaSymbol_isCompilerGenerated, METH_NOARGS, "Check if the data is compiler-generated."},
    {"is_const", (PyCFunction)PyDiaSymbol_isConst, METH_NOARGS, "Check if the data is const-qualified."},
    {"get_data_kind", (PyCFunction)PyDiaSymbol_getDataKind, METH_NOARGS, "Get the kind of data (e.g., local, global)."},
    {"is_aggregated", (PyCFunction)PyDiaSymbol_isAggregated, METH_NOARGS, "Check if the data is aggregated."},
    {"is_splitted", (PyCFunction)PyDiaSymbol_isSplitted, METH_NOARGS, "Check if the data is split."},
    {"get_length", (PyCFunction)PyDiaSymbol_getLength, METH_NOARGS, "Get the length of the data."},
    {"get_lexical_parent", (PyCFunction)PyDiaSymbol_getLexicalParent, METH_NOARGS, "Get the lexical parent of the data."},
    {"get_lexical_parent_id", (PyCFunction)PyDiaSymbol_getLexicalParentId, METH_NOARGS, "Get the lexical parent ID of the data."},
    {"get_location_type", (PyCFunction)PyDiaSymbol_getLocationType, METH_NOARGS, "Get the location type of the data."},
    {"get_name", (PyCFunction)PyDiaSymbol_getName, METH_NOARGS, "Get the name of the data."},
    {"get_offset", (PyCFunction)PyDiaSymbol_getOffset, METH_NOARGS, "Get the offset of the data."},
    {"get_register_id", (PyCFunction)PyDiaSymbol_getRegisterId, METH_NOARGS, "Get the register ID associated with the data."},
    {"get_relative_virtual_address", (PyCFunction)PyDiaSymbol_getRelativeVirtualAddress, METH_NOARGS,
     "Get the relative virtual address of the data."},
    {"get_slot", (PyCFunction)PyDiaSymbol_getSlot, METH_NOARGS, "Get the slot number of the data."},
    {"get_sym_index_id", (PyCFunction)PyDiaSymbol_getSymIndexId, METH_NOARGS, "Get the symbol index ID of the data."},
    {"get_sym_tag", (PyCFunction)PyDiaSymbol_getSymTag, METH_NOARGS, "Get the symbol tag of the data."},
    {"get_token", (PyCFunction)PyDiaSymbol_getToken, METH_NOARGS, "Get the token associated with the data."},
    {"get_type", (PyCFunction)PyDiaSymbol_getType, METH_NOARGS, "Get the type of the data."},
    {"get_type_id", (PyCFunction)PyDiaSymbol_getTypeId, METH_NOARGS, "Get the type ID of the data."},
    {"is_unaligned", (PyCFunction)PyDiaSymbol_isUnaligned, METH_NOARGS, "Check if the data is unaligned."},
    {"get_value", (PyCFunction)PyDiaSymbol_getValue, METH_NOARGS, "Get the constant value of the data."},
    {"get_virtual_address", (PyCFunction)PyDiaSymbol_getVirtualAddress, METH_NOARGS, "Get the virtual address of the data."},
    {"is_volatile", (PyCFunction)PyDiaSymbol_isVolatile, METH_NOARGS, "Check if the data is volatile-qualified."},
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
