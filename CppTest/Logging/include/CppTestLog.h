///--------------------------------------------------------------------------------------
/// @file	ICppTestLog.h
/// @brief	Log classes for test tool.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_LOG_H)
#define CPP_TEST_LOG_H


#include "ICppTestLog.h"


namespace MrTest {

class ICase;


//----------------------------------------------------------------------------------------
/// @brief	Pure virtual base class for retrieving and formatting logging information.
/// 
/// The logger derived objects write a header, one line per test and then a footer to
/// its logOutput object.
///
//----------------------------------------------------------------------------------------
class Log : public ILog {
public:

	/// @brief	Constructor.
	Log();


	/// @brief	Constructor.
	/// @param	output		A SharedObject reference to a logOutput object for output.
	/// @param	summaryLog	A SharedObject reference to a log object for summary output.
	Log( 
		mr_utils::SharedPtr<MrTest::ILogOutput>&	output,
		mr_utils::SharedPtr<MrTest::ILog>&			summaryLog
	);


	/// @brief	Destructor.
	virtual ~Log();


	/// @brief	Log the testCase information.
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	/// @exception	throws a mr_utils::mr_exception if test has a state that is not handled.
	/// @exception	throws a mr_utils::mr_exception if the output object is invalid.
	/// @param	fixture	Pointer to the test case fixture object that contains information to log.
	/// @return	true if successful, otherwise false.
	bool LogTest(MrTest::ICase& testCase);


	/// @brief	Write the summary of the logging.
	///
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	///
	/// @return	true if successful, otherwise false.
	virtual bool Summarize();


	/// @brief	Get the successful test count.
	virtual int GetSuccessCount() const;


	/// @brief	Get the failed init test count.
	virtual int GetFailInitCount() const;


	/// @brief	Get the failed setup test count.
	virtual int GetFailSetupCount() const;


	/// @brief	Get the exec cleanup test count.
	virtual int GetFailTestCount() const;


	/// @brief	Get the failed cleanup test count.
	virtual int GetFailCleanupCount() const;


	/// @brief	Get the Not exist test count.
	virtual int GetNotExistCount() const;	


	/// @brief	Get the total test count.
	virtual int GetTotalCount() const;	


protected:
	mr_utils::SharedPtr<MrTest::ILogOutput>	m_output;	///< logOutput pointer.
	mr_utils::SharedPtr<MrTest::ILog>	m_summaryLog;		///< summary logger pointer.
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
	virtual bool WriteEntry(MrTest::ICase& testCase) = 0;


	/// @brief	Determine if the existing log is to be overwritten or appended. 
	///
	///			By default this method will return true to the indicate overwrite. A
	///			child class can over
	///
	/// @return true if it is to be overwrite, otherwise false to be appended.
	virtual bool OverwriteExistingLog() const;

};


} // end namespace

#endif
