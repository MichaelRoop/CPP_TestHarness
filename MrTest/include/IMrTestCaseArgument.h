///--------------------------------------------------------------------------------------
/// @file	MrTestFixture.h
/// @brief	One argument for a test case
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(IMR_TEST_CASE_ARGUMENT_H)
#define IMR_TEST_CASE_ARGUMENT_H

#include "MrTestDefines.h"
#include "mr_defines.h"
#include "mr_string.h"

namespace MrTest {

class MRTESCASE_API ICaseArgument {
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

/// @typedef Typedef for a vector of argument pairs.
typedef std::vector<ICaseArgument> TestCaseArguments;

}

MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::allocator<MrTest::ICaseArgument>;
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::vector<MrTest::ICaseArgument>;

#endif
