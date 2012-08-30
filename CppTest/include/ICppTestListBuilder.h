///--------------------------------------------------------------------------------------
/// @file	ICppTestListBuilder.h
/// @brief	
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_LIST_BUILDER_H)
#define ICPP_TEST_LIST_BUILDER_H

#include "CppTestCrossPlatform.h"
//#include "CppTestLogEngine.h"
#include "ICppTestScriptReader.h"
//#include "ICppTestCase.h"
//#include "ICppTestFixture.h"
//#include "ICppTestFixtureTestCaseNames.h"
//#include "ICppTestFixtureInfoObject.h"
#include "CppTestFixtureInfoObject.h"
//#include "mr_string.h"
#include "mr_SharedPtr.h"

#include <vector>

namespace CppTest {

///--------------------------------------------------------------------------------------
/// 
/// @brief	A Singleton class to drive the test case architecture.
///
///--------------------------------------------------------------------------------------
class CPPTESCASE_API IListBuilder {
public:

	/// @brief	Process the test cases using the vector of info objects that were assembled
	/// @param	list	The test fixture info objects and their tests
	virtual std::vector< mr_utils::SharedPtr<CppTest::TestFixtureInfoObject> > 
		Build(CppTest::IScriptReader& theReader) const = 0;

};

} // end namesapce

// Force export of class with std objects
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator< mr_utils::SharedPtr<CppTest::IListBuilder> >;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector< mr_utils::SharedPtr<CppTest::IListBuilder> >;


#endif
