///--------------------------------------------------------------------------------------
/// @file	CppTestOdbcOutput.cpp
/// @brief	Output class to output logger information to an ODBC driver.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestOdbcOutput.h"
#include "mr_exception.h"
#include "mr_defines.h"

#include <assert.h>
#include "mr_iostream.h"



#if defined(MR_USE_THE_ODBC_OUTPUT)

namespace MrTest {


//odbcOutput::odbcOutput( const mr_utils::mr_string&, const mr_utils::mr_string& )
OdbcOutput::OdbcOutput(mr_utils::SharedPtr<MrTest::ILogInitialiser>& initialiser)
:
  #if defined(_WIN32)
  m_odbcEnv(SQL_NULL_HENV),
	m_odbcHdbc(SQL_NULL_HDBC),
	m_odbcVersion(0),
  #endif
	m_connectTimeout(0) {
	initialiser->Load();
	this->m_dsn = initialiser->GetOdbcDsnName();
	this->m_user = initialiser->GetOdbcUserName();
	this->m_authorisation = initialiser->GetOdbcAUthorisationStr();
	this->m_odbcVersion = initialiser->GetOdbcVersion();
	this->m_connectTimeout = initialiser->GetOdbcConnectTimeout();
}


bool OdbcOutput::InitOutput()
{
#if defined(_WIN32)
	// Create the environment handle.
	SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_odbcEnv);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		return false;
	}

	// Set the ODBC version.  We will hardcode it as 3 for now.
	/// @todo	Read ODBC version from the config file.
	ret = SQLSetEnvAttr( 
		this->m_odbcEnv, 
		SQL_ATTR_ODBC_VERSION, 
		(this->m_odbcVersion == 3 ? (void*)SQL_OV_ODBC3 : (void*)SQL_OV_ODBC2), 
		0 
	);

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		return this->FreeHandles();
	}

	// Allocate the connection handle.
	ret = SQLAllocHandle( SQL_HANDLE_DBC, m_odbcEnv, &m_odbcHdbc );
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		return this->FreeHandles();
	}

	// Set connection timeout attribute.  Hardcode for 7 seconds.
	/// @todo Read connection timeout from config.
	ret = SQLSetConnectAttr(this->m_odbcHdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)this->m_connectTimeout, 0);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		return this->FreeHandles();
	}

	/// @todo replace the DB name and user ID, & authorisation string? from config?
	ret = SQLConnect( 
		this->m_odbcHdbc, 
		(SQLTCHAR*)this->m_dsn.c_str(), 
		this->m_dsn.length(), 
		(SQLTCHAR*)this->m_user.c_str(), 
		this->m_user.length(), 
		(SQLTCHAR*)this->m_authorisation.c_str(), 
		this->m_authorisation.length() 
	);

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		return this->FreeHandles();
	}
	return true;
#else
    return false;
#endif
}


void OdbcOutput::CloseOutput() {
	this->FreeHandles();
}


bool OdbcOutput::Write( const mr_utils::mr_string& str ) {
#if defined (_WIN32)
	mr_utils::mr_exception::assertCondition(this->m_odbcEnv != SQL_NULL_HENV, _FL_, _L_("No DB Connection"));

	SQLHSTMT stmt;
	SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_STMT, this->m_odbcHdbc, &stmt); 

	mr_utils::mr_exception::assertCondition( 
		ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO, 
		_FL_, 
		_L_("Failed to allocate ODBC statement handle") 
	);


	ret = SQLExecDirect(stmt, const_cast<SQLTCHAR*>(str.c_str()), SQL_NTS);

	if (ret == SQL_ERROR) {
		//assert(ret == SQL_SUCCESS);
		SQLTCHAR    buffer[SQL_MAX_MESSAGE_LENGTH + 1];
		SQLTCHAR    sqlstate[SQL_SQLSTATE_SIZE + 1];
		SQLINTEGER	sqlcode;
		SQLSMALLINT length;
  
		while (SQLError(this->m_odbcEnv, this->m_odbcHdbc, stmt, sqlstate, &sqlcode, buffer,
						 SQL_MAX_MESSAGE_LENGTH + 1, &length) == SQL_SUCCESS) {
			mr_cout << std::endl << L("**** ERROR *****") << std::endl;
			mr_cout << L("SQLSTATE:") << sqlstate << std::endl;
			mr_cout << L("Native Error Code:") << sqlcode << std::endl;
			mr_cout << buffer << std::endl;
		};
	}

	/// @todo if SQL_SUCCESS_WITH_INFO or SQL_ERROR we can get the error info before closing handle.
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);

	return ret == SQL_SUCCESS;
#else
    return false;
#endif
}


bool OdbcOutput::FreeHandles() {
#if defined(_WIN32)
	// Start with connection then the environment.
	if (this->m_odbcHdbc != SQL_NULL_HDBC) {
		SQLDisconnect(this->m_odbcHdbc);
		SQLFreeHandle(SQL_HANDLE_DBC, this->m_odbcHdbc);
		this->m_odbcHdbc = SQL_NULL_HDBC;
	}

	if (this->m_odbcEnv != SQL_NULL_HENV) {
		SQLFreeHandle(SQL_HANDLE_DBC, this->m_odbcEnv );
		this->m_odbcEnv = SQL_NULL_HENV;
	}
#endif
	
	return false;
}

} // end namespace

#endif
