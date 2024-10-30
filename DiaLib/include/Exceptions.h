#pragma once
#include <atlbase.h>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>

#define CHECK_DIACOM_EXCEPTION(message, hResult)                                                                                                     \
    do                                                                                                                                               \
    {                                                                                                                                                \
        if (FAILED(hResult))                                                                                                                         \
        {                                                                                                                                            \
            throw DiaComException(message, hResult);                                                                                                 \
        }                                                                                                                                            \
        else if (S_FALSE == hResult)                                                                                                                 \
        {                                                                                                                                            \
            /* throw dia::InvalidUsageException("Queried property that is not available for the symbol!"); */                                        \
        }                                                                                                                                            \
    } while (0)

class DiaSymbolMasterException : public std::exception
{
public:
    using std::exception::exception;
};

class DiaComException : public DiaSymbolMasterException
{
public:
    DiaComException(const char* message, HRESULT result)
        : DiaSymbolMasterException{message}
        , m_result{result} {};

    HRESULT getResult() const { return m_result; }

private:
    HRESULT m_result{S_OK};
};

class WinApiException : public std::exception
{
public:
    WinApiException(const std::string& fuck, int errorCode = GetLastError())
        : WinApiException{fuck.c_str(), errorCode}
    {
    }

    WinApiException(const char* fuck, int errorCode = GetLastError())
        : std::exception(fuck)
        , m_errorCode(errorCode)
    {
    }

    virtual const char* what() const
    {
        if (0 == m_fullErrorDescription.size())
        {
            const std::string baseDescrption  = std::exception::what();
            const auto winapiErrorDescription = formatMessage(m_errorCode);
            m_fullErrorDescription            = {"[" + std::to_string(m_errorCode) + "] " + baseDescrption + " : " + winapiErrorDescription};
        }
        return m_fullErrorDescription.c_str();
    }

private:
    static std::string formatMessage(int errorCode)
    {
        LPSTR messageBuffer = nullptr;

        // Ask Win32 to give us the string version of the errorCode.
        // The parameters we pass in, tell Win32 to create the buffer that
        // holds the message for us (because we don't yet know how long the
        // message string will be).
        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,  // dwFlags
                                     NULL,                                                                                         // lpSource
                                     errorCode,                                                                                    // dwMessageId
                                     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),                                                    // dwLanguageId
                                     reinterpret_cast<LPSTR>(&messageBuffer),                                                      // lpBuffer
                                     0,                                                                                            // nSize
                                     NULL                                                                                          // Arguments
        );
        if (0 == size)
        {
            throw WinApiException("Failed to format error message!");
        }
        if (nullptr == messageBuffer)
        {
            throw std::bad_alloc();
        }

        // Copy the error message into a std::string.
        std::string message(messageBuffer, size);

        // Free the Win32's string's buffer.
        LocalFree(messageBuffer);

        return message;
    }

    const int m_errorCode = 0;
    mutable std::string m_fullErrorDescription{};
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

namespace dia
{
#define DEFINE_TRIVIAL_EXCEPTION(exceptionName)                                                                                                      \
    class exceptionName : public DiaSymbolMasterException                                                                                            \
    {                                                                                                                                                \
    public:                                                                                                                                          \
        using ::DiaSymbolMasterException::DiaSymbolMasterException;                                                                                  \
    };


DEFINE_TRIVIAL_EXCEPTION(SymbolNotFoundException);
DEFINE_TRIVIAL_EXCEPTION(TooManyMatchesForFindException);
DEFINE_TRIVIAL_EXCEPTION(DataMemberDataKindMismatchException);
DEFINE_TRIVIAL_EXCEPTION(InvalidFileFormatException);

class InvalidUsageException : public std::logic_error
{
public:
    using std::logic_error::logic_error;
};


}  // namespace dia
