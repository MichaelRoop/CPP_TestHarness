///--------------------------------------------------------------------------------------
/// @file	CppTestFixtureInfoObject.h
/// @brief	cross platform and char width holder for test information.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_FIXTURE_INFO_OBJECT_H)
#define CPP_TEST_FIXTURE_INFO_OBJECT_H

#include "ICppTestFixtureInfoObject.h"


namespace CppTest {


///--------------------------------------------------------------------------------------
///
/// @brief	Class to abstract the information necessary to retrieve a Fixture of test cases
///
///--------------------------------------------------------------------------------------
class TestFixtureInfoObject {

public:

	/// @brief Retrieve Test fixture name
	virtual const mr_utils::mr_string& GetName() const;


	/// @brief Set the Test fixture name
	/// @brief	name	The test fixture name
	virtual const void SetName(mr_utils::mr_string& name);


	/// @brief	Retrieve the argument set.
	///
	/// @return	The argument set.
	virtual const std::vector<CppTest::TestInfoObject>& GetTestInfoVector();


	/// @brief	Add an argument to the argument set.
	///
	/// @param	name	The name of the argument.
	/// @param	value	The value of the argument.
	virtual void AddTestInfo(const CppTest::TestInfoObject& info);

private:
	mr_utils::mr_string						m_name;		///< Fixture name
	std::vector<CppTest::TestInfoObject>	m_tests;	///< Info objects for tests 	


	/// @brief Default constructor
	TestFixtureInfoObject() {
	}


	/// @brief Copy constructor
	TestFixtureInfoObject(const TestFixtureInfoObject&) {
	}

};


} // end namespace


#endif
