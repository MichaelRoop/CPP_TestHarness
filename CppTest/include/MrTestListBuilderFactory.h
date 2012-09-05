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
#if !defined(MR_TEST_LIST_BUILDER_FACTORY_H)
#define MR_TEST_LIST_BUILDER_FACTORY_H

#include "CppTestDefines.h"
#include "ICppTestFixtureInfoObject.h"
#include "mr_SharedPtr.h"
#include <vector>

namespace MrTest {

class IFixutureTestCaseNames;

///--------------------------------------------------------------------------------------
/// 
/// @brief	Build a list of tests grouped by fixture
///
///--------------------------------------------------------------------------------------
class CPPTESCASE_API ListBuilderFactory {
public:

	/// @brief	Build a test list from file
	/// @param	filename	The name of the file with the list
	static std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> > 
		FromFile(
			const mr_utils::mr_string&	filename, 		
			mr_utils::mr_char			nameDelimiter = _L_('$'),
			mr_utils::mr_char			argDelimiter = _L_('|'));

	/// @brief	Build a test list from a single line
	/// @param	line	The line with test information to process
	static std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> > 
		FromLine(const mr_utils::mr_string& line);


	/// @brief	Build a test list from a vector of lines, one test per line
	/// @param	lines	The vector with the test lines 
	static std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> > 
		FromLines(
			const std::vector<mr_utils::mr_string>&	lines,
			mr_utils::mr_char						nameDelimiter = _L_('$'),
			mr_utils::mr_char						argDelimiter = _L_('|'));


	/// @brief	Build a test list from a vector Fixture Test Case Names
	/// @param	lines	The vector with the test case names objects 
	static std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> > 
		FromTestCaseNames(const std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> >& testCaseNames);

};

} // end namesapce

// Force export of class with std objects
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator< mr_utils::SharedPtr<MrTest::ListBuilderFactory*> >;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector< mr_utils::SharedPtr<MrTest::ListBuilderFactory*> >;


#endif
