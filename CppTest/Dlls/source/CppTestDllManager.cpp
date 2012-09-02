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


#if defined(WIN32)
#	define DLL_HANDLE_NULL NULL
#	define OPEN_DLL(__dll_name__) LoadLibrary((__dll_name__))
#	define FREE_DLL_HANDLE(__dll_handle__) FreeLibrary((__dll_handle__))
#else
#	define DLL_HANDLE_NULL 0
#	define OPEN_DLL(__dll_name__) dlopen((__dll_name__), RTLD_NOW)
#	define FREE_DLL_HANDLE(__dll_handle__) dlclose((__dll_handle__)) 
#endif



namespace CppTest {


DllManager::DllManager() : m_dllHandle(DLL_HANDLE_NULL) {
}



DllManager::~DllManager() {
	this->Unload();
}


void DllManager::Load(const mr_utils::mr_string& name) {
	this->Unload();
	try {
		this->m_dllHandle = OPEN_DLL(name.c_str());
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


} // end namespace cppTest::Case
