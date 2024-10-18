#include "DiaSymbolFuncs.h"
#include "DiaSymbol.h"
#include "Exceptions.h"

namespace dia
{
DWORD getAddressSection(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_addressSection(&retVal);
    CHECK_DIACOM_EXCEPTION("get_addressSection failed!", result);
    return retVal;
}

bool getAddressTaken(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_addressTaken(&retVal);
    CHECK_DIACOM_EXCEPTION("get_addressTaken failed!", result);
    return FALSE != retVal;
}

ULONG getAge(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_age(&retVal);
    CHECK_DIACOM_EXCEPTION("get_age failed!", result);
    return retVal;
}

ULONG getArrayIndexTypeId(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_arrayIndexTypeId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_arrayIndexTypeId failed!", result);
    return retVal;
}

const Symbol getBaseSymbol(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_baseSymbol(&retVal);
    CHECK_DIACOM_EXCEPTION("get_baseSymbol failed!", result);
    return Symbol{retVal};
}

ULONG getBaseSymbolId(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_baseSymbolId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_baseSymbolId failed!", result);
    return retVal;
}

ULONG getBindSpace(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_bindSpace(&retVal);
    CHECK_DIACOM_EXCEPTION("get_bindSpace failed!", result);
    return retVal;
}

ULONG getBitPosition(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_bitPosition(&retVal);
    CHECK_DIACOM_EXCEPTION("get_bitPosition failed!", result);
    return retVal;
}

ULONG getBuiltInKind(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_builtInKind(&retVal);
    CHECK_DIACOM_EXCEPTION("get_builtInKind failed!", result);
    return retVal;
}

ULONG getCallingConvention(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_callingConvention(&retVal);
    CHECK_DIACOM_EXCEPTION("get_callingConvention failed!", result);
    return retVal;
}

ULONG getCharacteristics(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_characteristics(&retVal);
    CHECK_DIACOM_EXCEPTION("get_characteristics failed!", result);
    return retVal;
}

const Symbol getClassParent(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_classParent(&retVal);
    CHECK_DIACOM_EXCEPTION("get_classParent failed!", result);
    return Symbol{retVal};
}

bool getCode(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_code(&retVal);
    CHECK_DIACOM_EXCEPTION("get_code failed!", result);
    return FALSE != retVal;
}

const Symbol getCoffGroup(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_coffGroup(&retVal);
    CHECK_DIACOM_EXCEPTION("get_coffGroup failed!", result);
    return Symbol{retVal};
}

bool getCompilerGenerated(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_compilerGenerated(&retVal);
    CHECK_DIACOM_EXCEPTION("get_compilerGenerated failed!", result);
    return FALSE != retVal;
}

bool getConstantExport(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_constantExport(&retVal);
    CHECK_DIACOM_EXCEPTION("get_constantExport failed!", result);
    return FALSE != retVal;
}

bool getDataExport(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_dataExport(&retVal);
    CHECK_DIACOM_EXCEPTION("get_dataExport failed!", result);
    return FALSE != retVal;
}

enum DataKind getDataKind(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_dataKind(&retVal);
    CHECK_DIACOM_EXCEPTION("get_dataKind failed!", result);
    return static_cast<enum DataKind>(retVal);
}
DWORD getExceptionHandlerAddressOffset(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result =
        symbol.get()->get_exceptionHandlerAddressOffset(&retVal);
    CHECK_DIACOM_EXCEPTION("get_exceptionHandlerAddressOffset failed!", result);
    return retVal;
}

DWORD getExceptionHandlerAddressSection(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result =
        symbol.get()->get_exceptionHandlerAddressSection(&retVal);
    CHECK_DIACOM_EXCEPTION("get_exceptionHandlerAddressSection failed!",
                           result);
    return retVal;
}

ULONG getExceptionHandlerRelativeVirtualAddress(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result =
        symbol.get()->get_exceptionHandlerRelativeVirtualAddress(&retVal);
    CHECK_DIACOM_EXCEPTION("get_exceptionHandlerRelativeVirtualAddress failed!",
                           result);
    return retVal;
}

ULONGLONG getExceptionHandlerVirtualAddress(const Symbol& symbol)
{
    ULONGLONG retVal = 0;
    const auto result =
        symbol.get()->get_exceptionHandlerVirtualAddress(&retVal);
    CHECK_DIACOM_EXCEPTION("get_exceptionHandlerVirtualAddress failed!",
                           result);
    return retVal;
}

bool getExportHasExplicitlyAssignedOrdinal(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result =
        symbol.get()->get_exportHasExplicitlyAssignedOrdinal(&retVal);
    CHECK_DIACOM_EXCEPTION("get_exportHasExplicitlyAssignedOrdinal failed!",
                           result);
    return FALSE != retVal;
}

bool getExportIsForwarder(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_exportIsForwarder(&retVal);
    CHECK_DIACOM_EXCEPTION("get_exportIsForwarder failed!", result);
    return FALSE != retVal;
}

ULONG getFinalLiveStaticSize(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_finalLiveStaticSize(&retVal);
    CHECK_DIACOM_EXCEPTION("get_finalLiveStaticSize failed!", result);
    return retVal;
}

ULONG getFrameSize(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_frameSize(&retVal);
    CHECK_DIACOM_EXCEPTION("get_frameSize failed!", result);
    return retVal;
}

bool getFunction(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_function(&retVal);
    CHECK_DIACOM_EXCEPTION("get_function failed!", result);
    return FALSE != retVal;
}

bool getHasControlFlowCheck(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasControlFlowCheck(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasControlFlowCheck failed!", result);
    return FALSE != retVal;
}

bool getHasValidPGOCounts(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasValidPGOCounts(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasValidPGOCounts failed!", result);
    return FALSE != retVal;
}

bool getIsOptimizedForSpeed(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isOptimizedForSpeed(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isOptimizedForSpeed failed!", result);
    return FALSE != retVal;
}

bool getIsPGO(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isPGO(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isPGO failed!", result);
    return FALSE != retVal;
}

ULONGLONG getLength(const Symbol& symbol)
{
    ULONGLONG retVal = 0;
    const auto result = symbol.get()->get_length(&retVal);
    CHECK_DIACOM_EXCEPTION("get_length failed!", result);
    return retVal;
}

const Symbol getLexicalParent(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_lexicalParent(&retVal);
    CHECK_DIACOM_EXCEPTION("get_lexicalParent failed!", result);
    return Symbol{retVal};
}

enum LocationType getLocationType(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_locationType(&retVal);
    CHECK_DIACOM_EXCEPTION("get_locationType failed!", result);
    return static_cast<enum LocationType>(retVal);
}

const Symbol getLowerBound(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_lowerBound(&retVal);
    CHECK_DIACOM_EXCEPTION("get_lowerBound failed!", result);
    return Symbol{retVal};
}

ULONG getLowerBoundId(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_lowerBoundId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_lowerBoundId failed!", result);
    return retVal;
}

bool getManaged(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_managed(&retVal);
    CHECK_DIACOM_EXCEPTION("get_managed failed!", result);
    return FALSE != retVal;
}

bool getMsil(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_msil(&retVal);
    CHECK_DIACOM_EXCEPTION("get_msil failed!", result);
    return FALSE != retVal;
}
const BstrWrapper getName(const Symbol& symbol)
{
    BSTR retVal = nullptr;
    const auto result = symbol.get()->get_name(&retVal);
    CHECK_DIACOM_EXCEPTION("get_name failed!", result);
    return retVal;
}

bool getNoNameExport(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_noNameExport(&retVal);
    CHECK_DIACOM_EXCEPTION("get_noNameExport failed!", result);
    return FALSE != retVal;
}

LONG getOffset(const Symbol& symbol)
{
    LONG retVal = 0;
    const auto result = symbol.get()->get_offset(&retVal);
    CHECK_DIACOM_EXCEPTION("get_offset failed!", result);
    return retVal;
}

ULONG getOrdinal(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_ordinal(&retVal);
    CHECK_DIACOM_EXCEPTION("get_ordinal failed!", result);
    return retVal;
}

ULONGLONG getPGODynamicInstructionCount(const Symbol& symbol)
{
    ULONGLONG retVal = 0;
    const auto result = symbol.get()->get_PGODynamicInstructionCount(&retVal);
    CHECK_DIACOM_EXCEPTION("get_PGODynamicInstructionCount failed!", result);
    return retVal;
}

DWORD getPGOEdgeCount(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_PGOEdgeCount(&retVal);
    CHECK_DIACOM_EXCEPTION("get_PGOEdgeCount failed!", result);
    return retVal;
}

DWORD getPGOEntryCount(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_PGOEntryCount(&retVal);
    CHECK_DIACOM_EXCEPTION("get_PGOEntryCount failed!", result);
    return retVal;
}

const BstrWrapper getPhaseName(const Symbol& symbol)
{
    BSTR retVal = nullptr;
    const auto result = symbol.get()->get_phaseName(&retVal);
    CHECK_DIACOM_EXCEPTION("get_phaseName failed!", result);
    return retVal;
}

bool getPrivateExport(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_privateExport(&retVal);
    CHECK_DIACOM_EXCEPTION("get_privateExport failed!", result);
    return FALSE != retVal;
}

ULONG getRank(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_rank(&retVal);
    CHECK_DIACOM_EXCEPTION("get_rank failed!", result);
    return retVal;
}

ULONG getRegisterId(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_registerId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_registerId failed!", result);
    return retVal;
}

ULONG getRelativeVirtualAddress(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_relativeVirtualAddress(&retVal);
    CHECK_DIACOM_EXCEPTION("get_relativeVirtualAddress failed!", result);
    return retVal;
}

ULONG getSignature(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_signature(&retVal);
    CHECK_DIACOM_EXCEPTION("get_signature failed!", result);
    return retVal;
}

ULONG getStaticSize(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_staticSize(&retVal);
    CHECK_DIACOM_EXCEPTION("get_staticSize failed!", result);
    return retVal;
}

ULONG getSymIndexId(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_symIndexId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_symIndexId failed!", result);
    return retVal;
}

enum SymTagEnum getSymTag(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_symTag(&retVal);
    CHECK_DIACOM_EXCEPTION("get_symTag failed!", result);
    _ASSERT((0 <= retVal) && (retVal < static_cast<DWORD>(SymTagMax)));
    return static_cast<enum SymTagEnum>(retVal);
}

const Symbol getType(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_type(&retVal);
    CHECK_DIACOM_EXCEPTION("get_type failed!", result);
    return Symbol{retVal};
}

ULONG getTypeId(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_typeId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_typeId failed!", result);
    return retVal;
}

const BstrWrapper getUndecoratedName(const Symbol& symbol)
{
    BSTR retVal = nullptr;
    const auto result = symbol.get()->get_undecoratedName(&retVal);
    CHECK_DIACOM_EXCEPTION("get_undecoratedName failed!", result);
    return retVal;
}

const Symbol getUpperBound(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_upperBound(&retVal);
    CHECK_DIACOM_EXCEPTION("get_upperBound failed!", result);
    return Symbol{retVal};
}
ULONG getUpperBoundId(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_upperBoundId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_upperBoundId failed!", result);
    return retVal;
}

ULONGLONG getVirtualAddress(const Symbol& symbol)
{
    ULONGLONG retVal = 0;
    const auto result = symbol.get()->get_virtualAddress(&retVal);
    CHECK_DIACOM_EXCEPTION("get_virtualAddress failed!", result);
    return retVal;
}

DWORD getVirtualBaseDispIndex(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_virtualBaseDispIndex(&retVal);
    CHECK_DIACOM_EXCEPTION("get_virtualBaseDispIndex failed!", result);
    return retVal;
}

ULONG getVirtualTableShapeId(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_virtualTableShapeId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_virtualTableShapeId failed!", result);
    return retVal;
}

const IDiaLineNumber* getSrcLineOnTypeDefn(const Symbol& symbol)
{
    IDiaLineNumber* retVal = 0;
    const auto result = symbol.get()->getSrcLineOnTypeDefn(&retVal);
    CHECK_DIACOM_EXCEPTION("get_srcLineOnTypeDefn failed!", result);
    return retVal;
}

bool getRValueReference(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_RValueReference(&retVal);
    CHECK_DIACOM_EXCEPTION("get_RValueReference failed!", result);
    return FALSE != retVal;
}

ULONG getBackEndBuild(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_backEndBuild(&retVal);
    CHECK_DIACOM_EXCEPTION("get_backEndBuild failed!", result);
    return retVal;
}

ULONG getBackEndMajor(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_backEndMajor(&retVal);
    CHECK_DIACOM_EXCEPTION("get_backEndMajor failed!", result);
    return retVal;
}

ULONG getBackEndMinor(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_backEndMinor(&retVal);
    CHECK_DIACOM_EXCEPTION("get_backEndMinor failed!", result);
    return retVal;
}

ULONG getBackEndQFE(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_backEndQFE(&retVal);
    CHECK_DIACOM_EXCEPTION("get_backEndQFE failed!", result);
    return retVal;
}

DWORD getBaseDataOffset(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_baseDataOffset(&retVal);
    CHECK_DIACOM_EXCEPTION("get_baseDataOffset failed!", result);
    return retVal;
}

ULONG getBaseDataSlot(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_baseDataSlot(&retVal);
    CHECK_DIACOM_EXCEPTION("get_baseDataSlot failed!", result);
    return retVal;
}

DWORD getBaseType(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_baseType(&retVal);
    CHECK_DIACOM_EXCEPTION("get_baseType failed!", result);
    return retVal;
}

ULONG getBindID(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_bindID(&retVal);
    CHECK_DIACOM_EXCEPTION("get_bindID failed!", result);
    return retVal;
}

ULONG getBindSlot(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_bindSlot(&retVal);
    CHECK_DIACOM_EXCEPTION("get_bindSlot failed!", result);
    return retVal;
}

ULONG getClassParentId(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_classParentId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_classParentId failed!", result);
    return retVal;
}

const BstrWrapper getCompilerName(const Symbol& symbol)
{
    BSTR retVal = nullptr;
    const auto result = symbol.get()->get_compilerName(&retVal);
    CHECK_DIACOM_EXCEPTION("get_compilerName failed!", result);
    return retVal;
}

bool getConstType(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_constType(&retVal);
    CHECK_DIACOM_EXCEPTION("get_constType failed!", result);
    return FALSE != retVal;
}

bool getConstructor(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_constructor(&retVal);
    CHECK_DIACOM_EXCEPTION("get_constructor failed!", result);
    return FALSE != retVal;
}

const Symbol getContainer(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_container(&retVal);
    CHECK_DIACOM_EXCEPTION("get_container failed!", result);
    return Symbol{retVal};
}
ULONG getCount(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_count(&retVal);
    CHECK_DIACOM_EXCEPTION("get_count failed!", result);
    return retVal;
}

ULONG getCountLiveRanges(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_countLiveRanges(&retVal);
    CHECK_DIACOM_EXCEPTION("get_countLiveRanges failed!", result);
    return retVal;
}

bool getCustomCallingConvention(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_customCallingConvention(&retVal);
    CHECK_DIACOM_EXCEPTION("get_customCallingConvention failed!", result);
    return FALSE != retVal;
}

#if 0
const std::vector<BYTE> getDataBytes(const Symbol& symbol)
{
    CComPtr<IDiaEnumSymbols> pEnum;
    const auto result = symbol.get()->get_dataBytes(&pEnum);
    CHECK_DIACOM_EXCEPTION("get_dataBytes failed!", result);

    std::vector<BYTE> dataBytes;
    ULONG celtFetched = 0;
    CComPtr<IDiaSymbol> pSymbol;
    while (SUCCEEDED(pEnum->Next(1, &pSymbol, &celtFetched)) &&
           celtFetched == 1)
    {
        BYTE byte;
        pSymbol->get_value(&byte);
        dataBytes.push_back(byte);
        pSymbol.Release();
    }
    return dataBytes;
}
#endif

bool getEditAndContinueEnabled(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_editAndContinueEnabled(&retVal);
    CHECK_DIACOM_EXCEPTION("get_editAndContinueEnabled failed!", result);
    return FALSE != retVal;
}

bool getFarReturn(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_farReturn(&retVal);
    CHECK_DIACOM_EXCEPTION("get_farReturn failed!", result);
    return FALSE != retVal;
}

bool getFramePointerPresent(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_framePointerPresent(&retVal);
    CHECK_DIACOM_EXCEPTION("get_framePointerPresent failed!", result);
    return FALSE != retVal;
}

ULONG getFrontEndBuild(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_frontEndBuild(&retVal);
    CHECK_DIACOM_EXCEPTION("get_frontEndBuild failed!", result);
    return retVal;
}

ULONG getFrontEndMajor(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_frontEndMajor(&retVal);
    CHECK_DIACOM_EXCEPTION("get_frontEndMajor failed!", result);
    return retVal;
}

ULONG getFrontEndMinor(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_frontEndMinor(&retVal);
    CHECK_DIACOM_EXCEPTION("get_frontEndMinor failed!", result);
    return retVal;
}

ULONG getFrontEndQFE(const Symbol& symbol)
{
    ULONG retVal = 0;
    const auto result = symbol.get()->get_frontEndQFE(&retVal);
    CHECK_DIACOM_EXCEPTION("get_frontEndQFE failed!", result);
    return retVal;
}

const GUID getGuid(const Symbol& symbol)
{
    GUID retVal = {};
    const auto result = symbol.get()->get_guid(&retVal);
    CHECK_DIACOM_EXCEPTION("get_guid failed!", result);
    return retVal;
}

bool getHasAlloca(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasAlloca(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasAlloca failed!", result);
    return FALSE != retVal;
}

bool getHasAssignmentOperator(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasAssignmentOperator(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasAssignmentOperator failed!", result);
    return FALSE != retVal;
}

bool getHasCastOperator(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasCastOperator(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasCastOperator failed!", result);
    return FALSE != retVal;
}

bool getHasDebugInfo(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasDebugInfo(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasDebugInfo failed!", result);
    return FALSE != retVal;
}

bool getHasEH(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasEH(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasEH failed!", result);
    return FALSE != retVal;
}

bool getHasEHa(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasEHa(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasEHa failed!", result);
    return FALSE != retVal;
}

bool getHasInlAsm(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasInlAsm(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasInlAsm failed!", result);
    return FALSE != retVal;
}

bool getHasLongJump(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasLongJump(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasLongJump failed!", result);
    return FALSE != retVal;
}
bool getHasManagedCode(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasManagedCode(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasManagedCode failed!", result);
    return FALSE != retVal;
}

bool getHasNestedTypes(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasNestedTypes(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasNestedTypes failed!", result);
    return FALSE != retVal;
}

bool getHasSEH(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasSEH(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasSEH failed!", result);
    return FALSE != retVal;
}

bool getHasSecurityChecks(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasSecurityChecks(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasSecurityChecks failed!", result);
    return FALSE != retVal;
}

bool getHasSetJump(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hasSetJump(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hasSetJump failed!", result);
    return FALSE != retVal;
}

bool getHfaDouble(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hfaDouble(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hfaDouble failed!", result);
    return FALSE != retVal;
}

bool getHfaFloat(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_hfaFloat(&retVal);
    CHECK_DIACOM_EXCEPTION("get_hfaFloat failed!", result);
    return FALSE != retVal;
}

bool getIndirectVirtualBaseClass(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_indirectVirtualBaseClass(&retVal);
    CHECK_DIACOM_EXCEPTION("get_indirectVirtualBaseClass failed!", result);
    return FALSE != retVal;
}

bool getInlSpec(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_inlSpec(&retVal);
    CHECK_DIACOM_EXCEPTION("get_inlSpec failed!", result);
    return FALSE != retVal;
}

bool getInterruptReturn(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_interruptReturn(&retVal);
    CHECK_DIACOM_EXCEPTION("get_interruptReturn failed!", result);
    return FALSE != retVal;
}

bool getIntrinsic(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_intrinsic(&retVal);
    CHECK_DIACOM_EXCEPTION("get_intrinsic failed!", result);
    return FALSE != retVal;
}

bool getIntro(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_intro(&retVal);
    CHECK_DIACOM_EXCEPTION("get_intro failed!", result);
    return FALSE != retVal;
}

bool getIsAcceleratorGroupSharedLocal(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result =
        symbol.get()->get_isAcceleratorGroupSharedLocal(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isAcceleratorGroupSharedLocal failed!", result);
    return FALSE != retVal;
}

bool getIsAcceleratorPointerTagLiveRange(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result =
        symbol.get()->get_isAcceleratorPointerTagLiveRange(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isAcceleratorPointerTagLiveRange failed!",
                           result);
    return FALSE != retVal;
}

bool getIsAcceleratorStubFunction(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isAcceleratorStubFunction(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isAcceleratorStubFunction failed!", result);
    return FALSE != retVal;
}

bool getIsAggregated(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isAggregated(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isAggregated failed!", result);
    return FALSE != retVal;
}

bool getIsCTypes(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isCTypes(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isCTypes failed!", result);
    return FALSE != retVal;
}

bool getIsCVTCIL(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isCVTCIL(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isCVTCIL failed!", result);
    return FALSE != retVal;
}

bool getIsConstructorVirtualBase(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isConstructorVirtualBase(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isConstructorVirtualBase failed!", result);
    return FALSE != retVal;
}

bool getIsCxxReturnUdt(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isCxxReturnUdt(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isCxxReturnUdt failed!", result);
    return FALSE != retVal;
}
bool getIsDataAligned(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isDataAligned(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isDataAligned failed!", result);
    return FALSE != retVal;
}

bool getIsHLSLData(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isHLSLData(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isHLSLData failed!", result);
    return FALSE != retVal;
}

bool getIsHotpatchable(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isHotpatchable(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isHotpatchable failed!", result);
    return FALSE != retVal;
}

bool getIsInterfaceUdt(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isInterfaceUdt(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isInterfaceUdt failed!", result);
    return FALSE != retVal;
}

bool getIsLTCG(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isLTCG(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isLTCG failed!", result);
    return FALSE != retVal;
}

bool getIsLocationControlFlowDependent(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result =
        symbol.get()->get_isLocationControlFlowDependent(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isLocationControlFlowDependent failed!",
                           result);
    return FALSE != retVal;
}

bool getIsMSILNetmodule(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isMSILNetmodule(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isMSILNetmodule failed!", result);
    return FALSE != retVal;
}

bool getIsMatrixRowMajor(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isMatrixRowMajor(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isMatrixRowMajor failed!", result);
    return FALSE != retVal;
}

bool getIsMultipleInheritance(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isMultipleInheritance(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isMultipleInheritance failed!", result);
    return FALSE != retVal;
}

bool getIsNaked(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isNaked(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isNaked failed!", result);
    return FALSE != retVal;
}

bool getIsOptimizedAway(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isOptimizedAway(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isOptimizedAway failed!", result);
    return FALSE != retVal;
}

bool getIsPointerBasedOnSymbolValue(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isPointerBasedOnSymbolValue(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isPointerBasedOnSymbolValue failed!", result);
    return FALSE != retVal;
}

bool getIsPointerToDataMember(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isPointerToDataMember(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isPointerToDataMember failed!", result);
    return FALSE != retVal;
}

bool getIsPointerToMemberFunction(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isPointerToMemberFunction(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isPointerToMemberFunction failed!", result);
    return FALSE != retVal;
}

bool getIsRefUdt(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isRefUdt(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isRefUdt failed!", result);
    return FALSE != retVal;
}

bool getIsReturnValue(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isReturnValue(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isReturnValue failed!", result);
    return FALSE != retVal;
}

bool getIsSafeBuffers(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isSafeBuffers(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isSafeBuffers failed!", result);
    return FALSE != retVal;
}

bool getIsSdl(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isSdl(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isSdl failed!", result);
    return FALSE != retVal;
}

bool getIsSingleInheritance(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isSingleInheritance(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isSingleInheritance failed!", result);
    return FALSE != retVal;
}

bool getIsSplitted(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isSplitted(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isSplitted failed!", result);
    return FALSE != retVal;
}
bool getIsStatic(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isStatic(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isStatic failed!", result);
    return FALSE != retVal;
}

bool getIsStripped(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isStripped(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isStripped failed!", result);
    return FALSE != retVal;
}

bool getIsValueUdt(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isValueUdt(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isValueUdt failed!", result);
    return FALSE != retVal;
}

bool getIsVirtualInheritance(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isVirtualInheritance(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isVirtualInheritance failed!", result);
    return FALSE != retVal;
}

bool getIsWinRTPointer(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_isWinRTPointer(&retVal);
    CHECK_DIACOM_EXCEPTION("get_isWinRTPointer failed!", result);
    return FALSE != retVal;
}

DWORD getLanguage(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_language(&retVal);
    CHECK_DIACOM_EXCEPTION("get_language failed!", result);
    return retVal;
}

DWORD getLexicalParentId(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_lexicalParentId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_lexicalParentId failed!", result);
    return retVal;
}

const BstrWrapper getLibraryName(const Symbol& symbol)
{
    BSTR retVal = nullptr;
    const auto result = symbol.get()->get_libraryName(&retVal);
    CHECK_DIACOM_EXCEPTION("get_libraryName failed!", result);
    return retVal;
}

ULONGLONG getLiveRangeLength(const Symbol& symbol)
{
    ULONGLONG retVal = 0;
    const auto result = symbol.get()->get_liveRangeLength(&retVal);
    CHECK_DIACOM_EXCEPTION("get_liveRangeLength failed!", result);
    return retVal;
}

DWORD getLiveRangeStartAddressOffset(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_liveRangeStartAddressOffset(&retVal);
    CHECK_DIACOM_EXCEPTION("get_liveRangeStartAddressOffset failed!", result);
    return retVal;
}

DWORD getLiveRangeStartAddressSection(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_liveRangeStartAddressSection(&retVal);
    CHECK_DIACOM_EXCEPTION("get_liveRangeStartAddressSection failed!", result);
    return retVal;
}

DWORD getLiveRangeStartRelativeVirtualAddress(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result =
        symbol.get()->get_liveRangeStartRelativeVirtualAddress(&retVal);
    CHECK_DIACOM_EXCEPTION("get_liveRangeStartRelativeVirtualAddress failed!",
                           result);
    return retVal;
}

DWORD getLocalBasePointerRegisterId(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_localBasePointerRegisterId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_localBasePointerRegisterId failed!", result);
    return retVal;
}

DWORD getMachineType(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_machineType(&retVal);
    CHECK_DIACOM_EXCEPTION("get_machineType failed!", result);
    return retVal;
}

DWORD getMemorySpaceKind(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_memorySpaceKind(&retVal);
    CHECK_DIACOM_EXCEPTION("get_memorySpaceKind failed!", result);
    return retVal;
}

#if 0
const Symbol getModifierValues(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_modifierValues(&retVal);
    CHECK_DIACOM_EXCEPTION("get_modifierValues failed!", result);
    return Symbol{retVal};
}
#endif

bool getNested(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_nested(&retVal);
    CHECK_DIACOM_EXCEPTION("get_nested failed!", result);
    return FALSE != retVal;
}

bool getNoInline(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_noInline(&retVal);
    CHECK_DIACOM_EXCEPTION("get_noInline failed!", result);
    return FALSE != retVal;
}

bool getNoReturn(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_noReturn(&retVal);
    CHECK_DIACOM_EXCEPTION("get_noReturn failed!", result);
    return FALSE != retVal;
}

bool getNoStackOrdering(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_noStackOrdering(&retVal);
    CHECK_DIACOM_EXCEPTION("get_noStackOrdering failed!", result);
    return FALSE != retVal;
}
bool getNotReached(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_notReached(&retVal);
    CHECK_DIACOM_EXCEPTION("get_notReached failed!", result);
    return FALSE != retVal;
}

DWORD getNumberOfAcceleratorPointerTags(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result =
        symbol.get()->get_numberOfAcceleratorPointerTags(&retVal);
    CHECK_DIACOM_EXCEPTION("get_numberOfAcceleratorPointerTags failed!",
                           result);
    return retVal;
}

DWORD getNumberOfColumns(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_numberOfColumns(&retVal);
    CHECK_DIACOM_EXCEPTION("get_numberOfColumns failed!", result);
    return retVal;
}

DWORD getNumberOfModifiers(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_numberOfModifiers(&retVal);
    CHECK_DIACOM_EXCEPTION("get_numberOfModifiers failed!", result);
    return retVal;
}

DWORD getNumberOfRegisterIndices(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_numberOfRegisterIndices(&retVal);
    CHECK_DIACOM_EXCEPTION("get_numberOfRegisterIndices failed!", result);
    return retVal;
}

DWORD getNumberOfRows(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_numberOfRows(&retVal);
    CHECK_DIACOM_EXCEPTION("get_numberOfRows failed!", result);
    return retVal;
}

const Symbol getNumericProperties(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_numericProperties(&retVal);
    CHECK_DIACOM_EXCEPTION("get_numericProperties failed!", result);
    return Symbol{retVal};
}

const BstrWrapper getObjectFileName(const Symbol& symbol)
{
    BSTR retVal = nullptr;
    const auto result = symbol.get()->get_objectFileName(&retVal);
    CHECK_DIACOM_EXCEPTION("get_objectFileName failed!", result);
    return retVal;
}

const Symbol getObjectPointerType(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_objectPointerType(&retVal);
    CHECK_DIACOM_EXCEPTION("get_objectPointerType failed!", result);
    return Symbol{retVal};
}

DWORD getOemId(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_oemId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_oemId failed!", result);
    return retVal;
}

DWORD getOemSymbolId(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_oemSymbolId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_oemSymbolId failed!", result);
    return retVal;
}

DWORD getOffsetInUdt(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_offsetInUdt(&retVal);
    CHECK_DIACOM_EXCEPTION("get_offsetInUdt failed!", result);
    return retVal;
}

bool getOptimizedCodeDebugInfo(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_optimizedCodeDebugInfo(&retVal);
    CHECK_DIACOM_EXCEPTION("get_optimizedCodeDebugInfo failed!", result);
    return FALSE != retVal;
}

DWORD getOverloadedOperator(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_overloadedOperator(&retVal);
    CHECK_DIACOM_EXCEPTION("get_overloadedOperator failed!", result);
    return retVal;
}

bool getPacked(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_packed(&retVal);
    CHECK_DIACOM_EXCEPTION("get_packed failed!", result);
    return FALSE != retVal;
}

DWORD getParamBasePointerRegisterId(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_paramBasePointerRegisterId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_paramBasePointerRegisterId failed!", result);
    return retVal;
}

DWORD getPlatform(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_platform(&retVal);
    CHECK_DIACOM_EXCEPTION("get_platform failed!", result);
    return retVal;
}

bool getPure(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_pure(&retVal);
    CHECK_DIACOM_EXCEPTION("get_pure failed!", result);
    return FALSE != retVal;
}

bool getReference(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_reference(&retVal);
    CHECK_DIACOM_EXCEPTION("get_reference failed!", result);
    return FALSE != retVal;
}

DWORD getRegisterType(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_registerType(&retVal);
    CHECK_DIACOM_EXCEPTION("get_registerType failed!", result);
    return retVal;
}
const Symbol getRestrictedType(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_restrictedType(&retVal);
    CHECK_DIACOM_EXCEPTION("get_restrictedType failed!", result);
    return Symbol{retVal};
}

DWORD getSamplerSlot(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_samplerSlot(&retVal);
    CHECK_DIACOM_EXCEPTION("get_samplerSlot failed!", result);
    return retVal;
}

bool getScoped(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_scoped(&retVal);
    CHECK_DIACOM_EXCEPTION("get_scoped failed!", result);
    return FALSE != retVal;
}

bool getSealed(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_sealed(&retVal);
    CHECK_DIACOM_EXCEPTION("get_sealed failed!", result);
    return FALSE != retVal;
}

DWORD getSizeInUdt(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_sizeInUdt(&retVal);
    CHECK_DIACOM_EXCEPTION("get_sizeInUdt failed!", result);
    return retVal;
}

DWORD getSlot(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_slot(&retVal);
    CHECK_DIACOM_EXCEPTION("get_slot failed!", result);
    return retVal;
}

const BstrWrapper getSourceFileName(const Symbol& symbol)
{
    BSTR retVal = nullptr;
    const auto result = symbol.get()->get_sourceFileName(&retVal);
    CHECK_DIACOM_EXCEPTION("get_sourceFileName failed!", result);
    return retVal;
}

bool getStrictGSCheck(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_strictGSCheck(&retVal);
    CHECK_DIACOM_EXCEPTION("get_strictGSCheck failed!", result);
    return FALSE != retVal;
}

DWORD getStride(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_stride(&retVal);
    CHECK_DIACOM_EXCEPTION("get_stride failed!", result);
    return retVal;
}

const Symbol getSubType(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_subType(&retVal);
    CHECK_DIACOM_EXCEPTION("get_subType failed!", result);
    return Symbol{retVal};
}

DWORD getSubTypeId(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_subTypeId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_subTypeId failed!", result);
    return retVal;
}

const BstrWrapper getSymbolsFileName(const Symbol& symbol)
{
    BSTR retVal = nullptr;
    const auto result = symbol.get()->get_symbolsFileName(&retVal);
    CHECK_DIACOM_EXCEPTION("get_symbolsFileName failed!", result);
    return retVal;
}

DWORD getTargetOffset(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_targetOffset(&retVal);
    CHECK_DIACOM_EXCEPTION("get_targetOffset failed!", result);
    return retVal;
}

DWORD getTargetRelativeVirtualAddress(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_targetRelativeVirtualAddress(&retVal);
    CHECK_DIACOM_EXCEPTION("get_targetRelativeVirtualAddress failed!", result);
    return retVal;
}

DWORD getTargetSection(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_targetSection(&retVal);
    CHECK_DIACOM_EXCEPTION("get_targetSection failed!", result);
    return retVal;
}

ULONGLONG getTargetVirtualAddress(const Symbol& symbol)
{
    ULONGLONG retVal = 0;
    const auto result = symbol.get()->get_targetVirtualAddress(&retVal);
    CHECK_DIACOM_EXCEPTION("get_targetVirtualAddress failed!", result);
    return retVal;
}

DWORD getTextureSlot(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_textureSlot(&retVal);
    CHECK_DIACOM_EXCEPTION("get_textureSlot failed!", result);
    return retVal;
}

LONG getThisAdjust(const Symbol& symbol)
{
    LONG retVal = 0;
    const auto result = symbol.get()->get_thisAdjust(&retVal);
    CHECK_DIACOM_EXCEPTION("get_thisAdjust failed!", result);
    return retVal;
}

DWORD getThunkOrdinal(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_thunkOrdinal(&retVal);
    CHECK_DIACOM_EXCEPTION("get_thunkOrdinal failed!", result);
    return retVal;
}

DWORD getTimeStamp(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_timeStamp(&retVal);
    CHECK_DIACOM_EXCEPTION("get_timeStamp failed!", result);
    return retVal;
}
DWORD getToken(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_token(&retVal);
    CHECK_DIACOM_EXCEPTION("get_token failed!", result);
    return retVal;
}

const Symbol getTypeIds(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_typeIds(&retVal);
    CHECK_DIACOM_EXCEPTION("get_typeIds failed!", result);
    return Symbol{retVal};
}

const Symbol getTypes(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_types(&retVal);
    CHECK_DIACOM_EXCEPTION("get_types failed!", result);
    return Symbol{retVal};
}

DWORD getUavSlot(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_uavSlot(&retVal);
    CHECK_DIACOM_EXCEPTION("get_uavSlot failed!", result);
    return retVal;
}

DWORD getUdtKind(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_udtKind(&retVal);
    CHECK_DIACOM_EXCEPTION("get_udtKind failed!", result);
    return retVal;
}

bool getUnalignedType(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_unalignedType(&retVal);
    CHECK_DIACOM_EXCEPTION("get_unalignedType failed!", result);
    return FALSE != retVal;
}

const BstrWrapper getUndecoratedNameEx(const Symbol& symbol)
{
    BSTR retVal = nullptr;
    const auto result = symbol.get()->get_undecoratedNameEx(&retVal);
    CHECK_DIACOM_EXCEPTION("get_undecoratedNameEx failed!", result);
    return retVal;
}

const Symbol getUnmodifiedType(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_unmodifiedType(&retVal);
    CHECK_DIACOM_EXCEPTION("get_unmodifiedType failed!", result);
    return Symbol{retVal};
}

DWORD getUnmodifiedTypeId(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_unmodifiedTypeId(&retVal);
    CHECK_DIACOM_EXCEPTION("get_unmodifiedTypeId failed!", result);
    return retVal;
}

DWORD getUnused(const Symbol& symbol)
{
    DWORD retVal = 0;
    const auto result = symbol.get()->get_unused(&retVal);
    CHECK_DIACOM_EXCEPTION("get_unused failed!", result);
    return retVal;
}

VARIANT getValue(const Symbol& symbol)
{
    VARIANT retVal;
    VariantInit(&retVal);
    const auto result = symbol.get()->get_value(&retVal);
    CHECK_DIACOM_EXCEPTION("get_value failed!", result);
    return retVal;
}

const Symbol getVirtualBaseClass(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_virtualBaseClass(&retVal);
    CHECK_DIACOM_EXCEPTION("get_virtualBaseClass failed!", result);
    return Symbol{retVal};
}

LONG getVirtualBaseOffset(const Symbol& symbol)
{
    LONG retVal = 0;
    const auto result = symbol.get()->get_virtualBaseOffset(&retVal);
    CHECK_DIACOM_EXCEPTION("get_virtualBaseOffset failed!", result);
    return retVal;
}

LONG getVirtualBasePointerOffset(const Symbol& symbol)
{
    LONG retVal = 0;
    const auto result = symbol.get()->get_virtualBasePointerOffset(&retVal);
    CHECK_DIACOM_EXCEPTION("get_virtualBasePointerOffset failed!", result);
    return retVal;
}

const Symbol getVirtualBaseTableType(const Symbol& symbol)
{
    IDiaSymbol* retVal = nullptr;
    const auto result = symbol.get()->get_virtualBaseTableType(&retVal);
    CHECK_DIACOM_EXCEPTION("get_virtualBaseTableType failed!", result);
    return Symbol{retVal};
}

bool getVolatileType(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_volatileType(&retVal);
    CHECK_DIACOM_EXCEPTION("get_volatileType failed!", result);
    return FALSE != retVal;
}

bool getWasInlined(const Symbol& symbol)
{
    BOOL retVal = 0;
    const auto result = symbol.get()->get_wasInlined(&retVal);
    CHECK_DIACOM_EXCEPTION("get_wasInlined failed!", result);
    return FALSE != retVal;
}

} // namespace dia
