///--------------------------------------------------------------------------------------
/// @file	CppTestFixture.h
/// @brief	Provides a mechanism to associate its void member methods as test cases
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.5
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_FIXTURE_H)
#define CPP_TEST_FIXTURE_H

#include <string>

#include "CppTestCrossPlatform.h"



#include "mr_string.h"
#include "CppTestInfoObject.h"
#include "CppTestCase.h"

#include <assert.h>
#include <vector>

namespace CppTest {
	
class TestCaseHolder;

///--------------------------------------------------------------------------------------
///
///	@brief	Provides a mechanism to associate its void member methods as test cases
///
///	This class provides a base class to create and register void methods as test
/// cases which can be executed according to their registered method names.
///
/// There are three stages to a test case, the optional setup, the test, and the 
/// optional cleanup. There can be any number of test cases in one Fixture.
///
/// If a setup and/or teardown method are registered they are executed for each
/// test case in the Fixture.  You can also register an optional Fixture Setup
/// method which will be executed once before any of the tests.  The same goes for
/// the optional Fixture Teardown method which is executed once after the last
/// test case of the Fixture is executed.
///
/// All test, startup, and teardown methods that are registered have this 
/// signature: void MethodName()
///
/// This class encapsulates performance logging of each stage of the test.  As well, it
/// tracks the state and holds test information generated by the derived tests.
///
///--------------------------------------------------------------------------------------
class /*CPPTESCASE_API*/ Fixture {

public:

	/// @brief	Typdef of a class method pointer with no param and no return 
	typedef void (Fixture::*  fixture_method_ptr) (void);

public:

	/// @brief	Constructor
	///	@param	name	Name of the test case fixture.
	///	@param	desc	Description of test case fixture.
	Fixture(const mr_utils::mr_string& name, const mr_utils::mr_string& desc);


	/// @brief	Run the named test case contained in the fixture
	/// @param	name	The test case name
	/// @param	args	Arguments for the named test case
	void RunTest(const mr_utils::mr_string& name, const CppTest::TestCaseArguments& args);


	/// @brief	Called after the last fixture test case has executed
	void ResetFixture();


	/// @brief	Query if the test fixture has the named test case
	/// @parm	name	The test case name
	bool HasTest(const mr_utils::mr_string& name) const;


	/// @brief	Retrieve a list of test case names from fixture
	// TODO - decide on name format.  Probably should be TestFixtureName.TestCaseName
	const std::vector<mr_utils::mr_string> GetTestNames() const;


	/// @brief	Retrieve a copy of the currently executed test case
	Case& CurrentTestCase() const;

protected:

	/// @brief	Register a setup method to be executed once for the entire fixture
	/// @param	setup The setup method
	void RegisterFixtureSetup(fixture_method_ptr setup);


	/// @brief	Register a teardown method to be executed once for the entire fixture
	/// @param	teardown The teardown method
	void RegisterFixtureTeardown(fixture_method_ptr teardown);
	

	/// @brief	Register a setup method to be executed for each test in the fixture
	/// @param	setup The setup method
	void RegisterTestSetup(fixture_method_ptr setup);


	/// @brief	Register a teardown method to be executed for each test in the fixture
	/// @param	teardown The teardown method
	void RegisterTestTeardown(fixture_method_ptr teardown);


	/// @brief	Register a test to be executed when called by name
	/// @param	test	The test method pointer
	/// @param	name	The test name
	/// @param	description	The test description
	void RegisterTest(fixture_method_ptr test, const mr_utils::mr_string& name, const mr_utils::mr_string& description);


	///	@brief	Reset any data from previous test TODO - replace with current test.data
	void ResetTest();


	/// @brief	Retrieve test arguments for current test case.
	/// @return	The arguments for the test case.
	const CppTest::TestCaseArguments& CurrentArgs() const;

private:

	//mr_utils::mr_string			m_name;				// TODO - preserve the fixture name for lookup 
	CppTest::TestCaseArguments	m_args;				///< Arguments for current Test Case.
	fixture_method_ptr			m_fixtureSetup;		///< setup method for the entire fixture
	fixture_method_ptr			m_fixtureTeardown;	///< teardown method for the entire fixture
	fixture_method_ptr			m_testSetup;		///< setup method for each test
	fixture_method_ptr			m_testTeardown;		///< teardown method for each test
	bool						m_isFixtureCalled;	///< Determines if a test has been called on the fixture yet
	std::vector<TestCaseHolder*> m_tests;			///< The list of test cases
	TestCaseHolder*				m_currentTestCase;	///< The currently executing test case holder

private:

	/// @brief	Wrapper function to wrap performance logging for various methods.
	/// @param	timeVal	A reference to hold the timing information.
	/// @param	funcPtr	A pointer to the function to time.
	///
	/// @return	true if the function timed is successful, otherwise false.
	void ExecStep(long long& timeVal, fixture_method_ptr funcPtr, Case::TestCaseStatus failStatus);


	/// @brief	Execute the Fixture setup 
	void ExecTestFixtureSetup();

public:  // temp to check for linking
	
	///// @brief	Protected default constructor to force use of regular constructor.
	Fixture() ;


	/// @brief	Protected copy constructor to force use of regular constructor.
	/// @param	tc	The testCase used for construction.
	Fixture( const Fixture& tc );

};


///--------------------------------------------------------------------------------------
///
///	@brief	Associates the test pointer with the Case object that stores test results
///
///--------------------------------------------------------------------------------------
class TestCaseHolder {

public:

	/// @brief	Constructor
	/// @param	testPtr	Pointer to the test method
	/// @param	name	Test name
	/// @param	description	Test description
	TestCaseHolder(Fixture::fixture_method_ptr testPtr, const mr_utils::mr_string& name, const mr_utils::mr_string& description) :	
		m_test(testPtr),
		m_testData(new Case(name, description)) {
	}

	
	/// @brief	Destructor
	virtual ~TestCaseHolder() {
		if (this->m_testData != 0) {
			delete this->m_testData;
			this->m_testData = 0;
		}
	}


	/// @brief	Return the test method pointer
	Fixture::fixture_method_ptr Pointer() const {
		return this->m_test;
	}


	/// @brief	Return the test data capture object
	Case* Data() const {
		return this->m_testData;
	}


	/// @brief	Reset the test case data object to non run state
	void Reset() {
		assert(this->m_testData);
		this->m_testData->Reset();
	}

private:
	Fixture::fixture_method_ptr m_test;		///< Pointer to the test method
	Case*						m_testData;	///< Pointer to the test data capture object


	TestCaseHolder() {
	}

	TestCaseHolder(const TestCaseHolder&) {
	}

	TestCaseHolder& operator = (const TestCaseHolder&) {
	}


//public:
//	TestCaseHolder() {
//	}
//
//	TestCaseHolder(const TestCaseHolder&) {
//	}


};



} // end namespace cppTest



//#include <vector>
//CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<CppTest::Fixture>;
//CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<CppTest::Fixture>;
//
//CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<CppTest::TestCaseHolder>;
//CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<CppTest::TestCaseHolder>;
//
//CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<CppTest::TestCaseHolder*>;
//CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<CppTest::TestCaseHolder*>;


//EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<CppTest::Fixture>;
//EXP_TEMPLATE template class CPPTESTUTILS_API std::vector<CppTest::Fixture>;


		//#define CPPTESCASE_API __declspec(dllexport)
		//#define CPPTESCASE_EXP_TEMPLATE



#endif
