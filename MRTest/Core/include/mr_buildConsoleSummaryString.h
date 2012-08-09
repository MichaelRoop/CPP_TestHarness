///--------------------------------------------------------------------------------------
/// @file	mr_BuildConsoleSummaryString.h
/// @brief	Builds strings with for summary columns.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_BUILD_CONSOLE_SUMMARY_STRING_H)
#define MR_BUILD_CONSOLE_SUMMARY_STRING_H


#include "mr_buildSummaryColumnValueString.h"


namespace mr_test
{

///--------------------------------------------------------------------------------------
/// @brief	Functor to Add a value to the value string on each iteration.
///
/// You can use this with the std::for each
class buildConsoleSummaryString : public buildSummaryColumnValueString
{

public:

	/// @brief	Function operator called on each iteration.
	///
	/// @param	field	The current field at iteration.
	void operator () ( const FieldPair& field );


	/// @brief	Constructor.
	///
	/// @param	os			The output stringstream.
	/// @param	delimiter	The delimiter between fields.
	/// @param	strQuotes	The string delimiter character.
	/// @param	theLog		The iTestLog to query for the column data.
	buildConsoleSummaryString( 
		mr_utils::mr_stringstream&	os,
		const mr_utils::mr_string&	delimiter,
		const mr_utils::mr_string&	strQuotes,
		iTestLog*					theLog 
	);
};


} // end namespace

#endif

