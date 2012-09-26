///--------------------------------------------------------------------------------------
/// @file	MrTestBuildColumnValueString.h
/// @brief	Builds strings with for column information.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_BUILD_COLUMN_VALUE_STRING_H)
#define MR_BUILD_COLUMN_VALUE_STRING_H


#include "MrTestFieldPair.h"
#include "mr_string.h"
#include "mr_sstream.h"


namespace MrTest {

///--------------------------------------------------------------------------------------
/// @brief	Functor to Add a value to the value string on each iteration.
///
/// You can use this with the std::for each
class BuildColumnValueString {
public:

	/// @brief	Constructor.
	///
	/// @param	os			The output stringstream.
	/// @param	delimiter	The delimiter between fields.
	/// @param	strQuotes	The string delimiter character.
	BuildColumnValueString( 
		mr_utils::mr_stringstream&	os,
		const mr_utils::mr_string&	delimiter,
		const mr_utils::mr_string&	strQuotes
	);


	/// @brief	Function operator called on each iteration.
	///
	/// @param	field	The current field at iteration.
	virtual void operator () (const MrTest::FieldPair& field);

protected:
	mr_utils::mr_stringstream&	m_os;
	mr_utils::mr_string			m_delimiter;
	mr_utils::mr_string			m_strQuotes;
	int							m_count;


	/// @brief	Handles the building of column data.
	//
	/// @param	field	The current field at iteration.
	virtual void Build(const FieldPair& field) = 0;


	/// @brief	Helper function to concatenate string values to the value string
	///			with the proper string delimiter.
	///
	///	@param	str	The string to concatenate.
	void ConcatenateStr(const mr_utils::mr_string& str);
};

} // end namespace

#endif
