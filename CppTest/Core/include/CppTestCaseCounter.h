///--------------------------------------------------------------------------------------
/// @file	CppTestCaseCounter.h
/// @brief	To keep a summary count of the test run
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_CASE_COUNTER_H)
#define CPP_TEST_CASE_COUNTER_H

#include "CppTestDefines.h"
#include "ICppTestRunSummary.h"
#include "mr_SharedPtr.h"
#include "mr_string.h"

namespace MrTest {

class ICase;

///--------------------------------------------------------------------------------------
///	@brief	Accumatalate summary information on test cases through a run
///--------------------------------------------------------------------------------------
class CPPTESCASE_API CaseCounter {
public:

	/// @brief	Constructor
	CaseCounter();	


	/// @brief	Increment counts with test case information
	void Count(const MrTest::ICase& testCase);


	/// @brief	Called to reset internal state
	void Reset();


	/// @brief	Get a snapshot of the latest test summary data
	mr_utils::SharedPtr<MrTest::IRunSummary> Summary(const mr_utils::mr_string& runId) const;


	/// @brief	Number of test with status success
	int SuccessCount() const;


	/// @brief	Number of test with status Fixture Setup Failed
	int FailFixtureSetupCount() const;


	/// @brief	Number of test with status Setup Failed
	int FailSetupCount() const;


	/// @brief	Number of test with status Test Failed
	int FailTestCount() const;


	/// @brief	Number of test with status Teardown Failed
	int FailTeardownCount() const;
	

	/// @brief	Number of test with status Not Found
	int NotFoundCount() const;


	/// @brief	Number of test with status Disabled
	int DisabledCount() const;

public:
	int			m_success;			///< Counter for successful tests.
	int			m_failFixtureSetup;	///< Counter tests that failed on fixture setup.
	int			m_failSetup;		///< Counter tests that failed on setup.
	int			m_failTest;			///< Counter tests that failed on test.
	int			m_failTeardown;		///< Counter tests that failed on teardown.
	int			m_notFound;			///< Counter tests not found.
	int			m_disabled;			///< Counter tests not found.

};

} // end namespace 

// Force export of std items
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<MrTest::CaseCounter*>;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<MrTest::CaseCounter*>;

#endif
