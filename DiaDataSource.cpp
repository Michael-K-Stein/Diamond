#include "DiaDataSource.h"
#include "BstrWrapper.h"
#include "DiaStruct.h"
#include "DiaSymbolEnumerator.h"
#include "Exceptions.h"

namespace dia
{
DiaDataSource::DiaDataSource()
{
    const auto result = CoCreateInstance(
        CLSID_DiaSource, NULL, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource),
        reinterpret_cast<void**>(&m_comPtr));
    CHECK_DIACOM_EXCEPTION("DiaSource creation failed!", result);
}

DiaDataSource::~DiaDataSource() {}

void DiaDataSource::loadDataFromPdb(const std::wstring& pdbFilePath)
{
    if (sessionOpened())
    {
        throw DiaSymbolMasterException{"Session already openned!"};
    }
    const auto result = m_comPtr->loadDataFromPdb(pdbFilePath.c_str());
    CHECK_DIACOM_EXCEPTION("Failed to load data from PDB!", result);
    openSession();
}

void DiaDataSource::loadDataForExe(const std::wstring& exePath)
{
    if (sessionOpened())
    {
        throw DiaSymbolMasterException{"Session already openned!"};
    }
    const auto p = getSymbolSearchPath();
    std::wcout << p << std::endl;
    const auto result = m_comPtr->loadDataForExe(
        exePath.c_str(), getSymbolSearchPath().c_str(), nullptr);
    CHECK_DIACOM_EXCEPTION("Failed to load data from EXE!", result);
    openSession();
}

std::vector<Symbol> DiaDataSource::getExports(enum SymTagEnum symTag) const
{
    std::vector<Symbol> items{};
    auto exports = enumerate<Symbol>(getGlobalScope(), symTag);
    for (const auto& item : exports)
    {
        items.push_back(item);
    }
    return items;
}

std::vector<Symbol>
DiaDataSource::getExportedUserDefinedTypes(enum UdtKind kind) const
{
    std::vector<Symbol> items{};
    const auto userDefinedTypes = getExportedUserDefinedTypes();
    for (const auto& type : userDefinedTypes)
    {
        if (type.getUdtKind() != kind)
        {
            continue;
        }
        items.push_back(type);
    }
    return items;
}
//
// void DiaDataSource::getExports() const
//{
//    CComPtr<IDiaEnumSymbols> exportedSymbols = nullptr;
//    auto result = m_globalScope->findChildren(SymTagUDT, L"_KTHREAD", nsNone,
//                                              &exportedSymbols);
//    CHECK_DIACOM_EXCEPTION("Failed to find children of global scope!",
//    result); LONG amountOfSymbols = 0; result =
//    exportedSymbols->get_Count(&amountOfSymbols);
//    CHECK_DIACOM_EXCEPTION("Failed to get count of exports!", result);
//    for (LONG i = 0; i < amountOfSymbols; ++i)
//    {
//        IDiaSymbol* symbol = nullptr;
//        result = exportedSymbols->Item(i, &symbol);
//        CHECK_DIACOM_EXCEPTION("Failed to get export item!", result);
//
//        BstrWrapper symbolName{};
//        result = symbol->get_name(symbolName.makeFromRaw());
//        CHECK_DIACOM_EXCEPTION("Failed to get export name!", result);
//
//        std::wcout << "typedef struct " << symbolName << " {" << std::endl;
//
//        Struct diaStruct{symbol};
//
//        for (const auto& member : diaStruct.enumerateMembers())
//        {
//            std::wcout << "\t"
//                       << "/* 0x" << std::hex << member.getOffset() << " */ "
//                       << member.getType() << " " << member.getName() << ";"
//                       << std::endl;
//        }
//        std::wcout << "} " << symbolName.get() + 1 << ", *P"
//                   << symbolName.get() + 1 << ";" << std::endl;
//
//        symbol->Release();
//    }
//    exportedSymbols.Release();
//}

Struct DiaDataSource::getExportedStruct(const std::wstring& structName) const
{
    std::vector<Symbol> items{};
    auto exports = enumerate(getGlobalScope(), SymTagUDT, structName.c_str(),
                             nsfCaseSensitive);
    for (const auto& item : exports)
    {
        items.push_back(item);
    }
    if (items.size() < 1)
    {
        throw std::runtime_error("Struct by name not found!");
    }
    if (items.size() > 1)
    {
        throw std::runtime_error("Too many structs found matching name!");
    }
    return items.at(0);
}

Symbol& DiaDataSource::getGlobalScope()
{
    if (!m_globalScope)
    {
        const auto result =
            m_sessionComPtr->get_globalScope(&m_globalScope.makeFromRaw());
        CHECK_DIACOM_EXCEPTION("Failed to get global scope!", result);
    }

    return m_globalScope;
}

void DiaDataSource::openSession()
{
    const auto result = m_comPtr->openSession(&m_sessionComPtr);
    CHECK_DIACOM_EXCEPTION("Failed to open IDiaSession!", result);
    m_sessionOpenned = true;
    getGlobalScope();
}
} // namespace dia
