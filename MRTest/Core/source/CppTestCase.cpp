///--------------------------------------------------------------------------------------
/// @file	CppTestCase.cpp
/// @brief	Test case base class.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestCase.h"
#include "mr_staticTimer.h"
#include "mr_iostream.h"
#include "mr_exception.h"
#include "mr_defines.h"
#include "mr_pointerException.h"

#include <assert.h>
#include <algorithm>

namespace CppTest {


Case::Case(const mr_utils::mr_string& name, const mr_utils::mr_string& desc) 
:	m_name( name ),
	m_desc( desc ),
	m_setupTime( 0 ),
	m_execTime( 0 ),
	m_cleanupTime( 0 ),
	m_status( ST_NONE ) {
}


Case::Case(const Case& copy) {
	this->m_status = copy.m_status;
	this->m_name = copy.m_name;
	this->m_desc = copy.m_desc;
	//this->m_args.clear();  // TODO - figure out what to do with args
	this->m_buffer << copy.m_buffer.rdbuf();
	this->m_verboseBuffer << copy.m_verboseBuffer.rdbuf();
	this->m_setupTime = copy.m_setupTime;
	this->m_execTime = copy.m_execTime;
	this->m_cleanupTime = copy.m_cleanupTime;
}


const mr_utils::mr_string& Case::name() const {
	return this->m_name;
}


const mr_utils::mr_string& Case::desc() const {
	return this->m_desc;
}


mr_utils::mr_string Case::status() const {
	switch (this->m_status)
	{
	case ST_NONE:			return L( "NONE" );
	case ST_SUCCESS:		return L( "SUCCESS" );
	case ST_FAIL_SETUP:		return L( "FAIL_SETUP" );
	case ST_FAIL_TEST:		return L( "FAIL_TEST" );
	case ST_FAIL_CLEANUP:	return L( "FAIL_CLEANUP" );
	case ST_NOT_EXISTS:		return L( "NOT_EXISTS" );

	case ST_FAIL_FIXTURE_SETUP: return _L_("FAIL_FIXTURE_SETUP");
	case ST_FAIL_FIXTURE_TEARDOWN: return _L_("FAIL_FIXTURE_TEARDOWN");

	default:				
		mr_utils::mr_exception::assertCondition( 0, FL, L( "ERROR-NO-STATUS" ) );
		return L( "ERROR-NO-STATUS" );
	}
}


Case::TestCaseStatus Case::statusEnum() const {
	return this->m_status;
}


long long Case::setupTime() const {
	return this->m_setupTime;
}


long long Case::execTime() const {
	return this->m_execTime;
}


long long Case::cleanupTime() const {
	return this->m_cleanupTime;
}


mr_utils::mr_stringstream& Case::getMsgBuffer() {
	return this->m_buffer;
}


mr_utils::mr_stringstream& Case::getVerboseBuffer() {
	return this->m_verboseBuffer;
}


void Case::Reset() {
	// Reset the state for the new test
	this->m_status = ST_NONE;
	//this->m_name = _L_(""); // name and description never change
	//this->m_desc = _L_("");
	this->m_args.clear();
	mr_utils::ResetStringStream(this->m_buffer);
	mr_utils::ResetStringStream(this->m_verboseBuffer);
	this->m_setupTime = 0;
	this->m_execTime = 0;
	this->m_cleanupTime = 0;
}


} // end namespace
