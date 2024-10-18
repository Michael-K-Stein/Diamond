#pragma once
#include <atlbase.h>
#include <dia2.h>
#include <iostream>
#include <memory>
#include <string>

class BstrWrapper final
{
public:
    BstrWrapper() = default;

    BstrWrapper(const BstrWrapper& other);
    BstrWrapper operator=(const BstrWrapper& other);
    BstrWrapper(BstrWrapper&& other) noexcept;
    BstrWrapper operator=(BstrWrapper&& other) noexcept;

    BstrWrapper(const BSTR& data);
    BstrWrapper(BSTR&& data);
    ~BstrWrapper() noexcept;

    BSTR& get();
    const BSTR& get() const;

    BSTR* makeFromRaw();

    operator std::wstring() const;

private:
    void move(BstrWrapper&& other) noexcept;

    BSTR m_data{nullptr};
};

std::wostream& operator<<(std::wostream& os, const BstrWrapper& bstr);
