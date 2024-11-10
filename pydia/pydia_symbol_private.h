#pragma once
// DO NOT INCLUDE THIS HEADER!
// This header is EXPLICITLY only for very internal implementations of the pydia library!
#include <Python.h>
//
#include "pydia_exceptions.h"
#include "pydia_symbol.h"


#define PYDIA_SYMBOL_TYPE_DEFINITION(className, classMethods)                                                                                        \
    PyTypeObject PyDia##className##_Type = {                                                                                                         \
        PyVarObject_HEAD_INIT(NULL, 0) "pydia." #className, /* tp_name */                                                                            \
        sizeof(PyDia##className),                           /* tp_basicsize */                                                                       \
        0,                                                  /* tp_itemsize */                                                                        \
        (destructor)PyDia##className##_dealloc,             /* tp_dealloc */                                                                         \
        0,                                                  /* tp_print */                                                                           \
        0,                                                  /* tp_getattr */                                                                         \
        0,                                                  /* tp_setattr */                                                                         \
        0,                                                  /* tp_as_async */                                                                        \
        (reprfunc)PyDiaSymbol_repr,                         /* tp_repr */                                                                            \
        0,                                                  /* tp_as_number */                                                                       \
        0,                                                  /* tp_as_sequence */                                                                     \
        0,                                                  /* tp_as_mapping */                                                                      \
        (hashfunc)PyDiaSymbol_hash,                         /* tp_hash  */                                                                           \
        0,                                                  /* tp_call */                                                                            \
        0,                                                  /* tp_str */                                                                             \
        0,                                                  /* tp_getattro */                                                                        \
        0,                                                  /* tp_setattro */                                                                        \
        0,                                                  /* tp_as_buffer */                                                                       \
        Py_TPFLAGS_DEFAULT,                                 /* tp_flags */                                                                           \
        #className " object",                               /* tp_doc */                                                                             \
        0,                                                  /* tp_traverse */                                                                        \
        0,                                                  /* tp_clear */                                                                           \
        (richcmpfunc)PyDiaSymbol_richcompare,               /* tp_richcompare */                                                                     \
        0,                                                  /* tp_weaklistoffset */                                                                  \
        0,                                                  /* tp_iter */                                                                            \
        0,                                                  /* tp_iternext */                                                                        \
        classMethods,                                       /* tp_methods */                                                                         \
        0,                                                  /* tp_members */                                                                         \
        0,                                                  /* tp_getset */                                                                          \
        0,                                                  /* tp_base */                                                                            \
        0,                                                  /* tp_dict */                                                                            \
        0,                                                  /* tp_descr_get */                                                                       \
        0,                                                  /* tp_descr_set */                                                                       \
        0,                                                  /* tp_dictoffset */                                                                      \
        (initproc)PyDia##className##_init,                  /* tp_init */                                                                            \
        0,                                                  /* tp_alloc */                                                                           \
        PyType_GenericNew,                                  /* tp_new */                                                                             \
    };


Py_hash_t PyDiaSymbol_hash(PyObject* self);
PyObject* PyDiaSymbol_richcompare(PyObject* self, PyObject* other, int op);
PyObject* PyDiaSymbol_repr(const PyDiaSymbol* self);

PyObject* PyDiaSymbol_getAccess(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getAccess = {"get_access", (PyCFunction)PyDiaSymbol_getAccess, METH_NOARGS,
                                                       "Get the access level of the function."};

PyObject* PyDiaSymbol_getSymIndexId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getSymIndexId = {"get_sym_index_id", (PyCFunction)PyDiaSymbol_getSymIndexId, METH_NOARGS,
                                                           "Get the symbol index ID."};

PyObject* PyDiaSymbol_isScoped(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isScoped = {"is_scoped", (PyCFunction)PyDiaSymbol_isScoped, METH_NOARGS, "Check if the symbol is scoped."};

PyObject* PyDiaSymbol_getClassParent(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getClassParent = {"get_class_parent", (PyCFunction)PyDiaSymbol_getClassParent, METH_NOARGS,
                                                            "Get the class parent of the symbol."};

PyObject* PyDiaSymbol_getClassParentId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getClassParentId = {"get_class_parent_id", (PyCFunction)PyDiaSymbol_getClassParentId, METH_NOARGS,
                                                              "Get the class parent ID."};

PyObject* PyDiaSymbol_isVolatile(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isVolatile = {"is_volatile", (PyCFunction)PyDiaSymbol_isVolatile, METH_NOARGS,
                                                        "Check if the symbol is volatile."};

PyObject* PyDiaSymbol_getLength(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getLength = {"get_length", (PyCFunction)PyDiaSymbol_getLength, METH_NOARGS,
                                                       "Get the length of the symbol."};

PyObject* PyDiaSymbol_isAddressTaken(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isAddressTaken = {"is_address_taken", (PyCFunction)PyDiaSymbol_isAddressTaken, METH_NOARGS,
                                                            "Check if the address is taken."};

PyObject* PyDiaSymbol_getAge(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getAge = {"get_age", (PyCFunction)PyDiaSymbol_getAge, METH_NOARGS, "Get the age of the symbol."};

PyObject* PyDiaSymbol_getArrayIndexType(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getArrayIndexType = {"get_array_index_type", (PyCFunction)PyDiaSymbol_getArrayIndexType, METH_NOARGS,
                                                               "Get the array index type of the symbol."};

PyObject* PyDiaSymbol_getArrayIndexTypeId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getArrayIndexTypeId = {"get_array_index_type_id", (PyCFunction)PyDiaSymbol_getArrayIndexTypeId, METH_NOARGS,
                                                                 "Get the array index type ID."};

PyObject* PyDiaSymbol_getBackendBuild(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getBackendBuild = {"get_backend_build", (PyCFunction)PyDiaSymbol_getBackendBuild, METH_NOARGS,
                                                             "Get the backend build version."};

PyObject* PyDiaSymbol_getBackendMajor(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getBackendMajor = {"get_backend_major", (PyCFunction)PyDiaSymbol_getBackendMajor, METH_NOARGS,
                                                             "Get the backend major version."};

PyObject* PyDiaSymbol_getBackendMinor(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getBackendMinor = {"get_backend_minor", (PyCFunction)PyDiaSymbol_getBackendMinor, METH_NOARGS,
                                                             "Get the backend minor version."};

PyObject* PyDiaSymbol_getBackendQfe(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getBackendQfe = {"get_backend_qfe", (PyCFunction)PyDiaSymbol_getBackendQfe, METH_NOARGS,
                                                           "Get the backend QFE version."};

PyObject* PyDiaSymbol_getBaseDataOffset(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getBaseDataOffset = {"get_base_data_offset", (PyCFunction)PyDiaSymbol_getBaseDataOffset, METH_NOARGS,
                                                               "Get the base data offset of the symbol."};

PyObject* PyDiaSymbol_getBaseDataSlot(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getBaseDataSlot = {"get_base_data_slot", (PyCFunction)PyDiaSymbol_getBaseDataSlot, METH_NOARGS,
                                                             "Get the base data slot of the symbol."};

PyObject* PyDiaSymbol_getBaseSymbol(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getBaseSymbol = {"get_base_symbol", (PyCFunction)PyDiaSymbol_getBaseSymbol, METH_NOARGS,
                                                           "Get the base symbol of the symbol."};

PyObject* PyDiaSymbol_getBaseSymbolId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getBaseSymbolId = {"get_base_symbol_id", (PyCFunction)PyDiaSymbol_getBaseSymbolId, METH_NOARGS,
                                                             "Get the base symbol ID."};

PyObject* PyDiaSymbol_getBaseType(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getBaseType = {"get_base_type", (PyCFunction)PyDiaSymbol_getBaseType, METH_NOARGS,
                                                         "Get the base type of the symbol."};

PyObject* PyDiaSymbol_getBitPosition(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getBitPosition = {"get_bit_position", (PyCFunction)PyDiaSymbol_getBitPosition, METH_NOARGS,
                                                            "Get the bit position of the symbol."};

PyObject* PyDiaSymbol_getBindId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getBindId = {"get_bind_id", (PyCFunction)PyDiaSymbol_getBindId, METH_NOARGS,
                                                       "Get the bind ID of the symbol."};

PyObject* PyDiaSymbol_getBindSlot(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getBindSlot = {"get_bind_slot", (PyCFunction)PyDiaSymbol_getBindSlot, METH_NOARGS,
                                                         "Get the bind slot of the symbol."};

PyObject* PyDiaSymbol_isCode(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isCode = {"is_code", (PyCFunction)PyDiaSymbol_isCode, METH_NOARGS, "Check if the symbol represents code."};

PyObject* PyDiaSymbol_getCoffGroup(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getCoffGroup = {"get_coff_group", (PyCFunction)PyDiaSymbol_getCoffGroup, METH_NOARGS,
                                                          "Get the COFF group of the symbol."};

PyObject* PyDiaSymbol_isCompilerGenerated(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isCompilerGenerated = {"is_compiler_generated", (PyCFunction)PyDiaSymbol_isCompilerGenerated, METH_NOARGS,
                                                                 "Check if the symbol is compiler-generated."};

PyObject* PyDiaSymbol_getCompilerName(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getCompilerName = {"get_compiler_name", (PyCFunction)PyDiaSymbol_getCompilerName, METH_NOARGS,
                                                             "Get the compiler name of the symbol."};

PyObject* PyDiaSymbol_isConst(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isConst = {"is_const", (PyCFunction)PyDiaSymbol_isConst, METH_NOARGS, "Check if the symbol is constant."};

PyObject* PyDiaSymbol_isConstantExport(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isConstantExport = {"is_constant_export", (PyCFunction)PyDiaSymbol_isConstantExport, METH_NOARGS,
                                                              "Check if the symbol is a constant export."};

PyObject* PyDiaSymbol_hasConstructor(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasConstructor = {"has_constructor", (PyCFunction)PyDiaSymbol_hasConstructor, METH_NOARGS,
                                                            "Check if the symbol has a constructor."};

PyObject* PyDiaSymbol_getCount(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getCount = {"get_count", (PyCFunction)PyDiaSymbol_getCount, METH_NOARGS, "Get the count of the symbol."};

PyObject* PyDiaSymbol_getCountLiveRanges(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getCountLiveRanges = {"get_count_live_ranges", (PyCFunction)PyDiaSymbol_getCountLiveRanges, METH_NOARGS,
                                                                "Get the count of live ranges for the symbol."};

PyObject* PyDiaSymbol_hasCustomCallingConvention(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasCustomCallingConvention = {"has_custom_calling_convention",
                                                                        (PyCFunction)PyDiaSymbol_hasCustomCallingConvention, METH_NOARGS,
                                                                        "Check if the symbol has a custom calling convention."};

PyObject* PyDiaSymbol_getCallingConvention(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getCallingConvention = {"get_calling_convention", (PyCFunction)PyDiaSymbol_getCallingConvention,
                                                                  METH_NOARGS, "Get the calling convention of the symbol."};

#if 0
PyObject* PyDiaSymbol_getDataBytes(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getDataBytes = {"get_data_bytes", (PyCFunction)PyDiaSymbol_getDataBytes, METH_NOARGS,
                                                          "Get the data bytes of the symbol."};
#endif

PyObject* PyDiaSymbol_isDataExport(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isDataExport = {"is_data_export", (PyCFunction)PyDiaSymbol_isDataExport, METH_NOARGS,
                                                          "Check if the symbol is a data export."};

PyObject* PyDiaSymbol_getDataKind(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getDataKind = {"get_data_kind", (PyCFunction)PyDiaSymbol_getDataKind, METH_NOARGS,
                                                         "Get the data kind of the symbol."};

PyObject* PyDiaSymbol_isEditAndContinueEnabled(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isEditAndContinueEnabled = {"is_edit_and_continue_enabled",
                                                                      (PyCFunction)PyDiaSymbol_isEditAndContinueEnabled, METH_NOARGS,
                                                                      "Check if Edit and Continue is enabled for the symbol."};

PyObject* PyDiaSymbol_getExceptionHandlerAddressOffset(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getExceptionHandlerAddressOffset = {"get_exception_handler_address_offset",
                                                                              (PyCFunction)PyDiaSymbol_getExceptionHandlerAddressOffset, METH_NOARGS,
                                                                              "Get the exception handler address offset for the symbol."};

PyObject* PyDiaSymbol_getExceptionHandlerAddressSection(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getExceptionHandlerAddressSection = {
    "get_exception_handler_address_section", (PyCFunction)PyDiaSymbol_getExceptionHandlerAddressSection, METH_NOARGS,
    "Get the exception handler address section for the symbol."};

PyObject* PyDiaSymbol_getExceptionHandlerRelativeVirtualAddress(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getExceptionHandlerRelativeVirtualAddress = {
    "get_exception_handler_relative_virtual_address", (PyCFunction)PyDiaSymbol_getExceptionHandlerRelativeVirtualAddress, METH_NOARGS,
    "Get the exception handler relative virtual address for the symbol."};

PyObject* PyDiaSymbol_getExceptionHandlerVirtualAddress(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getExceptionHandlerVirtualAddress = {
    "get_exception_handler_virtual_address", (PyCFunction)PyDiaSymbol_getExceptionHandlerVirtualAddress, METH_NOARGS,
    "Get the exception handler virtual address for the symbol."};

PyObject* PyDiaSymbol_isExportWithExplicitOrdinal(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isExportWithExplicitOrdinal = {"is_export_with_explicit_ordinal",
                                                                         (PyCFunction)PyDiaSymbol_isExportWithExplicitOrdinal, METH_NOARGS,
                                                                         "Check if the symbol is an export with an explicit ordinal."};

PyObject* PyDiaSymbol_isExportForwarder(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isExportForwarder = {"is_export_forwarder", (PyCFunction)PyDiaSymbol_isExportForwarder, METH_NOARGS,
                                                               "Check if the symbol is an export forwarder."};

PyObject* PyDiaSymbol_isFarReturn(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isFarReturn = {"is_far_return", (PyCFunction)PyDiaSymbol_isFarReturn, METH_NOARGS,
                                                         "Check if the symbol has a far return."};
PyObject* PyDiaSymbol_getFinalLiveStaticSize(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getFinalLiveStaticSize = {"get_final_live_static_size", (PyCFunction)PyDiaSymbol_getFinalLiveStaticSize,
                                                                    METH_NOARGS, "Get the final live static size of the symbol."};

PyObject* PyDiaSymbol_isFramePointerPresent(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isFramePointerPresent = {"is_frame_pointer_present", (PyCFunction)PyDiaSymbol_isFramePointerPresent,
                                                                   METH_NOARGS, "Check if the frame pointer is present for the symbol."};

PyObject* PyDiaSymbol_getFrameSize(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getFrameSize = {"get_frame_size", (PyCFunction)PyDiaSymbol_getFrameSize, METH_NOARGS,
                                                          "Get the frame size of the symbol."};

PyObject* PyDiaSymbol_getFrontEndBuild(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getFrontEndBuild = {"get_front_end_build", (PyCFunction)PyDiaSymbol_getFrontEndBuild, METH_NOARGS,
                                                              "Get the front-end build version of the symbol."};

PyObject* PyDiaSymbol_getFrontEndMajor(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getFrontEndMajor = {"get_front_end_major", (PyCFunction)PyDiaSymbol_getFrontEndMajor, METH_NOARGS,
                                                              "Get the front-end major version of the symbol."};

PyObject* PyDiaSymbol_getFrontEndMinor(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getFrontEndMinor = {"get_front_end_minor", (PyCFunction)PyDiaSymbol_getFrontEndMinor, METH_NOARGS,
                                                              "Get the front-end minor version of the symbol."};

PyObject* PyDiaSymbol_getFrontEndQfe(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getFrontEndQfe = {"get_front_end_qfe", (PyCFunction)PyDiaSymbol_getFrontEndQfe, METH_NOARGS,
                                                            "Get the front-end QFE (Quick Fix Engineering) version of the symbol."};

PyObject* PyDiaSymbol_isFunction(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isFunction = {"is_function", (PyCFunction)PyDiaSymbol_isFunction, METH_NOARGS,
                                                        "Check if the symbol represents a function."};

PyObject* PyDiaSymbol_getGuid(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getGuid = {"get_guid", (PyCFunction)PyDiaSymbol_getGuid, METH_NOARGS, "Get the GUID of the symbol."};

PyObject* PyDiaSymbol_hasAlloca(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasAlloca = {"has_alloca", (PyCFunction)PyDiaSymbol_hasAlloca, METH_NOARGS,
                                                       "Check if the symbol uses alloca."};

PyObject* PyDiaSymbol_hasAssignmentOperator(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasAssignmentOperator = {"has_assignment_operator", (PyCFunction)PyDiaSymbol_hasAssignmentOperator,
                                                                   METH_NOARGS, "Check if the symbol has an assignment operator."};

PyObject* PyDiaSymbol_hasCastOperator(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasCastOperator = {"has_cast_operator", (PyCFunction)PyDiaSymbol_hasCastOperator, METH_NOARGS,
                                                             "Check if the symbol has a cast operator."};

PyObject* PyDiaSymbol_hasControlFlowCheck(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasControlFlowCheck = {"has_control_flow_check", (PyCFunction)PyDiaSymbol_hasControlFlowCheck, METH_NOARGS,
                                                                 "Check if the symbol has control flow check enabled."};

PyObject* PyDiaSymbol_hasDebugInfo(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasDebugInfo = {"has_debug_info", (PyCFunction)PyDiaSymbol_hasDebugInfo, METH_NOARGS,
                                                          "Check if the symbol has debug information."};

PyObject* PyDiaSymbol_hasEh(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasEh = {"has_eh", (PyCFunction)PyDiaSymbol_hasEh, METH_NOARGS,
                                                   "Check if the symbol has exception handling (EH) enabled."};

PyObject* PyDiaSymbol_hasEha(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasEha = {"has_eha", (PyCFunction)PyDiaSymbol_hasEha, METH_NOARGS,
                                                    "Check if the symbol has asynchronous exception handling (EHA) enabled."};

PyObject* PyDiaSymbol_hasInlineAsm(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasInlineAsm = {"has_inline_asm", (PyCFunction)PyDiaSymbol_hasInlineAsm, METH_NOARGS,
                                                          "Check if the symbol contains inline assembly."};

PyObject* PyDiaSymbol_hasLongJump(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasLongJump = {"has_long_jump", (PyCFunction)PyDiaSymbol_hasLongJump, METH_NOARGS,
                                                         "Check if the symbol uses long jump (setjmp/longjmp)."};

PyObject* PyDiaSymbol_hasManagedCode(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasManagedCode = {"has_managed_code", (PyCFunction)PyDiaSymbol_hasManagedCode, METH_NOARGS,
                                                            "Check if the symbol contains managed code."};

PyObject* PyDiaSymbol_hasNestedTypes(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasNestedTypes = {"has_nested_types", (PyCFunction)PyDiaSymbol_hasNestedTypes, METH_NOARGS,
                                                            "Check if the symbol has nested types."};

PyObject* PyDiaSymbol_hasSeh(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasSeh = {"has_seh", (PyCFunction)PyDiaSymbol_hasSeh, METH_NOARGS,
                                                    "Check if the symbol has structured exception handling (SEH) enabled."};
PyObject* PyDiaSymbol_hasSecurityChecks(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasSecurityChecks = {"has_security_checks", (PyCFunction)PyDiaSymbol_hasSecurityChecks, METH_NOARGS,
                                                               "Check if the symbol has security checks enabled."};

PyObject* PyDiaSymbol_hasSetJump(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasSetJump = {"has_set_jump", (PyCFunction)PyDiaSymbol_hasSetJump, METH_NOARGS,
                                                        "Check if the symbol uses set jump."};

PyObject* PyDiaSymbol_hasValidPgoCounts(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasValidPgoCounts = {"has_valid_pgo_counts", (PyCFunction)PyDiaSymbol_hasValidPgoCounts, METH_NOARGS,
                                                               "Check if the symbol has valid PGO counts."};

PyObject* PyDiaSymbol_getHfaDouble(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getHfaDouble = {"get_hfa_double", (PyCFunction)PyDiaSymbol_getHfaDouble, METH_NOARGS,
                                                          "Get the HFA (Homogeneous Floating-point Aggregate) double status of the symbol."};

PyObject* PyDiaSymbol_getHfaFloat(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getHfaFloat = {"get_hfa_float", (PyCFunction)PyDiaSymbol_getHfaFloat, METH_NOARGS,
                                                         "Get the HFA (Homogeneous Floating-point Aggregate) float status of the symbol."};

PyObject* PyDiaSymbol_getIndirectVirtualBaseClass(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getIndirectVirtualBaseClass = {"get_indirect_virtual_base_class",
                                                                         (PyCFunction)PyDiaSymbol_getIndirectVirtualBaseClass, METH_NOARGS,
                                                                         "Get the indirect virtual base class of the symbol."};

PyObject* PyDiaSymbol_hasInlineSpecifier(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasInlineSpecifier = {"has_inline_specifier", (PyCFunction)PyDiaSymbol_hasInlineSpecifier, METH_NOARGS,
                                                                "Check if the symbol has an inline specifier."};

PyObject* PyDiaSymbol_hasInterruptReturn(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasInterruptReturn = {"has_interrupt_return", (PyCFunction)PyDiaSymbol_hasInterruptReturn, METH_NOARGS,
                                                                "Check if the symbol has an interrupt return."};

PyObject* PyDiaSymbol_isIntrinsic(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isIntrinsic = {"is_intrinsic", (PyCFunction)PyDiaSymbol_isIntrinsic, METH_NOARGS,
                                                         "Check if the symbol is intrinsic."};

PyObject* PyDiaSymbol_isIntro(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isIntro = {"is_intro", (PyCFunction)PyDiaSymbol_isIntro, METH_NOARGS,
                                                     "Check if the symbol is introductory."};

PyObject* PyDiaSymbol_isAggregated(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isAggregated = {"is_aggregated", (PyCFunction)PyDiaSymbol_isAggregated, METH_NOARGS,
                                                          "Check if the symbol is aggregated."};

PyObject* PyDiaSymbol_isCtypes(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isCtypes = {"is_ctypes", (PyCFunction)PyDiaSymbol_isCtypes, METH_NOARGS,
                                                      "Check if the symbol is of ctypes type."};

PyObject* PyDiaSymbol_isConstructorVirtualBase(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isConstructorVirtualBase = {"is_constructor_virtual_base",
                                                                      (PyCFunction)PyDiaSymbol_isConstructorVirtualBase, METH_NOARGS,
                                                                      "Check if the symbol is a constructor for a virtual base class."};

PyObject* PyDiaSymbol_isCxxReturnUdt(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isCxxReturnUdt = {"is_cxx_return_udt", (PyCFunction)PyDiaSymbol_isCxxReturnUdt, METH_NOARGS,
                                                            "Check if the symbol returns a C++ user-defined type (UDT)."};

PyObject* PyDiaSymbol_isDataAligned(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isDataAligned = {"is_data_aligned", (PyCFunction)PyDiaSymbol_isDataAligned, METH_NOARGS,
                                                           "Check if the symbol data is aligned."};

PyObject* PyDiaSymbol_isHlslData(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isHlslData = {"is_hlsl_data", (PyCFunction)PyDiaSymbol_isHlslData, METH_NOARGS,
                                                        "Check if the symbol represents HLSL data."};

PyObject* PyDiaSymbol_isMultipleInheritance(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isMultipleInheritance = {"is_multiple_inheritance", (PyCFunction)PyDiaSymbol_isMultipleInheritance,
                                                                   METH_NOARGS, "Check if the symbol has multiple inheritance."};

PyObject* PyDiaSymbol_isNaked(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isNaked = {"is_naked", (PyCFunction)PyDiaSymbol_isNaked, METH_NOARGS,
                                                     "Check if the symbol is naked (has no prologue/epilogue)."};

PyObject* PyDiaSymbol_isOptimizedAway(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isOptimizedAway = {"is_optimized_away", (PyCFunction)PyDiaSymbol_isOptimizedAway, METH_NOARGS,
                                                             "Check if the symbol is optimized away."};

PyObject* PyDiaSymbol_isOptimizedForSpeed(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isOptimizedForSpeed = {"is_optimized_for_speed", (PyCFunction)PyDiaSymbol_isOptimizedForSpeed, METH_NOARGS,
                                                                 "Check if the symbol is optimized for speed."};

PyObject* PyDiaSymbol_isPgo(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isPgo = {"is_pgo", (PyCFunction)PyDiaSymbol_isPgo, METH_NOARGS,
                                                   "Check if the symbol is optimized with Profile-Guided Optimization (PGO)."};

PyObject* PyDiaSymbol_isPointerToDataMember(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isPointerToDataMember = {"is_pointer_to_data_member", (PyCFunction)PyDiaSymbol_isPointerToDataMember,
                                                                   METH_NOARGS, "Check if the symbol is a pointer to a data member."};

PyObject* PyDiaSymbol_isSingleInheritance(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isSingleInheritance = {"is_single_inheritance", (PyCFunction)PyDiaSymbol_isSingleInheritance, METH_NOARGS,
                                                                 "Check if the symbol has single inheritance."};
PyObject* PyDiaSymbol_isSplitted(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isSplitted = {"is_splitted", (PyCFunction)PyDiaSymbol_isSplitted, METH_NOARGS,
                                                        "Check if the symbol is split."};

PyObject* PyDiaSymbol_isStatic(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isStatic = {"is_static", (PyCFunction)PyDiaSymbol_isStatic, METH_NOARGS, "Check if the symbol is static."};

PyObject* PyDiaSymbol_isStripped(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isStripped = {"is_stripped", (PyCFunction)PyDiaSymbol_isStripped, METH_NOARGS,
                                                        "Check if the symbol is stripped."};

PyObject* PyDiaSymbol_getLanguage(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getLanguage = {"get_language", (PyCFunction)PyDiaSymbol_getLanguage, METH_NOARGS,
                                                         "Get the language of the symbol."};

PyObject* PyDiaSymbol_getLexicalParent(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getLexicalParent = {"get_lexical_parent", (PyCFunction)PyDiaSymbol_getLexicalParent, METH_NOARGS,
                                                              "Get the lexical parent of the symbol."};

PyObject* PyDiaSymbol_getLexicalParentId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getLexicalParentId = {"get_lexical_parent_id", (PyCFunction)PyDiaSymbol_getLexicalParentId, METH_NOARGS,
                                                                "Get the lexical parent ID of the symbol."};

PyObject* PyDiaSymbol_getLibraryName(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getLibraryName = {"get_library_name", (PyCFunction)PyDiaSymbol_getLibraryName, METH_NOARGS,
                                                            "Get the library name of the symbol."};

PyObject* PyDiaSymbol_getLiveRangeLength(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getLiveRangeLength = {"get_live_range_length", (PyCFunction)PyDiaSymbol_getLiveRangeLength, METH_NOARGS,
                                                                "Get the live range length of the symbol."};

PyObject* PyDiaSymbol_getLiveRangeStartAddressOffset(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getLiveRangeStartAddressOffset = {"get_live_range_start_address_offset",
                                                                            (PyCFunction)PyDiaSymbol_getLiveRangeStartAddressOffset, METH_NOARGS,
                                                                            "Get the live range start address offset of the symbol."};

PyObject* PyDiaSymbol_getLiveRangeStartAddressSection(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getLiveRangeStartAddressSection = {"get_live_range_start_address_section",
                                                                             (PyCFunction)PyDiaSymbol_getLiveRangeStartAddressSection, METH_NOARGS,
                                                                             "Get the live range start address section of the symbol."};

PyObject* PyDiaSymbol_getLiveRangeStartRelativeVirtualAddress(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getLiveRangeStartRelativeVirtualAddress = {
    "get_live_range_start_relative_virtual_address", (PyCFunction)PyDiaSymbol_getLiveRangeStartRelativeVirtualAddress, METH_NOARGS,
    "Get the live range start relative virtual address of the symbol."};

PyObject* PyDiaSymbol_getLocalBasePointerRegisterId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getLocalBasePointerRegisterId = {"get_local_base_pointer_register_id",
                                                                           (PyCFunction)PyDiaSymbol_getLocalBasePointerRegisterId, METH_NOARGS,
                                                                           "Get the local base pointer register ID of the symbol."};

PyObject* PyDiaSymbol_getLocationType(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getLocationType = {"get_location_type", (PyCFunction)PyDiaSymbol_getLocationType, METH_NOARGS,
                                                             "Get the location type of the symbol."};

PyObject* PyDiaSymbol_getLowerBound(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getLowerBound = {"get_lower_bound", (PyCFunction)PyDiaSymbol_getLowerBound, METH_NOARGS,
                                                           "Get the lower bound of the symbol."};

PyObject* PyDiaSymbol_getLowerBoundId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getLowerBoundId = {"get_lower_bound_id", (PyCFunction)PyDiaSymbol_getLowerBoundId, METH_NOARGS,
                                                             "Get the lower bound ID of the symbol."};

PyObject* PyDiaSymbol_getMachineType(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getMachineType = {"get_machine_type", (PyCFunction)PyDiaSymbol_getMachineType, METH_NOARGS,
                                                            "Get the machine type of the symbol."};

PyObject* PyDiaSymbol_isManaged(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isManaged = {"is_managed", (PyCFunction)PyDiaSymbol_isManaged, METH_NOARGS,
                                                       "Check if the symbol is managed."};

PyObject* PyDiaSymbol_getMemorySpaceKind(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getMemorySpaceKind = {"get_memory_space_kind", (PyCFunction)PyDiaSymbol_getMemorySpaceKind, METH_NOARGS,
                                                                "Get the memory space kind of the symbol."};

PyObject* PyDiaSymbol_getModifierValues(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getModifierValues = {"get_modifier_values", (PyCFunction)PyDiaSymbol_getModifierValues, METH_NOARGS,
                                                               "Get the modifier values of the symbol."};

PyObject* PyDiaSymbol_isMsil(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isMsil = {"is_msil", (PyCFunction)PyDiaSymbol_isMsil, METH_NOARGS,
                                                    "Check if the symbol is MSIL (Microsoft Intermediate Language)."};

PyObject* PyDiaSymbol_getName(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getName = {"get_name", (PyCFunction)PyDiaSymbol_getName, METH_NOARGS, "Get the name of the symbol."};

PyObject* PyDiaSymbol_isNested(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isNested = {"is_nested", (PyCFunction)PyDiaSymbol_isNested, METH_NOARGS, "Check if the symbol is nested."};

PyObject* PyDiaSymbol_isNoInline(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isNoInline = {"is_no_inline", (PyCFunction)PyDiaSymbol_isNoInline, METH_NOARGS,
                                                        "Check if the symbol has no inline specifier."};
PyObject* PyDiaSymbol_isNoNameExport(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isNoNameExport = {"is_no_name_export", (PyCFunction)PyDiaSymbol_isNoNameExport, METH_NOARGS,
                                                            "Check if the symbol has no name export."};

PyObject* PyDiaSymbol_isNoReturn(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isNoReturn = {"is_no_return", (PyCFunction)PyDiaSymbol_isNoReturn, METH_NOARGS,
                                                        "Check if the symbol is marked as no return."};

PyObject* PyDiaSymbol_hasNoStackOrdering(const PyDiaSymbol* self);  // TODO: This name is odd
static PyMethodDef PyDiaSymbolMethodEntry_hasNoStackOrdering = {"has_no_stack_ordering", (PyCFunction)PyDiaSymbol_hasNoStackOrdering, METH_NOARGS,
                                                                "Check if the symbol has no stack ordering."};

PyObject* PyDiaSymbol_isNotReached(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isNotReached = {"is_not_reached", (PyCFunction)PyDiaSymbol_isNotReached, METH_NOARGS,
                                                          "Check if the symbol is not reached."};

PyObject* PyDiaSymbol_getNumberOfModifiers(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getNumberOfModifiers = {"get_number_of_modifiers", (PyCFunction)PyDiaSymbol_getNumberOfModifiers,
                                                                  METH_NOARGS, "Get the number of modifiers of the symbol."};

PyObject* PyDiaSymbol_getNumberOfRegisterIndices(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getNumberOfRegisterIndices = {"get_number_of_register_indices",
                                                                        (PyCFunction)PyDiaSymbol_getNumberOfRegisterIndices, METH_NOARGS,
                                                                        "Get the number of register indices of the symbol."};

PyObject* PyDiaSymbol_getObjectFileName(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getObjectFileName = {"get_object_file_name", (PyCFunction)PyDiaSymbol_getObjectFileName, METH_NOARGS,
                                                               "Get the object file name of the symbol."};

PyObject* PyDiaSymbol_getObjectPointerType(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getObjectPointerType = {"get_object_pointer_type", (PyCFunction)PyDiaSymbol_getObjectPointerType,
                                                                  METH_NOARGS, "Get the object pointer type of the symbol."};

PyObject* PyDiaSymbol_getOemId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getOemId = {"get_oem_id", (PyCFunction)PyDiaSymbol_getOemId, METH_NOARGS, "Get the OEM ID of the symbol."};

PyObject* PyDiaSymbol_getOemSymbolId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getOemSymbolId = {"get_oem_symbol_id", (PyCFunction)PyDiaSymbol_getOemSymbolId, METH_NOARGS,
                                                            "Get the OEM symbol ID of the symbol."};

PyObject* PyDiaSymbol_getOffset(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getOffset = {"get_offset", (PyCFunction)PyDiaSymbol_getOffset, METH_NOARGS,
                                                       "Get the offset of the symbol."};

PyObject* PyDiaSymbol_getOffsetInUdt(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getOffsetInUdt = {"get_offset_in_udt", (PyCFunction)PyDiaSymbol_getOffsetInUdt, METH_NOARGS,
                                                            "Get the offset in UDT of the symbol."};

PyObject* PyDiaSymbol_hasOptimizedCodeDebugInfo(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasOptimizedCodeDebugInfo = {"has_optimized_code_debug_info",
                                                                       (PyCFunction)PyDiaSymbol_hasOptimizedCodeDebugInfo, METH_NOARGS,
                                                                       "Check if the symbol has optimized code debug info."};

PyObject* PyDiaSymbol_getOrdinal(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getOrdinal = {"get_ordinal", (PyCFunction)PyDiaSymbol_getOrdinal, METH_NOARGS,
                                                        "Get the ordinal of the symbol."};

PyObject* PyDiaSymbol_hasOverloadedOperator(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasOverloadedOperator = {"has_overloaded_operator", (PyCFunction)PyDiaSymbol_hasOverloadedOperator,
                                                                   METH_NOARGS, "Check if the symbol has an overloaded operator."};

PyObject* PyDiaSymbol_getPgoDynamicInstructionCount(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getPgoDynamicInstructionCount = {"get_pgo_dynamic_instruction_count",
                                                                           (PyCFunction)PyDiaSymbol_getPgoDynamicInstructionCount, METH_NOARGS,
                                                                           "Get the PGO dynamic instruction count of the symbol."};

PyObject* PyDiaSymbol_isPacked(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isPacked = {"is_packed", (PyCFunction)PyDiaSymbol_isPacked, METH_NOARGS, "Check if the symbol is packed."};


#if 0
PyObject* PyDiaSymbol_getNumericProperties(const PyDiaSymbol* self);
#endif

PyObject* PyDiaSymbol_isPure(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isPure = {"is_pure", (PyCFunction)PyDiaSymbol_isPure, METH_NOARGS,
                                                    "Check if the function is pure virtual."};
PyObject* PyDiaSymbol_getNumberOfRows(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getNumberOfRows = {"get_number_of_rows", (PyCFunction)PyDiaSymbol_getNumberOfRows, METH_NOARGS,
                                                             "Get the number of rows associated with the symbol."};

PyObject* PyDiaSymbol_isRValueReference(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isRValueReference = {"is_rvalue_reference", (PyCFunction)PyDiaSymbol_isRValueReference, METH_NOARGS,
                                                               "Check if the symbol is an rvalue reference."};

PyObject* PyDiaSymbol_getRank(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getRank = {"get_rank", (PyCFunction)PyDiaSymbol_getRank, METH_NOARGS, "Get the rank of the symbol."};

PyObject* PyDiaSymbol_isReference(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isReference = {"is_reference", (PyCFunction)PyDiaSymbol_isReference, METH_NOARGS,
                                                         "Check if the symbol is a reference."};

PyObject* PyDiaSymbol_getRegisterType(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getRegisterType = {"get_register_type", (PyCFunction)PyDiaSymbol_getRegisterType, METH_NOARGS,
                                                             "Get the register type of the symbol."};

PyObject* PyDiaSymbol_getRelativeVirtualAddress(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getRelativeVirtualAddress = {"get_relative_virtual_address",
                                                                       (PyCFunction)PyDiaSymbol_getRelativeVirtualAddress, METH_NOARGS,
                                                                       "Get the relative virtual address of the symbol."};

PyObject* PyDiaSymbol_isRestrictedType(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isRestrictedType = {"is_restricted_type", (PyCFunction)PyDiaSymbol_isRestrictedType, METH_NOARGS,
                                                              "Check if the symbol is a restricted type."};

PyObject* PyDiaSymbol_getSamplerSlot(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getSamplerSlot = {"get_sampler_slot", (PyCFunction)PyDiaSymbol_getSamplerSlot, METH_NOARGS,
                                                            "Get the sampler slot of the symbol."};

PyObject* PyDiaSymbol_isSealed(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isSealed = {"is_sealed", (PyCFunction)PyDiaSymbol_isSealed, METH_NOARGS, "Check if the symbol is sealed."};

PyObject* PyDiaSymbol_getSignature(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getSignature = {"get_signature", (PyCFunction)PyDiaSymbol_getSignature, METH_NOARGS,
                                                          "Get the signature of the symbol."};

PyObject* PyDiaSymbol_getSizeInUdt(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getSizeInUdt = {"get_size_in_udt", (PyCFunction)PyDiaSymbol_getSizeInUdt, METH_NOARGS,
                                                          "Get the size in UDT of the symbol."};

PyObject* PyDiaSymbol_getSlot(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getSlot = {"get_slot", (PyCFunction)PyDiaSymbol_getSlot, METH_NOARGS,
                                                     "Get the slot associated with the symbol."};

PyObject* PyDiaSymbol_getSourceFileName(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getSourceFileName = {"get_source_file_name", (PyCFunction)PyDiaSymbol_getSourceFileName, METH_NOARGS,
                                                               "Get the source file name of the symbol."};

PyObject* PyDiaSymbol_getStaticSize(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getStaticSize = {"get_static_size", (PyCFunction)PyDiaSymbol_getStaticSize, METH_NOARGS,
                                                           "Get the static size of the symbol."};

PyObject* PyDiaSymbol_hasStrictGsCheck(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_hasStrictGsCheck = {"has_strict_gs_check", (PyCFunction)PyDiaSymbol_hasStrictGsCheck, METH_NOARGS,
                                                              "Check if the symbol has strict GS check enabled."};

PyObject* PyDiaSymbol_getStride(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getStride = {"get_stride", (PyCFunction)PyDiaSymbol_getStride, METH_NOARGS,
                                                       "Get the stride associated with the symbol."};

PyObject* PyDiaSymbol_getSubType(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getSubType = {"get_sub_type", (PyCFunction)PyDiaSymbol_getSubType, METH_NOARGS,
                                                        "Get the sub-type of the symbol."};

PyObject* PyDiaSymbol_getSubTypeId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getSubTypeId = {"get_sub_type_id", (PyCFunction)PyDiaSymbol_getSubTypeId, METH_NOARGS,
                                                          "Get the sub-type ID of the symbol."};

PyObject* PyDiaSymbol_getSymTag(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getSymTag = {"get_sym_tag", (PyCFunction)PyDiaSymbol_getSymTag, METH_NOARGS,
                                                       "Get the symbol tag of the symbol."};

PyObject* PyDiaSymbol_getSymbolsFileName(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getSymbolsFileName = {"get_symbols_file_name", (PyCFunction)PyDiaSymbol_getSymbolsFileName, METH_NOARGS,
                                                                "Get the symbols file name of the symbol."};

PyObject* PyDiaSymbol_getTargetOffset(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getTargetOffset = {"get_target_offset", (PyCFunction)PyDiaSymbol_getTargetOffset, METH_NOARGS,
                                                             "Get the target offset of the symbol."};

PyObject* PyDiaSymbol_getThisAdjust(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getThisAdjust = {"get_this_adjust", (PyCFunction)PyDiaSymbol_getThisAdjust, METH_NOARGS,
                                                           "Get the this-adjustment of the symbol."};

PyObject* PyDiaSymbol_getThunkOrdinal(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getThunkOrdinal = {"get_thunk_ordinal", (PyCFunction)PyDiaSymbol_getThunkOrdinal, METH_NOARGS,
                                                             "Get the thunk ordinal of the symbol."};

PyObject* PyDiaSymbol_getTimeStamp(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getTimeStamp = {"get_time_stamp", (PyCFunction)PyDiaSymbol_getTimeStamp, METH_NOARGS,
                                                          "Get the timestamp of the symbol."};

PyObject* PyDiaSymbol_getToken(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getToken = {"get_token", (PyCFunction)PyDiaSymbol_getToken, METH_NOARGS,
                                                      "Get the token associated with the symbol."};

PyObject* PyDiaSymbol_getType(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getType = {"get_type", (PyCFunction)PyDiaSymbol_getType, METH_NOARGS, "Get the type of the symbol."};

PyObject* PyDiaSymbol_getTypeId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getTypeId = {"get_type_id", (PyCFunction)PyDiaSymbol_getTypeId, METH_NOARGS,
                                                       "Get the type ID of the symbol."};

PyObject* PyDiaSymbol_getTypeIds(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getTypeIds = {"get_type_ids", (PyCFunction)PyDiaSymbol_getTypeIds, METH_NOARGS,
                                                        "Get the type IDs associated with the symbol."};

PyObject* PyDiaSymbol_getTypes(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getTypes = {"get_types", (PyCFunction)PyDiaSymbol_getTypes, METH_NOARGS,
                                                      "Get the types associated with the symbol."};

PyObject* PyDiaSymbol_isUnaligned(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isUnaligned = {"is_unaligned", (PyCFunction)PyDiaSymbol_isUnaligned, METH_NOARGS,
                                                         "Check if the symbol is unaligned."};

PyObject* PyDiaSymbol_getUndecoratedName(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getUndecoratedName = {"get_undecorated_name", (PyCFunction)PyDiaSymbol_getUndecoratedName, METH_NOARGS,
                                                                "Get the undecorated name of the symbol."};

PyObject* PyDiaSymbol_getUndecoratedNameEx(const PyDiaSymbol* self, DWORD options);
static PyMethodDef PyDiaSymbolMethodEntry_getUndecoratedNameEx = {"get_undecorated_name_ex", (PyCFunction)PyDiaSymbol_getUndecoratedNameEx,
                                                                  METH_VARARGS, "Get the undecorated name of the symbol with options."};

PyObject* PyDiaSymbol_getUnmodifiedType(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getUnmodifiedType = {"get_unmodified_type", (PyCFunction)PyDiaSymbol_getUnmodifiedType, METH_NOARGS,
                                                               "Get the unmodified type of the symbol."};

PyObject* PyDiaSymbol_isUnused(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isUnused = {"is_unused", (PyCFunction)PyDiaSymbol_isUnused, METH_NOARGS, "Check if the symbol is unused."};

PyObject* PyDiaSymbol_getValue(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getValue = {"get_value", (PyCFunction)PyDiaSymbol_getValue, METH_NOARGS, "Get the value of the symbol."};

PyObject* PyDiaSymbol_isVirtual(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_isVirtual = {"is_virtual", (PyCFunction)PyDiaSymbol_isVirtual, METH_NOARGS,
                                                       "Check if the symbol is virtual."};

PyObject* PyDiaSymbol_getVirtualAddress(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getVirtualAddress = {"get_virtual_address", (PyCFunction)PyDiaSymbol_getVirtualAddress, METH_NOARGS,
                                                               "Get the virtual address of the symbol."};

PyObject* PyDiaSymbol_getVirtualBaseClass(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getVirtualBaseClass = {"get_virtual_base_class", (PyCFunction)PyDiaSymbol_getVirtualBaseClass, METH_NOARGS,
                                                                 "Get the virtual base class of the symbol."};

PyObject* PyDiaSymbol_getVirtualBaseDispIndex(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getVirtualBaseDispIndex = {"get_virtual_base_disp_index", (PyCFunction)PyDiaSymbol_getVirtualBaseDispIndex,
                                                                     METH_NOARGS, "Get the virtual base displacement index of the symbol."};

PyObject* PyDiaSymbol_getVirtualBaseOffset(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getVirtualBaseOffset = {"get_virtual_base_offset", (PyCFunction)PyDiaSymbol_getVirtualBaseOffset,
                                                                  METH_NOARGS, "Get the virtual base offset of the symbol."};

PyObject* PyDiaSymbol_getVirtualBasePointerOffset(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getVirtualBasePointerOffset = {"get_virtual_base_pointer_offset",
                                                                         (PyCFunction)PyDiaSymbol_getVirtualBasePointerOffset, METH_NOARGS,
                                                                         "Get the virtual base pointer offset of the symbol."};

PyObject* PyDiaSymbol_getVirtualBaseTableType(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getVirtualBaseTableType = {"get_virtual_base_table_type", (PyCFunction)PyDiaSymbol_getVirtualBaseTableType,
                                                                     METH_NOARGS, "Get the virtual base table type of the symbol."};

PyObject* PyDiaSymbol_getVirtualTableShape(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getVirtualTableShape = {"get_virtual_table_shape", (PyCFunction)PyDiaSymbol_getVirtualTableShape,
                                                                  METH_NOARGS, "Get the virtual table shape of the symbol."};

PyObject* PyDiaSymbol_getVirtualTableShapeId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getVirtualTableShapeId = {"get_virtual_table_shape_id", (PyCFunction)PyDiaSymbol_getVirtualTableShapeId,
                                                                    METH_NOARGS, "Get the virtual table shape ID of the symbol."};

PyObject* PyDiaSymbol_getAddressOffset(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getAddressOffset = {"get_address_offset", (PyCFunction)PyDiaSymbol_getAddressOffset, METH_NOARGS,
                                                              "Get the address offset of the function."};
PyObject* PyDiaSymbol_getAddressSection(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getAddressSection = {"get_address_section", (PyCFunction)PyDiaSymbol_getAddressSection, METH_NOARGS,
                                                               "Get the address section of the function."};
PyObject* PyDiaSymbol_wasInlined(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_wasInlined = {"was_inlined", (PyCFunction)PyDiaSymbol_wasInlined, METH_NOARGS,
                                                        "Check if the symbol was inlined."};

PyObject* PyDiaSymbol_getPgoEdgeCount(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getPgoEdgeCount = {"get_pgo_edge_count", (PyCFunction)PyDiaSymbol_getPgoEdgeCount, METH_NOARGS,
                                                             "Get the PGO edge count of the symbol."};

PyObject* PyDiaSymbol_getPgoEntryCount(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getPgoEntryCount = {"get_pgo_entry_count", (PyCFunction)PyDiaSymbol_getPgoEntryCount, METH_NOARGS,
                                                              "Get the PGO entry count of the symbol."};

PyObject* PyDiaSymbol_getParamBasePointerRegisterId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getParamBasePointerRegisterId = {"get_param_base_pointer_register_id",
                                                                           (PyCFunction)PyDiaSymbol_getParamBasePointerRegisterId, METH_NOARGS,
                                                                           "Get the parameter base pointer register ID of the symbol."};

PyObject* PyDiaSymbol_getPhaseName(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getPhaseName = {"get_phase_name", (PyCFunction)PyDiaSymbol_getPhaseName, METH_NOARGS,
                                                          "Get the phase name of the symbol."};

PyObject* PyDiaSymbol_getPlatform(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getPlatform = {"get_platform", (PyCFunction)PyDiaSymbol_getPlatform, METH_NOARGS,
                                                         "Get the platform of the symbol."};

PyObject* PyDiaSymbol_getRegisterId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getRegisterId = {"get_register_id", (PyCFunction)PyDiaSymbol_getRegisterId, METH_NOARGS,
                                                           "Get the register ID of the symbol."};

PyObject* PyDiaSymbol_getSrcLineOnTypeDefn(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getSrcLineOnTypeDefn = {"get_src_line_on_type_defn", (PyCFunction)PyDiaSymbol_getSrcLineOnTypeDefn,
                                                                  METH_NOARGS, "Get the source line on type definition of the symbol."};

PyObject* PyDiaSymbol_getTargetRelativeVirtualAddress(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getTargetRelativeVirtualAddress = {"get_target_relative_virtual_address",
                                                                             (PyCFunction)PyDiaSymbol_getTargetRelativeVirtualAddress, METH_NOARGS,
                                                                             "Get the target relative virtual address of the symbol."};

PyObject* PyDiaSymbol_getTargetSection(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getTargetSection = {"get_target_section", (PyCFunction)PyDiaSymbol_getTargetSection, METH_NOARGS,
                                                              "Get the target section of the symbol."};

PyObject* PyDiaSymbol_getTargetVirtualAddress(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getTargetVirtualAddress = {"get_target_virtual_address", (PyCFunction)PyDiaSymbol_getTargetVirtualAddress,
                                                                     METH_NOARGS, "Get the target virtual address of the symbol."};

PyObject* PyDiaSymbol_getTextureSlot(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getTextureSlot = {"get_texture_slot", (PyCFunction)PyDiaSymbol_getTextureSlot, METH_NOARGS,
                                                            "Get the texture slot of the symbol."};

PyObject* PyDiaSymbol_getUdtKind(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getUdtKind = {"get_udt_kind", (PyCFunction)PyDiaSymbol_getUdtKind, METH_NOARGS,
                                                        "Get the UDT kind of the symbol."};

PyObject* PyDiaSymbol_getUpperBound(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getUpperBound = {"get_upper_bound", (PyCFunction)PyDiaSymbol_getUpperBound, METH_NOARGS,
                                                           "Get the upper bound of the symbol."};

PyObject* PyDiaSymbol_getUpperBoundId(const PyDiaSymbol* self);
static PyMethodDef PyDiaSymbolMethodEntry_getUpperBoundId = {"get_upper_bound_id", (PyCFunction)PyDiaSymbol_getUpperBoundId, METH_NOARGS,
                                                             "Get the upper bound ID of the symbol."};
