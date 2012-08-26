///--------------------------------------------------------------------------------------
/// @file	CppTestCaseHolder.h
/// @brief	Interface object that holds a test function pointer and the test data 
///			accumulator
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.5
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_CASE_HOLDER_H)
#define ICPP_TEST_CASE_HOLDER_H

#include "CppTestCrossPlatform.h"
#include "ICppTestFixture.h"
#include "mr_exception.h"

namespace CppTest {

///--------------------------------------------------------------------------------------
///
///	@brief	Associates the test pointer with the Case object that stores test results
///
///--------------------------------------------------------------------------------------
class CPPTESCASE_API ITestCaseHolder {

public:

	/// @brief	Default constructor
	ITestCaseHolder() {
	}


	/// @brief	Destructor
	virtual ~ITestCaseHolder() {
	}


	/// @brief	Copy constructor
	ITestCaseHolder(const ITestCaseHolder& obj) {
		// Must be public to use vector to force the export
	}

	/// @brief	Assignement operator
	ITestCaseHolder& operator = (const ITestCaseHolder& rhs) {
		// Must be public to use vector to force the export
		return *this;
	}


	/// @brief	Return the test method pointer
	virtual IFixture::Ifixture_method_ptr Pointer() const {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}


	/// @brief	Return the test data capture object
	virtual ICase* Data() const = 0;
	//{
	//	// Should be pure virtual but cannot export the class
	//	throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	//}


	/// @brief	Reset the test case data object to non run state
	virtual void Reset() {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}

};

} // end namespace cppTest

//#include <vector>
//CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<CppTest::ITestCaseHolder>;
//CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<CppTest::ITestCaseHolder>;


CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<CppTest::ITestCaseHolder*>;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<CppTest::ITestCaseHolder*>;



#endif

