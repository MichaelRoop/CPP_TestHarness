///--------------------------------------------------------------------------------------
/// @file	mr_testLog.h
/// @brief	Log classes for test tool.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_LOG_H)
#define MR_TEST_LOG_H


#include "mr_iTestLog.h"

namespace CppTest {
	class Case;
}

namespace mr_test
{


//----------------------------------------------------------------------------------------
/// @brief	Pure virtual base class for retrieving and formatting logging information.
/// 
/// The logger derived objects write a header, one line per test and then a footer to
/// its logOutput object.
///
//----------------------------------------------------------------------------------------
class testLog : public iTestLog
{
public:

	/// @brief	Constructor.
	testLog();


	/// @brief	Constructor.
	///
	/// @param	output		A SharedObject reference to a logOutput object for output.
	/// @param	summaryLog	A SharedObject reference to a log object for summary output.
	testLog( 
		mr_utils::SharedPtr<iLogOutput>&		output,
		mr_utils::SharedPtr<iTestLog>&			summaryLog
	);


	/// @brief	Destructor.
	virtual ~testLog();


	/// @brief	Log the testCase information.
	///
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	/// @exception	throws a mr_utils::mr_exception if test has a state that is not handled.
	/// @exception	throws a mr_utils::mr_exception if the output object is invalid.
	///
	/// @param	fixture	Pointer to the test case fixture object that contains information to log.
	///
	/// @return	true if successful, otherwise false.
	bool log(CppTest::Case& testCase);


	/// @brief	Write the summary of the logging.
	///
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	///
	/// @return	true if successful, otherwise false.
	virtual bool summarize();


	/// @brief	Get the successful test count.
	virtual int getSuccessCount() const;


	/// @brief	Get the failed init test count.
	virtual int getFailInitCount() const;


	/// @brief	Get the failed setup test count.
	virtual int getFailSetupCount() const;


	/// @brief	Get the exec cleanup test count.
	virtual int getFailTestCount() const;


	/// @brief	Get the failed cleanup test count.
	virtual int getFailCleanupCount() const;


	/// @brief	Get the Not exist test count.
	virtual int getNotExistCount() const;	


	/// @brief	Get the total test count.
	virtual int getTotalCount() const;	


protected:
	mr_utils::SharedPtr<iLogOutput>	m_output;		///< logOutput pointer.
	mr_utils::SharedPtr<iTestLog>	m_summaryLog;	///< summary logger pointer.
	int			m_stSuccessCount;		///< Counter for successful tests.
	int			m_stFailInitCount;		///< Counter tests that failed on Init.
	int			m_stFailSetupCount;		///< Counter tests that failed on setup.
	int			m_stFailTestCount;		///< Counter tests that failed on test.
	int			m_stFailCleanupCount;	///< Counter tests that failed on cleanup.
	int			m_stNotExistCount;		///< Counter tests not found.
	bool		m_overwrite;			///< Overwrite previous log flag.


	/// @brief	Write the line entry for the log output.
	///
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	///
	/// @param	fixture	Pointer to the test case fixture object that contains information to log.
	///
	/// @return	true if successful, otherwise false.
	virtual bool writeEntry(CppTest::Case& testCase) = 0;


	/// @brief	Determine if the existing log is to be overwritten or appended. 
	///
	///			By default this method will return true to the indicate overwrite. A
	///			child class can over
	///
	/// @return true if it is to be overwrite, otherwise false to be appended.
	virtual bool overwriteExistingLog() const;

};


}

#endif