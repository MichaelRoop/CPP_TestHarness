///--------------------------------------------------------------------------------------
/// @file	mr_iLogInitialiser.h
/// @brief	Abstracts the retrieval of the intialisation data for the log object.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_ILOG_INITIALISER_H)
#define MR_ILOG_INITIALISER_H


#include "mr_string.h"
#include "mr_fieldPair.h"
#include <vector>


namespace mr_test
{

//----------------------------------------------------------------------------------------
/// @brief	Interface for retrieving configuration information for the logger.
///
//----------------------------------------------------------------------------------------
class iLogInitialiser
{
public:

	/// @brief	Load the data from source.
	virtual bool load() = 0;


	/// @brief	Retrieve the SQL table or file etc. name, to contain log data.
	virtual mr_utils::mr_string getLogName() = 0;


	/// @brief	Retrieve list of fields to log.
	virtual FieldVector getFields() = 0;


	/// @brief	Retrieve the SQL CREATE statement template.
	virtual mr_utils::mr_string getSqlCreateTemplate() = 0;


	/// @brief	Retrieve the SQL DROP statement template.
	virtual mr_utils::mr_string getSqlDropTemplate() = 0;


	/// @brief	Retrieve the SQL INSERT statement template.
	virtual mr_utils::mr_string getSqlInsertTemplate() = 0;


	/// @brief	Retrieve the ODBC DSN name.
	virtual mr_utils::mr_string getOdbcDsnName() = 0;


	/// @brief	Retrieve the ODBC user name.
	virtual mr_utils::mr_string getOdbcUserName() = 0;


	/// @brief	Retrieve the ODBC Authorisation String, usually password.
	virtual mr_utils::mr_string getOdbcAUthorisationStr() = 0;


	/// @brief	Retrieve the ODBC .
	virtual int getOdbcVersion() = 0;


	/// @brief	Retrieve the ODBC connection timeout.
	virtual int getOdbcConnectTimeout() = 0;


	/// @brief	Retrieve the string delimiter character.
	///
	///	@param	Is it a fatal error if there is no value.
	virtual mr_utils::mr_string getStringDelimiter( bool emptyErr ) = 0;


	/// @brief	Retrieve the field delimiter character.
	virtual mr_utils::mr_string getFieldDelimiter() = 0;


	/// @brief	Retrieve the overwrite file flag.
	virtual bool getOverwriteLogFlag() = 0;


	/// @brief	Retrieve the auto generate unique table name flag.
	virtual bool getUseAutoGenUniqueTableName() = 0;


	/// @brief	Retrieve the identifier for the summary log.
	virtual mr_utils::mr_string getSummaryLogId() = 0;


	/// @brief	Get the output type to construct the output object
	virtual mr_utils::mr_string getOutputType() = 0;


	/// @brief	Get the log type to construct the log object
	virtual mr_utils::mr_string getLogType() = 0;


	/// @brief	Get list of logs
	virtual std::vector<mr_utils::mr_string> getLogList() = 0;
};


} //end namespace

#endif
