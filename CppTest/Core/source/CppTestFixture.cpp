///--------------------------------------------------------------------------------------
/// @file	CppTestFixture.cpp
/// @brief	Provides a mechanism to associate its void member methods as test cases
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.5
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------

//#include <string>

#include "CppTestFixture.h"
#include "mr_staticTimer.h"

#include "mr_iostream.h"

#include <algorithm>

//// Win32 only
//#if defined (_WIN32)
//#include <excpt.h>
//#include <Windows.h>
//#endif

namespace CppTest {




//---------------------------------------------------------------------------------------
/// @brief Functor to determine if the name is a match for the test case name.
struct HasNamedTestFunctor {
public:
	HasNamedTestFunctor(const mr_utils::mr_string& name) : m_name(name) {
	}
	
	bool operator () (const TestCaseHolder* testHolder) {
		return testHolder->Data()->Name == this->m_name;
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
		this->m_names.push_back(testHolder->Data()->Name);
	}

private:
	// TODO - look up the const in relation to reference. The reference is not changing but the object
	std::vector<mr_utils::mr_string>& m_names;
};
//---------------------------------------------------------------------------------------

// Functors require the npos internally and linkning fails




Fixture::Fixture(const mr_utils::mr_string& name, const mr_utils::mr_string& desc) 
:	//m_name( name ), // TODO - have the name of the Fixture preserved
	m_currentTestCase(0),
	m_fixtureSetup(0),
	m_fixtureTeardown(0),
	m_testSetup(0),
	m_testTeardown(0),
	m_isFixtureCalled(false) {
}


const CppTest::TestArguments& Fixture::CurrentArgs() const {
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
	
	// TODO - fix when linker problem solved in VS2010
	size_t end = (size_t) -1;
	if (pos != end) {
	//if (pos != mr_utils::mr_string::npos) {
		// TOTALLY WACKED - fails with npos not exported if I do a substring.

		//scratch = name.substr(pos + 2);
		scratch = mr_utils::SubString(name, pos +2);


		// if we invoke without the length param it will revert to default value npos and cause a link failure
//		scratch = name.substr(pos + 2, (name.length() - (pos + 3) ));
		//scratch = name.substr(pos + 2, 2); // TODO figure out what to do

		//name.substr(pos + 2);
	}

	mr_cout << _L_("Registering test : ") << scratch << std::endl;
	mr_cout << _L_("Before Parse:") << name << std::endl;

	this->m_tests.push_back(new TestCaseHolder(test, scratch, description));
	// TODO - destructor to clean up holders
}


bool Fixture::HasTest(const mr_utils::mr_string& name) const {
	// TODO - look at a scheme where you would have TestFixtureName.TestCaseName
	return std::find_if(
		this->m_tests.begin(), 
		this->m_tests.end(), 
		HasNamedTestFunctor(name)) != this->m_tests.end();

	//return false;
}


const std::vector<mr_utils::mr_string> Fixture::GetTestNames() const {
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
	return *(this->m_currentTestCase->Data());
}


void Fixture::RunTest(const mr_utils::mr_string& name, const CppTest::TestArguments& args ) {
	// Clear out any information from a previous test case
	this->ResetTest();

	// Get a copy of the optional arguments for the current named test case
	this->m_args = args;
	
	// Windows specific test code
//#if defined (_WIN32)
//__try {
//#endif
	try {
		// lookup the test
		std::vector<TestCaseHolder*>::iterator it = 
			std::find_if(this->m_tests.begin(), this->m_tests.end(), HasNamedTestFunctor(name));
		
		// TODO - report this as an error instead ?
		assert(it != this->m_tests.end());
		this->m_currentTestCase = (*it);

		this->ExecTestFixtureSetup();
		this->ExecStep(this->m_currentTestCase->Data()->SetupTime, this->m_testSetup, Case::ST_FAIL_SETUP);
		this->ExecStep(this->m_currentTestCase->Data()->ExecTime, this->m_currentTestCase->Pointer(), Case::ST_FAIL_TEST);	
		this->ExecStep(this->m_currentTestCase->Data()->CleanupTime, this->m_testTeardown, Case::ST_FAIL_CLEANUP);

		// Test fixture teardown is called on fixture from outside when no more tests to execute in fixture

		// TODO - add code to catch segfault and convert to exeception for catch and print out the stack info
	}
	catch (...) {
		// TODO - later we may put the writing to buffer here but for now we will do it in the assert methods
	}

//#if defined (_WIN32)
//	}
//__except(GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO) {
//		printf("Devide by 0 error");
//	}
//#endif

}


void Fixture::ExecStep(long long& timeVal, fixture_method_ptr funcPtr, Case::TestCaseStatus failStatus) {
	// In this case there may not even be a step registered
	timeVal = 0;
	if (funcPtr != 0) {
		mr_utils::StaticTimer timer;
		timer.start();
		// set to failed in case it throws
		this->m_currentTestCase->Data()->Status = failStatus;
		(this->*funcPtr)();
		this->m_currentTestCase->Data()->Status = Case::ST_SUCCESS;

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
