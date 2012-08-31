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

#include "CppTestDefines.h"
#include "mr_defines.h"
#include "mr_string.h"

namespace CppTest {

class CPPTESCASE_API ICaseArgument {
public:

	ICaseArgument(const mr_utils::mr_string& name, const mr_utils::mr_string& value)
	: Name(name),
	Value(value) {
	}


	/// @brief	Default constructor to satisfy vector requirements
	ICaseArgument()
	: Name(_L_("")),
	Value(_L_("")) {
	}


	/// @brief	Default constructor to satisfy vector requirements
	ICaseArgument(const ICaseArgument& obj) {
		this->Name = obj.Name;
		this->Value = obj.Value;
	}


	/// @brief	The argument name so the test case can identify it
	mr_utils::mr_string Name;

	/// @brief	The argument value in string format
	mr_utils::mr_string Value;

};

CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<CppTest::ICaseArgument>;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<CppTest::ICaseArgument>;

/// @typedef Typedef for a vector of argument pairs.
typedef std::vector<ICaseArgument> TestCaseArguments; 

}

#endif
