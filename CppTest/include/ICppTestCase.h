///--------------------------------------------------------------------------------------
/// @file	CppTestCase.h
/// @brief	Holder for test case execution results data
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.5
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_CASE_H)
#define ICPP_TEST_CASE_H

#include "CppTestCrossPlatform.h"
#include "mr_string.h"
#include "mr_sstream.h"
#include "mr_exception.h"
#include "mr_defines.h"
#include <assert.h>

namespace CppTest {

///--------------------------------------------------------------------------------------
///	@brief	Holder for test case execution results data
///
/// Besides name and description, this class encapsulates data accumulated during the 
// running of the named test. This includes test status, as well as performance counters
/// for setup, test and teardown. It also has optional long and short messages that can
/// be written within the test case or by one of the assert test macros.
///
/// The test case object can be querried by the logger derived objects to assemble the 
/// information required.
///--------------------------------------------------------------------------------------
class CPPTESCASE_API ICase {

public:

	/// @brief	Status indicator for the test case.
	typedef enum Status {
		ST_NONE,					///< No status. Default
		ST_NOT_EXISTS,				///< Test does not exist
		ST_SUCCESS,					///< Successful
		ST_FAIL_SETUP,				///< Failed on test setup
		ST_FAIL_TEST,				///< Failed on test
		ST_FAIL_CLEANUP,			///< Failed on test teardown
		ST_FAIL_FIXTURE_SETUP,		///< Failed on Fixture setup
		ST_FAIL_FIXTURE_TEARDOWN	///< Failed on Fixture teardown

	} TestCaseStatus;


	/// @brief	Static method to convert status enum to string
	/// @param	status	The enum to convert
	static mr_utils::mr_string ToString(ICase::TestCaseStatus status) {
		switch (status) {
			case ICase::ST_NONE:			return L( "NONE" );
			case ICase::ST_SUCCESS:		return L( "SUCCESS" );
			case ICase::ST_FAIL_SETUP:		return L( "FAIL_SETUP" );
			case ICase::ST_FAIL_TEST:		return L( "FAIL_TEST" );
			case ICase::ST_FAIL_CLEANUP:	return L( "FAIL_CLEANUP" );
			case ICase::ST_NOT_EXISTS:		return L( "NOT_EXISTS" );
			case ICase::ST_FAIL_FIXTURE_SETUP: return _L_("FAIL_FIXTURE_SETUP");
			case ICase::ST_FAIL_FIXTURE_TEARDOWN: return _L_("FAIL_FIXTURE_TEARDOWN");
		default:				
			assert(false);
			return L( "ERROR-NO-STATUS" );
		}
}


	/// @brief	Constructor
	ICase() {
	}


	/// @brief	Copy constructor
	/// @param	testCase	The testCase used for construction.
	ICase(const ICase& testCase) {
	}
	

	/// @brief	Called to reset internal state
	virtual void Reset()  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}


	ICase ICase::operator=(class CppTest::ICase const &) {
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}

public:
	ICase::TestCaseStatus		Status;			///< Status of the test case.
	mr_utils::mr_string			Name;			///< Test name.
	mr_utils::mr_string			Description;	///< Test description.
	//mr_test::TestArguments	m_args;			///< Test arguments.
	mr_utils::mr_stringstream	MsgBuffer;		///< Short message buffer.
	mr_utils::mr_stringstream	VerboseBuffer;	///< Verbose message buffer.
	long long					SetupTime;		///< Setup time in ms.
	long long					ExecTime;		///< Test time in ms.
	long long					CleanupTime;	///< Cleanup time in ms.


};

} // end namespace cppTest::Case


CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<CppTest::ICase>;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<CppTest::ICase>;


#endif
