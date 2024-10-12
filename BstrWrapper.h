#pragma once
#include <dia2.h>
#include <string>
#include <atlbase.h>
#include <iostream>
#include <memory>

class BstrWrapper
{
public:
	BstrWrapper() = default;
	BstrWrapper(BSTR&& data) : m_data{ std::move(data) } {}
	~BstrWrapper() noexcept { SysFreeString(m_data); }

	BSTR& get() { return m_data; }
	const BSTR& get() const { return m_data; }

	BSTR* makeFromRaw() {
		if (nullptr != m_data) { throw std::exception("Cannot re-makeFromRaw BstrWrapper!"); }
		return &m_data;
	}

private:
	BSTR m_data{ nullptr };
};

std::wostream& operator<<(std::wostream& os, const BstrWrapper& bstr)
{
	os << bstr.get();
	return os;
}

