#pragma once
#include <atlbase.h>
#include <dia2.h>
#include <iostream>
#include <memory>
#include <string>
namespace dia
{

template <typename InterfaceT = IUnknown>
class ComWrapper
{
public:
    ComWrapper() = default;
    ComWrapper(const CComPtr<InterfaceT>& item) : m_itemRef{item} {}
    ComWrapper(CComPtr<InterfaceT>&& item) : m_itemRef{std::move(item)} {}
    ComWrapper(ComWrapper&& other);
    ComWrapper operator=(ComWrapper&& other) noexcept;
    ComWrapper(const ComWrapper& other);
    ComWrapper operator=(const ComWrapper& other) noexcept;

    virtual ~ComWrapper() noexcept;

    /// @brief Create a C++ RAII wrapper from a raw COM pointer.
    /// @return An extremely unsafe mutable reference to the member holding the
    /// COM pointer.
    CComPtr<InterfaceT>& makeFromRaw()
    {
        _ASSERT(nullptr == m_itemRef);
        return m_itemRef;
    }

    /// @brief Check if this instance has been initialized.
    /// @return True if the underlying pointer is NULL, false otherwise.
    bool operator!() const;

protected:
    /// @brief Get raw COM pointer
    /// @return Raw com pointer.
    /// @note Use carfully!
    CComPtr<InterfaceT> get()
    {
        _ASSERT(nullptr != m_itemRef);
        return m_itemRef;
    }

    CComPtr<InterfaceT> get() const
    {
        _ASSERT(nullptr != m_itemRef);
        return m_itemRef;
    }

private:
    void move(ComWrapper&& other);

    mutable CComPtr<InterfaceT> m_itemRef{nullptr};
};

template <typename InterfaceT>
inline ComWrapper<InterfaceT>::ComWrapper(ComWrapper&& other)
{
    move(std::move(other));
}

template <typename InterfaceT>
inline ComWrapper<InterfaceT>
ComWrapper<InterfaceT>::operator=(ComWrapper<InterfaceT>&& other) noexcept
{
    move(std::move(other));
    return *this;
}

template <typename InterfaceT>
inline ComWrapper<InterfaceT>::ComWrapper(const ComWrapper& other)
    : m_itemRef{other.m_itemRef}
{
    _ASSERT(nullptr != m_itemRef);
}

template <typename InterfaceT>
inline ComWrapper<InterfaceT>
ComWrapper<InterfaceT>::operator=(const ComWrapper<InterfaceT>& other) noexcept
{
    ComWrapper base{other.m_itemRef};
    return base;
}

template <typename InterfaceT>
inline ComWrapper<InterfaceT>::~ComWrapper() noexcept
{
}

template <typename InterfaceT>
inline bool ComWrapper<InterfaceT>::operator!() const
{
    return nullptr == m_itemRef.p;
}

template <typename InterfaceT>
inline void ComWrapper<InterfaceT>::move(ComWrapper&& other)
{
    if (this == &other)
    {
        return;
    }
    m_itemRef = std::move(other.m_itemRef);
    other.m_itemRef = nullptr;
}

} // namespace dia
