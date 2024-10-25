#include "pch.h"
//
#include "Exceptions.h"
#include <memory>
#include <processenv.h>
#include <sstream>
#include <string>
#include <vector>

namespace dia
{

static std::wstring getEnvironmentVariableW(const std::wstring& variableName)
{
    // Return value is size in `count of characters`
    const auto requiredBufferSize = GetEnvironmentVariableW(variableName.c_str(), nullptr, 0);
    if (0 == requiredBufferSize)
    {
        throw WinApiException("Failed to get value of environment variable!");
    }

    // Initialize wstring of requiredBufferSize characters, all nullified
    std::wstring environmentVariableValue(requiredBufferSize, L'\x00');

    if (0 == GetEnvironmentVariableW(variableName.c_str(), const_cast<wchar_t*>(environmentVariableValue.data()), requiredBufferSize))
    {
        throw WinApiException("Failed to get value of environment variable!");
    }
    return environmentVariableValue;
}

const std::wstring getBasicSymbolSearchPath(bool withSrv)
{
    constexpr auto SYMBOL_PATH_ENVIRONMENT_VARIABLE_NAME = L"_NT_SYMBOL_PATH";
    // This should really not change throught the life-time of this program
    static std::wstring s_symbolSearchPath{};
    if (0 == s_symbolSearchPath.size())
    {
        // It is completely valid for there to not be a _NT_SYMBOL_PATH
        // explicitly set
        try
        {
            s_symbolSearchPath = getEnvironmentVariableW(SYMBOL_PATH_ENVIRONMENT_VARIABLE_NAME);
        }
        catch (const WinApiException& e)
        {
#ifdef _DEBUG
            std::wcerr << e.what() << std::endl;
#else
            UNREFERENCED_PARAMETER(e);
#endif
            if (withSrv)
            {
                s_symbolSearchPath = L"srv*C:\\Symbols*https://msdl.microsoft.com/download/symbols";
            }
            else
            {
                s_symbolSearchPath = L"C:\\Symbols*https://msdl.microsoft.com/download/symbols";
            }
        }
    }
    return s_symbolSearchPath;
}

// Function to split a string into tokens based on a
// delimiter
static std::vector<std::wstring> splitString(const std::wstring& input, wchar_t delimiter)
{
    // Creating an input wstring stream from the input wstring
    std::wistringstream stream(input);

    // Vector to store the tokens
    std::vector<std::wstring> tokens;

    // Temporary wstring to store each token
    std::wstring token;

    // Read tokens from the string stream separated by the
    // delimiter
    while (std::getline(stream, token, delimiter))
    {
        // Add the token to the vector of tokens
        tokens.push_back(token);
    }

    // Return the vector of tokens
    return tokens;
}

const std::wstring getSymbolSearchPathForExecutable(const std::wstring& executableFilePath, bool withSrv)
{
    std::wstring baseSearchPath{};

    baseSearchPath = getBasicSymbolSearchPath(withSrv);

#if 0
    // Remove filename from the path to get the directory it is in.
    std::wstring executableParentDirectory = executableFilePath;
    // String is altered in-place.
    if (FALSE == PathRemoveFileSpecW(executableParentDirectory.data()))
    {
        // PathRemoveFileSpecW returns FALSE iff nothing was removed from
        // the path. This is invalid since we explicitly state that the path
        // is a path to an executable file, not a directory.
        throw std::runtime_error("Path must refer to a file!");
    }

    std::wstring specificPath = executableParentDirectory;
#else
    UNREFERENCED_PARAMETER(executableFilePath);
#endif

    return baseSearchPath;
}
}  // namespace dia