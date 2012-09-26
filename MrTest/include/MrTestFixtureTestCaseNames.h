///--------------------------------------------------------------------------------------
/// @file	MrTestFixtureTestCaseNames.h
/// @brief	Storage for test fixture name and its test case names
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_FIXTURE_TEST_CASE_NAMES_H)
#define MR_TEST_FIXTURE_TEST_CASE_NAMES_H

#include "IMrTestFixtureTestCaseNames.h"

namespace MrTest {

//----------------------------------------------------------------------------------------
/// @brief	Storage for test fixture name and its test case names.
//----------------------------------------------------------------------------------------
class MRTESCASE_API FixutureTestCaseNames : public IFixutureTestCaseNames {
public:

	/// @brief The name of the fixture
	FixutureTestCaseNames(const mr_utils::mr_string& name);


	/// @brief A vector of the fixture test case names
	FixutureTestCaseNames(const FixutureTestCaseNames& obj);


	/// @brief The name of the fixture
	virtual const mr_utils::mr_string& FixtureName() const;


	/// @brief A vector of the fixture test case names
	virtual const std::vector<mr_utils::mr_string>& TestCaseNames() const;


	/// @brief Add a test case name to the list
	virtual void AddTestCaseName(const mr_utils::mr_string& name);

private:
	mr_utils::mr_string m_name;
	std::vector<mr_utils::mr_string> m_testCaseNames;

private:

	/// @brief Default constructor
	FixutureTestCaseNames() {
	}

};

} // end namespace

// Force export
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API mr_utils::SharedPtr<MrTest::FixutureTestCaseNames>;
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::allocator< mr_utils::SharedPtr<MrTest::FixutureTestCaseNames> >;
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::vector< mr_utils::SharedPtr<MrTest::FixutureTestCaseNames> >;

#endif
