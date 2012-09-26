///--------------------------------------------------------------------------------------
/// @file	IMrTestLogInitialiser.h
/// @brief	Abstracts the retrieval of the intialisation data for the log object.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(IMR_TEST_LOG_INITIALISER_H)
#define IMR_TEST_LOG_INITIALISER_H


#include "mr_string.h"
#include "MrTestFieldPair.h"
#include <vector>


namespace MrTest {

//----------------------------------------------------------------------------------------
/// @brief	Interface for retrieving configuration information for the logger.
///
//----------------------------------------------------------------------------------------
class ILogInitialiser {
public:

	/// @brief	Load the data from source.
	virtual bool Load() = 0;


	/// @brief	Retrieve the SQL table or file etc. name, to contain log data.
	virtual mr_utils::mr_string GetLogName() = 0;


	/// @brief	Retrieve list of fields to log.
	virtual FieldVector GetFields() = 0;


	/// @brief	Retrieve the SQL CREATE statement template.
	virtual mr_utils::mr_string GetSqlCreateTemplate() = 0;


	/// @brief	Retrieve the SQL DROP statement template.
	virtual mr_utils::mr_string GetSqlDropTemplate() = 0;


	/// @brief	Retrieve the SQL INSERT statement template.
	virtual mr_utils::mr_string GetSqlInsertTemplate() = 0;


	/// @brief	Retrieve the ODBC DSN name.
	virtual mr_utils::mr_string GetOdbcDsnName() = 0;


	/// @brief	Retrieve the ODBC user name.
	virtual mr_utils::mr_string GetOdbcUserName() = 0;


	/// @brief	Retrieve the ODBC Authorisation String, usually password.
	virtual mr_utils::mr_string GetOdbcAUthorisationStr() = 0;


	/// @brief	Retrieve the ODBC .
	virtual int GetOdbcVersion() = 0;


	/// @brief	Retrieve the ODBC connection timeout.
	virtual int GetOdbcConnectTimeout() = 0;


	/// @brief	Retrieve the string delimiter character.
	///
	///	@param	Is it a fatal error if there is no value.
	virtual mr_utils::mr_string GetStringDelimiter(bool emptyErr) = 0;


	/// @brief	Retrieve the field delimiter character.
	virtual mr_utils::mr_string GetFieldDelimiter() = 0;


	/// @brief	Retrieve the overwrite file flag.
	virtual bool GetOverwriteLogFlag() = 0;


	/// @brief	Retrieve the auto generate unique table name flag.
	virtual bool GetUseAutoGenUniqueTableName() = 0;


	/// @brief	Retrieve the identifier for the summary log.
	virtual mr_utils::mr_string GetSummaryLogId() = 0;


	/// @brief	Get the output type to construct the output object
	virtual mr_utils::mr_string GetOutputType() = 0;


	/// @brief	Get the log type to construct the log object
	virtual mr_utils::mr_string GetLogType() = 0;


	/// @brief	Get list of logs
	virtual std::vector<mr_utils::mr_string> GetLogList() = 0;
};


} //end namespace

#endif
