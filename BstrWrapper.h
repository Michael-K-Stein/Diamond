#pragma once
#include <atlbase.h>
#include <dia2.h>
#include <iostream>
#include <memory>
#include <string>

class BstrWrapper
{
public:
    BstrWrapper() = default;
    BstrWrapper(BSTR&& data) : m_data{std::move(data)} {}
    ~BstrWrapper() noexcept { SysFreeString(m_data); }

    BSTR& get() { return m_data; }
    const BSTR& get() const { return m_data; }

    BSTR* makeFromRaw()
    {
        if (nullptr != m_data)
        {
            throw std::exception("Cannot re-makeFromRaw BstrWrapper!");
        }
        return &m_data;
    }

    operator std::wstring() const
    {
        std::wstring v(m_data, SysStringLen(m_data));
        return v;
    }

private:
    BSTR m_data{nullptr};
};

static inline std::wostream& operator<<(std::wostream& os,
                                        const BstrWrapper& bstr)
{
    os << bstr.get();
    return os;
}
