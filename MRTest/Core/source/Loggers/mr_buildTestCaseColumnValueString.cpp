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
#include "mr_case.h"
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
	testCase*					theCase 
	) 
:	buildColumnValueString( os, delimiter, strQuotes ),
	m_testCase( theCase )
{
	mr_utils::mr_pointerException::ptrAssert( theCase, FL );
}


void buildTestCaseColumnValueString::build( const FieldPair& field )
{
	// add upper case conversion later.
	if (field.first.compare( L("ID") ) == 0)
	{
		this->concatenateStr( m_testCase->name() );
	}
	else if (field.first.compare( L("Description") ) == 0)
	{
		this->concatenateStr( m_testCase->desc() );
	}
	else if (field.first.compare( L("Status") ) == 0)
	{
		this->concatenateStr( m_testCase->status() );
	}
	else if (field.first.compare( L("Message") ) == 0)
	{
		this->concatenateStr( m_testCase->getMsgBuffer().str() );
	}
	else if (field.first.compare( L("SetupTime") ) == 0)
	{
		m_os << m_testCase->setupTime();
	}
	else if (field.first.compare( L("ExecTime") ) == 0)
	{
		m_os << m_testCase->execTime();
	}
	else if (field.first.compare( L("CleanupTime") ) == 0)
	{
		m_os << m_testCase->cleanupTime();
	}
	else if (field.first.compare( L("RunId") ) == 0)
	{
		m_os << mr_test::engine::getInstance().getRunId();
	}
	else if (field.first.compare( L("VerboseMessage") ) == 0)
	{
		this->concatenateVerboseBufferStr( m_testCase->getVerboseBuffer().str() );
	}
	else 
	{
		//very bad
		mr_utils::mr_stringstream os;
		os	<< field.first 
			<< L(": Illegal field name.  Allowed are ID, Description, Status, SetupTime, ExecTime, CleanupTime, RunId Message, VerboseMessage.");
		mr_utils::mr_exception::assertCondition( false, FL, os.str() );
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