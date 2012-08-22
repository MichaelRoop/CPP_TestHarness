///--------------------------------------------------------------------------------------
/// @file	mr_sqlLog.h
/// @brief	Simple Log for test tool.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_SQL_LOG_H)
#define MR_SQL_LOG_H


#include "mr_testLog.h"
#include "mr_sqlBuilder.h"
#include "mr_iLogInitialiser.h"

namespace CppTest {
	class Case;
}

namespace mr_test
{


//----------------------------------------------------------------------------------------
/// @brief	Log class for formatting SQL statements from data.
/// 
/// Header will create the file with table name, column names and types
/// 
/// 
/// The footer gives a summary of the total of successful and failed tests as well as a 
/// breakdown of the total failures per state.
/// 
class sqlLog : public testLog
{
public:

	/// @brief	Constructor.
	sqlLog();


	/// @brief	Constructor.
	///
	/// @param	output			A pointer to a logOutput object. It now assumes its ownership. 
	/// @param	summaryOutput	A SharedObject reference to a log object for summary output.
	/// @param	initialiser		A SharedObject reference to an iLogInitialiser.
	sqlLog( 
		mr_utils::SharedPtr<CppTest::ILogOutput>&		output, 
		mr_utils::SharedPtr<iTestLog>&			summaryLog, 
		mr_utils::SharedPtr<iLogInitialiser>&	initialiser 
	);


	/// @brief	Constructor.
	///
	/// @param	output			A pointer to a logOutput object. It now assumes its ownership. 
	/// @param	initialiser		A SharedObject reference to an iLogInitialiser.
	sqlLog( 
		mr_utils::SharedPtr<CppTest::ILogOutput>&		output, 
		mr_utils::SharedPtr<iLogInitialiser>&	initialiser 
	);



	/// @brief	Destructor.
	virtual ~sqlLog();


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

	SQLData				m_sqlData;		///< SQL data loaded from config.


	/// @brief	Initialisation method.
	///
	/// @param	initialiser		A SharedObject reference to an iLogInitialiser.
	void init( mr_utils::SharedPtr<iLogInitialiser>& initialiser );


	/// @brief	Returns the SQL DROP TABLE statement.
	///
	/// @return	The drop statement.
	const mr_utils::mr_string& getDropStmt() const;


	/// @brief	Returns the SQL CREATE TABLE statement.
	///
	/// @return	The create statement.
	const mr_utils::mr_string& getCreateStmt() const;


	/// @brief	Returns the SQL INSERT statement.
	///
	/// @return	The insert statement.
	mr_utils::mr_string getInsertStmt(CppTest::Case& testCase) const;


	/// @brief	Returns the SQL INSERT statement.
	///
	/// @return	The insert statement.
	mr_utils::mr_string getInsertStmt(  iTestLog* theLog ) const;

};





}

#endif