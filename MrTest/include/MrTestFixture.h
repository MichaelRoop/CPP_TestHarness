///--------------------------------------------------------------------------------------
/// @file	MrTestFixture.h
/// @brief	Provides a mechanism to associate its void member methods as test cases
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.5
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_FIXTURE_H)
#define MR_TEST_FIXTURE_H

#include "MrTestDefines.h"
#include "IMrTestFixture.h"
#include "IMrTestCaseHolder.h"
#include "mr_string.h"

namespace MrTest {

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
class MRTESCASE_API Fixture : public IFixture {

public:

	/// @brief	Constructor
	///	@param	name	Name of the test case fixture.
	Fixture(const mr_utils::mr_string& name);


	/// @bried	Destructor
	virtual ~Fixture();
	

	/// @brief	Run the named test case contained in the fixture
	/// @param	name	The test case name
	/// @param	args	Arguments for the named test case
	 virtual void RunTest(const mr_utils::mr_string& name, const MrTest::TestCaseArguments& args);


	/// @brief	Called after the last fixture test case has executed
	virtual void ResetFixture();


	/// @brief	Query if the test fixture has the named test case
	/// @parm	name	The test case name
	virtual bool HasTest(const mr_utils::mr_string& name) const;


	/// @brief	Retrieve the Fixture and test case names
	virtual mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> GetTestNames() const;


	/// @brief	Retrieve a copy of the currently executed test case
	virtual ICase& CurrentTestCase() const;


	/// @brief	Test Fixture name
	virtual const mr_utils::mr_string& Name() const;

protected:

	/// @brief	Register a setup method to be executed once for the entire fixture
	/// @param	setup The setup method
	virtual void RegisterFixtureSetup(IFixture::Ifixture_method_ptr setup);


	/// @brief	Register a teardown method to be executed once for the entire fixture
	/// @param	teardown The teardown method
	virtual void RegisterFixtureTeardown(IFixture::Ifixture_method_ptr teardown);
	

	/// @brief	Register a setup method to be executed for each test in the fixture
	/// @param	setup The setup method
	virtual void RegisterTestSetup(IFixture::Ifixture_method_ptr setup);


	/// @brief	Register a teardown method to be executed for each test in the fixture
	/// @param	teardown The teardown method
	virtual void RegisterTestTeardown(IFixture::Ifixture_method_ptr teardown);


	/// @brief	Register a test to be executed when called by name
	/// @param	test	The test method pointer
	/// @param	name	The test name
	/// @param	description	The test description
	virtual void RegisterTest(
		IFixture::Ifixture_method_ptr test, 
		const mr_utils::mr_string& name, 
		const mr_utils::mr_string& description);


	///	@brief	Reset any data from previous test TODO - replace with current test.data
	virtual void ResetTest();


	/// @brief	Retrieve test arguments for current test case.
	/// @return	The arguments for the test case.
	virtual const MrTest::TestCaseArguments& CurrentArgs() const;

private:

	mr_utils::mr_string				m_name;				///< Fixture name 
	MrTest::TestCaseArguments		m_args;				///< Arguments for current Test Case.
	IFixture::Ifixture_method_ptr	m_fixtureSetup;		///< setup method for the entire fixture
	IFixture::Ifixture_method_ptr	m_fixtureTeardown;	///< teardown method for the entire fixture
	IFixture::Ifixture_method_ptr	m_testSetup;		///< setup method for each test
	IFixture::Ifixture_method_ptr	m_testTeardown;		///< teardown method for each test
	bool							m_isFixtureCalled;	///< Determines if a test has been called on the fixture yet
	std::vector<ITestCaseHolder*>	m_tests;			///< The list of test cases
	ITestCaseHolder*				m_currentTestCase;	///< The currently executing test case holder
	mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> m_testCaseNames; ///< Object that holds test case name information

private:

	/// @brief	Wrapper function to wrap performance logging for various methods.
	/// @param	timeVal	A reference to hold the timing information.
	/// @param	funcPtr	A pointer to the function to time.
	/// @return	true if the function timed is successful, otherwise false.
	void ExecStep(long long& timeVal, IFixture::Ifixture_method_ptr funcPtr, ICase::TestCaseStatus failStatus);


	/// @brief	Execute the Fixture setup 
	void ExecTestFixtureSetup();

	/// @brief	Lookup and set the current test case by name
	/// @param	name	The name of the test case to lookup
	void SetCurrentTest(const mr_utils::mr_string& name);

private:  // temp to check for linking
	
	///// @brief Protected default constructor to force use of regular constructor.
	Fixture() ;


	/// @brief	Protected copy constructor to force use of regular constructor.
	/// @param	tc	The testCase used for construction.
	Fixture(const Fixture& tc);

};

} // end namespace MrTest

MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::allocator<MrTest::Fixture*>;
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::vector<MrTest::Fixture*>;

#endif
