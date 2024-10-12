#pragma once
#include "DiaSymbol.h"
#include <atlbase.h>
#include <cstddef> // For std::ptrdiff_t
#include <dia2.h>
#include <iterator> // For std::forward_iterator_tag
#include <string>
namespace dia
{

// Forward decleration
class DiaSymbolEnumerator;
DiaSymbolEnumerator enumerate(const Symbol& parentSymbol,
                              enum SymTagEnum symTag, LPCOLESTR name,
                              DWORD compareFlags);

class DiaSymbolEnumerator final
{
public:
    static DiaSymbolEnumerator enumerate(const Symbol& parentSymbol)
    {
        return enumerate(parentSymbol, SymTagNull);
    }

    static DiaSymbolEnumerator enumerate(const Symbol& parentSymbol,
                                         enum SymTagEnum symTag)
    {
        return enumerate(parentSymbol, symTag, nullptr);
    }

    static DiaSymbolEnumerator enumerate(const Symbol& parentSymbol,
                                         enum SymTagEnum symTag, LPCOLESTR name)
    {
        return enumerate(parentSymbol, symTag, name, nsNone);
    }

    static DiaSymbolEnumerator enumerate(const Symbol& parentSymbol,
                                         enum SymTagEnum symTag, LPCOLESTR name,
                                         DWORD compareFlags)
    {
        return dia::enumerate(parentSymbol, symTag, name, compareFlags);
    }

    class Iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Symbol;
        using pointer = Symbol*;
        using reference = Symbol&;

        // Default constructor (end iterator)
        Iterator()
            : m_enumSymbols(nullptr), m_currentSymbol(nullptr),
              m_endReached(true)
        {
        }

        // Constructor with enumerator
        Iterator(CComPtr<IDiaEnumSymbols> enumSymbols)
            : m_enumSymbols(enumSymbols), m_currentSymbol(nullptr),
              m_endReached(false)
        {
            // Initialize to the first symbol
            nextSymbol();
        }

        // Dereference operators
        reference operator*() { return m_currentData; }
        const Symbol& operator*() const { return m_currentData; }
        pointer operator->() { return &m_currentData; }
        const Symbol* operator->() const { return &m_currentData; }

        // Prefix increment
        Iterator& operator++()
        {
            nextSymbol();
            return *this;
        }

        // Postfix increment
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            nextSymbol();
            return tmp;
        }

        // Equality operators
        bool operator==(const Iterator& other) const
        {
            if (m_endReached && other.m_endReached)
                return true;
            if (m_endReached != other.m_endReached)
                return false;
            // Compare current symbols
            return m_currentSymbol == other.m_currentSymbol;
        }

        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }

    private:
        void nextSymbol()
        {
            if (!m_enumSymbols)
            {
                m_endReached = true;
                return;
            }

            CComPtr<IDiaSymbol> symbol{nullptr};
            ULONG celt = 0;
            HRESULT hr = m_enumSymbols->Next(1, &symbol, &celt);
            if (SUCCEEDED(hr) && celt == 1 && symbol)
            {
                m_currentSymbol = symbol;
                m_currentData = Symbol(std::move(symbol));
            }
            else
            {
                m_endReached = true;
                m_currentSymbol = nullptr;
            }
        }

        CComPtr<IDiaEnumSymbols> m_enumSymbols{nullptr};
        CComPtr<IDiaSymbol> m_currentSymbol{nullptr};
        Symbol m_currentData{};
        bool m_endReached{false};
    };

    // Begin and End methods for iteration
    Iterator begin();
    Iterator end();

private:
    DiaSymbolEnumerator() = default;
    DiaSymbolEnumerator(CComPtr<IDiaEnumSymbols>&& enumSymbols)
        : m_enumSymbols{std::move(enumSymbols)} {};

    CComPtr<IDiaEnumSymbols> m_enumSymbols{nullptr};

    friend DiaSymbolEnumerator enumerate(const Symbol& parentSymbol,
                                         enum SymTagEnum symTag, LPCOLESTR name,
                                         DWORD compareFlags);
};

static inline DiaSymbolEnumerator enumerate(const Symbol& parentSymbol,
                                            enum SymTagEnum symTag)
{
    return DiaSymbolEnumerator::enumerate(parentSymbol, symTag);
}

static inline DiaSymbolEnumerator
enumerate(const Symbol& parentSymbol, enum SymTagEnum symTag, LPCOLESTR name)
{
    return DiaSymbolEnumerator::enumerate(parentSymbol, symTag, name);
}

static inline DiaSymbolEnumerator enumerate(const Symbol& parentSymbol,
                                            enum SymTagEnum symTag,
                                            LPCOLESTR name, DWORD compareFlags)
{
    CComPtr<IDiaEnumSymbols> enumSymbols{nullptr};
    HRESULT hr = parentSymbol.get()->findChildren(symTag, name, compareFlags,
                                                  &enumSymbols);
    if (FAILED(hr) || !enumSymbols)
    {
        return {};
    }
    return DiaSymbolEnumerator{std::move(enumSymbols)};
}

// Begin iterator
inline DiaSymbolEnumerator::Iterator DiaSymbolEnumerator::begin()
{
    if (!m_enumSymbols)
    {
        return end();
    }

    return Iterator(m_enumSymbols);
}

// End iterator
inline DiaSymbolEnumerator::Iterator DiaSymbolEnumerator::end() { return Iterator(); }

} // namespace dia