///--------------------------------------------------------------------------------------
/// @file	ICppTestIniLogInitialiser.h
/// @brief	Abstracts the retrieval of the intialisation data for the log object from ini
///			file.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_INI_LOG_INITIALISER_H)
#define CPP_TEST_INI_LOG_INITIALISER_H


#include "ICppTestLogInitialiser.h"
#include "mr_ini_file.h"


namespace CppTest {

//----------------------------------------------------------------------------------------
/// @brief	Interface for retrieving configuration information for the logger from ini file.
///
//----------------------------------------------------------------------------------------
class IniLogInitialiser : public ILogInitialiser {
public:


	/// @brief	Constructor.
	///
	/// @param	fileName	Name of the ini file.
	/// @param	sectionName	The section that has the specific information for the output.
	IniLogInitialiser(const std::string& fileName, const mr_utils::mr_string& sectionName);


	/// @brief	Load the data from source.
	virtual bool Load();


	/// @brief	Retrieve the SQL table or file etc. name, to contain log data.
	virtual mr_utils::mr_string GetLogName();


	/// @brief	Retrieve list of fields to log.
	virtual FieldVector GetFields();


	/// @brief	Retrieve the SQL CREATE statement template.
	virtual mr_utils::mr_string GetSqlCreateTemplate();


	/// @brief	Retrieve the SQL DROP statement template.
	virtual mr_utils::mr_string GetSqlDropTemplate();


	/// @brief	Retrieve the SQL INSERT statement template.
	virtual mr_utils::mr_string GetSqlInsertTemplate();


	/// @brief	Retrieve the string delimiter character.
	///
	/// @param	emptyErr	Is it a fatal error if node empty.
	virtual mr_utils::mr_string GetStringDelimiter(bool emptyErr);


	/// @brief	Retrieve the ODBC DSN name.
	virtual mr_utils::mr_string GetOdbcDsnName();


	/// @brief	Retrieve the ODBC user name.
	virtual mr_utils::mr_string GetOdbcUserName();


	/// @brief	Retrieve the ODBC Authorisation String, usually password.
	virtual mr_utils::mr_string GetOdbcAUthorisationStr();


	/// @brief	Retrieve the ODBC version number.
	virtual int GetOdbcVersion();


	/// @brief	Retrieve the ODBC connection timeout.
	virtual int GetOdbcConnectTimeout();


	/// @brief	Retrieve the field delimiter character.
	virtual mr_utils::mr_string GetFieldDelimiter();


	/// @brief	Retrieve the overwrite file flag.
	virtual bool GetOverwriteLogFlag();


	/// @brief	Retrieve the auto generate unique table name flag.
	virtual bool GetUseAutoGenUniqueTableName();


	/// @brief	Retrieve the identifier for the summary log.
	virtual mr_utils::mr_string GetSummaryLogId();


	/// @brief	Get the output type to construct the output object
	virtual mr_utils::mr_string GetOutputType();


	/// @brief	Get the log type to construct the log object
	virtual mr_utils::mr_string GetLogType();

	/// @brief	Get list of logs
	virtual std::vector<mr_utils::mr_string> GetLogList();

private:
	std::string				m_fileName;
	mr_utils::mr_string		m_sectionName;
	mr_inireader::iniFile	m_iniFile;
	bool					m_loaded;


	/// @brief	Helper method to parse out syntax definitions and report errors.
	///
	/// @param	nodeName	The name of the node in the section defined by the 
	///						OutputSyntax ini entry for the output.
	/// @param	fatalErr	Is it fatal if node is not found or empty.
	///
	/// @return	The node value.
	mr_utils::mr_string GetSyntaxEntry(const mr_utils::mr_string&	nodeName, bool fatalErr = true);


	/// @brief	Helper method to retrieve a value from the section according to node name.
	///
	/// @param	sectionName	The name of the ini section.
	/// @param	nodeName	The name of the node within the section.
	/// @param	emptyErr	Is it a fatal error if node empty. Default is true.
	/// @param	foundErr	Is it a fatal error if node is not found. Default is true.
	///
	/// @return	The node value if successful or an empty string if no value or not found.
	mr_utils::mr_string GetNodeValue( 
		const mr_utils::mr_string&	sectionName, 
		const mr_utils::mr_string&	nodeName, 
		bool						emptyErr = true, 
		bool						foundErr = true 
	);


	/// @brief	Helper method to retrieve section by name.
	///
	/// @param	sectionName	The name of the ini section.
	///
	/// @return	A section Iterator.
	mr_inireader::iniFile::SectionIterator GetSection(const mr_utils::mr_string& sectionName);


	/// @brief	Helper method to format msg for exception and do throw.
	///
	/// @param	sectionName	The name of the ini section requested.
	/// @param	nodeName	The name of the node requested.
	/// @param	msg			Error message.
	void ThrowError( 
		const mr_utils::mr_string&	sectionName, 
		const mr_utils::mr_string&	nodeName, 
		const mr_utils::mr_string&	msg 
	);
};


} //end namespace

#endif
