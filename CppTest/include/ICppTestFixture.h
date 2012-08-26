///--------------------------------------------------------------------------------------
/// @file	CppTestFixture.h
/// @brief	Provides a mechanism to associate its void member methods as test cases
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_FIXTURE_H)
#define ICPP_TEST_FIXTURE_H


#include "CppTestCrossPlatform.h"
#include "ICppTestCase.h"
#include "ICppTestCaseArgument.h"
#include "mr_string.h"


namespace CppTest {

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
class CPPTESCASE_API IFixture {

public:

	/// @brief	Typdef of a class method pointer with no param and no return 
	typedef void (IFixture::*  Ifixture_method_ptr) (void);

public:

	/// @brief	Default constructor
	IFixture() {
	}


	/// @brief	Run the named test case contained in the fixture
	/// @param	name	The test case name
	/// @param	args	Arguments for the named test case
	virtual void RunTest(const mr_utils::mr_string& name, const CppTest::TestCaseArguments& args) = 0;
	

	/// @brief	Called after the last fixture test case has executed
	virtual void ResetFixture() = 0;


	/// @brief	Query if the test fixture has the named test case
	/// @parm	name	The test case name
	virtual bool HasTest(const mr_utils::mr_string& name) const = 0;


	/// @brief	Retrieve a list of test case names from fixture
	// TODO - decide on name format.  Probably should be TestFixtureName.TestCaseName
	virtual const std::vector<mr_utils::mr_string> GetTestNames() const = 0;


	/// @brief	Retrieve a copy of the currently executed test case
	virtual ICase& CurrentTestCase() const = 0;


	/// @brief	Test Fixture name
	virtual const mr_utils::mr_string& Name() const = 0;

protected: // the register test methods could be public

	/// @brief	Register a setup method to be executed once for the entire fixture
	/// @param	setup The setup method
	virtual void RegisterFixtureSetup(Ifixture_method_ptr setup) = 0;


	/// @brief	Register a teardown method to be executed once for the entire fixture
	/// @param	teardown The teardown method
	virtual void RegisterFixtureTeardown(Ifixture_method_ptr teardown) = 0;
	

	/// @brief	Register a setup method to be executed for each test in the fixture
	/// @param	setup The setup method
	virtual void RegisterTestSetup(Ifixture_method_ptr setup) = 0;


	/// @brief	Register a teardown method to be executed for each test in the fixture
	/// @param	teardown The teardown method
	virtual void RegisterTestTeardown(Ifixture_method_ptr teardown) = 0;


	/// @brief	Register a test to be executed when called by name
	/// @param	test	The test method pointer
	/// @param	name	The test name
	/// @param	description	The test description
	virtual void RegisterTest(
		Ifixture_method_ptr test, 
		const mr_utils::mr_string& name, 
		const mr_utils::mr_string& description) = 0;


	///	@brief	Reset any data from previous test TODO - replace with current test.data
	virtual void ResetTest() = 0;


	/// @brief	Retrieve test arguments for current test case.
	/// @return	The arguments for the test case.
	virtual const CppTest::TestCaseArguments& CurrentArgs() const = 0;

private:

	/// @brief	Protected copy constructor to force use of regular constructor.
	/// @param	tc	The testCase used for construction.
	IFixture(const IFixture& tc) {
	}

};

} // end namespace cppTest

// Force exposure of class using std objects
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<CppTest::IFixture*>;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<CppTest::IFixture*>;

#endif
