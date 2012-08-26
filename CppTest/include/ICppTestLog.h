///--------------------------------------------------------------------------------------
/// @file	ICppTestLog.h
/// @brief	Log interface for test tool.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_LOG_H)
#define ICPP_TEST_LOG_H

#include "CppTestCrossPlatform.h"
#include "ICppTestLogOutput.h"
#include "mr_sharedPtr.h"
#include "mr_exception.h"
#include "mr_defines.h"

namespace CppTest {

	class ICase;

//----------------------------------------------------------------------------------------
/// @brief	Interface for retrieving and formatting logging information.
/// 
/// The logger derived objects write a header, one line per test and then a footer to
/// its iLogOutput object.
///
//----------------------------------------------------------------------------------------
class CPPTESCASE_API ILog {
public:

	/// @brief	Write the header for the log output.
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	/// @return	true if successful, otherwise false.
	virtual bool WriteHeader()  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}


	/// @brief	Write the footer for the log output.
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	/// @return	true if successful, otherwise false.
	virtual bool WriteFooter()  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}


	/// @brief	Log the testCase information.
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	/// @exception	throws a mr_utils::mr_exception if test has a state that is not handled.
	/// @param	fixture	Pointer to the test case fixture object that contains information to log.
	/// @return	true if successful, otherwise false.
	virtual bool LogTest(CppTest::ICase& testCase)  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}


	/// @brief	Write the summary of the logging to the summary log output.
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	/// @return	true if successful, otherwise false.
	virtual bool Summarize()  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}


	/// @brief	Get the successful test count.
	virtual int GetSuccessCount() const  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}


	/// @brief	Get the failed test init count.
	virtual int GetFailInitCount() const  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}


	/// @brief	Get the failed test setup count.
	virtual int GetFailSetupCount() const  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}


	/// @brief	Get the failed exec test count.
	virtual int GetFailTestCount() const  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}


	/// @brief	Get the failed cleanup test count.
	virtual int GetFailCleanupCount() const  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}


	/// @brief	Get the failed test not exist count.
	virtual int GetNotExistCount() const  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}


	/// @brief	Get the total test count.
	virtual int GetTotalCount() const  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}


	/// @brief	Write a summary entry.
	virtual bool WriteSummaryEntry(ILog* log)  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}

};


CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator< mr_utils::SharedPtr<CppTest::ILog> >;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector< mr_utils::SharedPtr<CppTest::ILog> >;


}

#endif