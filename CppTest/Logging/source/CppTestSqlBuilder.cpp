///--------------------------------------------------------------------------------------
/// @file	CppTestSqlBuilder.cpp
/// @brief	Builds SQL statements for the sqlLog object.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestSqlBuilder.h"
#include "CppTestFixture.h"
#include "ICppTestLog.h"
#include "CppTestColumnBuilder.h"
#include "mr_exception.h"
#include "mr_defines.h"
#include "mr_sstream.h"


namespace CppTest {

void SqlBuilder::BuildCreateStmt(CppTest::SQLData& sqlData, mr_utils::mr_string createTemplate ) {
	BuildNameAndFields(sqlData, createTemplate, sqlData.m_createStmt, true, _FL_);
}


void SqlBuilder::BuildDropStmt(CppTest::SQLData& sqlData, const mr_utils::mr_string& dropTemplate) {
	AddTableName(sqlData.m_tableName, dropTemplate, sqlData.m_dropStmt, _FL_);
}


void SqlBuilder::BuildInsertStmt(CppTest::SQLData& sqlData, const mr_utils::mr_string& insertTemplate) {
	BuildNameAndFields(sqlData, insertTemplate, sqlData.m_insertStmt, false, _FL_);
}


mr_utils::mr_string SqlBuilder::BuildInsertStmtWithValues(const CppTest::SQLData& sqlData, CppTest::ICase& fixture) {
	mr_utils::mr_char delimiter = _L_('&');
	VerifyPlaceHolder( sqlData.m_insertStmt, delimiter, _FL_);

	mr_utils::mr_string::size_type pos = 0;
	mr_utils::mr_stringstream os;

	os << GetStmtChunk( sqlData.m_insertStmt, delimiter, pos, _FL_);

	// Get the values.
	os << ColumnBuilder::CreateColumnData( 
				sqlData.m_fields, 
				mr_utils::mr_string(_L_(",")), 
				sqlData.m_strQuote, 
				fixture 
			);

	os << GetStmtChunk(sqlData.m_insertStmt, delimiter, pos, _FL_);
	return os.str();
}


mr_utils::mr_string SqlBuilder::BuildInsertStmtWithValues(const CppTest::SQLData& sqlData, CppTest::ILog* theLog) {
	mr_utils::mr_char delimiter = _L_('&');
	VerifyPlaceHolder( sqlData.m_insertStmt, delimiter, _FL_ );

	mr_utils::mr_string::size_type pos = 0;
	mr_utils::mr_stringstream os;

	os << GetStmtChunk(sqlData.m_insertStmt, delimiter, pos, _FL_);

	// Get the values.
	os << ColumnBuilder::CreateColumnData( 
				sqlData.m_fields, 
				mr_utils::mr_string(_L_(",")), 
				sqlData.m_strQuote, 
				theLog);

	os << GetStmtChunk(sqlData.m_insertStmt, delimiter, pos, _FL_);
	return os.str();
}


void SqlBuilder::VerifyPlaceHolder( 
	const mr_utils::mr_string&	str, 
	mr_utils::mr_char			placeholder,
	const char*					file,
	int							line) {
	// TODO - fix when linker problem solved in VS2010
	size_t end = (size_t) -1;
	if (str.find_first_of( &placeholder, 0 ) == end) {
	//if (str.find_first_of( &placeholder, 0 ) == mr_utils::mr_string::npos) {
		mr_utils::mr_stringstream os;
		os << _L_("No ") << placeholder << _L_(" in statement: ") << str.c_str();
		mr_utils::mr_exception::assertCondition(false, file, line, os.str());
	}
}


mr_utils::mr_string SqlBuilder::GetStmtChunk(
	const mr_utils::mr_string&		str, 
	mr_utils::mr_char				delimiter,
	mr_utils::mr_string::size_type& pos,
	const char*						file,
	int								line
	) {
	mr_utils::mr_string token;
	if (!mr_utils::MrTokenize(pos, str, token, delimiter)) {	
		mr_utils::mr_stringstream os;
		os << _L_("Malformed statement: ") << str.c_str();
		mr_utils::mr_exception::assertCondition(false, file, line, os.str());
	}
	return token;
}


void SqlBuilder::AddTableName( 
	const mr_utils::mr_string&	tableName,  
	const mr_utils::mr_string&	stmtTemplate,  
	mr_utils::mr_string&		target,
	const char*					file,
	int							line
	) {
	mr_utils::mr_char delimiter = _L_('@');
	VerifyPlaceHolder( stmtTemplate, delimiter, file, line );

	mr_utils::mr_string::size_type pos = 0;
	mr_utils::mr_stringstream os;

	os << GetStmtChunk(stmtTemplate, delimiter, pos, file, line);
	os << tableName;

	// In case the table name placeholder is the last char in the template.
	if ( pos < stmtTemplate.length() - 1) {
		os << GetStmtChunk(stmtTemplate, delimiter, pos, file, line);
	}
	target = os.str();
}


void SqlBuilder::BuildNameAndFields( 
	CppTest::SQLData&			sqlData,  
	const mr_utils::mr_string&	stmtTemplate,  
	mr_utils::mr_string&		target,
	bool						addTypes,
	const char*					file,
	int							line
) {
	// Replace the table name placeholder with table name and save to target.
	AddTableName(sqlData.m_tableName, stmtTemplate, target, file, line);

	// Get statement up to fields placeholder
	mr_utils::mr_char delimiter = _L_('#');
	VerifyPlaceHolder(target, delimiter, file, line);

	mr_utils::mr_string::size_type pos = 0;
	mr_utils::mr_stringstream os;

	os << GetStmtChunk(target, delimiter, pos, file, line);

	// Get the field names from the order in the sqlData object.
	if (addTypes) {
		os << ColumnBuilder::CreateColumnNameTypeStr(sqlData.m_fields, _L_(" "), _L_(","));
	}
	else {
		os << ColumnBuilder::CreateColumnHeaders(sqlData.m_fields, _L_(","));
	}

	os << GetStmtChunk( target, delimiter, pos, file, line );

	// replace the partially formed statement
	target = os.str();
}


} // end namespace

