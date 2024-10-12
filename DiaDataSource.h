#pragma once
#include <Dia2.h>
#pragma comment(lib, "diaguids")
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
    ~DiaDataSource() noexcept;

    void loadDataFromPdb(const std::wstring& pdbFilePath);
    void loadAndValidateDataFromPdb();
    void loadDataForExe(const std::wstring& exePath);
    void loadDataFromIStream();
    void loadDataFromCodeViewInfo();
    void loadDataFromMiscInfo();

    std::vector<Symbol> getExports(enum SymTagEnum symTag) const;

    std::vector<Symbol> getUntypedExports() const
    {
        return getExports(SymTagNull);
    }
    std::vector<Symbol> getExportedCompilands() const
    {
        return getExports(SymTagCompiland);
    }
    std::vector<Symbol> getExportedCompilandDetails() const
    {
        return getExports(SymTagCompilandDetails);
    }
    std::vector<Symbol> getExportedCompilandEnvs() const
    {
        return getExports(SymTagCompilandEnv);
    }
    std::vector<Symbol> getExportedFunctions() const
    {
        return getExports(SymTagFunction);
    }
    std::vector<UserDefinedType> getExportedUserDefinedTypes() const
    {
        const auto exports = getExports(SymTagUDT);
        std::vector<UserDefinedType> types{exports.begin(), exports.end()};
        return types;
    }
    std::vector<Symbol> getExportedUserDefinedTypes(enum UdtKind kind) const;
    std::vector<Struct> getExportedStructs() const
    {
        const auto userDefinedStructs = getExportedUserDefinedTypes(UdtStruct);
        std::vector<Struct> structs{userDefinedStructs.begin(),
                                    userDefinedStructs.end()};
        return structs;
    }
    std::vector<Symbol> getExportedClasses() const
    {
        return getExportedUserDefinedTypes(UdtClass);
    }
    std::vector<Symbol> getExportedInterfaces() const
    {
        return getExportedUserDefinedTypes(UdtInterface);
    }
    std::vector<Symbol> getExportedUnions() const
    {
        return getExportedUserDefinedTypes(UdtUnion);
    }
    std::vector<Symbol> getExportedTaggedUnions() const
    {
        return getExportedUserDefinedTypes(UdtTaggedUnion);
    }

    Struct getExportedStruct(const std::wstring& structName) const;

    // void getExports() const;

    bool sessionOpened() const { return m_sessionOpenned; }

private:
    Symbol& getGlobalScope();
    const Symbol& getGlobalScope() const
    {
        ATLASSERT(!!m_globalScope);
        return m_globalScope;
    }
    void openSession();

    CComPtr<IDiaDataSource> m_comPtr{nullptr};
    CComPtr<IDiaSession> m_sessionComPtr{nullptr};
    Symbol m_globalScope{};
    bool m_sessionOpenned{false};
};

static inline const std::wstring& getSymbolSearchPath()
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
            s_symbolSearchPath =
                std::wstring{L"srv*C:\\Windows\\SYMBOLS*https://"
                             L"msdl.microsoft.com/download/symbols"};
        }
        else
        {
            s_symbolSearchPath = std::wstring{buffer.get(), requiredBufferSize};
        }
    }
    return s_symbolSearchPath;
}
} // namespace dia
