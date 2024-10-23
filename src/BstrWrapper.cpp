#include "BstrWrapper.h"

BstrWrapper::BstrWrapper(const BstrWrapper& other) : BstrWrapper{other.m_data}
{
}

BstrWrapper BstrWrapper::operator=(const BstrWrapper& other)
{
    BstrWrapper v(other);
    return v;
}

BstrWrapper::BstrWrapper(BstrWrapper&& other) noexcept
{
    move(std::move(other));
}

BstrWrapper BstrWrapper::operator=(BstrWrapper&& other) noexcept
{
    BstrWrapper v(std::move(other));
    return v;
}

BstrWrapper::BstrWrapper(const BSTR& data)
{
    auto dataCopy = SysAllocString(data);
    if (nullptr == dataCopy)
    {
        throw std::bad_alloc();
    }
    m_data = std::move(dataCopy);
}

BstrWrapper::BstrWrapper(BSTR&& data) : m_data{std::move(data)} {}

BstrWrapper::~BstrWrapper() noexcept
{
    if (nullptr != m_data)
    {
        SysFreeString(m_data);
    }
}

BSTR& BstrWrapper::get()
{
    if (nullptr == m_data)
    {
        throw std::runtime_error("BstrWrapper used before initialization!");
    }
    return m_data;
}

const BSTR& BstrWrapper::get() const
{
    if (nullptr == m_data)
    {
        throw std::runtime_error("BstrWrapper used before initialization!");
    }
    return m_data;
}

BSTR* BstrWrapper::makeFromRaw()
{
    if (nullptr != m_data)
    {
        throw std::exception("Cannot re-makeFromRaw BstrWrapper!");
    }
    return &m_data;
}

size_t BstrWrapper::length() const
{
    _ASSERT(nullptr != m_data);
    return SysStringLen(m_data);
}
BstrWrapper::operator std::wstring() const
{
    std::wstring v(m_data, SysStringLen(m_data));
    return v;
}

std::wstring BstrWrapper::operator+(const std::wstring& s) const
{
    return s + std::wstring(*this);
}

std::wstring BstrWrapper::operator+(const wchar_t* s) const
{
    return std::wstring{s, wcslen(s)} + std::wstring{*this};
}

void BstrWrapper::move(BstrWrapper&& other) noexcept
{
    m_data = std::move(other.m_data);
    other.m_data = nullptr;
}

std::wostream& operator<<(std::wostream& os, const BstrWrapper& bstr)
{
    os << bstr.get();
    return os;
}
