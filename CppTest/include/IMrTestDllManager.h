///--------------------------------------------------------------------------------------
/// @file	MrTestDllManager.h
/// @brief	Encapsulates loading and unloading of test case DLLs
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(IMR_TEST_DLL_MANAGER_H)
#define IMR_TEST_DLL_MANAGER_H

#include "MrTestDefines.h"
#include "mr_string.h"
#include "mr_SharedPtr.h"

namespace MrTest {

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

} // end namespace MrTest::Case

// Force export of std items
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API mr_utils::SharedPtr<MrTest::IDllManager>;

#endif
