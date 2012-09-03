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
#if !defined(CPP_TEST_DLL_MANAGER_H)
#define CPP_TEST_DLL_MANAGER_H

#include "ICppTestDllManager.h"

#if defined(WIN32)
#	define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#	include <windows.h>
	typedef HINSTANCE DLL_HANDLE;
#else
#	pragma message("WIN32 is not defined")
#	error Faild compilation Nix section not yet defined
	typedef void* DLL_HANDLE;
#endif


namespace MrTest {

///--------------------------------------------------------------------------------------
///	@brief	Manages the loading and unloading of test case DLLs
///--------------------------------------------------------------------------------------
class DllManager : public IDllManager {

public:

	/// @brief	Default constructor
	DllManager();


	/// @brief	Destructor
	virtual ~DllManager();


	/// @brief	Load a named DLL
	virtual void Load(const mr_utils::mr_string& name);


	/// @brief	Unload a named DLL
	virtual void Unload();

private:
	DLL_HANDLE m_dllHandle;


	/// @brief	Parse DLL header to load test cases from list of export functions
	void ParseHeaderAndLoad(const mr_utils::mr_string& dllName);

	/// @breif	Parse the DLL header to discover exported fixture load functions
	std::vector<std::string> GetMethodNames(const mr_utils::mr_string& dllName);


};

} // end namespace MrTest::Case

#endif
