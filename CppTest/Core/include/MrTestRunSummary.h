///--------------------------------------------------------------------------------------
/// @file	MrTestRunSummary.h
/// @brief	Test run summary data
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_RUN_SUMMARY_H)
#define MR_TEST_RUN_SUMMARY_H

#include "IMrTestRunSummary.h"
#include "MrTestCaseCounter.h"


namespace MrTest {

///--------------------------------------------------------------------------------------
///	@brief	Holder for test case summrary data
///--------------------------------------------------------------------------------------
class RunSummary : public MrTest::IRunSummary {
public:

	/// @brief
	RunSummary(const MrTest::CaseCounter& counter); 


	/// @brief	Get the total number of test of a given status
	/// @param	status	The total number of tests of this status will be returned
	virtual int Total(MrTest::ICase::TestCaseStatus status) const;


	/// @brief	Get the total number of all tests run
	virtual int Total() const;

private:
	int			m_Success;			///< Counter for successful tests.
	int			m_FailFixtureSetup;	///< Counter tests that failed on fixture setup.
	int			m_FailSetup;		///< Counter tests that failed on setup.
	int			m_FailTest;			///< Counter tests that failed on test.
	int			m_FailTeardown;		///< Counter tests that failed on teardown.
	int			m_NotFound;			///< Counter tests not found.
	int			m_Disabled;			///< Counter tests not found.

};

} // end namespace MrTest::Case

#endif
