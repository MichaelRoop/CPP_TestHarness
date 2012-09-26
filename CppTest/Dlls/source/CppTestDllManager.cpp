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
#include "CppTestMacros.h"
#include "mr_sstream.h"
#include "mr_exception.h"
#include "mr_defines.h"
#include "mr_iostream.h"

#include <algorithm>


#if defined(WIN32)
#	define DLL_HANDLE_NULL NULL
#	define OPEN_DLL(__dll_name__) LoadLibrary((__dll_name__).c_str())
#	define FREE_DLL_HANDLE(__dll_handle__) FreeLibrary((__dll_handle__))
#	define GET_DLL_FUNC_PTR(__dll_handle__,__func_name__) GetProcAddress((__dll_handle__),(__func_name__))
#elif defined(__linux) || defined(_linux_)
#   include <dlfcn.h>
#	define DLL_HANDLE_NULL 0
#	define OPEN_DLL(__dll_name__) dlopen(mr_utils::ToCharPtr((__dll_name__)).c_str(), RTLD_NOW)
#	define FREE_DLL_HANDLE(__dll_handle__) dlclose((__dll_handle__)) 
#	define GET_DLL_FUNC_PTR(__dll_handle__,__func_name__) dlsym((__dll_handle__),(__func_name__))
#else
#   error *** Neither WIN32 or Linux defined ***
#endif



namespace MrTest {

// typedef of an export function pointer
#if defined(__linux) || defined(_linux_)
typedef void (*ptrFunc)();
#else
typedef void (__cdecl *ptrFunc)();
#endif

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
#if defined(_WIN32)
        ( (ptrFunc)( GET_DLL_FUNC_PTR(this->m_handle,s.c_str()) ) )();
#elif defined(__linux) || defined(_linux_)
       dlerror();
       ptrFunc func = (ptrFunc) GET_DLL_FUNC_PTR(this->m_handle,s.c_str());
       char* err = dlerror();
       if (err != NULL) {
           mr_utils::mr_stringstream ss;
           ss << L("Could not find function named:") << s.c_str() << L(" - ") << err;
           mr_utils::mr_exception::assertCondition(false, _FL_, ss.str());
       }

       mr_cout << _L_("Retrieved the Calling:") << s.c_str() << std::endl;
       (*func)();

#endif
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
        mr_cout << L("Attempting open of ") << name.c_str() << std::endl;
        this->m_dllHandle = OPEN_DLL(name);
		this->ValidateDllOpen(this->m_dllHandle, name);
		this->ParseHeaderAndLoad(name.c_str());
	}
    catch (mr_utils::mr_exception& e) {
        //this->m_dllHandle = DLL_HANDLE_NULL;
		mr_utils::mr_stringstream ss;
        // TODO - get linux error here before close
        ss << _L_("Exception on opening dll named:") << name << L(" - ") << e.what();
        this->Unload();
		throw mr_utils::mr_exception(_FL_, ss.str());
    }
    catch (std::exception& e) { // TODO - Get the message from the exception - need conversion to mr_string
        //this->m_dllHandle = DLL_HANDLE_NULL;
		mr_utils::mr_stringstream ss;
        // TODO - get linux error here before close
        ss << _L_("Exception on opening dll named:") << name << L(" - ") << e.what();
        this->Unload();
		throw mr_utils::mr_exception(_FL_, ss.str());
	}
	catch (...) {
        //this->m_dllHandle = DLL_HANDLE_NULL;
		mr_utils::mr_stringstream ss;
        // TODO - get linux error here before close
        ss << _L_("Unkown Exception on opening dll named:") << name;
        this->Unload();
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
    mr_cout << L("ParseHeaderAndLoad") << std::endl;

	std::vector<std::string> funcNames = this->GetMethodNames(dllName);
	std::for_each(
		funcNames.begin(), 
		funcNames.end(), 
		ExecDllFunctionFunctor(this->m_dllHandle));
}


std::vector<std::string> DllManager::GetMethodNames(const mr_utils::mr_string& dllName) {
	// TODO - resolve narrow and wide char here
    mr_cout << L("GetMethodNames") << std::endl;

	std::vector<std::string> funcNames;

	// The windows version loads the tests by export functions created by the macros
#if	defined(WIN32)
	// Open a separate handle to the DLL just to parse out the export function names.  You 
	// need to use the other regular handle in order to invoke the export functions
	HMODULE handle = LoadLibraryEx(dllName.c_str(), NULL, DONT_RESOLVE_DLL_REFERENCES);
	this->ValidateDllOpen(handle, dllName);

	mr_utils::mr_exception::assertCondition(
		(((PIMAGE_DOS_HEADER)handle)->e_magic == IMAGE_DOS_SIGNATURE),  
		_FL_, 
		_L_("Header e_magic not equals IMAGE_DOS_SIGNATURE"));


	PIMAGE_NT_HEADERS header = (PIMAGE_NT_HEADERS) ((BYTE *)handle + ((PIMAGE_DOS_HEADER)handle)->e_lfanew);

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
		if (mr_utils::Contains(name, "_this_is_a_CppTest_loader_")) {
			funcNames.push_back( (char*)((BYTE *)handle + ((DWORD *)names)[i]));
		}
	}
	FreeLibrary(handle);
#else
    mr_cout << L("Pushing __nonWinCutTestCaseRegistrationMethod__ to names ") << std::endl;

    // Temporary measure until parsing of DLL ELF headers is done.
    // We will call a defined exported method in DLL to register the test cases
    // All registration macros in the method will be executed and their test
    // cases will self register with the TestEngine
    funcNames.push_back(MAIN_DLL_REG_FUNC);

    // TODO - for now we will try the __attribute__((constructor)) to emulate the
    // DllMain auto load for linux

#endif

	return funcNames;
}


void DllManager::ValidateDllOpen(DLL_HANDLE handle, const mr_utils::mr_string& name) {
    mr_cout << L("Validating Open of ") << name.c_str() << std::endl;

    if (handle == DLL_HANDLE_NULL) {
        mr_cout << name.c_str() << L(" handle is null") << std::endl;
        mr_utils::mr_stringstream ss;
		ss << _L_("Could not open DLL ") << name;
#if defined(__linux) || defined(_linux_)
        char* err = dlerror();
        if (err != NULL) {
            ss << L(" - ") << err;
        }
#endif

		mr_utils::mr_exception::assertCondition(false, _FL_, ss.str());
	}
    mr_cout << name.c_str() << L(" handle is ok") << std::endl;
}



} // end namespace MrTest::Case
