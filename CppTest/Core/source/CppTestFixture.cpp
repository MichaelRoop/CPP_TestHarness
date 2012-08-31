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

#include "CppTestFixture.h"
#include "CppTestCaseHolder.h"
#include "CppTestFixtureTestCaseNames.h"
#include "mr_staticTimer.h"
#include "mr_iostream.h"
#include "mr_functors.h"
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
	
	bool operator () (const ITestCaseHolder* testHolder) {
		return testHolder->Data()->Name == this->m_name;
	}
private:
	const mr_utils::mr_string& m_name;
};


Fixture::Fixture(const mr_utils::mr_string& name) 
:	m_name( name ),
	m_currentTestCase(0),
	m_fixtureSetup(0),
	m_fixtureTeardown(0),
	m_testSetup(0),
	m_testTeardown(0),
	m_isFixtureCalled(false),
	m_testCaseNames(new CppTest::FixutureTestCaseNames(name)) {
}


Fixture::~Fixture() {
	mr_utils::DeletePtr<ITestCaseHolder> deleter;
	std::for_each(this->m_tests.begin(), this->m_tests.end(), deleter);
}


const CppTest::TestCaseArguments& Fixture::CurrentArgs() const {
	return this->m_args;
}


void Fixture::RegisterFixtureSetup(IFixture::Ifixture_method_ptr setup) {
	assert(setup);
	this->m_fixtureSetup = setup;
}


void Fixture::RegisterFixtureTeardown(IFixture::Ifixture_method_ptr teardown) {
	assert(teardown);
	this->m_fixtureTeardown = teardown;
}


void Fixture::RegisterTestSetup(IFixture::Ifixture_method_ptr setup) {
	assert(setup);
	this->m_testSetup = setup;
}


void Fixture::RegisterTestTeardown(IFixture::Ifixture_method_ptr teardown) {
	assert(teardown);
	this->m_testTeardown = teardown;
}


void Fixture::RegisterTest(IFixture::Ifixture_method_ptr test, const mr_utils::mr_string& name, const mr_utils::mr_string& description) {
	assert(test);
	// TODO - test if already there?
	// TODO - look at a scheme where you would have TestFixtureName.TestCaseName

	// When using the macro it uses the # and will insert the full &ClassName::MethodName
	mr_utils::mr_string scratch(name);
	size_t pos = scratch.find(_L_("::"));
	
	// TODO - fix when linker problem solved in VS2010
	// Need to use exported method to access string global npos within the DLL
	if (pos != mr_utils::StrNPos()) {
		scratch = mr_utils::SubString(name, pos +2);
	}

	this->m_tests.push_back(new TestCaseHolder(test, this->Name(), scratch, description));
	this->m_testCaseNames->AddTestCaseName(scratch);
}


bool Fixture::HasTest(const mr_utils::mr_string& name) const {
	// TODO - look at a scheme where you would have TestFixtureName.TestCaseName
	return std::find_if(
		this->m_tests.begin(), 
		this->m_tests.end(), 
		HasNamedTestFunctor(name)) != this->m_tests.end();
}


mr_utils::SharedPtr<CppTest::IFixutureTestCaseNames> Fixture::GetTestNames() const {
	return this->m_testCaseNames;
}


ICase& Fixture::CurrentTestCase() const {
	assert(this->m_currentTestCase);
	return *(this->m_currentTestCase->Data());
}


const mr_utils::mr_string& Fixture::Name() const {
	return this->m_name;
}


void Fixture::RunTest(const mr_utils::mr_string& name, const CppTest::TestCaseArguments& args ) {
	// Clear out any information from a previous test case
	this->ResetTest();

	// Get a copy of the optional arguments for the current named test case
	this->m_args = args;
	
	// TODO - catch the segfault
	// Windows specific test code
//#if defined (_WIN32)
//__try {
//#endif
	try {
		// lookup the test
		std::vector<ITestCaseHolder*>::iterator it = 
			std::find_if(this->m_tests.begin(), this->m_tests.end(), HasNamedTestFunctor(name));
		
		// TODO - report this as an error instead ?
		assert(it != this->m_tests.end());
		this->m_currentTestCase = (*it);

		this->ExecTestFixtureSetup();
		this->ExecStep(this->m_currentTestCase->Data()->SetupTime, this->m_testSetup, ICase::ST_FAIL_SETUP);
		this->ExecStep(this->m_currentTestCase->Data()->ExecTime, this->m_currentTestCase->Pointer(), ICase::ST_FAIL_TEST);	
		this->ExecStep(this->m_currentTestCase->Data()->CleanupTime, this->m_testTeardown, ICase::ST_FAIL_CLEANUP);

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


void Fixture::ExecStep(long long& timeVal, IFixture::Ifixture_method_ptr funcPtr, ICase::TestCaseStatus failStatus) {
	// In this case there may not even be a step registered
	timeVal = 0;
	if (funcPtr != 0) {
		mr_utils::StaticTimer timer;
		timer.start();
		// set to failed in case it throws
		this->m_currentTestCase->Data()->Status = failStatus;
		(this->*funcPtr)();
		this->m_currentTestCase->Data()->Status = ICase::ST_SUCCESS;

		timer.stop();
		timeVal = timer.getMsInterval();
	}
}


void Fixture::ExecTestFixtureSetup() {
	// Fire the fixture setup if not previously fired by another test
	if (!this->m_isFixtureCalled) {
		// The fixture setup is not presently timed
		long long bogusTimeVal = 0;
		this->ExecStep(bogusTimeVal, this->m_fixtureSetup, ICase::ST_FAIL_FIXTURE_SETUP);
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
