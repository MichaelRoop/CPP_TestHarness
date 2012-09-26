///--------------------------------------------------------------------------------------
/// @file	IMrTestListBuilder.h
/// @brief	
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(IMR_TEST_LIST_BUILDER_H)
#define IMR_TEST_LIST_BUILDER_H

#include "MrTestDefines.h"
#include "IMrTestScriptReader.h"
#include "IMrTestFixtureInfoObject.h"
#include "mr_SharedPtr.h"
#include <vector>

namespace MrTest {

///--------------------------------------------------------------------------------------
/// 
/// @brief	Build a list of tests grouped by fixture
///
///--------------------------------------------------------------------------------------
class MRTESCASE_API IListBuilder {
public:

	/// @brief	Process the test cases using the vector of info objects that were assembled
	/// @param	list	The test fixture info objects and their tests
	virtual std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> > 
		Build(MrTest::IScriptReader& theReader) const = 0;

};

} // end namesapce

// Force export of class with std objects
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::allocator< mr_utils::SharedPtr<MrTest::IListBuilder> >;
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::vector< mr_utils::SharedPtr<MrTest::IListBuilder> >;


#endif
