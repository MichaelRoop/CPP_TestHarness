///--------------------------------------------------------------------------------------
/// @file	mr_simpleLog.h
/// @brief	Simple Log for test tool.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_SIMPLE_LOG_H)
#define MR_SIMPLE_LOG_H


#include "mr_testLog.h"
#include "mr_fieldPair.h"
#include "mr_iLogInitialiser.h"

namespace CppTest {
	class Case;
}

namespace mr_test
{


/// @brief	Structure to hold the loaded field.
/// @todo	Need to move this.
struct StreamFormatData
{
	mr_utils::mr_string m_strQuote;		///< Char that delineates a string.
	mr_utils::mr_string	m_delimiter;	///< Char that delineates a field.
	FieldVector			m_fields;		///< List of the field names and types.
};



//----------------------------------------------------------------------------------------
/// @brief	Simple logging class.
/// 
/// The simpleLogger writes one line per test to its logOutput object.  Each line an entry
/// for 3 columns, ID, Status, and Description.
/// 
/// The footer gives a summary of the total of successful and failed tests as well as a 
/// breakdown of the total failures per state.
/// 
class simpleLog : public testLog
{
public:

	/// @brief	Constructor.
	simpleLog();


	/// @brief	Constructor.
	///
	/// @param	output			A pointer to a logOutput object. It now assumes its ownership. 
	/// @param	summaryOutput	A SharedObject reference to a log object for summary output.
	/// @param	initialiser		A SharedObject reference to an iLogInitialiser.
	simpleLog( 
		mr_utils::SharedPtr<CppTest::ILogOutput>&		output, 
		mr_utils::SharedPtr<iTestLog>&			summaryLog, 
		mr_utils::SharedPtr<iLogInitialiser>&	initialiser 
	);


	/// @brief	Destructor.
	virtual ~simpleLog();


	/// @brief	Write the header for the log output.
	///
	/// @exception	throws a mr_utils::mr_exception if the output object is invalid.
	///
	/// @return	true if successful, otherwise false.
	bool writeHeader();


	/// @brief	Write the footer for the log output.
	///
	/// @exception	throws a mr_utils::mr_exception if the output object is invalid.
	///
	/// @return	true if successful, otherwise false.
	bool writeFooter();


	/// @brief	Write the line entry for the log output.
	///
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	/// @exception	throws a mr_utils::mr_exception if the output object is invalid.
	///
	/// @param	fixture	Pointer to the test case fixture object that contains information to log.
	///
	/// @return	true if successful, otherwise false.
	bool writeEntry(CppTest::Case& testCase);


	/// @brief	Write the summary of the logging.
	///
	/// @param	log	The log that contains the summary information.
	///
	/// @return	true if successful, otherwise false.
	virtual bool writeSummaryEntry( iTestLog* log );

private:

	StreamFormatData	m_formatData;
};



}

#endif