///--------------------------------------------------------------------------------------
/// @file	ICppTestFixtureInfoObject.h
/// @brief	cross platform and char width holder for test information.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_FIXTURE_INFO_OBJECT_H)
#define ICPP_TEST_FIXTURE_INFO_OBJECT_H

#include "CppTestDefines.h"
#include "CppTestInfoObject.h"
#include "mr_string.h"
#include "mr_SharedPtr.h"
#include <vector>


namespace MrTest {


///--------------------------------------------------------------------------------------
///
/// @brief	Class to abstract the information necessary to retrieve a Fixture of test cases
///
///--------------------------------------------------------------------------------------
class CPPTESCASE_API ITestFixtureInfoObject {

public:

	/// @brief Default constructor
	ITestFixtureInfoObject() {
	}


	/// @brief Retrieve Test fixture name
	virtual const mr_utils::mr_string& GetName() const = 0;


	/// @brief Set the Test fixture name
	/// @brief	name	The test fixture name
	virtual const void SetName(mr_utils::mr_string& name) = 0;


	/// @brief	Retrieve the argument set.
	///
	/// @return	The argument set.
	virtual const std::vector<MrTest::TestInfoObject>& GetTestInfoVector() = 0;


	/// @brief	Add an argument to the argument set.
	///
	/// @param	name	The name of the argument.
	/// @param	value	The value of the argument.
	virtual void AddTestInfo(const MrTest::TestInfoObject& info) = 0;

private:

	/// @brief	Protected copy constructor to force use of regular constructor.
	/// @param	tc	The testCase used for construction.
	ITestFixtureInfoObject(const ITestFixtureInfoObject& tc) {
	}

};

} // end namespace

// Force export of class with std objects
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<MrTest::ITestFixtureInfoObject*>;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<MrTest::ITestFixtureInfoObject*>;

#endif
