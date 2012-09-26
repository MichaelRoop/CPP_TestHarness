///--------------------------------------------------------------------------------------
/// @file	MrTestListBuilder.h
/// @brief	
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_LIST_BUILDER_H)
#define MR_TEST_LIST_BUILDER_H

#include "IMrTestListBuilder.h"

namespace MrTest {

///--------------------------------------------------------------------------------------
/// 
/// @brief	A Singleton class to drive the test case architecture.
///
///--------------------------------------------------------------------------------------
class MRTESCASE_API ListBuilder : public MrTest::IListBuilder {
public:

	/// @brief	Process the test cases using the vector of info objects that were assembled
	/// @param	list	The test fixture info objects and their tests
	virtual std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> > 
		Build(MrTest::IScriptReader& theReader) const;

};

} // end namesapce

// Force export of class with std objects
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::allocator< mr_utils::SharedPtr<MrTest::ListBuilder> >;
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::vector< mr_utils::SharedPtr<MrTest::ListBuilder> >;

#endif

