///--------------------------------------------------------------------------------------
/// @file	CppTestFixtureTestCaseNames.h
/// @brief	Storage for test fixture name and its test case names
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_FIXTURE_TEST_CASE_NAMES_H)
#define CPP_TEST_FIXTURE_TEST_CASE_NAMES_H

#include "ICppTestFixtureTestCaseNames.h"

namespace CppTest {

//----------------------------------------------------------------------------------------
/// @brief	Storage for test fixture name and its test case names.
//----------------------------------------------------------------------------------------
class FixutureTestCaseNames {
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

#endif
