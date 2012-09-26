///--------------------------------------------------------------------------------------
/// @file	MrTestBuildColumnInfoString.h
/// @brief	Builds strings with for column information.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_BUILD_COLUMN_INFO_STRING_H)
#define MR_TEST_BUILD_COLUMN_INFO_STRING_H


#include "MrTestFieldPair.h"
#include "mr_string.h"
#include "mr_sstream.h"


namespace MrTest {

///--------------------------------------------------------------------------------------
/// @brief	Functor to Add a value to the value string on each iteration.
///
/// You can use this with the std::for each
struct BuildColumnInfoString {
	typedef enum {
		NAME_ONLY,
		TYPE_ONLY,
		NAME_TYPE
	} ColumnInfoParts;


	/// @brief Functor constructor.
	///
	/// @param	os					The stream to receive the string.
	/// @param	nameTypeDelimiter	Delimiter between Column name and type.
	/// @param	unitDelimiter		Delimiter between info for one column.
	///	@param	parts				What column info to concatente.
	BuildColumnInfoString( 
		mr_utils::mr_stringstream& os,
		const mr_utils::mr_string&	nameTypeDelimiter,
		const mr_utils::mr_string&	unitDelimiter,
		ColumnInfoParts				parts
	);


	/// @brief	Function operator called on each iteration.
	///
	/// @param	field	The current field at iteration.
	void operator () (const FieldPair& field);

private:

	mr_utils::mr_stringstream&	m_os;				///< Stream to build string.
	mr_utils::mr_string			m_nameTypeDelimiter;///< Delimiter between names and types.	
	mr_utils::mr_string			m_unitDelimiter;	///< Delimiter between each column's info.
	ColumnInfoParts				m_parts;			///< Specifies which parts to add to string.
	int							m_count;			///< Iteration counter.
};

} // end namespace.

#endif
