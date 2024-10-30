#pragma once
// DO NOT INCLUDE THIS HEADER!
// This header is EXPLICITLY only for very internal implementations of the pydia library!
#include <Python.h>
//
#include "pydia_symbol.h"


#define PYDIA_SAFE_TRY_EXCEPT(unsafeCode, exceptionHandler)                                                                                          \
    do                                                                                                                                               \
    {                                                                                                                                                \
        try                                                                                                                                          \
        {                                                                                                                                            \
            do                                                                                                                                       \
            {                                                                                                                                        \
                unsafeCode;                                                                                                                          \
            } while (0);                                                                                                                             \
        }                                                                                                                                            \
        catch (const std::exception& e)                                                                                                              \
        {                                                                                                                                            \
            exceptionHandler;                                                                                                                        \
        }                                                                                                                                            \
    } while (0)

#define PYDIA_SAFE_TRY(unsafeCode)                                                                                                                   \
    PYDIA_SAFE_TRY_EXCEPT(unsafeCode, {                                                                                                              \
        do                                                                                                                                           \
        {                                                                                                                                            \
            PyErr_SetString(PyExc_RuntimeError, e.what());                                                                                           \
            return NULL;                                                                                                                             \
        } while (0);                                                                                                                                 \
    })


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
        0,                                                  /* tp_repr */                                                                            \
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

#if 1
PyObject* PyDiaSymbol_getSymIndexId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isScoped(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getClassParent(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getClassParentId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isVolatile(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLength(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getAccess(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_address_offset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_address_section(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isAddressTaken(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getAge(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getArrayIndexType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getArrayIndexTypeId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBackendBuild(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBackendMajor(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBackendMinor(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBackendQfe(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBaseDataOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBaseDataSlot(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBaseSymbol(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBaseSymbolId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBaseType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBindId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBindSlot(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isCode(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getCoffGroup(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isCompilerGenerated(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getCompilerName(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isConst(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isConstantExport(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasConstructor(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getContainer(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getCount(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getCountLiveRanges(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasCustomCallingConvention(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_data_bytes(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isDataExport(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getDataKind(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isEditAndContinueEnabled(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getExceptionHandlerAddressOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getExceptionHandlerAddressSection(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getExceptionHandlerRelativeVirtualAddress(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getExceptionHandlerVirtualAddress(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isExportWithExplicitOrdinal(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isExportForwarder(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isFarReturn(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getFinalLiveStaticSize(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isFramePointerPresent(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getFrameSize(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getFrontEndBuild(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getFrontEndMajor(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getFrontEndMinor(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getFrontEndQfe(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isFunction(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getGuid(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasAlloca(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasAssignmentOperator(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasCastOperator(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasControlFlowCheck(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasDebugInfo(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasEh(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasEha(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasInlineAsm(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasLongJump(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasManagedCode(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasNestedTypes(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasSeh(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasSecurityChecks(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasSetJump(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasValidPgoCounts(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getHfaDouble(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getHfaFloat(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getIndirectVirtualBaseClass(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getInlSpec(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasInterruptReturn(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isIntrinsic(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isIntro(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_accelerator_group_shared_local(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_accelerator_pointer_tag_live_range(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_accelerator_stub_function(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_aggregated(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_ctypes(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_cvtcil(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_constructor_virtual_base(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_cxx_return_udt(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_data_aligned(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_hlsl_data(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_hotpatchable(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_interface_udt(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_ltcg(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_location_control_flow_dependent(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_msil_netmodule(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_matrix_row_major(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_multiple_inheritance(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_naked(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_optimized_away(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_optimized_for_speed(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_pgo(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_pointer_based_on_symbol_value(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_pointer_to_data_member(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_pointer_to_member_function(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_ref_udt(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_return_value(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_safe_buffers(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_sdl(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_single_inheritance(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isSplitted(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_static(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_stripped(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_value_udt(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_virtual_inheritance(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_is_winrt_pointer(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLanguage(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLexicalParent(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLexicalParentId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLibraryName(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLiveRangeLength(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLiveRangeStartAddressOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLiveRangeStartAddressSection(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLiveRangeStartRelativeVirtualAddress(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLocalBasePointerRegisterId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLocationType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLowerBound(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLowerBoundId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getMachineType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isManaged(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getMemorySpaceKind(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getModifierValues(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isMsil(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getName(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isNested(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isNoInline(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isNoNameExport(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isNoReturn(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasNoStackOrdering(const PyDiaSymbol* self);  // TODO: This name is odd
PyObject* PyDiaSymbol_isNotReached(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_number_of_accelerator_pointer_tags(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_number_of_columns(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getNumberOfModifiers(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getNumberOfRegisterIndices(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getNumberOfRows(const PyDiaSymbol* self);
#if 0
PyObject* PyDiaSymbol_getNumericProperties(const PyDiaSymbol* self);
#endif
PyObject* PyDiaSymbol_getObjectFileName(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getObjectPointerType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getOemId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getOemSymbolId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getOffsetInUdt(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasOptimizedCodeDebugInfo(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getOrdinal(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasOverloadedOperator(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getPgoDynamicInstructionCount(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_pgo_edge_count(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_pgo_entry_count(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isPacked(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_param_base_pointer_register_id(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_phase_name(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_platform(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_private_export(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_pure(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_r_value_reference(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_rank(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_reference(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_register_id(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getRegisterType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getRelativeVirtualAddress(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isRestrictedType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSamplerSlot(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isScoped(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isSealed(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSignature(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSizeInUdt(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSlot(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSourceFileName(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_src_line_on_type_defn(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getStaticSize(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_hasStrictGsCheck(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getStride(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSubType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSubTypeId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSymIndexId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSymTag(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSymbolsFileName(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getTargetOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_target_relative_virtual_address(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_target_section(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_target_virtual_address(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_texture_slot(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_this_adjust(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getThunkOrdinal(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getTimeStamp(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getToken(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getTypeId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getTypeIds(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getTypes(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_uav_slot(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_udt_kind(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isUnaligned(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_undecorated_name(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_undecorated_name_ex(const PyDiaSymbol* self, DWORD options);
PyObject* PyDiaSymbol_unmodified_type(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_unmodified_type_id(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_unused(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_upper_bound(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_upper_bound_id(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getValue(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isVirtual(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtualAddress(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtualBaseClass(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtualBaseDispIndex(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtualBaseOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtualBasePointerOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtualBaseTableType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtualTableShape(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtualTableShapeId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_isVolatile(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_wasInlined(const PyDiaSymbol* self);
#endif

PyObject* PyDiaSymbol_getAddressOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getAddressSection(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getArrayIndexType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getArrayIndexTypeId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBackendBuild(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBackendMajor(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBackendMinor(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBackendQfe(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBaseDataOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBaseDataSlot(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBaseSymbol(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBaseSymbolId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBindId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getBindSlot(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getClassParent(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getClassParentId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getCoffGroup(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getCompilerName(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getContainer(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getCount(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getCountLiveRanges(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getDataKind(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getExceptionHandlerAddressOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getExceptionHandlerAddressSection(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getExceptionHandlerRelativeVirtualAddress(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getExceptionHandlerVirtualAddress(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getFinalLiveStaticSize(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getFrameSize(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getFrontEndBuild(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getFrontEndMajor(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getFrontEndMinor(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getFrontEndQfe(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getGuid(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getHfaDouble(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getHfaFloat(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getIndirectVirtualBaseClass(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getInlSpec(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getInterruptReturn(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getIntrinsic(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getIntro(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLanguage(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLexicalParent(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLexicalParentId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLibraryName(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLiveRangeLength(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLiveRangeStartAddressOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLiveRangeStartAddressSection(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLiveRangeStartRelativeVirtualAddress(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLocalBasePointerRegisterId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLocationType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLowerBound(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getLowerBoundId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getMachineType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getManaged(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getMemorySpaceKind(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getModifierValues(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getMsil(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getName(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getNoInline(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getNoNameExport(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getNoReturn(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getNoStackOrdering(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getNotReached(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getNumberOfAcceleratorPointerTags(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getNumberOfColumns(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getNumberOfModifiers(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getNumberOfRegisterIndices(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getNumberOfRows(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getObjectFileName(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getObjectPointerType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getOemId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getOemSymbolId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getOffsetInUdt(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getOptimizedCodeDebugInfo(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getOrdinal(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getPgoDynamicInstructionCount(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getPgoEdgeCount(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getPgoEntryCount(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getPacked(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getParamBasePointerRegisterId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getPhaseName(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getPlatform(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getPrivateExport(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getPure(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getRValueReference(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getRank(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getReference(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getRegisterId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getRegisterType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getRelativeVirtualAddress(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getRestrictedType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSamplerSlot(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getScoped(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSealed(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSignature(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSizeInUdt(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSlot(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSourceFileName(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSrcLineOnTypeDefn(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getStaticSize(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getStrictGsCheck(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getStride(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSubType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSubTypeId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSymIndexId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSymTag(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getSymbolsFileName(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getTargetOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getTargetRelativeVirtualAddress(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getTargetSection(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getTargetVirtualAddress(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getTextureSlot(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getThisAdjust(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getThunkOrdinal(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getTimeStamp(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getToken(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getTypeId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getUdtKind(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getUnalignedType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getUndecoratedName(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getUndecoratedNameEx(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getUnmodifiedType(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getUnused(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getUpperBound(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getUpperBoundId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getUsed(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getValue(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getValueOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtual(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtualAddress(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtualBaseClass(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtualBaseDispIndex(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtualBasePointerOffset(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtualTableShape(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVirtualTableShapeId(const PyDiaSymbol* self);
PyObject* PyDiaSymbol_getVolatileType(const PyDiaSymbol* self);
