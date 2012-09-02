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
#if !defined(ICPP_TEST_DLL_MANAGER_H)
#define ICPP_TEST_DLL_MANAGER_H

#include "CppTestDefines.h"
#include "mr_string.h"
#include "mr_SharedPtr.h"

namespace CppTest {

///--------------------------------------------------------------------------------------
///	@brief	Manages the loading and unloading of test case DLLs
///--------------------------------------------------------------------------------------
class IDllManager {

public:

	/// @brief	Load a named DLL
	virtual void Load(const mr_utils::mr_string& name) = 0;


	/// @brief	Unload a named DLL
	virtual void Unload() = 0;

};

} // end namespace cppTest::Case

// Force export of std items
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API mr_utils::SharedPtr<CppTest::IDllManager>;

#endif
