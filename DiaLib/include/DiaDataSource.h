#pragma once
#include "AnyString.h"
#include "DiaSymbol.h"
#include "DiaSymbolEnumerator.h"
#include "DiaUserDefinedTypeWrapper.h"
#include "SymbolTypes/DiaEnum.h"
#include "SymbolTypes/DiaFunction.h"
#include <DiaSession.h>
#include <atlbase.h>
#include <dia2.h>
#include <memory>
#include <string>
#include <vector>

namespace dia
{
/// @brief Wrapper for IDiaDataSource.
/// Initiates access to a source of debugging symbols.
class DataSource final
{
public:
    DataSource();
    DataSource(const AnyString& filePath);
    DataSource(const AnyString& filePath, const AnyString& symstoreDirectory);
    ~DataSource() noexcept;

    void addSymtoreDirectory(const AnyString& symstoreDirectory);

    void loadDataFromPdb(const AnyString& pdbFilePath);
    void loadDataForExe(const AnyString& exePath);

    // TODO: Implement
    void loadAndValidateDataFromPdb();
    void loadDataFromIStream();
    void loadDataFromCodeViewInfo();
    void loadDataFromMiscInfo();

    const std::wstring getLoadedPdbFile() const;

    Session& getSession() { return m_session; }

    Symbol getSymbolByHash(size_t symbolHash) const;

    DiaSymbolEnumerator<Symbol> getExports() const;

    DiaSymbolEnumerator<Symbol> getSymbols(enum SymTagEnum symTag) const;
    DiaSymbolEnumerator<Symbol> getSymbols(enum SymTagEnum symTag, LPCOLESTR symbolName) const;
    DiaSymbolEnumerator<Symbol> getSymbols(enum SymTagEnum symTag, LPCOLESTR symbolName, DWORD nameComparisonFlags) const;

    Enum getEnum(const AnyString& enumName) const;
    DiaSymbolEnumerator<Symbol> getUntypedSymbols() const;
    DiaSymbolEnumerator<Symbol> getCompilands() const;
    DiaSymbolEnumerator<Symbol> getCompilandDetails() const;
    DiaSymbolEnumerator<Symbol> getCompilandEnvs() const;
    const std::vector<Function> getFunctions() const;
    const std::vector<UserDefinedType> getUserDefinedTypes() const;
    std::vector<Symbol> getUserDefinedTypes(enum UdtKind kind) const;
    const std::vector<Struct> getStructs() const;
    std::vector<Symbol> getClasses() const;
    std::vector<Symbol> getInterfaces() const;
    std::vector<Symbol> getUnions() const;
    std::vector<Symbol> getTaggedUnions() const;
    const std::vector<Typedef> getTypedefs() const;

    UserDefinedType getStruct(const AnyString& structName) const;

    bool sessionOpened() const { return !(!m_session); }

    const Symbol& getGlobalScope() const;

private:
    void openSession();
    void loadDataFromArbitraryFile(const std::wstring& filePath);

    std::wstring buildSymbolSearchPath(const std::wstring& exePath) const;

    CComPtr<IDiaDataSource> m_comPtr{nullptr};
    Session m_session{};
    std::vector<std::wstring> m_additionalSymstoreDirectories{};
};

}  // namespace dia
