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
#include "CppTestFixture.h"
#include "mr_staticTimer.h"
#include "mr_iostream.h"
#include "mr_exception.h"
#include "mr_defines.h"
#include "mr_pointerException.h"

#include <assert.h>
#include <algorithm>

namespace CppTest {

//---------------------------------------------------------------------------------------
/// @brief Functor to determine if the name is a match for the test case name.
class HasNamedTestFunctor {
public:
	HasNamedTestFunctor(const mr_utils::mr_string& name) : m_name(name) {
	}
	
	bool operator () (const TestCaseHolder* testHolder) {
		return testHolder->m_testData->m_name == this->m_name;
	}
private:
	const mr_utils::mr_string& m_name;
};


/// @brief Functor to vector of test names held by fixture
class BuildNamesVectorFunctor {
public:
	BuildNamesVectorFunctor(std::vector<mr_utils::mr_string>& names) 
		: m_names(names) {
	}

	void operator () (const TestCaseHolder* testHolder) {
		this->m_names.push_back(testHolder->m_testData->m_name);
	}

private:
	// TODO - look up the const in relation to reference. The reference is not changing but the object
	std::vector<mr_utils::mr_string>& m_names;
};


Fixture::Fixture(const mr_utils::mr_string& name, const mr_utils::mr_string& desc) 
:	//m_name( name ), // TODO - have the name of the Fixture preserved
	m_currentTestCase(0),
	m_fixtureSetup(0),
	m_fixtureTeardown(0),
	m_testSetup(0),
	m_testTeardown(0),
	m_isFixtureCalled(false) {
}


const mr_test::TestArguments& Fixture::CurrentArgs() const {
	return this->m_args;
}


void Fixture::RegisterFixtureSetup(fixture_method_ptr setup) {
	assert(setup);
	this->m_fixtureSetup = setup;
}


void Fixture::RegisterFixtureTeardown(fixture_method_ptr teardown) {
	assert(teardown);
	this->m_fixtureTeardown = teardown;
}


void Fixture::RegisterTestSetup(fixture_method_ptr setup) {
	assert(setup);
	this->m_testSetup = setup;
}


void Fixture::RegisterTestTeardown(fixture_method_ptr teardown) {
	assert(teardown);
	this->m_testTeardown = teardown;
}


void Fixture::RegisterTest(fixture_method_ptr test, const mr_utils::mr_string& name, const mr_utils::mr_string& description) {
	assert(test);
	// TODO - test if already there?
	// TODO - look at a scheme where you would have TestFixtureName.TestCaseName

	// When using the macro it uses the # and will insert the full &ClassName::MethodName
	mr_utils::mr_string scratch(name);
	size_t pos = scratch.find(_L_("::"));
	if (pos != mr_utils::mr_string::npos) {
		scratch = name.substr(pos + 2);
	}

	this->m_tests.push_back(new TestCaseHolder(test, scratch, description));
	// TODO - destructor to clean up holders
}


bool Fixture::HasTest(const mr_utils::mr_string& name) {
	// TODO - look at a scheme where you would have TestFixtureName.TestCaseName
	return std::find_if(
		this->m_tests.begin(), 
		this->m_tests.end(), 
		HasNamedTestFunctor(name)) != this->m_tests.end();
}


const std::vector<mr_utils::mr_string> Fixture::GetTestNames() {
	// TODO - verify that stack var non pointer will pass out as a copy on return
	std::vector<mr_utils::mr_string> names;
	std::for_each(
		this->m_tests.begin(),
		this->m_tests.end(),
		BuildNamesVectorFunctor(names));

	return names;
}


Case& Fixture::CurrentTestCase() const {
	assert(this->m_currentTestCase);
	return *(this->m_currentTestCase->m_testData);
}


void Fixture::RunTest(const mr_utils::mr_string& name, const mr_test::TestArguments& args ) {
	// Clear out any information from a previous test case
	this->ResetTest();

	// Get a copy of the optional arguments for the current named test case
	this->m_args = args;
	
	try {
		// lookup the test
		std::vector<TestCaseHolder*>::iterator it = 
			std::find_if(this->m_tests.begin(), this->m_tests.end(), HasNamedTestFunctor(name));
		
		// TODO - report this as an error instead ?
		assert(it != this->m_tests.end());
		this->m_currentTestCase = (*it);

		this->ExecTestFixtureSetup();
		this->ExecStep(this->m_currentTestCase->m_testData->m_setupTime, this->m_testSetup, Case::ST_FAIL_SETUP);
		this->ExecStep(this->m_currentTestCase->m_testData->m_execTime, this->m_currentTestCase->m_test, Case::ST_FAIL_TEST);	
		this->ExecStep(this->m_currentTestCase->m_testData->m_cleanupTime, this->m_testTeardown, Case::ST_FAIL_CLEANUP);

		// Test fixture teardown is called on fixture from outside when no more tests to execute in fixture

		// TODO - add code to catch segfault and convert to exeception for catch and print out the stack info
	}
	catch (...) {
		// TODO - later we may put the writing to buffer here but for now we will do it in the assert methods
	}

}


void Fixture::ExecStep(long long& timeVal, fixture_method_ptr funcPtr, Case::TestCaseStatus failStatus) {
	// In this case there may not even be a step registered
	timeVal = 0;
	if (funcPtr != 0) {
		mr_utils::StaticTimer timer;
		timer.start();
		// set to failed in case it throws
		this->m_currentTestCase->m_testData->m_status = failStatus;
		(this->*funcPtr)();
		this->m_currentTestCase->m_testData->m_status = Case::ST_SUCCESS;

		timer.stop();
		timeVal = timer.getMsInterval();
	}
}


void Fixture::ExecTestFixtureSetup() {
	// Fire the fixture setup if not previously fired by another test
	if (!this->m_isFixtureCalled) {
		// The fixture setup is not presently timed
		long long bogusTimeVal = 0;
		this->ExecStep(bogusTimeVal, this->m_fixtureSetup, Case::ST_FAIL_FIXTURE_SETUP);
		this->m_isFixtureCalled = true;
	}
}


void Fixture::ResetTest() {
	if (this->m_currentTestCase != 0) {
		this->m_currentTestCase->Reset();
	}
}


void Fixture::ResetFixture() {
	this->ResetTest();
	if (this->m_isFixtureCalled) {

		// Do not report errors on test fixture teardown
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


} // end namespace
