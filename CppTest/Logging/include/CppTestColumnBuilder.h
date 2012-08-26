///--------------------------------------------------------------------------------------
/// @file	mr_columnBuilder.h
/// @brief	Builds strings for column headers and data.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_COLUMN_BUILDER_H)
#define CPP_TEST_COLUMN_BUILDER_H

#include "CppTestFieldPair.h"

namespace CppTest {

class ICase;	///< Forward declaration of Case class
class ILog;	///< Forward declaration of iTestLog.

//----------------------------------------------------------------------------------------
/// @brief	Class for building CSV strings.
/// 
///			Creates strings dynamicaly according to column order and formats it correctly for
///			comma delimited loading.
class ColumnBuilder {
public:

	/// @brief	Build the column header string.
	///
	/// @param	fieldInfo	Vector of that holds the field information and order.
	/// @param	delimiter	The char that delimits the header fields
	///		
	/// @return	Formated header column names string.
	static mr_utils::mr_string CreateColumnHeaders( 
		const FieldVector&			fieldInfo, 
		const mr_utils::mr_string&	delimiter 
	);


	/// @brief	Build the column header/data type string.
	///
	/// @param	fieldInfo			Vector that holds the field information and order.
	/// @param	nameTypeDelimiter	Delimiter between name and type.
	/// @param	colDelimiter		Delimiter of the column's info.
	///		
	/// @return	Formated header column names/types string.
	static mr_utils::mr_string CreateColumnNameTypeStr( 
		const FieldVector&			fieldInfo, 
		const mr_utils::mr_string&	nameTypeDelimiter, 
		const mr_utils::mr_string&	colDelimiter 
	);


	/// @brief	Build the column data string from test case.
	///
	/// @param	fieldInfo	Vector that holds the field information and order.
	/// @param	delimiter	The char that delimits the fields.
	/// @param	strQuotes	The char that starts and ends a string field value.
	/// @param	fixture		The test case fixture that holds the values.
	///		
	/// @return	Formated column data string.
	static mr_utils::mr_string CreateColumnData( 
		const FieldVector&			fieldInfo,
		const mr_utils::mr_string&	delimiter,
		const mr_utils::mr_string&	strQuotes,
		CppTest::ICase&			fixture 
	);


	/// @brief	Build the column data string from a log.
	///
	/// @param	fieldInfo	Vector that holds the field information and order.
	/// @param	delimiter	The char that delimits the fields.
	/// @param	strQuotes	The char that starts and ends a string field value.
	/// @param	theCase		The testCase that holds the values.
	///		
	/// @return	Formated column data string.
	static mr_utils::mr_string CreateColumnData( 
		const FieldVector&			fieldInfo,
		const mr_utils::mr_string&	delimiter,
		const mr_utils::mr_string&	strQuotes,
		CppTest::ILog*				theLog 
	);

};


} // end namespace

#endif
