///--------------------------------------------------------------------------------------
/// @file	IMrTestCaseHolder.h
/// @brief	Interface object that holds a test function pointer and the test data 
///			accumulator
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.5
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(IMR_TEST_CASE_HOLDER_H)
#define IMR_TEST_CASE_HOLDER_H

#include "MrTestDefines.h"
#include "IMrTestFixture.h"

namespace MrTest {

///--------------------------------------------------------------------------------------
///
///	@brief	Associates the test pointer with the Case object that stores test results
///
///--------------------------------------------------------------------------------------
class MRTESCASE_API ITestCaseHolder {

public:

	/// @brief	Default constructor
	ITestCaseHolder() {
	}


	/// @brief	Return the test method pointer
	virtual IFixture::Ifixture_method_ptr Pointer() const = 0;


	/// @brief	Return the test data capture object
	virtual ICase* Data() const = 0;


	/// @brief	Reset the test case data object to non run state
	virtual void Reset() = 0;

private:

	/// @brief	Copy constructor
	ITestCaseHolder(const ITestCaseHolder& obj) {
	}

};

} // end namespace MrTest

// Force export of contained std items
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::allocator<MrTest::ITestCaseHolder*>;
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::vector<MrTest::ITestCaseHolder*>;

#endif
