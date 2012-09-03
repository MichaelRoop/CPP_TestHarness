///--------------------------------------------------------------------------------------
/// @file	ICppTestRunSummary.h
/// @brief	Interface for test run summary data
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_RUN_SUMMARY_H)
#define ICPP_TEST_RUN_SUMMARY_H

#include "CppTestDefines.h"
#include "ICppTestCase.h"
#include "mr_string.h"

namespace MrTest {

///--------------------------------------------------------------------------------------
///	@brief	Holder for test case summary data
///--------------------------------------------------------------------------------------
class CPPTESCASE_API IRunSummary {
public:

	/// @brief	Get the total number of test of a given status
	/// @param	status	The total number of tests of this status will be returned
	virtual int Total(MrTest::ICase::TestCaseStatus status) const = 0;


	/// @brief	Get the total number of test run
	virtual int Total() const = 0;

};

} // end namespace MrTest::Case

#endif
