#include "pch.h"
//
#include "BstrWrapper.h"
#include "DiaDataSource.h"
#include "DiaSymbolEnumerator.h"
#include "DiaUserDefinedTypeWrapper.h"
#include "Exceptions.h"
#include "SymbolPathHelper.h"
#include "SymbolTypes/DiaEnum.h"
#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <memory>
#include <string>

namespace dia
{
unsigned char PDB_FILE_MAGIC[29] = {  // Microsft C/C++ MSF 7.00...DS
    0x4D, 0x69, 0x63, 0x72, 0x6F, 0x73, 0x6F, 0x66, 0x74, 0x20, 0x43, 0x2F, 0x43, 0x2B, 0x2B,
    0x20, 0x4D, 0x53, 0x46, 0x20, 0x37, 0x2E, 0x30, 0x30, 0x0D, 0x0A, 0x1A, 0x44, 0x53};

unsigned char PE_FILE_MAGIC[2]   = {0x4D, 0x5A};  // MZ

DataSource::DataSource()
{
    const auto result = CoCreateInstance(CLSID_DiaSource, NULL, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource), reinterpret_cast<void**>(&m_comPtr));
    CHECK_DIACOM_EXCEPTION("DiaSource creation failed!", result);
}

DataSource::DataSource(const AnyString& filePath)
    : DataSource{}
{
    loadDataFromArbitraryFile(filePath);
}

DataSource::DataSource(const AnyString& filePath, const AnyString& symstoreDirectory)
{

    addSymtoreDirectory(symstoreDirectory);
    loadDataFromArbitraryFile(filePath);
}

DataSource::~DataSource() {}

void DataSource::addSymtoreDirectory(const AnyString& symstoreDirectory) { m_additionalSymstoreDirectories.push_back(symstoreDirectory); }

void DataSource::loadDataFromPdb(const AnyString& pdbFilePath)
{
    if (sessionOpened())
    {
        throw InvalidUsageException{"Session already openned!"};
    }
    const auto result = m_comPtr->loadDataFromPdb(pdbFilePath.c_str());
    CHECK_DIACOM_EXCEPTION("Failed to load data from PDB!", result);
    openSession();
}

void DataSource::loadDataForExe(const AnyString& exePath)
{
    if (sessionOpened())
    {
        throw InvalidUsageException{"Session already openned!"};
    }

    const auto& symbolSearchPath = buildSymbolSearchPath(exePath);
    const auto result            = m_comPtr->loadDataForExe(exePath.c_str(), symbolSearchPath.c_str(), nullptr);
    CHECK_DIACOM_EXCEPTION("Failed to load data from executable!", result);
    openSession();
}

const std::wstring DataSource::getLoadedPdbFile() const { return getGlobalScope().getSymbolsFileName(); }

const std::vector<Symbol> DataSource::getExports() const
{
    CComPtr<IDiaEnumSymbols> rawExportEnum = nullptr;
    const auto result                      = m_sessionComPtr->getExports(&rawExportEnum);
    CHECK_DIACOM_EXCEPTION("Failed to get session exports!", result);
    DiaSymbolEnumerator<Symbol> exports{std::move(rawExportEnum)};
    std::vector<Symbol> items{};
    for (const auto& item : exports)
    {
        items.push_back(item);
    }
    return items;
}

const std::vector<Symbol> DataSource::getSymbols(enum SymTagEnum symTag) const
{
    if (SymTagExport == symTag)
    {
        throw InvalidUsageException("You probably meant to use DataSource::getExports()");
    }
    std::vector<Symbol> items{};
    auto exports = enumerate<Symbol>(getGlobalScope(), symTag);
    for (const auto& item : exports)
    {
        items.push_back(item);
    }
    return items;
}

const std::vector<Symbol> DataSource::getSymbols(enum SymTagEnum symTag, LPCOLESTR symbolName) const
{
    if (SymTagExport == symTag)
    {
        throw InvalidUsageException("You probably meant to use DataSource::getExports()");
    }
    std::vector<Symbol> items{};
    auto exports = enumerate<Symbol>(getGlobalScope(), symTag, symbolName);
    for (const auto& item : exports)
    {
        items.push_back(item);
    }
    return items;
}

const std::vector<Symbol> DataSource::getSymbols(enum SymTagEnum symTag, LPCOLESTR symbolName, DWORD nameComparisonFlags) const
{
    if (SymTagExport == symTag)
    {
        throw InvalidUsageException("You probably meant to use DataSource::getExports()");
    }
    std::vector<Symbol> items{};
    auto exports = enumerate<Symbol>(getGlobalScope(), symTag, symbolName, nameComparisonFlags);
    for (const auto& item : exports)
    {
        items.push_back(item);
    }
    return items;
}

const Enum DataSource::getEnum(const AnyString& enumName) const
{
    const auto rawEnumSymbols = getSymbols(SymTagEnum, enumName.c_str());
    if (rawEnumSymbols.size() < 1)
    {
        throw SymbolNotFoundException("Enum by name not found!");
    }
    if (rawEnumSymbols.size() > 1)
    {
        throw std::runtime_error("Too many enums found matching name!");
    }
    return static_cast<const Enum&>(rawEnumSymbols.at(0));
}

const std::vector<Symbol> DataSource::getUntypedSymbols() const { return getSymbols(SymTagNull); }

const std::vector<Symbol> DataSource::getCompilands() const { return getSymbols(SymTagCompiland); }

const std::vector<Symbol> DataSource::getCompilandDetails() const { return getSymbols(SymTagCompilandDetails); }

const std::vector<Symbol> DataSource::getCompilandEnvs() const { return getSymbols(SymTagCompilandEnv); }

const std::vector<Function> DataSource::getFunctions() const { return convertSymbolVector<Function>(getSymbols(SymTagFunction)); }

const std::vector<UserDefinedType> DataSource::getUserDefinedTypes() const { return convertSymbolVector<UserDefinedType>(getSymbols(SymTagUDT)); }

const std::vector<Struct> DataSource::getStructs() const { return convertSymbolVector<Struct>(getUserDefinedTypes(UdtStruct)); }

const std::vector<Symbol> DataSource::getClasses() const { return getUserDefinedTypes(UdtClass); }

const std::vector<Symbol> DataSource::getInterfaces() const { return getUserDefinedTypes(UdtInterface); }

const std::vector<Symbol> DataSource::getUnions() const { return getUserDefinedTypes(UdtUnion); }

const std::vector<Symbol> DataSource::getTaggedUnions() const { return getUserDefinedTypes(UdtTaggedUnion); }

const std::vector<Symbol> DataSource::getUserDefinedTypes(enum UdtKind kind) const
{
    std::vector<Symbol> items{};
    const auto userDefinedTypes = getUserDefinedTypes();
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

UserDefinedType DataSource::getStruct(const AnyString& structName) const
{
    std::vector<Symbol> items{};
    auto exports = enumerate<Symbol>(getGlobalScope(), SymTagUDT, structName.c_str());
    for (const auto& item : exports)
    {
        if (UdtStruct != item.getUdtKind())
        {
            continue;
        }
        items.push_back(item);
    }
    if (items.size() < 1)
    {
        throw SymbolNotFoundException("Struct by name not found!");
    }
    if (items.size() > 1)
    {
        throw std::runtime_error("Too many structs found matching name!");
    }
    return static_cast<const UserDefinedType&>(items.at(0));
}

Symbol& DataSource::getGlobalScope()
{
    if (!m_globalScope)
    {
        const auto result = m_sessionComPtr->get_globalScope(&m_globalScope.makeFromRaw());
        CHECK_DIACOM_EXCEPTION("Failed to get global scope!", result);
    }

    return m_globalScope;
}

void DataSource::openSession()
{
    const auto result = m_comPtr->openSession(&m_sessionComPtr);
    CHECK_DIACOM_EXCEPTION("Failed to open IDiaSession!", result);
    m_sessionOpenned = true;
    getGlobalScope();
}

void DataSource::loadDataFromArbitraryFile(const std::wstring& filePath)
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
             {L"acm", L"ax", L"cpl", L"drv", L"efi", L"mui", L"ocx", L"scr", L"tsp", L"mun", L"exe", L"dll", L"sys"})
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

    throw InvalidFileFormatException("Failed to deduce file format!");
}

std::wstring DataSource::buildSymbolSearchPath(const std::wstring& exePath) const
{
    std::wstring searchPath = L"srv*";
    for (const auto& dir : m_additionalSymstoreDirectories)
    {
        searchPath += dir + L"*";
    }
    searchPath += getSymbolSearchPathForExecutable(exePath, false);
    return searchPath;
}

}  // namespace dia
