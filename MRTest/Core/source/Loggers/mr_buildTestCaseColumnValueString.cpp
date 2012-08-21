///--------------------------------------------------------------------------------------
/// @file	mr_buildTestCaseColumnValueString.h
/// @brief	Builds strings with for column information for test cases.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_buildTestCaseColumnValueString.h"
#include "CppTestCase.h"
#include "mr_exception.h"
#include "mr_pointerException.h"
#include "mr_defines.h"
#include "mr_testEngine.h"

namespace mr_test
{

buildTestCaseColumnValueString::buildTestCaseColumnValueString( 
	mr_utils::mr_stringstream&	os,
	const mr_utils::mr_string&	delimiter,
	const mr_utils::mr_string&	strQuotes,
	CppTest::Case&				testCase 
	) 
:	buildColumnValueString( os, delimiter, strQuotes ),
	m_testCase(testCase)
{
	//mr_utils::mr_pointerException::ptrAssert(fixture, _FL_);
}


void buildTestCaseColumnValueString::build( const FieldPair& field )
{
	// add upper case conversion later.
	if (field.first.compare(L("ID")) == 0) {
		this->concatenateStr(this->m_testCase.Name);
	}
	else if (field.first.compare(L("Description")) == 0) {
		this->concatenateStr(this->m_testCase.Description);
	}
	else if (field.first.compare(L("Status")) == 0) {
		this->concatenateStr(CppTest::Case::ToString(this->m_testCase.Status));
	}
	else if (field.first.compare(L("Message")) == 0) {
		this->concatenateStr(this->m_testCase.MsgBuffer.str() );
	}
	else if (field.first.compare(L("SetupTime")) == 0) {
		m_os << this->m_testCase.SetupTime;
	}
	else if (field.first.compare(L("ExecTime")) == 0) {
		m_os << this->m_testCase.ExecTime;
	}
	else if (field.first.compare(L("CleanupTime")) == 0) {
		m_os << this->m_testCase.CleanupTime;
	}
	else if (field.first.compare( L("RunId")) == 0) {
		m_os << mr_test::engine::getInstance().getRunId();
	}
	else if (field.first.compare(L("VerboseMessage")) == 0) {
		this->concatenateVerboseBufferStr( this->m_testCase.VerboseBuffer.str() );
	}
	else {
		//very bad
		mr_utils::mr_stringstream os;
		os	<< field.first 
			<< L(": Illegal field name.  Allowed are ID, Description, Status, SetupTime, ExecTime, CleanupTime, RunId Message, VerboseMessage.");
		mr_utils::mr_exception::assertCondition(false, FL, os.str());
	}
}


void buildTestCaseColumnValueString::concatenateVerboseBufferStr( const mr_utils::mr_string& str )
{
	m_os << m_strQuotes.c_str();
	if (!str.empty())
	{
		m_os << std::endl
			 << L( "-----------------------------------" )	<<std::endl
			 << str.c_str() 
			 <<std::endl 
			 <<std::endl;
	}
	m_os << m_strQuotes.c_str();
}

} // end namespace