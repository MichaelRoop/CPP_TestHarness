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


#if defined (_WIN32)
#	define WIN_EXECP_SIGNAL_HANDLING
#endif

// Win32 only
#if defined (WIN_EXECP_SIGNAL_HANDLING)
#	include <excpt.h>
#	include <Windows.h>
#endif

namespace MrTest {


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
	m_testCaseNames(new MrTest::FixutureTestCaseNames(name)) {
}


Fixture::~Fixture() {
	mr_utils::DeletePtr<ITestCaseHolder> deleter;
	std::for_each(this->m_tests.begin(), this->m_tests.end(), deleter);
}


const MrTest::TestCaseArguments& Fixture::CurrentArgs() const {
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


mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> Fixture::GetTestNames() const {
	return this->m_testCaseNames;
}


ICase& Fixture::CurrentTestCase() const {
	assert(this->m_currentTestCase);
	return *(this->m_currentTestCase->Data());
}


const mr_utils::mr_string& Fixture::Name() const {
	return this->m_name;
}


#if defined(WIN_EXECP_SIGNAL_HANDLING)
int filter(unsigned int code, struct _EXCEPTION_POINTERS *ep, ITestCaseHolder* currentTestCase) {
//	printf("------- %d --------in filter.\n", code);

	switch (code) {
	case EXCEPTION_ACCESS_VIOLATION:
		printf("-------------caught AV as expected.\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_INT_DIVIDE_BY_ZERO:
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		if (currentTestCase != 0) {
			//ep->ContextRecord->
			//ep->ExceptionRecord->ExceptionInformation
			//ep->ExceptionRecord->ExceptionCode
			//GetListingForException(

			mr_utils::ResetStringStream(currentTestCase->Data()->MsgBuffer);
			currentTestCase->Data()->MsgBuffer << L("Caught devide by zero fault");
		}
		return EXCEPTION_EXECUTE_HANDLER;
	
	case EXCEPTION_DATATYPE_MISALIGNMENT:
		printf("---------------EXCEPTION_DATATYPE_MISALIGNMENT\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_BREAKPOINT:
		printf("---------------EXCEPTION_BREAKPOINT\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_SINGLE_STEP:
		printf("---------------EXCEPTION_SINGLE_STEP\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		printf("---------------EXCEPTION_ARRAY_BOUNDS_EXCEEDED\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_FLT_DENORMAL_OPERAND:
		printf("---------------EXCEPTION_FLT_DENORMAL_OPERAND\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_FLT_INEXACT_RESULT:
		printf("---------------EXCEPTION_FLT_INEXACT_RESULT\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_FLT_INVALID_OPERATION:
		printf("---------------EXCEPTION_FLT_INVALID_OPERATION\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_FLT_OVERFLOW:
		printf("---------------EXCEPTION_FLT_OVERFLOW\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_FLT_STACK_CHECK:
		printf("---------------EXCEPTION_FLT_STACK_CHECK\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_FLT_UNDERFLOW:
		printf("---------------EXCEPTION_FLT_UNDERFLOW\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_INT_OVERFLOW:
		printf("---------------EXCEPTION_INT_OVERFLOW\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_PRIV_INSTRUCTION:
		printf("---------------EXCEPTION_PRIV_INSTRUCTION\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_IN_PAGE_ERROR:
		printf("---------------EXCEPTION_IN_PAGE_ERROR\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_ILLEGAL_INSTRUCTION:
		printf("---------------EXCEPTION_ILLEGAL_INSTRUCTION\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_NONCONTINUABLE_EXCEPTION:
		printf("---------------EXCEPTION_NONCONTINUABLE_EXCEPTION\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_STACK_OVERFLOW:
		printf("---------------EXCEPTION_STACK_OVERFLOW\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_INVALID_DISPOSITION:
		printf("---------------EXCEPTION_INVALID_DISPOSITION\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_GUARD_PAGE:
		printf("---------------EXCEPTION_GUARD_PAGE\n");
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_INVALID_HANDLE:
		printf("---------------EXCEPTION_INVALID_HANDLE\n");
		return EXCEPTION_EXECUTE_HANDLER;

	//case EXCEPTION_POSSIBLE_DEADLOCK:
	//	printf("---------------EXCEPTION_POSSIBLE_DEADLOCK\n");
	//	return EXCEPTION_EXECUTE_HANDLER;

	default:
		// this is where reqular exceptions come
		//printf("---------------didn't catch AV, unexpected.\n");
		//return EXCEPTION_CONTINUE_SEARCH;
		return EXCEPTION_EXECUTE_HANDLER;
	}

}
#endif


void Fixture::RunTest(const mr_utils::mr_string& name, const MrTest::TestCaseArguments& args ) {
	// Clear out any information from a previous test case
	this->ResetTest();

	// Get a copy of the optional arguments for the current named test case
	this->m_args = args;
	


	// TODO - catch the segfault
	// Windows specific test code
#if defined (WIN_EXECP_SIGNAL_HANDLING)
__try {
#else
	try {
#endif

#if defined(WIN_EXECP_SIGNAL_HANDLING)
		// cannot use iterator because of __try
		unsigned size = this->m_tests.size();
		bool found = false;
		for (unsigned i = 0; i < size; i++) {
			if (this->m_tests[i]->Data()->Name == name) {
				this->m_currentTestCase = this->m_tests[i];
				found = true;
				break;
			}
		}
		assert(found);
#else
		 //lookup the test
		std::vector<ITestCaseHolder*>::iterator it = 
			std::find_if(this->m_tests.begin(), this->m_tests.end(), HasNamedTestFunctor(name));
		
		// TODO - report this as an error instead ?
		assert(it != this->m_tests.end());
		this->m_currentTestCase = (*it);

#endif
	
		this->ExecTestFixtureSetup();
		this->ExecStep(this->m_currentTestCase->Data()->SetupTime, this->m_testSetup, ICase::ST_FAIL_SETUP);
		this->ExecStep(this->m_currentTestCase->Data()->ExecTime, this->m_currentTestCase->Pointer(), ICase::ST_FAIL_TEST);	
		this->ExecStep(this->m_currentTestCase->Data()->CleanupTime, this->m_testTeardown, ICase::ST_FAIL_CLEANUP);

		// Test fixture teardown is called on fixture from outside when no more tests to execute in fixture

		// TODO - add code to catch segfault and convert to exeception for catch and print out the stack info
	}
#if defined (WIN_EXECP_SIGNAL_HANDLING)
	__except(filter(GetExceptionCode(), GetExceptionInformation(), this->m_currentTestCase)) {
	//printf(" ############## after filter expcept\n");
#else 
	catch (...) {
		// TODO - later we may put the writing to buffer here but for now we will do it in the assert methods
#endif
	}
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
