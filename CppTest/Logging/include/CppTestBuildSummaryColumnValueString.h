///--------------------------------------------------------------------------------------
/// @file	CppTestBuildSummaryColumnValueString.h
/// @brief	Builds strings with for summary columns.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_BUILD_SUMMARY_COLUMN_VALUE_STRING_H)
#define CPP_TEST_BUILD_SUMMARY_COLUMN_VALUE_STRING_H


#include "CppTestBuildColumnValueString.h"


namespace MrTest {

class ILog;	///< Forward declaration of iTestLog interface.


///--------------------------------------------------------------------------------------
/// @brief	Functor to Add a value to the value string on each iteration.
///
/// You can use this with the std::for each
class BuildSummaryColumnValueString : public BuildColumnValueString
{

public:

	/// @brief	Constructor.
	///
	/// @param	os			The output stringstream.
	/// @param	delimiter	The delimiter between fields.
	/// @param	strQuotes	The string delimiter character.
	/// @param	theLog		The iTestLog to query for the column data.
	BuildSummaryColumnValueString( 
		mr_utils::mr_stringstream&	os,
		const mr_utils::mr_string&	delimiter,
		const mr_utils::mr_string&	strQuotes,
		MrTest::ILog*				theLog 
	);

protected:

	MrTest::ILog* m_log; ///< Pointer to the testLog;


	/// @brief	Handles the building of column data.
	//
	/// @param	field	The current field at iteration.
	virtual void Build(const MrTest::FieldPair& field);
};

} // end namespace

#endif

