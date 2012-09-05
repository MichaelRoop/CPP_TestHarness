///--------------------------------------------------------------------------------------
/// @file	MrTestVectorLineReader.h
/// @brief	Converts a vector of lines argument to test info
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_VECTOR_FIXTURE_TEST_CASE_NAMES_READER_H)
#define MR_TEST_VECTOR_FIXTURE_TEST_CASE_NAMES_READER_H

#include "MrTestScriptReaderBase.h"
#include "ICppTestFixtureTestCaseNames.h"

#include "mr_SharedPtr.h"
#include <vector>

namespace MrTest {
	
class IFixutureTestCaseNames;

///--------------------------------------------------------------------------------------
///
/// @brief	Class to abstract the reading of a vector IFixtureTestCaseNames
///
///--------------------------------------------------------------------------------------
class VectorFixtureTestCaseNames : public MrTest::ScriptReaderBase {
public:

	/// @brief	Constructor.
	/// @param	nameDelimiter	Delimiter character to tokenize the name and 
	///							argument portion of the line.
	/// @param	argDelimiter	Delimiter to tokenize the argument portion of the
	///							line into separate arguments.
	VectorFixtureTestCaseNames(
		const std::vector< mr_utils::SharedPtr< MrTest::IFixutureTestCaseNames > >& fixtureInfos);


	/// @brief	Sets the vector state to the beginning 
	void Open();


	/// @brief	Extracts the test information from the TestFixtureinfoOjbect
	/// @param	fixtureName	Name of the fixture for the test case.
	///	@throw	Throws a scriptException on syntax failure.
	/// @return	The populated testInfoObject for the test.  If the object has no more
	///			lines the testInfoObject.isValid() will return false.
	MrTest::TestInfoObject getNextTest(mr_utils::mr_string& fixtureName);

private:
	std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> >	m_infos;

	// TODO - determine why export of iterator failing
	mr_utils::mr_string::size_type				m_fixtureIndex;
	mr_utils::mr_string::size_type				m_testCaseIndex;

};

} // end namespace

CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<mr_utils::SharedPtr<MrTest::VectorFixtureTestCaseNames> >;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<mr_utils::SharedPtr<MrTest::VectorFixtureTestCaseNames> >;

#endif
