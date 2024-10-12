#pragma once
#include <atlbase.h>
#include <dia2.h>
#include <iostream>
#include <memory>
#include <string>
namespace dia
{

template <typename InterfaceT = IUnknown>
class Base
{
public:
    Base() = default;
    Base(const CComPtr<InterfaceT>& item) : m_itemRef{item} { incRef(); }
    Base(CComPtr<InterfaceT>&& item) : m_itemRef{std::move(item)} {}
    Base(Base&& other);
    Base& operator=(Base&& other) noexcept;
    Base(const Base& other);
    Base& operator=(const Base& other) noexcept;
    virtual ~Base() noexcept;

    CComPtr<InterfaceT>& makeFromRaw() { return m_itemRef; }

    bool operator!() const;

protected:
    CComPtr<InterfaceT> get() { return m_itemRef; }
    CComPtr<InterfaceT> get() const { return m_itemRef; }

private:
    void incRef();
    void decRef();
    void move(Base&& other);

    mutable CComPtr<InterfaceT> m_itemRef{nullptr};
};

template <typename InterfaceT>
inline Base<InterfaceT>::Base(Base&& other)
{
    move(std::move(other));
}

template <typename InterfaceT>
inline Base<InterfaceT>&
Base<InterfaceT>::operator=(Base<InterfaceT>&& other) noexcept
{
    move(std::move(other));
    return *this;
}

template <typename InterfaceT>
inline Base<InterfaceT>::Base(const Base& other) : m_itemRef{other.m_itemRef}
{
    incRef();
}

template <typename InterfaceT>
inline Base<InterfaceT>&
Base<InterfaceT>::operator=(const Base<InterfaceT>& other) noexcept
{
    Base base{other.m_itemRef};
    base.get().p->AddRef();
    return base;
}

template <typename InterfaceT>
inline Base<InterfaceT>::~Base() noexcept
{
    if (nullptr != m_itemRef)
    {
        decRef();
    }
}

template <typename InterfaceT>
inline bool Base<InterfaceT>::operator!() const
{
    return nullptr == m_itemRef.p;
}

template <typename InterfaceT>
inline void Base<InterfaceT>::incRef()
{
    m_itemRef.p->AddRef();
}

template <typename InterfaceT>
inline void Base<InterfaceT>::decRef()
{
    // m_itemRef.p->Release();
    // m_itemRef.Release();
}

template <typename InterfaceT>
inline void Base<InterfaceT>::move(Base&& other)
{
    if (this == &other)
    {
        return;
    }
    m_itemRef = std::move(other.m_itemRef);
    other.m_itemRef = nullptr;
}

} // namespace dia