// DiaSymbolMaster.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include "DiaDataSource.h"
#include "Exceptions.h"
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
        // dia.loadDataFromPdb(L"C:\\Windows\\SYMBOLS\\ntkrnlmp.pdb\\EA046425240DE177323859123B166FAC1\\ntkrnlmp.pdb");
        dia.loadDataFromPdb(
            L"C:\\Windows\\SYMBOLS\\ntkrnlmp."
            L"pdb\\BC9E67554B228F3E5C46B0D1622B6E321\\ntkrnlmp.pdb");

        // DiaDataSource dia2{};
        // dia2.loadDataFromPdb(L"C:\\Windows\\SYMBOLS\\ntkrnlmp.pdb\\9074FC2B82ED2B7E1CB3366B64BE62F91\\ntkrnlmp.pdb");
        // dia2.loadDataFromPdb(
        //     L"C:\\Windows\\SYMBOLS\\ntkrnlmp."
        //     L"pdb\\36D4EAA48F7E03C46A5F0FDE2A8F78301\\ntkrnlmp.pdb");
        // // dia.loadDataForExe(L"C:\\Windows\\System32\\ntoskrnl.exe");

        std::wcout << dia.getExportedStruct(L"_KTHREAD") << std::endl;

        return 0;

        // std::map<std::wstring, size_t> foundHashes{};
        // for (const auto& exportedStruct : dia.getExportedStructs())
        //{
        //    if (exportedStruct.getName() == L"<unnamed-tag>")
        //    {
        //        continue;
        //    }
        //    const auto hash = std::hash<Struct>()(exportedStruct);
        //    if (foundHashes.find(exportedStruct.getName()) !=
        //    foundHashes.end())
        //    {
        //        if (foundHashes[exportedStruct.getName()] == hash)
        //        {
        //            continue;
        //        }
        //        std::wcout << L"!!! HASH COLLISION !!! "
        //                   << exportedStruct.getName() << L" " << hash
        //                   << L" != " << foundHashes[exportedStruct.getName()]
        //                   << std::endl;
        //        std::wcout << exportedStruct << std::endl;
        //    }
        //    foundHashes.emplace(exportedStruct.getName(), hash);
        //}

        // for (const auto& exportedStruct : dia2.getExportedStructs())
        //{
        //    if (exportedStruct.getName() == L"<unnamed-tag>")
        //    {
        //        continue;
        //    }
        //    const auto hash = std::hash<Struct>()(exportedStruct);
        //    const auto otherHash = foundHashes[exportedStruct.getName()];
        //    if (hash != otherHash)
        //    {
        //        std::wcout << exportedStruct.getName() << L" changed!"
        //                   << std::endl;
        //    }
        //}
    }
    catch (const DiaComException& e)
    {
        std::cerr << e << std::endl;
    }
    catch (const DiaSymbolMasterException& e)
    {
        std::cerr << e << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unexpected error!" << std::endl;
    }
}
