///--------------------------------------------------------------------------------------
/// @file	mr_buildTestCaseColumnValueString.h
/// @brief	Builds strings with for column information for test cases.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_BUILD_TEST_CASE_COLUMN_VALUE_STRING_H)
#define MR_BUILD_TEST_CASE_COLUMN_VALUE_STRING_H

#include "mr_buildColumnValueString.h"

namespace CppTest {
	class Case;	///< Forward declaration of testCase.
}

namespace mr_test {

///--------------------------------------------------------------------------------------
/// @brief	Functor to Add a value to the value string on each iteration.
///
/// You can use this with the std::for each
class buildTestCaseColumnValueString : public buildColumnValueString
{

public:

	/// @brief	Constructor.
	///
	/// @param	os			The output stringstream.
	/// @param	delimiter	The delimiter between fields.
	/// @param	strQuotes	The string delimiter character.
	buildTestCaseColumnValueString( 
		mr_utils::mr_stringstream&	os,
		const mr_utils::mr_string&	delimiter,
		const mr_utils::mr_string&	strQuotes,
		CppTest::Case&				testCase 
	);

private:

	CppTest::Case& m_testCase; ///< The testCase to log column values.


	/// @brief	Handles the building of column data.
	//
	/// @param	field	The current field at iteration.
	virtual void build( const FieldPair& field );


	/// @brief	Helper function to concatenate string values to the value string
	///			with the proper string delimiter, specificaly for the verbose field.
	///
	///	@param	str	The string to concatenate.
	void concatenateVerboseBufferStr( const mr_utils::mr_string& str );
};

} // end namespace

#endif

