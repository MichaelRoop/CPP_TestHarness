// ExperimentDllLoader.cpp : Defines the entry point for the console application.
//

//#define WIN32_LEAN_AND_MEAN
//#define VC_EXTRALEAN
#include "windows.h"
//#include <WinNT.h>

//#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>

//#include "Winbase.h"

//void ListDLLFunctions(std::string sADllName, std::vector<std::string>& slListOfDllFunctions);

// typedef  void (__stdcall *ptrFunc) () ;
//ptrFunc Func ;


#include "DllReflection.h"


typedef void (__cdecl *ptrFunc)();

class ExecDllFunctionFunctor {
public:
	ExecDllFunctionFunctor(HINSTANCE handle) : m_handle(handle) {
	}

	void operator () (const std::string& s) {
		std::cout << "Before getting function pointer '" << s << "'" << std::endl;
		ptrFunc Func = (ptrFunc) ( GetProcAddress(this->m_handle,s.c_str()) );
		std::cout << "After getting function pointer" << std::endl;
		Func() ;
		std::cout << "After calling function pointer" << std::endl;
	}

private:
	HINSTANCE m_handle;
};


//int _tmain(int argc, _TCHAR* argv[])
int main(int argc, char* argv[])
{
	
//	HMODULE lib = LoadLibraryEx(L"C:\\Dev\\ExperimentDll.dll", NULL, DONT_RESOLVE_DLL_REFERENCES);
//	assert(((PIMAGE_DOS_HEADER)lib)->e_magic == IMAGE_DOS_SIGNATURE);
//
//	PIMAGE_NT_HEADERS header = (PIMAGE_NT_HEADERS) ((BYTE *)lib + ((PIMAGE_DOS_HEADER)lib)->e_lfanew);
//	assert(header->Signature == IMAGE_NT_SIGNATURE);
//	assert(header->OptionalHeader.NumberOfRvaAndSizes > 0);
//
//	PIMAGE_EXPORT_DIRECTORY exports = (PIMAGE_EXPORT_DIRECTORY) 
//		((BYTE *)lib + header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
//	PVOID names = (BYTE *)lib + exports->AddressOfNames;
//
//std::vector<std::string> namesV;
//
//std::cout << "DLL Exported Method Names discovery" << std::endl;
//for (int i = 0; i < exports->NumberOfNames; i++) {
//    printf("Export Function Name: %s\n", (BYTE *)lib + ((DWORD *)names)[i]);
//	namesV.push_back( (char*)((BYTE *)lib + ((DWORD *)names)[i]));
//}
//
//FreeLibrary(lib);
//std::cout << std::endl;

	std::vector<std::string> namesV = cppTest::GetMethodNames(std::wstring(L"C:\\Dev\\ExperimentDll.dll"));


std::cout << "DLL Exported Method Execution" << std::endl;
	
	std::cout << "Before load library" << std::endl;
	HINSTANCE handle = LoadLibrary(L"C:\\Dev\\ExperimentDll.dll") ;
	std::cout << "After load library" << std::endl;

	std::for_each(namesV.begin(), namesV.end(), ExecDllFunctionFunctor(handle));

	FreeLibrary(handle);

	////ptrFunc Func = static_cast < ptrFunc > ( GetProcAddress(handle,"Func1") );
	//ptrFunc Func = (ptrFunc) ( GetProcAddress(handle,"Func1") );

	//std::cout << "After getting function pointer" << std::endl;

	//Func() ;

	//std::cout << "After calling function pointer" << std::endl;
	
/*
for (	
for (int i = 0; i < exports->NumberOfNames; i++) {
    //printf("Export: %s\n", (BYTE *)lib + ((DWORD *)names)[i]);
	ptrFunc Func = (ptrFunc) ( GetProcAddress(handle,"Func1") );

	std::cout << "After getting function pointer" << std::endl;

	Func() ;

	std::cout << "After calling function pointer" << std::endl;
	
}
*/

	//std::vector<std::string> names;
 //   ListDLLFunctions("KERNEL32.DLL", names);
	
	return 0;
}



//void ListDLLFunctions(std::string sADllName, std::vector<std::string>& slListOfDllFunctions)
//{
//    DWORD *dNameRVAs(0);
//    _IMAGE_EXPORT_DIRECTORY *ImageExportDirectory;
//    unsigned long cDirSize;
//    _LOADED_IMAGE LoadedImage;
//    string sName;
//    slListOfDllFunctions.clear();
//    if (MapAndLoad(sADllName.c_str(), NULL, &LoadedImage, TRUE, TRUE))
//    {
//        ImageExportDirectory = (_IMAGE_EXPORT_DIRECTORY*)
//            ImageDirectoryEntryToData(LoadedImage.MappedAddress,
//            false, IMAGE_DIRECTORY_ENTRY_EXPORT, &cDirSize);
//        if (ImageExportDirectory != NULL)
//        {
//            dNameRVAs = (DWORD *)ImageRvaToVa(LoadedImage.FileHeader, 
//                LoadedImage.MappedAddress,
//            ImageExportDirectory->AddressOfNames, NULL);
//            for(size_t i = 0; i < ImageExportDirectory->NumberOfNames; i++)
//            {
//                sName = (char *)ImageRvaToVa(LoadedImage.FileHeader, 
//                        LoadedImage.MappedAddress,
//                       dNameRVAs[i], NULL);
//             slListOfDllFunctions.push_back(sName);
//            }
//        }
//        UnMapAndLoad(&LoadedImage);
//    }
//}
