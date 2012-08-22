///--------------------------------------------------------------------------------------
/// @file	CppTestSqlLog.h
/// @brief	Simple Log for test tool.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_SQL_LOG_H)
#define CPP_TEST_SQL_LOG_H


#include "CppTestLog.h"
#include "CppTestSqlBuilder.h"
#include "ICppTestLogInitialiser.h"

namespace CppTest {

class Case;


//----------------------------------------------------------------------------------------
/// @brief	Log class for formatting SQL statements from data.
/// 
/// Header will create the file with table name, column names and types
/// 
/// 
/// The footer gives a summary of the total of successful and failed tests as well as a 
/// breakdown of the total failures per state.
/// 
class SqlLog : public CppTest::Log {
public:

	/// @brief	Constructor.
	SqlLog();


	/// @brief	Constructor.
	/// @param	output			A pointer to a logOutput object. It now assumes its ownership. 
	/// @param	summaryOutput	A SharedObject reference to a log object for summary output.
	/// @param	initialiser		A SharedObject reference to an iLogInitialiser.
	SqlLog( 
		mr_utils::SharedPtr<CppTest::ILogOutput>&		output, 
		mr_utils::SharedPtr<CppTest::ILog>&				summaryLog, 
		mr_utils::SharedPtr<CppTest::ILogInitialiser>&	initialiser);


	/// @brief	Constructor.
	/// @param	output			A pointer to a logOutput object. It now assumes its ownership. 
	/// @param	initialiser		A SharedObject reference to an iLogInitialiser.
	SqlLog( 
		mr_utils::SharedPtr<CppTest::ILogOutput>&		output, 
		mr_utils::SharedPtr<CppTest::ILogInitialiser>&	initialiser);



	/// @brief	Destructor.
	virtual ~SqlLog();


	/// @brief	Write the header for the log output.
	/// @exception	throws a mr_utils::mr_exception if the output object is invalid.
	/// @return	true if successful, otherwise false.
	bool WriteHeader();


	/// @brief	Write the footer for the log output.
	/// @exception	throws a mr_utils::mr_exception if the output object is invalid.
	/// @return	true if successful, otherwise false.
	bool WriteFooter();


	/// @brief	Write the line entry for the log output.
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	/// @exception	throws a mr_utils::mr_exception if the output object is invalid.
	/// @param	fixture	Pointer to the test case fixture object that contains information to log.
	/// @return	true if successful, otherwise false.
	bool WriteEntry(CppTest::Case& testCase);


	/// @brief	Write the summary of the logging.
	/// @param	log	The log that contains the summary information.
	/// @return	true if successful, otherwise false.
	virtual bool WriteSummaryEntry(CppTest::ILog* log );

private:

	CppTest::SQLData	m_sqlData;		///< SQL data loaded from config.


	/// @brief	Initialisation method.
	/// @param	initialiser		A SharedObject reference to an iLogInitialiser.
	void Init( mr_utils::SharedPtr<CppTest::ILogInitialiser>& initialiser );


	/// @brief	Returns the SQL DROP TABLE statement.
	/// @return	The drop statement.
	const mr_utils::mr_string& GetDropStmt() const;


	/// @brief	Returns the SQL CREATE TABLE statement.
	/// @return	The create statement.
	const mr_utils::mr_string& GetCreateStmt() const;


	/// @brief	Returns the SQL INSERT statement.
	/// @return	The insert statement.
	mr_utils::mr_string GetInsertStmt(CppTest::Case& testCase) const;


	/// @brief	Returns the SQL INSERT statement.
	/// @return	The insert statement.
	mr_utils::mr_string GetInsertStmt(CppTest::ILog* log) const;

};





}

#endif