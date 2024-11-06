#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h>
// Python.h must be included before anything else
#include <objbase.h>

// C pydia imports
#include "pydia_exceptions.h"
#include "pydia_function.h"
#include "pydia_helper_routines.h"
#include "pydia_symbol_private.h"
#include "pydia_trivial_init.h"
#include "pydia_wrapping_types.h"

// C++ DiaSymbolMaster imports
#include <SymbolTypes/DiaFunction.h>

TRIVIAL_INIT_DEINIT(Function);
// Python method table for dia::Function
static PyMethodDef PyDiaFunction_methods[] = {
    {"get_access", (PyCFunction)PyDiaSymbol_getAccess, METH_NOARGS, "Get the access level of the function."},
    {"get_address_offset", (PyCFunction)PyDiaSymbol_getAddressOffset, METH_NOARGS, "Get the address offset of the function."},
    {"get_address_section", (PyCFunction)PyDiaSymbol_getAddressSection, METH_NOARGS, "Get the address section of the function."},
    {"get_class_parent", (PyCFunction)PyDiaSymbol_getClassParent, METH_NOARGS, "Get the class parent of the function."},
    {"get_class_parent_id", (PyCFunction)PyDiaSymbol_getClassParentId, METH_NOARGS, "Get the class parent ID of the function."},
    {"has_custom_calling_convention", (PyCFunction)PyDiaSymbol_hasCustomCallingConvention, METH_NOARGS,
     "Get the custom calling convention of the function."},

    {"has_alloca", (PyCFunction)PyDiaSymbol_hasAlloca, METH_NOARGS, "Check if the function uses alloca."},
    {"has_eh", (PyCFunction)PyDiaSymbol_hasEh, METH_NOARGS, "Check if the function has exception handling (EH)."},
    {"has_eha", (PyCFunction)PyDiaSymbol_hasEha, METH_NOARGS, "Check if the function has asynchronous exception handling (EHa)."},
    {"has_inl_asm", (PyCFunction)PyDiaSymbol_hasInlineAsm, METH_NOARGS, "Check if the function contains inline assembly."},
    {"has_long_jump", (PyCFunction)PyDiaSymbol_hasLongJump, METH_NOARGS, "Check if the function uses long jumps."},
    {"has_security_checks", (PyCFunction)PyDiaSymbol_hasSecurityChecks, METH_NOARGS, "Check if the function has security checks."},
    {"has_seh", (PyCFunction)PyDiaSymbol_hasSeh, METH_NOARGS, "Check if the function has structured exception handling (SEH)."},
    {"has_set_jump", (PyCFunction)PyDiaSymbol_hasSetJump, METH_NOARGS, "Check if the function uses setjmp."},
    {"has_inl_spec", (PyCFunction)PyDiaSymbol_hasInlineSpecifier, METH_NOARGS, "Check if the function has an inline specifier."},
    {"has_no_stack_ordering", (PyCFunction)PyDiaSymbol_hasNoStackOrdering, METH_NOARGS, "Check if the function has no stack ordering."},
    {"has_optimized_code_debug_info", (PyCFunction)PyDiaSymbol_hasOptimizedCodeDebugInfo, METH_NOARGS,
     "Get debug info about optimized code in the function."},

    {"is_pure", (PyCFunction)PyDiaSymbol_isPure, METH_NOARGS, "Check if the function is pure."},
    {"is_far_return", (PyCFunction)PyDiaSymbol_isFarReturn, METH_NOARGS, "Check if the function uses a far return."},
    {"is_const", (PyCFunction)PyDiaSymbol_isConst, METH_NOARGS, "Check if the function is const-qualified."},
    {"is_unaligned", (PyCFunction)PyDiaSymbol_isUnaligned, METH_NOARGS, "Check if the function is unaligned."},
    {"is_naked", (PyCFunction)PyDiaSymbol_isNaked, METH_NOARGS, "Check if the function is naked."},
    {"is_static", (PyCFunction)PyDiaSymbol_isStatic, METH_NOARGS, "Check if the function is static."},
    {"is_not_reached", (PyCFunction)PyDiaSymbol_isNotReached, METH_NOARGS, "Check if the function cannot be reached."},
    {"is_virtual", (PyCFunction)PyDiaSymbol_isVirtual, METH_NOARGS, "Check if the function is virtual."},
    {"is_volatile", (PyCFunction)PyDiaSymbol_isVolatile, METH_NOARGS, "Check if the function is volatile-qualified."},
    {"is_no_inline", (PyCFunction)PyDiaSymbol_isNoInline, METH_NOARGS, "Check if the function is marked as no-inline."},
    {"is_no_return", (PyCFunction)PyDiaSymbol_isNoReturn, METH_NOARGS, "Check if the function is marked as no-return."},

    {"get_interrupt_return", (PyCFunction)PyDiaSymbol_hasInterruptReturn, METH_NOARGS, "Check if the function returns with an interrupt."},
    {"get_intro", (PyCFunction)PyDiaSymbol_isIntro, METH_NOARGS, "Get the introduction status of the function."},

    {"get_length", (PyCFunction)PyDiaSymbol_getLength, METH_NOARGS, "Get the length of the function."},
    {"get_lexical_parent", (PyCFunction)PyDiaSymbol_getLexicalParent, METH_NOARGS, "Get the lexical parent of the function."},
    {"get_lexical_parent_id", (PyCFunction)PyDiaSymbol_getLexicalParentId, METH_NOARGS, "Get the lexical parent ID of the function."},
    {"get_location_type", (PyCFunction)PyDiaSymbol_getLocationType, METH_NOARGS, "Get the location type of the function."},
    {"get_name", (PyCFunction)PyDiaSymbol_getName, METH_NOARGS, "Get the name of the function."},

    {"get_relative_virtual_address", (PyCFunction)PyDiaSymbol_getRelativeVirtualAddress, METH_NOARGS,
     "Get the relative virtual address of the function."},
    {"get_sym_index_id", (PyCFunction)PyDiaSymbol_getSymIndexId, METH_NOARGS, "Get the symbol index ID of the function."},
    {"get_sym_tag", (PyCFunction)PyDiaSymbol_getSymTag, METH_NOARGS, "Get the symbol tag of the function."},
    {"get_token", (PyCFunction)PyDiaSymbol_getToken, METH_NOARGS, "Get the token of the function."},
    {"get_type", (PyCFunction)PyDiaSymbol_getType, METH_NOARGS, "Get the type of the function."},
    {"get_type_id", (PyCFunction)PyDiaSymbol_getTypeId, METH_NOARGS, "Get the type ID of the function."},
    {"get_undecorated_name", (PyCFunction)PyDiaSymbol_getUndecoratedName, METH_NOARGS, "Get the undecorated name of the function."},

#if 0
    // Should be VA_ARGS
    {"get_undecorated_name_ex", (PyCFunction)PyDiaSymbol_getUndecoratedNameEx, METH_NOARGS, "Get the extended undecorated name of the function."},
#endif

    {"get_virtual_address", (PyCFunction)PyDiaSymbol_getVirtualAddress, METH_NOARGS, "Get the virtual address of the function."},
    {"get_virtual_base_offset", (PyCFunction)PyDiaSymbol_getVirtualBaseOffset, METH_NOARGS, "Get the virtual base offset of the function."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define the Python DiaFunction type object
PYDIA_SYMBOL_TYPE_DEFINITION(Function, PyDiaFunction_methods);
TRIVIAL_C_TO_PYTHON_SYMBOL_CONVERSION(Function);
