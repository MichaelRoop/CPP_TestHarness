///--------------------------------------------------------------------------------------
/// @file	MrTestCase.h
/// @brief	Holder for test case execution results data
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.5
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_CASE_H)
#define MR_TEST_CASE_H

#include "IMrTestCase.h"

namespace MrTest {

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
class Case : public MrTest::ICase {

public:

	/// @brief	Constructor
	///	@param	name	Name of the test case.
	///	@param	description	Description of test case.
	Case(
		const mr_utils::mr_string& fixtureName, 
		const mr_utils::mr_string& name, 
		const mr_utils::mr_string& description);


	/// @brief	Destructor
	virtual ~Case();


	/// @brief	Called to reset internal state
	virtual void Reset();

};

} // end namespace MrTest::Case

#endif
