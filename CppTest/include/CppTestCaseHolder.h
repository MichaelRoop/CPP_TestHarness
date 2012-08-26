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
#if !defined(CPP_TEST_CASE_HOLDER_H)
#define CPP_TEST_CASE_HOLDER_H

#include "ICppTestCaseHolder.h"
#include "ICppTestCase.h"
#include "ICppTestFixture.h"


namespace CppTest {

///--------------------------------------------------------------------------------------
///
///	@brief	Associates the test pointer with the Case object that stores test results
///
///--------------------------------------------------------------------------------------
class TestCaseHolder : public CppTest::ITestCaseHolder {

public:

	/// @brief	Constructor
	/// @param	testPtr	Pointer to the test method
	/// @param	name	Test name
	/// @param	description	Test description
	TestCaseHolder(
		IFixture::Ifixture_method_ptr testPtr, 
		const mr_utils::mr_string& name, 
		const mr_utils::mr_string& description);


	/// @brief	Destructor
	virtual ~TestCaseHolder();


	/// @brief	Return the test method pointer
	virtual IFixture::Ifixture_method_ptr Pointer() const;


	/// @brief	Return the test data capture object
	virtual ICase* Data() const;


	/// @brief	Reset the test case data object to non run state
	virtual void Reset();


private:
	IFixture::Ifixture_method_ptr	m_test;		///< Pointer to the test method
	ICase*							m_testData;	///< Pointer to the test data capture object

	/// @brief	Constructor
	TestCaseHolder() {
	}


	TestCaseHolder(const ITestCaseHolder&) {
	}

};


} // end namespace cppTest


#endif

