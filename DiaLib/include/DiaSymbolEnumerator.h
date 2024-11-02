#pragma once
#include "DiaSymbol.h"
#include "Exceptions.h"
#include "SymbolTypes/DiaData.h"
#include "SymbolTypes/DiaSymbolTypes.h"
#include <atlbase.h>
#include <cstddef>  // For std::ptrdiff_t
#include <dia2.h>
#include <iterator>  // For std::forward_iterator_tag
#include <string>

namespace dia
{

// Forward declaration
template <typename T = Symbol>
class DiaSymbolEnumerator;

template <typename T = Symbol>
DiaSymbolEnumerator<T> enumerate(const Symbol& parentSymbol, enum SymTagEnum symTag, LPCOLESTR name, DWORD compareFlags);

template <typename T>
class DiaSymbolEnumerator final
{
public:
    // Explicit NULL constructor
    explicit DiaSymbolEnumerator(nullptr_t)
        : DiaSymbolEnumerator(){};

    DiaSymbolEnumerator(const DiaSymbolEnumerator& other);
    DiaSymbolEnumerator operator=(const DiaSymbolEnumerator& other);
    DiaSymbolEnumerator(DiaSymbolEnumerator&& other) noexcept;
    DiaSymbolEnumerator operator=(DiaSymbolEnumerator&& other) noexcept;

    static DiaSymbolEnumerator enumerate(const Symbol& parentSymbol) { return ::dia::enumerate<T>(parentSymbol, SymTagNull); }

    static DiaSymbolEnumerator enumerate(const Symbol& parentSymbol, enum SymTagEnum symTag)
    {
        return ::dia::enumerate<T>(parentSymbol, symTag, nullptr, nsNone);
    }

    static DiaSymbolEnumerator enumerate(const Symbol& parentSymbol, enum SymTagEnum symTag, LPCOLESTR name)
    {
        return ::dia::enumerate<T>(parentSymbol, symTag, name, nsNone);
    }

    static DiaSymbolEnumerator enumerate(const Symbol& parentSymbol, enum SymTagEnum symTag, LPCOLESTR name, DWORD compareFlags)
    {
        return ::dia::enumerate<T>(parentSymbol, symTag, name, compareFlags);
    }

    class Iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        // Default constructor (end iterator)
        Iterator()
            : m_enumSymbols(nullptr)
            , m_currentSymbol(nullptr)
            , m_endReached(true)
        {
        }

        // Constructor with enumerator
        Iterator(CComPtr<IDiaEnumSymbols> enumSymbols)
            : m_enumSymbols(enumSymbols)
            , m_currentSymbol(nullptr)
            , m_endReached(false)
        {
            // Initialize to the first symbol
            nextSymbol();
        }

        // Dereference operators
        reference operator*() { return m_currentData; }

        const T& operator*() const { return m_currentData; }

        pointer operator->() { return &m_currentData; }

        const T* operator->() const { return &m_currentData; }

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
            if (m_endReached && other.m_endReached) return true;
            if (m_endReached != other.m_endReached) return false;
            // Compare current symbols
            return m_currentSymbol == other.m_currentSymbol;
        }

        bool operator!=(const Iterator& other) const { return !(*this == other); }

    private:
        void nextSymbol()
        {
            if (!m_enumSymbols)
            {
                m_endReached = true;
                return;
            }

            CComPtr<IDiaSymbol> symbol{nullptr};
            ULONG celt    = 0;
            const auto hr = m_enumSymbols->Next(1, &symbol, &celt);
            if (SUCCEEDED(hr) && celt == 1 && symbol)
            {
                m_currentSymbol = symbol;
                m_currentData   = T{std::move(symbol)};
            }
            else
            {
                m_endReached    = true;
                m_currentSymbol = nullptr;
            }
        }

        CComPtr<IDiaEnumSymbols> m_enumSymbols{nullptr};
        CComPtr<IDiaSymbol> m_currentSymbol{nullptr};
        T m_currentData{};
        bool m_endReached{false};
    };

    // Begin and End methods for iteration
    Iterator begin();
    Iterator end();

    size_t count() const;

    operator const std::vector<T>()
    {
        std::vector<T> myVector{};
        for (const auto& item : *this)
        {
            myVector.push_back(item);
        }
        return myVector;
    }

private:
    DiaSymbolEnumerator() = default;

    DiaSymbolEnumerator(CComPtr<IDiaEnumSymbols>&& enumSymbols)
        : m_enumSymbols{std::move(enumSymbols)}
    {
    }

    void move(DiaSymbolEnumerator&& other) noexcept;

    CComPtr<IDiaEnumSymbols> m_enumSymbols{nullptr};

    // Correct friend function declaration
    template <typename U>
    friend DiaSymbolEnumerator<U> enumerate(const Symbol& parentSymbol, enum SymTagEnum symTag, LPCOLESTR name, DWORD compareFlags);
    friend class DataSource;
    friend class Session;
};

template <typename T>
inline DiaSymbolEnumerator<T>::DiaSymbolEnumerator(const DiaSymbolEnumerator& other)
{
    _ASSERT(nullptr == m_enumSymbols);
    const auto result = other.m_enumSymbols->Clone(&m_enumSymbols);
    CHECK_DIACOM_EXCEPTION("Failed to clone symbol's enumerator!", result);
}

template <typename T>
inline DiaSymbolEnumerator<T> DiaSymbolEnumerator<T>::operator=(const DiaSymbolEnumerator& other)
{
    _ASSERT(nullptr == m_enumSymbols);
    const auto result = other.m_enumSymbols->Clone(&m_enumSymbols);
    CHECK_DIACOM_EXCEPTION("Failed to clone symbol's enumerator!", result);
    return *this;
}

template <typename T>
inline DiaSymbolEnumerator<T>::DiaSymbolEnumerator(DiaSymbolEnumerator&& other) noexcept
{
    _ASSERT(nullptr == m_enumSymbols);
    if (this != &other)
    {
        move(std::move(other));
    }
}

template <typename T>
inline DiaSymbolEnumerator<T> DiaSymbolEnumerator<T>::operator=(DiaSymbolEnumerator&& other) noexcept
{
    _ASSERT(nullptr == m_enumSymbols);
    if (this != &other)
    {
        move(std::move(other));
    }
    return *this;
}

// Begin iterator
template <typename T>
inline typename DiaSymbolEnumerator<T>::Iterator DiaSymbolEnumerator<T>::begin()
{
    if (!m_enumSymbols)
    {
        return end();
    }

    return Iterator(m_enumSymbols);
}

// End iterator
template <typename T>
inline typename DiaSymbolEnumerator<T>::Iterator DiaSymbolEnumerator<T>::end()
{
    return Iterator();
}

template <typename T>
inline size_t DiaSymbolEnumerator<T>::count() const
{
    auto copiedEnumerator = *this;
    return std::distance(copiedEnumerator.begin(), copiedEnumerator.end());
}

template <typename T>
inline void DiaSymbolEnumerator<T>::move(DiaSymbolEnumerator&& other) noexcept
{
    _ASSERT(this != &other);
    m_enumSymbols       = std::move(other.m_enumSymbols);
    other.m_enumSymbols = nullptr;
}

// Templated enumerate implementations
template <typename T>
inline DiaSymbolEnumerator<T> enumerate(const Symbol& parentSymbol, enum SymTagEnum symTag)
{
    return enumerate<T>(parentSymbol, symTag, nullptr, nsNone);
}

template <typename T>
inline DiaSymbolEnumerator<T> enumerate(const Symbol& parentSymbol, enum SymTagEnum symTag, LPCOLESTR name)
{
    return enumerate<T>(parentSymbol, symTag, name, nsfCaseSensitive);
}

template <typename T>
inline DiaSymbolEnumerator<T> enumerate(const Symbol& parentSymbol, enum SymTagEnum symTag, LPCOLESTR name, DWORD compareFlags)
{
    _ASSERT(SymTagNull <= symTag && symTag < SymTagMax);
    CComPtr<IDiaEnumSymbols> enumSymbols{nullptr};
    const auto result = parentSymbol.get()->findChildren(symTag, name, compareFlags, &enumSymbols);
    CHECK_DIACOM_EXCEPTION("Failed to find children!", result);
    return DiaSymbolEnumerator<T>{std::move(enumSymbols)};
}

}  // namespace dia
