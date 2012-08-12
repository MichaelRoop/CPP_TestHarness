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
#include "mr_pointerException.h"

#include <assert.h>
#include <algorithm>

namespace mr_test
{

//---------------------------------------------------------------------------------------
/// @brief Functor to determine if the name is a match for the test case name.
class HasNamedTestFunctor {
public:
	HasNamedTestFunctor(const mr_utils::mr_string& name) : m_name(name) {
	}
	
	bool operator () (const TestCaseHolder& testHolder) {
		return testHolder.m_name == this->m_name;
	}
private:
	const mr_utils::mr_string& m_name;
};


class BuildNamesVectorFunctor {
public:
	BuildNamesVectorFunctor(std::vector<mr_utils::mr_string>& names) 
		: m_names(names) {
	}

	void operator () (const TestCaseHolder& testHolder) {
		this->m_names.push_back(testHolder.m_name);
	}

private:
	// TODO - look up the const in relation to reference. The reference is not changing but the object
	std::vector<mr_utils::mr_string>& m_names;
};


testCase::testCase( const mr_utils::mr_string& name, const mr_utils::mr_string& desc ) 
:	m_name( name ),
	m_desc( desc ),
	m_setupTime( 0 ),
	m_execTime( 0 ),
	m_cleanupTime( 0 ),
	m_status( ST_NONE ),
	m_fixtureSetup(0),
	m_fixtureTeardown(0),
	m_testSetup(0),
	m_testTeardown(0),
	m_isFixtureCalled(false)
{
}

#ifdef blah1_execMethodsRemoved
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
#endif


const mr_utils::mr_string& testCase::name() const {
	return this->m_name;
}


const TestArguments& testCase::args() const {
	return this->m_args;
}


const mr_utils::mr_string& testCase::desc() const {
	return this->m_desc;
}


mr_utils::mr_string testCase::status() const {
	switch (this->m_status)
	{
	case ST_NONE:			return L( "NONE" );
	case ST_SUCCESS:		return L( "SUCCESS" );
	case ST_FAIL_INIT:		return L( "FAIL_INIT" );
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


testCase::TestCaseStatus testCase::statusEnum() const {
	return this->m_status;
}


long long testCase::setupTime() const {
	return this->m_setupTime;
}


long long testCase::execTime() const {
	return this->m_execTime;
}


long long testCase::cleanupTime() const {
	return this->m_cleanupTime;
}

#ifdef blah1_execMethodsRemoved
bool testCase::execStep( long long& timeVal, step_ptr funcPtr )
{
	try {
		mr_utils::StaticTimer timer;
		timer.start();
		bool retVal = (this->*funcPtr)();
		timer.stop();
		timeVal = timer.getMsInterval();
		return retVal;
	}
	catch(mr_utils::mr_exception const & e) {
		// TODO - at present, the values being logged before the exception is called by macros

		//mr_cout << "** Caught mr_exception on Test ** File:" << e.fileName() << _L_(" Line:") << e.fileLine() << _L_(" Msg:") << e.msg()  << _L_(" LongMsg:") << e.longMsg() << std::endl;
		//mr_cout << "** Caught mr_exception on Test ** File:" << e.fileName() << _L_(" Line:") << e.fileLine() << _L_(" Msg:") << e.msg() << std::endl;
	}
	catch(std::exception const & e) {
		//mr_cout << "** Caught std::exception on Test **" << e.what() <<  std::endl;
	}
	catch(std::string const & s) {
		//mr_cout << "** Caught std::string on Test **" << s.c_str() <<  std::endl;
	}
	catch (...) {
		//printf("** Caught Unknown Exception on Test **\n");
	}

	return false;
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
#endif

mr_utils::mr_stringstream& testCase::getMsgBuffer() {
	return this->m_buffer;
}


mr_utils::mr_stringstream& testCase::getVerboseBuffer() {
	return this->m_verboseBuffer;
}


///////////////////////////////////////////////////////////////////
//				Start New Stuff                                  //   
///////////////////////////////////////////////////////////////////


void testCase::RegisterFixtureSetup(testCase_ptr setup) {
	assert(setup);
	this->m_fixtureSetup = setup;
}


void testCase::RegisterFixtureTeardown(testCase_ptr teardown) {
	assert(teardown);
	this->m_fixtureTeardown = teardown;
}


void testCase::RegisterTestSetup(testCase_ptr setup) {
	assert(setup);
	this->m_testSetup = setup;
}


void testCase::RegisterTestTeardown(testCase_ptr teardown) {
	assert(teardown);
	this->m_testTeardown = teardown;
}


void testCase::RegisterTest(testCase_ptr test, const mr_utils::mr_string& name, const mr_utils::mr_string& description) {
	assert(test);
	// TODO - test if already there?

	// When using the macro it uses the # and will insert the full &ClassName::MethodName
	mr_utils::mr_string scratch(name);
	size_t pos = scratch.find(_L_("::"));
	if (pos != mr_utils::mr_string::npos) {
		scratch = name.substr(pos + 2);
	}
	this->m_tests.push_back(TestCaseHolder(test, scratch, description));
}


bool testCase::HasTest(const mr_utils::mr_string& name) {
	//std::vector<TestCaseHolder>::iterator it = 
	//	std::find_if(this->m_tests.begin(), this->m_tests.end(), HasNamedTestFunctor(name));
	//return it != this->m_tests.end();

	return std::find_if(
		this->m_tests.begin(), 
		this->m_tests.end(), 
		HasNamedTestFunctor(name)) != this->m_tests.end();
}


const std::vector<mr_utils::mr_string> testCase::GetTestNames() {
	// TODO - verify that stack var non pointer will pass out as a copy on return
	std::vector<mr_utils::mr_string> names;
	std::for_each(
		this->m_tests.begin(),
		this->m_tests.end(),
		BuildNamesVectorFunctor(names));

	return names;

	//assert(this->m_testNames.size() != 0);
	//return this->m_testNames;
}


void testCase::RunTest(const mr_utils::mr_string& name, const TestArguments& args ) {
	this->ResetTest();

	// Get a copy of the optional arguments for this test
	this->m_args = args;
	
	try {
		// lookup the test
		std::vector<TestCaseHolder>::iterator it = 
			std::find_if(this->m_tests.begin(), this->m_tests.end(), HasNamedTestFunctor(name));

		
		// TODO - report this as an error instead
		assert(it != this->m_tests.end());

		// TODO - replace this with having a current ptr to test with all info instead or writting over fixture information
		this->m_name = it->m_name;
		this->m_desc = it->m_description;

		this->ExecTestFixtureSetup();
		this->ExecStep(this->m_setupTime, this->m_testSetup, ST_FAIL_SETUP);
		this->ExecStep(this->m_execTime, it->m_test, ST_FAIL_TEST);	
		this->ExecStep(this->m_cleanupTime, this->m_testTeardown, ST_FAIL_CLEANUP);

		// Test fixture teardown called from outside when no more tests to execute in fixture
	}
	catch (...) {
		// TODO - later we may put the writing to buffer here but for now we will do it in the assert methods
	}

}

void testCase::ExecStep(long long& timeVal, testCase_ptr funcPtr, TestCaseStatus failStatus) {
	// In this case there may not even be a step registered
	timeVal = 0;
	if (funcPtr != 0) {
		mr_utils::StaticTimer timer;
		timer.start();
		// set to failed in case it throws
		this->m_status = failStatus;
		(this->*funcPtr)();
		this->m_status = ST_SUCCESS;

		timer.stop();
		timeVal = timer.getMsInterval();
	}
}


void testCase::ExecTestFixtureSetup() {
	// Fire the fixture setup if not previously fired by another test
	if (!this->m_isFixtureCalled) {
		// The fixture setup is not presently timed
		long long bogusTimeVal = 0;
		this->ExecStep(bogusTimeVal, this->m_fixtureSetup, ST_FAIL_FIXTURE_SETUP);
		this->m_isFixtureCalled = true;
	}
}


void testCase::ResetTest() {
	// Reset the state for the new test
	this->m_status = ST_NONE;
	this->m_name = _L_("");
	this->m_desc = _L_("");
	this->m_args.clear();
	mr_utils::ResetStringStream(this->m_buffer);
	mr_utils::ResetStringStream(this->m_verboseBuffer);
	this->m_setupTime = 0;
	this->m_execTime = 0;
	this->m_cleanupTime = 0;
}


void testCase::ResetFixture() {
	this->ResetTest();
	if (this->m_isFixtureCalled) {

		// Have try Catch - the test results have already been reported.
		try {
			this->m_isFixtureCalled = false;
			if (this->m_fixtureTeardown != 0) {
				(this->*m_fixtureTeardown)();
			}
		}
		catch (...) {
			// TODO - try to log something here
		}
	}
}


///////////////////////////////////////////////////////////////////
//                END NEW STUFF                                  //
///////////////////////////////////////////////////////////////////



}
