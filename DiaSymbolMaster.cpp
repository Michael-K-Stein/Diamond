// DiaSymbolMaster.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include "src/DiaDataSource.h"
#include "src/Exceptions.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

using namespace dia;

// Custom deleter for COM library
struct CoUninitializeDeleter
{
    void operator()(void*) const { CoUninitialize(); }
};

int main()
{
    // Initialize COM and create a unique_ptr to ensure CoUninitialize is called
    HRESULT hr = CoInitialize(nullptr);
    if (FAILED(hr))
    {
        std::cerr << "Failed to initialize COM library. HRESULT: " << hr
                  << std::endl;
        return -1;
    }

    // Use unique_ptr with a custom deleter to ensure CoUninitialize is called
    // at the end
    std::unique_ptr<void, CoUninitializeDeleter> comGuard(
        (void*)1); // Use a dummy pointer as unique_ptr cannot be null

    // Program logic here
    std::cout << "COM library initialized successfully." << std::endl;

    try
    {

        DiaDataSource dia{};
        dia.loadDataFromPdb(
            L"C:\\Windows\\SYMBOLS\\ntkrnlmp."
            L"pdb\\BC9E67554B228F3E5C46B0D1622B6E321\\ntkrnlmp.pdb");

        const auto& sym = dia.getExportedStruct(L"_ETHREAD");
        std::wcout << sym << std::endl;

        std::wcout << L"Depends on: " << std::endl;
        for (const auto& type : sym.queryDependsOnTypes())
        {
            std::wcout << type.getName() << std::endl;
        }

        std::wcout << L"Depends on (as pointers): " << std::endl;
        for (const auto& type : sym.queryDependsOnForwardTypes())
        {
            std::wcout << type.getName() << std::endl;
        }

        return 0;
    }
    catch (const DiaComException& e)
    {
        std::cerr << e << std::endl;
    }
    catch (const DiaSymbolMasterException& e)
    {
        std::cerr << e << std::endl;
    }
#ifndef _DEBUG
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unexpected error!" << std::endl;
    }
#endif
}
