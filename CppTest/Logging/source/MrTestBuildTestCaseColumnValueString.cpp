///--------------------------------------------------------------------------------------
/// @file	MrTestuildTestCaseColumnValueString.h
/// @brief	Builds strings with for column information for test cases.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "MrTestBuildTestCaseColumnValueString.h"
#include "MrTestCase.h"
#include "MrTestEngine.h"
#include "mr_exception.h"
#include "mr_pointerException.h"
#include "mr_defines.h"

namespace MrTest {

BuildTestCaseColumnValueString::BuildTestCaseColumnValueString( 
	mr_utils::mr_stringstream&	os,
	const mr_utils::mr_string&	delimiter,
	const mr_utils::mr_string&	strQuotes,
	MrTest::ICase&				testCase) 
:	BuildColumnValueString(os, delimiter, strQuotes),
	m_testCase(testCase) {
}


void BuildTestCaseColumnValueString::Build(const MrTest::FieldPair& field) {
	// add upper case conversion later.
	if (field.first.compare(_L_("ID")) == 0) {
		this->ConcatenateStr(this->m_testCase.Name);
	}
	else if (field.first.compare(_L_("Description")) == 0) {
		this->ConcatenateStr(this->m_testCase.Description);
	}
	else if (field.first.compare(_L_("Status")) == 0) {
		this->ConcatenateStr(MrTest::Case::ToString(this->m_testCase.Status));
	}
	else if (field.first.compare(_L_("Message")) == 0) {
		this->ConcatenateStr(this->m_testCase.MsgBuffer.str() );
	}
	else if (field.first.compare(_L_("SetupTime")) == 0) {
		this->m_os << this->m_testCase.SetupTime;
	}
	else if (field.first.compare(_L_("ExecTime")) == 0) {
		this->m_os << this->m_testCase.ExecTime;
	}
	else if (field.first.compare(_L_("CleanupTime")) == 0) {
		this->m_os << this->m_testCase.CleanupTime;
	}
	else if (field.first.compare(_L_("RunId")) == 0) {
		this->m_os << MrTest::Engine::Instance().GetRunId();
	}
	else if (field.first.compare(_L_("VerboseMessage")) == 0) {
		this->ConcatenateVerboseBufferStr(this->m_testCase.VerboseBuffer.str());
	}
	else {
		//very bad
		mr_utils::mr_stringstream os;
		os	<< field.first 
			<< _L_(": Illegal field name.  Allowed are ID, Description, Status, SetupTime, ExecTime, CleanupTime, RunId Message, VerboseMessage.");
		mr_utils::mr_exception::assertCondition(false, _FL_, os.str());
	}
}


void BuildTestCaseColumnValueString::ConcatenateVerboseBufferStr(const mr_utils::mr_string& str) {
	this->m_os << m_strQuotes.c_str();
	if (!str.empty()) {
		this->m_os << std::endl
			 << L( "-----------------------------------" )	<<std::endl
			 << str.c_str() 
			 << std::endl 
			 << std::endl;
	}
	this->m_os << m_strQuotes.c_str();
}

} // end namespace
