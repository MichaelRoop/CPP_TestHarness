///--------------------------------------------------------------------------------------
/// @file	CppTestBuildTestCaseColumnValueString.h
/// @brief	Builds strings with for column information for test cases.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_BUILD_TEST_CASE_COLUMN_VALUE_STRING_H)
#define CPP_TEST_BUILD_TEST_CASE_COLUMN_VALUE_STRING_H

#include "CppTestBuildColumnValueString.h"

namespace MrTest {

class ICase;	///< Forward declaration of testCase.

///--------------------------------------------------------------------------------------
/// @brief	Functor to Add a value to the value string on each iteration.
///
/// You can use this with the std::for each
class BuildTestCaseColumnValueString : public BuildColumnValueString {

public:

	/// @brief	Constructor.
	///
	/// @param	os			The output stringstream.
	/// @param	delimiter	The delimiter between fields.
	/// @param	strQuotes	The string delimiter character.
	BuildTestCaseColumnValueString( 
		mr_utils::mr_stringstream&	os,
		const mr_utils::mr_string&	delimiter,
		const mr_utils::mr_string&	strQuotes,
		MrTest::ICase&				testCase 
	);

private:

	MrTest::ICase& m_testCase; ///< The testCase to log column values.


	/// @brief	Handles the building of column data.
	/// @param	field	The current field at iteration.
	virtual void Build(const MrTest::FieldPair& field);


	/// @brief	Helper function to concatenate string values to the value string
	///			with the proper string delimiter, specificaly for the verbose field.
	///	@param	str	The string to concatenate.
	void ConcatenateVerboseBufferStr(const mr_utils::mr_string& str);
};

} // end namespace

#endif

