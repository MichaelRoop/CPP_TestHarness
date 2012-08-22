///--------------------------------------------------------------------------------------
/// @file	mr_buildColumnValueString.h
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


#include "mr_string.h"
#include "mr_sstream.h"
#include "mr_fieldPair.h"


namespace mr_test
{

///--------------------------------------------------------------------------------------
/// @brief	Functor to Add a value to the value string on each iteration.
///
/// You can use this with the std::for each
class buildColumnValueString //: public iBuildColumnValueString
{
public:

	/// @brief	Constructor.
	///
	/// @param	os			The output stringstream.
	/// @param	delimiter	The delimiter between fields.
	/// @param	strQuotes	The string delimiter character.
	buildColumnValueString( 
		mr_utils::mr_stringstream&	os,
		const mr_utils::mr_string&	delimiter,
		const mr_utils::mr_string&	strQuotes
	);


	/// @brief	Function operator called on each iteration.
	///
	/// @param	field	The current field at iteration.
	virtual void operator () ( const FieldPair& field );

protected:

	mr_utils::mr_stringstream&	m_os;
	mr_utils::mr_string			m_delimiter;
	mr_utils::mr_string			m_strQuotes;
	int							m_count;


	/// @brief	Handles the building of column data.
	//
	/// @param	field	The current field at iteration.
	virtual void build( const FieldPair& field ) = 0;


	/// @brief	Helper function to concatenate string values to the value string
	///			with the proper string delimiter.
	///
	///	@param	str	The string to concatenate.
	void concatenateStr( const mr_utils::mr_string& str );
};

} // end namespace

#endif
