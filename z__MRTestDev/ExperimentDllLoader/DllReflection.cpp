#include "DllReflection.h"

#if defined(WIN32)
	#include "windows.h"
#endif

#include <assert.h>


namespace cppTest {

std::vector<std::string> GetMethodNames(const std::wstring& dllName) {
	// TODO - resolve narrow and wide char here
	
	std::vector<std::string> namesVector;

	#if defined(WIN32)
		HMODULE handle = LoadLibraryEx(dllName.c_str(), NULL, DONT_RESOLVE_DLL_REFERENCES);
		assert(((PIMAGE_DOS_HEADER)handle)->e_magic == IMAGE_DOS_SIGNATURE);

		PIMAGE_NT_HEADERS header = (PIMAGE_NT_HEADERS) ((BYTE *)handle + ((PIMAGE_DOS_HEADER)handle)->e_lfanew);
		assert(header->Signature == IMAGE_NT_SIGNATURE);
		assert(header->OptionalHeader.NumberOfRvaAndSizes > 0);

		PIMAGE_EXPORT_DIRECTORY exports = (PIMAGE_EXPORT_DIRECTORY) 
			((BYTE *)handle + header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
		PVOID names = (BYTE *)handle + exports->AddressOfNames;

		
				
		for (int i = 0; i < exports->NumberOfNames; i++) {
			//printf("Export Function Name: %s\n", (BYTE *)lib + ((DWORD *)names)[i]);
			namesVector.push_back( (char*)((BYTE *)handle + ((DWORD *)names)[i]));
		}

		FreeLibrary(handle);
	#endif

		return namesVector;
}

}