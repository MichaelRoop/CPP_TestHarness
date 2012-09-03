///--------------------------------------------------------------------------------------
/// @file	MrTestTypes.h
/// @brief	To export types and typedefs used by MrTest classes
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_TYPE_H)
#define MR_TEST_TYPE_H

#include "CppTestDefines.h"
#include "ICppTestCase.h"
#include "ICppTestRunSummary.h"


namespace MrTest {

/// @brief	Typedef of a call back event that will be called to send back results data from 
///			one test case
typedef void (* DataLoggedEvent) (const MrTest::ICase&);


/// @brief	Typedef of a call back event that will be called to send back summary data from the entire
///			group of test case run
typedef void (* TestRunSummaryData) (const MrTest::IRunSummary&);

} // end namespace

// Force export so it can be used in of std contained object 
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<MrTest::DataLoggedEvent>;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<MrTest::DataLoggedEvent>;

// Force export so it can be used in of std contained object 
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<MrTest::TestRunSummaryData>;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<MrTest::TestRunSummaryData>;


#endif