///--------------------------------------------------------------------------------------
/// @file	CppTestOdbcOutput.h
/// @brief	Output class to output logger information to an ODBC driver.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_ODBC_OUTPUT_H)
#define CPP_TEST_ODBC_OUTPUT_H


#include "ICppTestLogOutput.h"
#include "ICppTestLogInitialiser.h"
#include "mr_sharedPtr.h"


#define MR_USE_THE_ODBC_OUTPUT
#if defined(MR_USE_THE_ODBC_OUTPUT)

// Note:	If this file is included in the WIN build, the entire build has to be done with the 
//			MR_USE_WIDE_STR defined since ODBC requires the string to be WCHAR. In NIX it is not
//			to be defined since NIX uses the short form of the ODBC calls.

#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
	#include <windows.h>
#endif

//#include <sql.h>
#include <sqlext.h>
#include "ICppTestLogInitialiser.h"


namespace CppTest {

//----------------------------------------------------------------------------------------
/// @brief	Class for outputing logging information to an ODBC connection.
///
/// Always use the cross character width objects and macros to make the data portable
/// for wide and narrow char compilation.  This would be the L() macro and mr_string and 
/// mr_stringstream objects.
///
///	 example:	mr_utils::mr_stringstream os 
///				os << L("This is a message");
///				odbcOutput->write( os.str() );
/// 
///	 example: 
///		mr_string s( L("This is a message") );
///		odbcOutput->write( s );
///
/// This class is used by derived log classes to output the log data after formating.
///
//----------------------------------------------------------------------------------------
class OdbcOutput : public ILogOutput {
public:

	/// @brief	Constructor.
	/// @param	initialiser	A SharedObject reference to an iLogInitialiser.
	OdbcOutput(mr_utils::SharedPtr<CppTest::ILogInitialiser>& initialiser);


	/// @brief	Initialise the object.
	/// @exception	mr_exception if the file name is empty or the file cannot be opened.
	/// @return	true if successful, otherwise false.
	bool InitOutput();


	/// @brief	Close the object.
	/// @return	true if successful, otherwise false.
	void CloseOutput();


	/// @brief	Write to the output object.
	/// @exception mr_utils::mr_exception if file is not open.
	/// @return	true if successful, otherwise false.
	bool Write( const mr_utils::mr_string& str );

private:
	SQLHENV					m_odbcEnv;			///< ODBC Environment handle.
	SQLHDBC					m_odbcHdbc;			///< ODBC DB Connection handle.
	mr_utils::mr_string		m_dsn;				///< ODBC DSN name.
	mr_utils::mr_string		m_user;				///< User name for connection.
	mr_utils::mr_string		m_authorisation;	///< Authorisation string, typicaly password.
	int						m_odbcVersion;		///< ODBC version.
	int						m_connectTimeout;	///< Connect timeout.


	/// @brief	Default constructor hidden to protect against default construction.
	OdbcOutput();

	/// @todo Create an adaptor for reading config file and have it saved here.


	/// @brief	Helper method to free up the ODBC handles.
	///
	/// @return Always returns false.
	bool FreeHandles();

};

}

#endif // the ODBC include define

#endif
