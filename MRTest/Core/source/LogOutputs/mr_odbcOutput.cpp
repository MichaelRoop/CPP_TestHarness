///--------------------------------------------------------------------------------------
/// @file	mr_odbcOutput.cpp
/// @brief	Output class to output logger information to an ODBC driver.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_odbcOutput.h"
#include "mr_exception.h"
#include "mr_defines.h"

#include <assert.h>
#include "mr_iostream.h"



#if defined(MR_USE_THE_ODBC_OUTPUT)

namespace mr_test
{


//odbcOutput::odbcOutput( const mr_utils::mr_string&, const mr_utils::mr_string& )
odbcOutput::odbcOutput( mr_utils::SharedPtr<iLogInitialiser>& initialiser )
:	m_odbcEnv( SQL_NULL_HENV ),
	m_odbcHdbc( SQL_NULL_HDBC ),
	m_odbcVersion( 0 ),
	m_connectTimeout( 0 )
{
	initialiser->load();
	m_dsn = initialiser->getOdbcDsnName();
	m_user = initialiser->getOdbcUserName();
	m_authorisation = initialiser->getOdbcAUthorisationStr();
	m_odbcVersion = initialiser->getOdbcVersion();
	m_connectTimeout = initialiser->getOdbcConnectTimeout();
}


bool odbcOutput::initOutput()
{
	// Create the environment handle.
	SQLRETURN ret = SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_odbcEnv );
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		return false;
	}

	// Set the ODBC version.  We will hardcode it as 3 for now.
	/// @todo	Read ODBC version from the config file.
	ret = SQLSetEnvAttr( 
		m_odbcEnv, 
		SQL_ATTR_ODBC_VERSION, 
		( m_odbcVersion == 3 ? (void*)SQL_OV_ODBC3 : (void*)SQL_OV_ODBC2 ),
		0 
	);

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		return this->freeHandles();
	}

	// Allocate the connection handle.
	ret = SQLAllocHandle( SQL_HANDLE_DBC, m_odbcEnv, &m_odbcHdbc );
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		return this->freeHandles();
	}

	// Set connection timeout attribute.  Hardcode for 7 seconds.
	/// @todo Read connection timeout from config.
	ret = SQLSetConnectAttr( m_odbcHdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)m_connectTimeout, 0);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		return this->freeHandles();
	}

	/// @todo replace the DB name and user ID, & authorisation string? from config?
	ret = SQLConnect( 
		m_odbcHdbc, 
		(SQLTCHAR*)m_dsn.c_str(), 
		m_dsn.length(), 
		(SQLTCHAR*)m_user.c_str(), 
		m_user.length(), 
		(SQLTCHAR*)m_authorisation.c_str(), 
		m_authorisation.length() 
	);

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		return this->freeHandles();
	}
	return true;
}


void odbcOutput::closeOutput()
{
	this->freeHandles();
}


bool odbcOutput::write( const mr_utils::mr_string& str )
{
	mr_utils::mr_exception::assertCondition( m_odbcEnv != SQL_NULL_HENV, FL, L("No DB Connection") );

	SQLHSTMT stmt;
	SQLRETURN ret = SQLAllocHandle( SQL_HANDLE_STMT, m_odbcHdbc, &stmt ); 

	mr_utils::mr_exception::assertCondition( 
		ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO, 
		FL, 
		L("Failed to allocate ODBC statement handle") 
	);


	ret = SQLExecDirect( stmt, const_cast<SQLTCHAR*>( str.c_str() ), SQL_NTS );

	if (ret == SQL_ERROR)
	{
		//assert(ret == SQL_SUCCESS);
		SQLTCHAR     buffer[SQL_MAX_MESSAGE_LENGTH + 1];
		SQLTCHAR     sqlstate[SQL_SQLSTATE_SIZE + 1];
		SQLINTEGER  sqlcode;
		SQLSMALLINT length;
  
		while ( SQLError(m_odbcEnv, m_odbcHdbc, stmt, sqlstate, &sqlcode, buffer,
						 SQL_MAX_MESSAGE_LENGTH + 1, &length) == SQL_SUCCESS )
		{
			mr_cout << std::endl << L("**** ERROR *****") << std::endl;
			mr_cout << L("SQLSTATE:") << sqlstate << std::endl;
			mr_cout << L("Native Error Code:") << sqlcode << std::endl;
			mr_cout << buffer << std::endl;
		};
	}


	/// @todo if SQL_SUCCESS_WITH_INFO or SQL_ERROR we can get the error info before closing handle.
	SQLFreeHandle( SQL_HANDLE_STMT, stmt );

	return ret == SQL_SUCCESS;
}


bool odbcOutput::freeHandles()
{
	// Start with connection then the environment.
	if (m_odbcHdbc != SQL_NULL_HDBC)
	{
		SQLDisconnect( m_odbcHdbc );
		SQLFreeHandle( SQL_HANDLE_DBC, m_odbcHdbc );
		m_odbcHdbc = SQL_NULL_HDBC;
	}

	if (m_odbcEnv != SQL_NULL_HENV)
	{
		SQLFreeHandle( SQL_HANDLE_DBC, m_odbcEnv );
		m_odbcEnv = SQL_NULL_HENV;
	}
	
	return false;
}

} // end namespace

#endif