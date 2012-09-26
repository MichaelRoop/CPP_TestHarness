///--------------------------------------------------------------------------------------
/// @file	MrTestSqlBuilder.h
/// @brief	Builds SQL statements for the sqlLog object.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_SQL_BUILDER_H)
#define MR_TEST_SQL_BUILDER_H


#include "IMrTestCase.h"
#include "MrTestFieldPair.h"

namespace MrTest {

class Case;
struct SQLData; ///< Forward declaration of SQLData structure.
class ILog;		///< Forward declaration of test log.


//----------------------------------------------------------------------------------------
/// @brief	Class for building SQL statements.
/// 
/// 
class SqlBuilder {
public:

	/// @brief	Build the CREATE statement from the table name and template.
	/// @exception	mr_exception if the build fails.
	/// @param	sqlData			Structure that will hold the finished statement. It also 
	///							holds the field information and order.
	/// @param	createTemplate	The create statement template.
	static void BuildCreateStmt(MrTest::SQLData& sqlData, mr_utils::mr_string createTemplate);


	/// @brief	Build the DROP statement from the table name and template.
	///
	/// @exception	mr_exception if the build fails.
	///
	/// @param	sqlData			Structure that will hold the finished statement.
	/// @param	dropTemplate	The drop statement template.
	static void BuildDropStmt(MrTest::SQLData& sqlData, const mr_utils::mr_string& dropTemplate);


	/// @brief	Build the INSERT statement from the table name and template.
	/// @exception	mr_exception if the build fails.
	/// @param	sqlData			Structure that will hold the finished statement. It also 
	///							holds the field information and order.
	/// @param	insertTemplate	The drop statement template.
	static void BuildInsertStmt(MrTest::SQLData& sqlData, const mr_utils::mr_string& insertTemplate);


	/// @brief	Build the INSERT statement from the built template and values.
	/// @exception	mr_exception if the build fails.
	/// @param	sqlData			Structure that will holds the INSERT template and 
	///							field information and order.
	/// @param	fixture			The test case fixture that holds the values.
	/// @return	The INSERT statement with the data values.
	static mr_utils::mr_string BuildInsertStmtWithValues(const MrTest::SQLData& sqlData, MrTest::ICase& fixture);


	/// @brief	Build the INSERT statement from the built template and values.
	/// @exception	mr_exception if the build fails.
	/// @param	sqlData			Structure that will holds the INSERT template and 
	///							field information and order.
	/// @param	theLog			The iTestLog that holds the values.
	/// @return	The INSERT statement with the data values.
	static mr_utils::mr_string BuildInsertStmtWithValues(const MrTest::SQLData& sqlData, MrTest::ILog* theLog);

private:

	/// @brief	Varifies existence of placeholder.
	/// @exception	mr_exception if the build fails.
	/// @param	str			The string in which to verify the existence of the placeholder.
	/// @param	placeholder	The placeholder to verify.
	/// @param	file		The file from which this was called.
	/// @param	line		The file line from which this was called.
	static void VerifyPlaceHolder( 
		const mr_utils::mr_string&	str, 
		mr_utils::mr_char			placeholder,
		const char*					file,
		int							line);


	/// @brief	Gets next chunk of statement fragment before or after placeholder by tokenizing.
	/// @exception	mr_exception if the build fails.
	/// @param	str			The string to tokenize.
	/// @param	delimiter	The placeholder that the tokenizing is based on.
	/// @param	pos			The current position of the tokenizing calls.
	/// @param	file		The file from which this was called.
	/// @param	line		The file line from which this was called.
	/// @return	The next tokenized segment of the string.
	static mr_utils::mr_string GetStmtChunk(
		const mr_utils::mr_string&		str, 
		mr_utils::mr_char				delimiter,
		mr_utils::mr_string::size_type& pos,
		const char*						file,
		int								line);


	/// @brief	Replaces the table name token with the table name.
	/// @exception	mr_exception if the build fails.
	/// @param	tableName		The name of the DB table.
	/// @param	stmtTemplate	The statement template with the '@' table name placeholder.
	/// @param	target			The target string for the new statement with table name.
	/// @param	file			The file from which this was called.
	/// @param	line			The file line from which this was called.
	static void AddTableName( 
		const mr_utils::mr_string&	tableName,  
		const mr_utils::mr_string&	stmtTemplate,  
		mr_utils::mr_string&		target,
		const char*					file,
		int							line);


	/// @brief	Replaces the table name and field tokens with the table name and field info.
	/// @exception	mr_exception if the build fails.
	/// @param	sqlData			SQLData information structure.
	/// @param	stmtTemplate	Statement template with the '@' table name and '#' fields placeholders.
	/// @param	target			Target string for the new statement with table name.
	/// @param	addTypes		Specifies whether to add type information with field names.
	/// @param	file			File from which this was called.
	/// @param	line			The file line from which this was called.
	static void BuildNameAndFields( 
		MrTest::SQLData&			sqlData,  
		const mr_utils::mr_string&	stmtTemplate,  
		mr_utils::mr_string&		target,
		bool						addTypes,
		const char*					file,
		int							line);

};


/// @brief	Structure to hold the loaded SQL statement data.
struct SQLData {
	mr_utils::mr_string m_tableName;	///< Table name for log.
	mr_utils::mr_string m_strQuote;		///< Char that delineates a string.
	mr_utils::mr_string m_dropStmt;		///< Complete DROP statement.
	mr_utils::mr_string m_createStmt;	///< Complete CREATE statement.
	mr_utils::mr_string m_insertStmt;	///< INSERT statemtment waiting for values.
	FieldVector			m_fields;		///< List of the field names and types.
};


} // end namespace

#endif
