#include "pch.h"
//
#include "DiaSession.h"
#include "DiaSymbolEnumerator.h"

namespace dia
{
bool Session::operator!() const { return !m_openned; }

Symbol& Session::getGlobalScope() const
{
    if (!m_globalScope)
    {
        const auto result = get()->get_globalScope(&m_globalScope.makeFromRaw());
        CHECK_DIACOM_EXCEPTION("Failed to get global scope!", result);
    }
    return m_globalScope;
}

DiaSymbolEnumerator<Symbol> Session::getExports() const
{
    CComPtr<IDiaEnumSymbols> rawExportEnum = nullptr;
    const auto result                      = get()->getExports(&rawExportEnum);
    CHECK_DIACOM_EXCEPTION("Failed to get session exports!", result);
    DiaSymbolEnumerator<Symbol> exports{std::move(rawExportEnum)};
    return exports;
}

Symbol Session::getSymbolById(DWORD symbolId) const
{
    Symbol foundSymbol{};
    const auto result = get()->symbolById(symbolId, &foundSymbol.makeFromRaw());
    CHECK_DIACOM_EXCEPTION("Failed to get symbol by id!", result);
    return foundSymbol;
}

bool Session::areSymbolsEquivalent(const Symbol& symbolA, const Symbol& symbolB) const
{
    const auto result = get()->symsAreEquiv(symbolA.get(), symbolB.get());
    if (S_OK == result)
    {
        return true;
    }
    if (S_FALSE == result)
    {
        return false;
    }
    CHECK_DIACOM_EXCEPTION("Failed to check if symbols are equivalent!", result);

    // Unreachable
    __assume(false);
}
}  // namespace dia
