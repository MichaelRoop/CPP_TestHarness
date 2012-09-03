///--------------------------------------------------------------------------------------
/// @file	CppTestDllManager.h
/// @brief	Encapsulates loading and unloading of test case DLLs
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestDllManager.h"
#include "mr_sstream.h"
#include "mr_exception.h"
#include "mr_defines.h"
#include "mr_iostream.h"

#include <algorithm>


#if defined(WIN32)
#	define DLL_HANDLE_NULL NULL
#	define OPEN_DLL(__dll_name__) LoadLibrary((__dll_name__))
#	define FREE_DLL_HANDLE(__dll_handle__) FreeLibrary((__dll_handle__))
#	define GET_DLL_FUNC_PTR(__dll_handle__,__func_name__) GetProcAddress((__dll_handle__),(__func_name__))
#else
#	define DLL_HANDLE_NULL 0
#	define OPEN_DLL(__dll_name__) dlopen((__dll_name__), RTLD_NOW)
#	define FREE_DLL_HANDLE(__dll_handle__) dlclose((__dll_handle__)) 
#endif



namespace MrTest {

// typedef of an export function pointer
typedef void (__cdecl *ptrFunc)();

// functors ------------------------------------------------------------------

// Functor which call the export function on the DLL that creates an instance 
// of the test fixture which causes it to auto-register itself with the test
// engine.  The export functions were created by the REGISTER_FIXTURE macro
class ExecDllFunctionFunctor {
public:
	ExecDllFunctionFunctor(DLL_HANDLE handle) : m_handle(handle) {
	}

	void operator () (const std::string& s) {
		mr_cout << _L_("Calling:") << s.c_str() << std::endl;
		// Get the pointer, cast it to a function pointer and invoke
		( (ptrFunc)( GET_DLL_FUNC_PTR(this->m_handle,s.c_str()) ) )();
	}

private:
	DLL_HANDLE m_handle;
};

// End of functors -----------------------------------------------------------

DllManager::DllManager() : m_dllHandle(DLL_HANDLE_NULL) {
}


DllManager::~DllManager() {
	this->Unload();
}


void DllManager::Load(const mr_utils::mr_string& name) {
	this->Unload();
	try {
		// Load the DLL to trigger the dllMain. If using header parsing another handle 
		// is opened just to read in the header information for export function names
		this->m_dllHandle = OPEN_DLL(name.c_str());
		this->ParseHeaderAndLoad(name.c_str());
	}
	catch (std::exception&) { // TODO - Get the message from the exception - need conversion to mr_string
		this->m_dllHandle = DLL_HANDLE_NULL;
		mr_utils::mr_stringstream ss;
		ss << _L_("Exception on opening dll named:") << name;
		throw mr_utils::mr_exception(_FL_, ss.str());
	}
}


void DllManager::Unload() {
	try {
		if (this->m_dllHandle != DLL_HANDLE_NULL) {
			FREE_DLL_HANDLE(this->m_dllHandle);
			this->m_dllHandle = DLL_HANDLE_NULL;
		}
	}
	catch (std::exception&)  { // TODO - Get the message from the exception - need conversion to mr_string
		this->m_dllHandle = DLL_HANDLE_NULL;
		throw mr_utils::mr_exception(_FL_, _L_("Exception on closing dll handle"));
	}
}


void DllManager::ParseHeaderAndLoad(const mr_utils::mr_string& dllName) {
	std::vector<std::string> funcNames = this->GetMethodNames(dllName);
	std::for_each(
		funcNames.begin(), 
		funcNames.end(), 
		ExecDllFunctionFunctor(this->m_dllHandle));
}



std::vector<std::string> DllManager::GetMethodNames(const mr_utils::mr_string& dllName) {
	// TODO - resolve narrow and wide char here
	
	std::vector<std::string> funcNames;

	// The windows version loads the tests by export functions created by the macros
#if	defined(WIN32)
	// Open a separate handle to the DLL just to parse out the export function names.  You 
	// need to use the other regular handle in order to invoke the export functions
	HMODULE handle = LoadLibraryEx(dllName.c_str(), NULL, DONT_RESOLVE_DLL_REFERENCES);
	//assert(((PIMAGE_DOS_HEADER)handle)->e_magic == IMAGE_DOS_SIGNATURE);
	mr_utils::mr_exception::assertCondition(
		(((PIMAGE_DOS_HEADER)handle)->e_magic == IMAGE_DOS_SIGNATURE),  
		_FL_, 
		_L_("Header e_magic not equals IMAGE_DOS_SIGNATURE"));


	PIMAGE_NT_HEADERS header = (PIMAGE_NT_HEADERS) ((BYTE *)handle + ((PIMAGE_DOS_HEADER)handle)->e_lfanew);
	//assert(header->Signature == IMAGE_NT_SIGNATURE);
	//assert(header->OptionalHeader.NumberOfRvaAndSizes > 0);

	mr_utils::mr_exception::assertCondition(
		(header->Signature == IMAGE_NT_SIGNATURE),  
		_FL_, 
		_L_("Header signature not equals IMAGE_NT_SIGNATURE"));
	mr_utils::mr_exception::assertCondition(
		(header->OptionalHeader.NumberOfRvaAndSizes > 0),  
		_FL_, 
		_L_("Header Optional Header Number of Rva And Sizes 0"));

	PIMAGE_EXPORT_DIRECTORY exports = (PIMAGE_EXPORT_DIRECTORY) 
		((BYTE*)handle + header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	// All the export functions
	PVOID names = (BYTE *)handle + exports->AddressOfNames;
	
	// Iterate through array of export function names				
	for (unsigned int i = 0; i < exports->NumberOfNames; i++) {

		std::string name( (char*)((BYTE *)handle + ((DWORD *)names)[i]));
		//printf("Export Function Name: %s\n", (BYTE *)lib + ((DWORD *)names)[i]);
		if (mr_utils::Contains(name, "_this_is_a_CppTest_loader_")) {
			funcNames.push_back( (char*)((BYTE *)handle + ((DWORD *)names)[i]));
		}
	}
	FreeLibrary(handle);
#else
#endif

	return funcNames;
}




} // end namespace MrTest::Case