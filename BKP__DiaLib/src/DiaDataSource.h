#pragma once
#include <Dia2.h>
#pragma comment(lib, "diaguids")
#include "DiaStruct.h"
#include "DiaSymbol.h"
#include "DiaSymbolEnumerator.h"
#include "DiaSymbolTypes/DiaFunction.h"
#include <atlbase.h>
#include <memory>
#include <string>
#include <vector>

namespace dia
{

class DataSource final
{
public:
    DataSource();
    DataSource(const std::string& filePath);
    DataSource(const std::wstring& filePath);
    DataSource(const std::string& filePath, const std::string& symstoreDirectory);
    DataSource(const std::wstring& filePath, const std::wstring& symstoreDirectory);
    ~DataSource() noexcept;

    void addSymtoreDirectory(const std::string& symstoreDirectory);
    void addSymtoreDirectory(const std::wstring& symstoreDirectory);

    void loadDataFromPdb(const std::string& pdbFilePath);
    void loadDataFromPdb(const std::wstring& pdbFilePath);
    void loadDataForExe(const std::string& exePath);
    void loadDataForExe(const std::wstring& exePath);

    // TODO: Implement
    void loadAndValidateDataFromPdb();
    void loadDataFromIStream();
    void loadDataFromCodeViewInfo();
    void loadDataFromMiscInfo();

    const std::wstring getLoadedPdbFile() const;

    const std::vector<Symbol> getExports() const;

    const std::vector<Symbol> getSymbols(enum SymTagEnum symTag) const;
    const std::vector<Symbol> getUntypedSymbols() const;
    const std::vector<Symbol> getCompilands() const;
    const std::vector<Symbol> getCompilandDetails() const;
    const std::vector<Symbol> getCompilandEnvs() const;
    const std::vector<Function> getFunctions() const;
    const std::vector<UserDefinedType> getUserDefinedTypes() const;
    const std::vector<Symbol> getUserDefinedTypes(enum UdtKind kind) const;
    const std::vector<Struct> getStructs() const;
    const std::vector<Symbol> getClasses() const;
    const std::vector<Symbol> getInterfaces() const;
    const std::vector<Symbol> getUnions() const;
    const std::vector<Symbol> getTaggedUnions() const;

    const Struct getStruct(const std::wstring& structName) const;

    bool sessionOpened() const { return m_sessionOpenned; }

private:
    Symbol& getGlobalScope();

    const Symbol& getGlobalScope() const
    {
        if (!!!m_globalScope)
        {
            throw std::runtime_error("A DIA session must be openned and a global "
                                     "scope must be identified before using this API!");
        }
        return m_globalScope;
    }

    void openSession();
    void loadDataFromArbitraryFile(const std::wstring& filePath);

    std::wstring buildSymbolSearchPath(const std::wstring& exePath) const;

    CComPtr<IDiaDataSource> m_comPtr{nullptr};
    CComPtr<IDiaSession> m_sessionComPtr{nullptr};
    Symbol m_globalScope{};
    bool m_sessionOpenned{false};
    std::vector<std::wstring> m_additionalSymstoreDirectories{};
};

}  // namespace dia
