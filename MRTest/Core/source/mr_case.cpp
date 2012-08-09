///--------------------------------------------------------------------------------------
/// @file	mr_case.cpp
/// @brief	Test case base class.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_case.h"
#include "mr_staticTimer.h"
#include "mr_iostream.h"
#include "mr_exception.h"
#include "mr_defines.h"

#include <assert.h>

namespace mr_test
{


testCase::testCase( const mr_utils::mr_string& name, const mr_utils::mr_string& desc ) 
:	m_name( name ),
	m_desc( desc ),
	m_setupTime( 0 ),
	m_execTime( 0 ),
	m_cleanupTime( 0 ),
	m_status( ST_NONE ),
	m_fixtureSetup(0),
	m_fixtureTeardown(0)
{
}


bool testCase::init( const TestArguments& args )
{
	m_args = args;
	return true;
}


bool testCase::setup()
{
	return true;
}


bool testCase::cleanup()
{
	return true;
}



const mr_utils::mr_string& testCase::name() const
{
	return m_name;
}


const TestArguments& testCase::args() const
{
	return this->m_args;
}


const mr_utils::mr_string& testCase::desc() const
{
	return m_desc;
}


mr_utils::mr_string testCase::status() const
{
	switch (m_status)
	{
	case ST_NONE:			return L( "NONE" );
	case ST_SUCCESS:		return L( "SUCCESS" );
	case ST_FAIL_INIT:		return L( "FAIL_INIT" );
	case ST_FAIL_SETUP:		return L( "FAIL_SETUP" );
	case ST_FAIL_TEST:		return L( "FAIL_TEST" );
	case ST_FAIL_CLEANUP:	return L( "FAIL_CLEANUP" );
	case ST_NOT_EXISTS:		return L( "NOT_EXISTS" );
	default:				
		mr_utils::mr_exception::assertCondition( 0, FL, L( "ERROR-NO-STATUS" ) );
		return L( "ERROR-NO-STATUS" );
	}
}


testCase::TestCaseStatus testCase::statusEnum() const
{
	return m_status;
}


long long testCase::setupTime() const
{
	return m_setupTime;
}


long long testCase::execTime() const
{
	return m_execTime;
}


long long testCase::cleanupTime() const
{
	return m_cleanupTime;
}


bool testCase::execStep( long long& timeVal, step_ptr funcPtr )
{
	mr_utils::StaticTimer timer;
	timer.start();
	bool retVal = (this->*funcPtr)();
	timer.stop();
	timeVal = timer.getMsInterval();
	return retVal;
}


bool testCase::setStatus( bool isOk, TestCaseStatus failStatus )
{
	m_status = (isOk == true) ? ST_SUCCESS : failStatus;
	return isOk;
}


bool testCase::executeInit(  const TestArguments& args )
{
	return this->setStatus( this->init( args ), ST_FAIL_INIT );
}


bool testCase::executeSetup()
{
	if (m_status == ST_SUCCESS)
	{
		// TODO temp to see if there is a fixture setup registered
		if (this->m_fixtureSetup != 0) {
			(this->*m_fixtureSetup)();

			return true; // need a catch
		}
		else {
			return this->setStatus( execStep( m_setupTime, &testCase::setup ), ST_FAIL_SETUP );
		}
	}
	return false;
}


bool testCase::executeTest()
{
	if (m_status == ST_SUCCESS)
	{
		return this->setStatus( execStep( m_execTime, &testCase::test ), ST_FAIL_TEST );
	}
	return false;
}


bool testCase::executeCleanup()
{
	bool success = false;

	// TODO temp to test the registered fixture teardown
	if (this->m_fixtureTeardown != 0) {
			(this->*m_fixtureTeardown)();

			success = true; // need a catch
		}
		else {
			success = execStep( m_cleanupTime, &testCase::cleanup );
		}


	// Cleanup always executed.
	//bool success = execStep( m_cleanupTime, &testCase::cleanup );

	// Failure on cleanup will only be logged if all else was successful.
	if (m_status == ST_SUCCESS)
	{
		return this->setStatus( success, ST_FAIL_CLEANUP );
	}
	return success;
}


mr_utils::mr_stringstream& testCase::getMsgBuffer()
{
	return m_buffer;
}


mr_utils::mr_stringstream& testCase::getVerboseBuffer()
{
	return m_verboseBuffer;
}


void testCase::RegisterFixtureSetup(testCase_ptr setup) {
	assert(setup);
	this->m_fixtureSetup = setup;
}

void testCase::RegisterFixtureTeardown(testCase_ptr teardown) {
	assert(teardown);
	this->m_fixtureTeardown = teardown;
}


}
