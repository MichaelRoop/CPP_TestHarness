///--------------------------------------------------------------------------------------
/// @file	ICppTestFixtureTestCaseNames.h
/// @brief	Interface for storage for test fixture name and its test case names
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_FIXTURE_TEST_CASE_NAMES_H)
#define ICPP_TEST_FIXTURE_TEST_CASE_NAMES_H

#include "CppTestDefines.h"
#include "mr_string.h"
#include "mr_SharedPtr.h"
#include <vector>

namespace MrTest {

//----------------------------------------------------------------------------------------
/// @brief	Interface for storage for storage for test fixture name and its test case names.
//----------------------------------------------------------------------------------------
class CPPTESCASE_API IFixutureTestCaseNames {
public:

	/// @brief The name of the fixture
	virtual const mr_utils::mr_string& FixtureName() const = 0;


	/// @brief A vector of the fixture test case names
	virtual const std::vector<mr_utils::mr_string>& TestCaseNames() const = 0;


	/// @brief Add a test case name to the list
	virtual void AddTestCaseName(const mr_utils::mr_string& name) = 0;

};

// Force the export of the std objects in the class
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames>;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator< mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> >;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector< mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> >;

}

#endif
