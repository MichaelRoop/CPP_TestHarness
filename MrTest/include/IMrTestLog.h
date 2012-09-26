///--------------------------------------------------------------------------------------
/// @file	IMrTestLog.h
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

#include "MrTestDefines.h"
#include "IMrTestLogOutput.h"
#include "mr_sharedPtr.h"

namespace MrTest {

	class ICase;

//----------------------------------------------------------------------------------------
/// @brief	Interface for retrieving and formatting logging information.
/// 
/// The logger derived objects write a header, one line per test and then a footer to
/// its iLogOutput object.
///
//----------------------------------------------------------------------------------------
class MRTESCASE_API ILog {
public:

	/// @brief	Write the header for the log output.
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	/// @return	true if successful, otherwise false.
	virtual bool WriteHeader() = 0;


	/// @brief	Write the footer for the log output.
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	/// @return	true if successful, otherwise false.
	virtual bool WriteFooter() = 0;


	/// @brief	Log the testCase information.
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	/// @exception	throws a mr_utils::mr_exception if test has a state that is not handled.
	/// @param	fixture	Pointer to the test case fixture object that contains information to log.
	/// @return	true if successful, otherwise false.
	virtual bool LogTest(MrTest::ICase& testCase) = 0;


	/// @brief	Write the summary of the logging to the summary log output.
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	/// @return	true if successful, otherwise false.
	virtual bool Summarize() = 0;


	/// @brief	Get the successful test count.
	virtual int GetSuccessCount() const = 0;


	/// @brief	Get the failed test init count.
	virtual int GetFailInitCount() const = 0;


	/// @brief	Get the failed test setup count.
	virtual int GetFailSetupCount() const = 0;


	/// @brief	Get the failed exec test count.
	virtual int GetFailTestCount() const = 0;


	/// @brief	Get the failed cleanup test count.
	virtual int GetFailCleanupCount() const = 0;


	/// @brief	Get the failed test not exist count.
	virtual int GetNotExistCount() const = 0;


	/// @brief	Get the total test count.
	virtual int GetTotalCount() const = 0;


	/// @brief	Write a summary entry.
	virtual bool WriteSummaryEntry(ILog* log) = 0;

};

} // end namespace

MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::allocator< mr_utils::SharedPtr<MrTest::ILog> >;
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::vector< mr_utils::SharedPtr<MrTest::ILog> >;

#endif
