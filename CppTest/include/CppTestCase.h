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
#if !defined(CPP_TEST_CASE_H)
#define CPP_TEST_CASE_H

#include "ICppTestCase.h"
#include "mr_string.h"
#include "mr_sstream.h"

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
class Case : public CppTest::ICase {

public:

	///// @brief	Status indicator for the test case.
	//typedef enum Status {
	//	ST_NONE,					///< No status. Default
	//	ST_NOT_EXISTS,				///< Test does not exist
	//	ST_SUCCESS,					///< Successful
	//	ST_FAIL_SETUP,				///< Failed on test setup
	//	ST_FAIL_TEST,				///< Failed on test
	//	ST_FAIL_CLEANUP,			///< Failed on test teardown
	//	ST_FAIL_FIXTURE_SETUP,		///< Failed on Fixture setup
	//	ST_FAIL_FIXTURE_TEARDOWN	///< Failed on Fixture teardown

	//} TestCaseStatus;


	///// @brief	Static method to convert status enum to string
	///// @param	status	The enum to convert
	//static mr_utils::mr_string ToString(Case::TestCaseStatus status);

	/// @brief	Protected default constructor to force use of regular constructor.
	Case() {
	}


	/// @brief	Constructor
	///	@param	name	Name of the test case.
	///	@param	description	Description of test case.
	Case(const mr_utils::mr_string& name, const mr_utils::mr_string& description);


	/// @brief	Copy constructor
	/// @param	testCase	The testCase used for construction.
	Case(const Case& testCase);
	

	virtual ~Case() {
	}

	/// @brief	Called to reset internal state
	virtual void Reset();

public:
	//Case::TestCaseStatus		Status;			///< Status of the test case.
	//mr_utils::mr_string			Name;			///< Test name.
	//mr_utils::mr_string			Description;	///< Test description.
	////mr_test::TestArguments	m_args;			///< Test arguments.
	//mr_utils::mr_stringstream	MsgBuffer;		///< Short message buffer.
	//mr_utils::mr_stringstream	VerboseBuffer;	///< Verbose message buffer.
	//long long					SetupTime;		///< Setup time in ms.
	//long long					ExecTime;		///< Test time in ms.
	//long long					CleanupTime;	///< Cleanup time in ms.

//private:
//	/// @brief	Protected default constructor to force use of regular constructor.
//	Case() ;

};

} // end namespace cppTest::Case

#endif
