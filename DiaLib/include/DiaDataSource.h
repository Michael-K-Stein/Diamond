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

    template <typename T>
    DiaSymbolEnumerator<T> getSymbols(enum SymTagEnum symTag) const;
    DiaSymbolEnumerator<Symbol> getSymbols(enum SymTagEnum symTag) const;
    DiaSymbolEnumerator<Symbol> getSymbols(enum SymTagEnum symTag, LPCOLESTR symbolName) const;
    DiaSymbolEnumerator<Symbol> getSymbols(enum SymTagEnum symTag, LPCOLESTR symbolName, DWORD nameComparisonFlags) const;

    DiaSymbolEnumerator<Symbol> getUntypedSymbols() const;
    DiaSymbolEnumerator<Symbol> getCompilands() const;
    DiaSymbolEnumerator<Symbol> getCompilandDetails() const;
    DiaSymbolEnumerator<Symbol> getCompilandEnvs() const;

    Enum getEnum(const AnyString& enumName) const;
    DiaSymbolEnumerator<Enum> getEnums() const;

    Function getFunction(const AnyString& name) const;
    DiaSymbolEnumerator<Function> getFunctions() const;

    Typedef getTypedef(const AnyString& name) const;
    DiaSymbolEnumerator<Typedef> getTypedefs() const;

    DiaSymbolEnumerator<UserDefinedType> getUserDefinedTypes() const;
    std::vector<Symbol> getUserDefinedTypes(enum UdtKind kind) const;

    UserDefinedType getStruct(const AnyString& structName) const;
    std::vector<Struct> getStructs() const;
    std::vector<Class> getClasses() const;
    std::vector<Interface> getInterfaces() const;
    std::vector<Union> getUnions() const;
    std::vector<TaggedUnion> getTaggedUnions() const;

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
