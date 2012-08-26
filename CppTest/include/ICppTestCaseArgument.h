///--------------------------------------------------------------------------------------
/// @file	CppTestFixture.h
/// @brief	One argument for a test case
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_CASE_ARGUMENT_H)
#define ICPP_TEST_CASE_ARGUMENT_H

#include "mr_string.h"

namespace CppTest {

class ICaseArgument {
public:

	/// @brief	The argument name so the test case can identify it
	mr_utils::mr_string Name;

	/// @brief	The argument value in string format
	mr_utils::mr_string Value;

};


// TODO put the force macro here for export

/// @typedef Typedef for a vector of argument pairs.
typedef std::vector<ICaseArgument> TestCaseArguments; 

}

#endif
