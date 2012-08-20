///--------------------------------------------------------------------------------------
/// @file	mr_sqlBuilder.cpp
/// @brief	Builds SQL statements for the sqlLog object.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_sqlBuilder.h"
#include "CppTestFixture.h"
#include "mr_iTestLog.h"
#include "mr_exception.h"
#include "mr_defines.h"
#include "mr_columnBuilder.h"
#include "mr_sstream.h"


namespace mr_test
{

void sqlBuilder::buildCreateStmt( SQLData& sqlData, mr_utils::mr_string createTemplate )
{
	BuildNameAndFields( sqlData, createTemplate, sqlData.m_createStmt, true, FL );
}


void sqlBuilder::buildDropStmt( SQLData& sqlData, const mr_utils::mr_string& dropTemplate )
{
	addTableName( sqlData.m_tableName, dropTemplate, sqlData.m_dropStmt, FL );
}


void sqlBuilder::buildInsertStmt( SQLData& sqlData, const mr_utils::mr_string& insertTemplate )
{
	BuildNameAndFields( sqlData, insertTemplate, sqlData.m_insertStmt, false, FL );
}


mr_utils::mr_string sqlBuilder::buildInsertStmtWithValues( const SQLData& sqlData, CppTest::Case& fixture)
{
	mr_utils::mr_char delimiter = L('&');
	verifyPlaceHolder( sqlData.m_insertStmt, delimiter, FL );

	mr_utils::mr_string::size_type pos = 0;
	mr_utils::mr_stringstream os;

	os << GetStmtChunk( sqlData.m_insertStmt, delimiter, pos, FL );

	// Get the values.
	os << columnBuilder::createColumnData( 
				sqlData.m_fields, 
				mr_utils::mr_string( L(",") ), 
				sqlData.m_strQuote, 
				fixture 
			);

	os << GetStmtChunk( sqlData.m_insertStmt, delimiter, pos, FL );
	return os.str();
}


mr_utils::mr_string sqlBuilder::buildInsertStmtWithValues( const SQLData& sqlData, iTestLog* theLog )
{
	mr_utils::mr_char delimiter = L('&');
	verifyPlaceHolder( sqlData.m_insertStmt, delimiter, FL );

	mr_utils::mr_string::size_type pos = 0;
	mr_utils::mr_stringstream os;

	os << GetStmtChunk( sqlData.m_insertStmt, delimiter, pos, FL );

	// Get the values.
	os << columnBuilder::createColumnData( 
				sqlData.m_fields, 
				mr_utils::mr_string( L(",") ), 
				sqlData.m_strQuote, 
				theLog 
			);

	os << GetStmtChunk( sqlData.m_insertStmt, delimiter, pos, FL );
	return os.str();
}


void sqlBuilder::verifyPlaceHolder( 
	const mr_utils::mr_string&	str, 
	mr_utils::mr_char			placeholder,
	const char*					file,
	int							line
)
{
	if (str.find_first_of( &placeholder, 0 ) == mr_utils::mr_string::npos)
	{
		mr_utils::mr_stringstream os;
		os << L("No ") << placeholder << L(" in statement: ") << str.c_str();
		mr_utils::mr_exception::assertCondition( false, file, line, os.str() );
	}
}


mr_utils::mr_string sqlBuilder::GetStmtChunk(
	const mr_utils::mr_string&		str, 
	mr_utils::mr_char				delimiter,
	mr_utils::mr_string::size_type& pos,
	const char*						file,
	int								line
)
{
	mr_utils::mr_string token;
	if (!mr_utils::MrTokenize( pos, str, token, delimiter ))
	{	
		mr_utils::mr_stringstream os;
		os << L( "Malformed statement: " ) << str.c_str();
		mr_utils::mr_exception::assertCondition( false, file, line, os.str() );
	}
	return token;
}


void sqlBuilder::addTableName( 
	const mr_utils::mr_string&	tableName,  
	const mr_utils::mr_string&	stmtTemplate,  
	mr_utils::mr_string&		target,
	const char*					file,
	int							line
)
{
	mr_utils::mr_char delimiter = L('@');
	verifyPlaceHolder( stmtTemplate, delimiter, file, line );

	mr_utils::mr_string::size_type pos = 0;
	mr_utils::mr_stringstream os;

	os << GetStmtChunk( stmtTemplate, delimiter, pos, file, line );
	os << tableName;

	// In case the table name placeholder is the last char in the template.
	if ( pos < stmtTemplate.length() - 1)
	{
		os << GetStmtChunk( stmtTemplate, delimiter, pos, file, line );
	}
	target = os.str();
}


void sqlBuilder::BuildNameAndFields( 
	SQLData&					sqlData,  
	const mr_utils::mr_string&	stmtTemplate,  
	mr_utils::mr_string&		target,
	bool						addTypes,
	const char*					file,
	int							line
)
{
	// Replace the table name placeholder with table name and save to target.
	addTableName( sqlData.m_tableName, stmtTemplate, target, file, line );

	// Get statement up to fields placeholder
	mr_utils::mr_char delimiter = L('#');
	verifyPlaceHolder( target, delimiter, file, line );

	mr_utils::mr_string::size_type pos = 0;
	mr_utils::mr_stringstream os;

	os << GetStmtChunk( target, delimiter, pos, file, line );

	// Get the field names from the order in the sqlData object.
	if (addTypes)
	{
		os << columnBuilder::createColumnNameTypeStr( sqlData.m_fields, L(" "), L(",") );
	}
	else
	{
		os << columnBuilder::createColumnHeaders( sqlData.m_fields, L(",") );
	}

	os << GetStmtChunk( target, delimiter, pos, file, line );

	// replace the partially formed statement
	target = os.str();
}


} // end namespace

