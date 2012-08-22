///--------------------------------------------------------------------------------------
/// @file	CppTestCase.cpp
/// @brief	Holder for test case execution results data
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.5
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestCase.h"
#include "mr_exception.h"
#include "mr_defines.h"

namespace CppTest {

mr_utils::mr_string Case::ToString(Case::TestCaseStatus status) { 
	switch (status) {
		case Case::ST_NONE:			return L( "NONE" );
		case Case::ST_SUCCESS:		return L( "SUCCESS" );
		case Case::ST_FAIL_SETUP:		return L( "FAIL_SETUP" );
		case Case::ST_FAIL_TEST:		return L( "FAIL_TEST" );
		case Case::ST_FAIL_CLEANUP:	return L( "FAIL_CLEANUP" );
		case Case::ST_NOT_EXISTS:		return L( "NOT_EXISTS" );
		case Case::ST_FAIL_FIXTURE_SETUP: return _L_("FAIL_FIXTURE_SETUP");
		case Case::ST_FAIL_FIXTURE_TEARDOWN: return _L_("FAIL_FIXTURE_TEARDOWN");
	default:				
		mr_utils::mr_exception::assertCondition(false, _FL_, _L_( "ERROR-NO-STATUS" ) );
		return L( "ERROR-NO-STATUS" );
	}
}


Case::Case(const mr_utils::mr_string& name, const mr_utils::mr_string& desc) 
:	Name( name ),
	Description( desc ),
	SetupTime( 0 ),
	ExecTime( 0 ),
	CleanupTime( 0 ),
	Status( ST_NONE ) {
}


Case::Case(const Case& copy) {
	this->Status = copy.Status;
	this->Name = copy.Name;
	this->Description = copy.Description;
	//this->m_args.clear();  // TODO - figure out what to do with args
	this->MsgBuffer << copy.MsgBuffer.rdbuf();
	this->VerboseBuffer << copy.VerboseBuffer.rdbuf();
	this->SetupTime = copy.SetupTime;
	this->ExecTime = copy.ExecTime;
	this->CleanupTime = copy.CleanupTime;
}

void Case::Reset() {
	this->Status = Case::ST_NONE;
	//this->m_args.clear();
	mr_utils::ResetStringStream(this->MsgBuffer);
	mr_utils::ResetStringStream(this->VerboseBuffer);
	this->SetupTime = 0;
	this->ExecTime = 0;
	this->CleanupTime = 0;
}

} // end namespace
