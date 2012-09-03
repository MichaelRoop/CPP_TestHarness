///--------------------------------------------------------------------------------------
/// @file	CppTestBuildConsoleSummaryString.h
/// @brief	Builds strings with for summary columns.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_BUILD_CONSOLE_SUMMARY_STRING_H)
#define CPP_TEST_BUILD_CONSOLE_SUMMARY_STRING_H


#include "CppTestBuildSummaryColumnValueString.h"


namespace MrTest {

///--------------------------------------------------------------------------------------
/// @brief	Functor to Add a value to the value string on each iteration.
///
/// You can use this with the std::for each
class BuildConsoleSummaryString : public BuildSummaryColumnValueString {

public:

	/// @brief	Function operator called on each iteration.
	///
	/// @param	field	The current field at iteration.
	void operator () (const MrTest::FieldPair& field);


	/// @brief	Constructor.
	///
	/// @param	os			The output stringstream.
	/// @param	delimiter	The delimiter between fields.
	/// @param	strQuotes	The string delimiter character.
	/// @param	theLog		The iTestLog to query for the column data.
	BuildConsoleSummaryString( 
		mr_utils::mr_stringstream&	os,
		const mr_utils::mr_string&	delimiter,
		const mr_utils::mr_string&	strQuotes,
		MrTest::ILog*				theLog 
	);
};


} // end namespace

#endif

