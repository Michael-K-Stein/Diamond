#pragma once
#include <stdexcept>
#include <atlbase.h>
#include <cstdio>
#include <iostream>

#define CHECK_DIACOM_EXCEPTION(message, hResult) \
	do { if (FAILED(hResult)) { throw  DiaComException(message, hResult); } } while(0)



class DiaSymbolMasterException : public std::exception { public: using std::exception::exception; };
class DiaComException : public DiaSymbolMasterException {
public:
	DiaComException(const char* message, HRESULT result) :DiaSymbolMasterException{ message }, m_result{ result } {};
	HRESULT getResult() const { return m_result; }
private:
	HRESULT m_result{ S_OK };
};

static inline std::ostream& operator<<(std::ostream& os, const DiaSymbolMasterException& exception)
{
	os << "DiaSymbolMasterException: " << exception.what() << std::endl;
	return os;
}

static inline std::ostream& operator<<(std::ostream& os, const DiaComException& exception)
{
	os << "DiaComException[" << std::hex << exception.getResult() << std::dec << "]: " << exception.what() << std::endl;
	return os;
}
