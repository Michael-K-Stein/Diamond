#pragma once
#include <Dia2.h>
#pragma comment(lib, "diaguids")
#include "DiaFunction.h"
#include "DiaStruct.h"
#include "DiaSymbol.h"
#include <atlbase.h>
#include <memory>
#include <string>
#include <vector>

namespace dia
{

class DiaDataSource final
{
public:
    DiaDataSource();
    DiaDataSource(const std::string& filePath);
    DiaDataSource(const std::wstring& filePath);
    ~DiaDataSource() noexcept;

    void loadDataFromPdb(const std::string& pdbFilePath);
    void loadDataFromPdb(const std::wstring& pdbFilePath);
    void loadDataForExe(const std::string& exePath);
    void loadDataForExe(const std::wstring& exePath);

    void loadAndValidateDataFromPdb();
    void loadDataFromIStream();
    void loadDataFromCodeViewInfo();
    void loadDataFromMiscInfo();

    std::vector<Symbol> getExports(enum SymTagEnum symTag) const;
    std::vector<Symbol> getUntypedExports() const;
    std::vector<Symbol> getExportedCompilands() const;
    std::vector<Symbol> getExportedCompilandDetails() const;
    std::vector<Symbol> getExportedCompilandEnvs() const;
    std::vector<Function> getExportedFunctions() const;
    std::vector<UserDefinedType> getExportedUserDefinedTypes() const;
    std::vector<Symbol> getExportedUserDefinedTypes(enum UdtKind kind) const;
    std::vector<Struct> getExportedStructs() const;
    std::vector<Symbol> getExportedClasses() const;
    std::vector<Symbol> getExportedInterfaces() const;
    std::vector<Symbol> getExportedUnions() const;
    std::vector<Symbol> getExportedTaggedUnions() const;
    Struct getExportedStruct(const std::wstring& structName) const;

    bool sessionOpened() const { return m_sessionOpenned; }

private:
    Symbol& getGlobalScope();
    const Symbol& getGlobalScope() const
    {
        if (!!!m_globalScope)
        {
            throw std::runtime_error(
                "A DIA session must be openned and a global "
                "scope must be identified before using this API!");
        }
        return m_globalScope;
    }
    void openSession();
    void loadDataFromArbitraryFile(const std::wstring& filePath);

    CComPtr<IDiaDataSource> m_comPtr{nullptr};
    CComPtr<IDiaSession> m_sessionComPtr{nullptr};
    Symbol m_globalScope{};
    bool m_sessionOpenned{false};
};

} // namespace dia
