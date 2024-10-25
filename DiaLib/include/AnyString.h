#pragma once
#include <stdexcept>
#include <string>

template <typename CharT>
class AnyStringT;

static inline const std::wstring convertToWstring(const std::string& str)
{
    std::wstring wstr(str.begin(), str.end());
    return wstr;
}

template <typename CharT = wchar_t>
class AnyStringT final
{
public:
    AnyStringT() = default;
    AnyStringT(const AnyStringT& other);
    AnyStringT& operator=(const AnyStringT& other);
    AnyStringT(AnyStringT&& other);
    AnyStringT& operator=(AnyStringT&& other);

    AnyStringT(const std::string& string);
    AnyStringT(const std::wstring& string);

    template <size_t N>
    AnyStringT(const wchar_t (&string)[N]);

    template <size_t N>
    AnyStringT(const char (&string)[N]);


    operator std::wstring() const;

    const CharT* c_str() const { return m_string.c_str(); }

    CharT* data() { return m_string.data(); }

    bool operator==(const AnyStringT& other);
    bool operator<(const AnyStringT& other);
    bool operator<=(const AnyStringT& other);
    bool operator>(const AnyStringT& other);
    bool operator>=(const AnyStringT& other);

    bool operator==(const std::basic_string<CharT>& other);
    bool operator<(const std::basic_string<CharT>& other);
    bool operator<=(const std::basic_string<CharT>& other);
    bool operator>(const std::basic_string<CharT>& other);
    bool operator>=(const std::basic_string<CharT>& other);

private:
    std::basic_string<CharT> m_string{};
};

template <typename CharT>
inline AnyStringT<CharT>::AnyStringT(const AnyStringT<CharT>& other)
    : m_string{other.m_string}
{
}

template <typename CharT>
inline AnyStringT<CharT>& AnyStringT<CharT>::operator=(const AnyStringT& other)
{
    m_string = other.m_string;
    return *this;
}

template <typename CharT>
inline AnyStringT<CharT>::AnyStringT(AnyStringT&& other)
    : m_string{std::move(other.m_string)}
{
}

template <typename CharT>
inline AnyStringT<CharT>& AnyStringT<CharT>::operator=(AnyStringT&& other)
{
    m_string = std::move(other.m_string);
    return *this;
}

template <>
inline AnyStringT<wchar_t>::AnyStringT(const std::string& string)
    : m_string{convertToWstring(string)}
{
}

template <>
inline AnyStringT<char>::AnyStringT(const std::string& string)
    : m_string{string}
{
}

template <>
inline AnyStringT<wchar_t>::AnyStringT(const std::wstring& string)
    : m_string{string}
{
}

template <>
inline AnyStringT<char>::AnyStringT(const std::wstring& string)
{
    throw std::runtime_error("Cannot demote wide string to normal string!");
}

template <>
inline AnyStringT<wchar_t>::operator std::wstring() const
{
    return m_string;
}

template <>
inline AnyStringT<char>::operator std::wstring() const
{
    return convertToWstring(m_string);
}

template <typename CharT>
inline bool AnyStringT<CharT>::operator==(const AnyStringT& other)
{
    return m_string == other.m_string;
}

template <typename CharT>
inline bool AnyStringT<CharT>::operator<(const AnyStringT& other)
{
    return m_string < other.m_string;
}

template <typename CharT>
inline bool AnyStringT<CharT>::operator<=(const AnyStringT& other)
{
    return m_string <= other.m_string;
}

template <typename CharT>
inline bool AnyStringT<CharT>::operator>(const AnyStringT& other)
{
    return m_string > other.m_string;
}

template <typename CharT>
inline bool AnyStringT<CharT>::operator>=(const AnyStringT& other)
{
    return m_string >= other.m_string;
}

template <typename CharT>
inline bool AnyStringT<CharT>::operator==(const std::basic_string<CharT>& other)
{
    return m_string == other;
}

template <typename CharT>
inline bool AnyStringT<CharT>::operator<(const std::basic_string<CharT>& other)
{
    return m_string < other;
}

template <typename CharT>
inline bool AnyStringT<CharT>::operator<=(const std::basic_string<CharT>& other)
{
    return m_string <= other;
}

template <typename CharT>
inline bool AnyStringT<CharT>::operator>(const std::basic_string<CharT>& other)
{
    return m_string > other;
}

template <typename CharT>
inline bool AnyStringT<CharT>::operator>=(const std::basic_string<CharT>& other)
{
    return m_string >= other;
}

using AnyString = AnyStringT<>;

template <>
template <size_t N>
inline AnyStringT<wchar_t>::AnyStringT(const wchar_t (&string)[N])
    : m_string{string}
{
}

template <>
template <size_t N>
inline AnyStringT<wchar_t>::AnyStringT(const char (&string)[N])
{
    m_string = convertToWstring(std::string(string, N));
}
