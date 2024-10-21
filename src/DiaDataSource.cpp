#include "DiaDataSource.h"
#include "BstrWrapper.h"
#include "DiaStruct.h"
#include "DiaSymbolEnumerator.h"
#include "Exceptions.h"
#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <memory>
#include <string>

namespace dia
{
unsigned char PDB_FILE_MAGIC[29] = { // Microsft C/C++ MSF 7.00...DS
    0x4D, 0x69, 0x63, 0x72, 0x6F, 0x73, 0x6F, 0x66, 0x74, 0x20,
    0x43, 0x2F, 0x43, 0x2B, 0x2B, 0x20, 0x4D, 0x53, 0x46, 0x20,
    0x37, 0x2E, 0x30, 0x30, 0x0D, 0x0A, 0x1A, 0x44, 0x53};

unsigned char PE_FILE_MAGIC[2] = {0x4D, 0x5A}; // MZ

static const std::wstring getSymbolSearchPath()
{
    static std::wstring s_symbolSearchPath{};
    if (s_symbolSearchPath.empty())
    {
        // Return value is size in `count of characters`
        const auto requiredBufferSize =
            GetEnvironmentVariableW(L"_NT_SYMBOL_PATH", nullptr, 0);
        auto buffer = std::make_unique<wchar_t[]>(requiredBufferSize);
        memset(buffer.get(), 0, requiredBufferSize);
        if (0 == GetEnvironmentVariableW(L"_NT_SYMBOL_PATH", buffer.get(),
                                         requiredBufferSize))
        {
            s_symbolSearchPath = std::wstring{L"TODO: This?"};
        }
        else
        {
            s_symbolSearchPath = std::wstring{buffer.get(), requiredBufferSize};
        }
    }
    return s_symbolSearchPath;
}

static const std::wstring convertToWstring(const std::string& str)
{

    std::wstring wstr(str.begin(), str.end());
    return wstr;
}

DiaDataSource::DiaDataSource()
{
    const auto result = CoCreateInstance(
        CLSID_DiaSource, NULL, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource),
        reinterpret_cast<void**>(&m_comPtr));
    CHECK_DIACOM_EXCEPTION("DiaSource creation failed!", result);
}

DiaDataSource::DiaDataSource(const std::string& filePath)
    : DiaDataSource{convertToWstring(filePath)}
{
}

DiaDataSource::DiaDataSource(const std::wstring& filePath) : DiaDataSource{}
{
    loadDataFromArbitraryFile(filePath);
}

DiaDataSource::~DiaDataSource() {}

void DiaDataSource::loadDataFromPdb(const std::string& pdbFilePath)
{
    loadDataFromPdb(convertToWstring(pdbFilePath));
}

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

void DiaDataSource::loadDataForExe(const std::string& exePath)
{
    loadDataForExe(convertToWstring(exePath));
}

void DiaDataSource::loadDataForExe(const std::wstring& exePath)
{
    if (sessionOpened())
    {
        throw DiaSymbolMasterException{"Session already openned!"};
    }
    const auto& symbolSearchPath = getSymbolSearchPath();
    std::wcout << symbolSearchPath << std::endl;
    const auto result = m_comPtr->loadDataForExe(
        exePath.c_str(), getSymbolSearchPath().c_str(), nullptr);
    CHECK_DIACOM_EXCEPTION("Failed to load data from executable!", result);
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

std::vector<Symbol> DiaDataSource::getUntypedExports() const
{
    return getExports(SymTagNull);
}
std::vector<Symbol> DiaDataSource::getExportedCompilands() const
{
    return getExports(SymTagCompiland);
}
std::vector<Symbol> DiaDataSource::getExportedCompilandDetails() const
{
    return getExports(SymTagCompilandDetails);
}
std::vector<Symbol> DiaDataSource::getExportedCompilandEnvs() const
{
    return getExports(SymTagCompilandEnv);
}
std::vector<Function> DiaDataSource::getExportedFunctions() const
{
    const auto functionSymbols = getExports(SymTagFunction);
    std::vector<Function> functions{functionSymbols.begin(),
                                    functionSymbols.end()};
    return functions;
}
std::vector<UserDefinedType> DiaDataSource::getExportedUserDefinedTypes() const
{
    const auto exports = getExports(SymTagUDT);
    std::vector<UserDefinedType> types{exports.begin(), exports.end()};
    return types;
}
std::vector<Struct> DiaDataSource::getExportedStructs() const
{
    const auto userDefinedStructs = getExportedUserDefinedTypes(UdtStruct);
    std::vector<Struct> structs{userDefinedStructs.begin(),
                                userDefinedStructs.end()};
    return structs;
}
std::vector<Symbol> DiaDataSource::getExportedClasses() const
{
    return getExportedUserDefinedTypes(UdtClass);
}
std::vector<Symbol> DiaDataSource::getExportedInterfaces() const
{
    return getExportedUserDefinedTypes(UdtInterface);
}
std::vector<Symbol> DiaDataSource::getExportedUnions() const
{
    return getExportedUserDefinedTypes(UdtUnion);
}
std::vector<Symbol> DiaDataSource::getExportedTaggedUnions() const
{
    return getExportedUserDefinedTypes(UdtTaggedUnion);
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
void DiaDataSource::loadDataFromArbitraryFile(const std::wstring& filePath)
{
    const auto fileExtension = filePath.substr(filePath.find_last_of(L".") + 1);
    if (0 == lstrcmpiW(L"pdb", fileExtension.c_str()))
    {
        loadDataFromPdb(filePath);
        return;
    }
    else
    {
        for (const auto& executableExtension :
             // List taken from
             // https://en.wikipedia.org/wiki/Portable_Executable
             {L"acm", L"ax", L"cpl", L"drv", L"efi", L"mui", L"ocx", L"scr",
              L"tsp", L"mun", L"exe", L"dll", L"sys"})
        {
            if (0 != lstrcmpiW(executableExtension, fileExtension.c_str()))
            {
                continue;
            }
            loadDataForExe(filePath);
            return;
        }
    }

    // File did not have a known extension, try deducing it using file
    // signature magics

    std::ifstream unknownFile{filePath};
    char magicBuffer[max(sizeof(PDB_FILE_MAGIC), sizeof(PE_FILE_MAGIC))] = {};
    // If the file is too small to read a magic, it is most definitely
    // corrup anyway.
    unknownFile.read(magicBuffer, sizeof(magicBuffer));

    if (0 == memcmp(magicBuffer, PDB_FILE_MAGIC, sizeof(PDB_FILE_MAGIC)))
    {
        loadDataFromPdb(filePath);
        return;
    }
    else if (0 == memcmp(magicBuffer, PE_FILE_MAGIC, sizeof(PE_FILE_MAGIC)))
    {
        loadDataForExe(filePath);
        return;
    }

    throw std::runtime_error("Failed to deduce file format!");
}
} // namespace dia
