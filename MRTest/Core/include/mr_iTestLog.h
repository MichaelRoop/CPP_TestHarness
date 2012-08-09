///--------------------------------------------------------------------------------------
/// @file	mr_testLog.h
/// @brief	Log interface for test tool.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_ITEST_LOG_H)
#define MR_ITEST_LOG_H

#include "mr_iLogOutput.h"
#include "mr_sharedPtr.h"


namespace mr_test
{

class testCase;		///< testCase class forward declaration.


//----------------------------------------------------------------------------------------
/// @brief	Interface for retrieving and formatting logging information.
/// 
/// The logger derived objects write a header, one line per test and then a footer to
/// its iLogOutput object.
///
//----------------------------------------------------------------------------------------
class iTestLog
{
public:

	/// @brief	Write the header for the log output.
	///
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	///
	/// @return	true if successful, otherwise false.
	virtual bool writeHeader() = 0;


	/// @brief	Write the footer for the log output.
	///
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	///
	/// @return	true if successful, otherwise false.
	virtual bool writeFooter() = 0;


	/// @brief	Log the testCase information.
	///
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	/// @exception	throws a mr_utils::mr_exception if test has a state that is not handled.
	///
	/// @param	theCase	Pointer to the testCase object that contains information to log.
	///
	/// @return	true if successful, otherwise false.
	virtual bool log(  testCase* theCase ) = 0;


	/// @brief	Write the summary of the logging to the summary log output.
	///
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	///
	/// @return	true if successful, otherwise false.
	virtual bool summarize() = 0;


	/// @brief	Get the successful test count.
	virtual int getSuccessCount() const = 0;


	/// @brief	Get the failed test init count.
	virtual int getFailInitCount() const = 0;


	/// @brief	Get the failed test setup count.
	virtual int getFailSetupCount() const = 0;


	/// @brief	Get the failed exec test count.
	virtual int getFailTestCount() const = 0;


	/// @brief	Get the failed cleanup test count.
	virtual int getFailCleanupCount() const = 0;


	/// @brief	Get the failed test not exist count.
	virtual int getNotExistCount() const = 0;	


	/// @brief	Get the total test count.
	virtual int getTotalCount() const = 0;	


	/// @brief	Write a summary entry.
	virtual bool writeSummaryEntry( iTestLog* theLog ) = 0;

};


}

#endif