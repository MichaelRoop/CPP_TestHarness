///--------------------------------------------------------------------------------------
/// @file	mr_iniInputLine.h
/// @brief	Encapsulates the logic of parsing and identifying the type of data.
///
///	The text string will either indicate that it is a section identifier or a
/// key value pair line, or a comment line, or other.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_INI_INPUT_LINE_H)
#define MR_INI_INPUT_LINE_H

#include "MrTestUtilsDefine.h"
#include "mr_string.h"

namespace mr_inireader {

/// @brief	Ini file reader.
class CPPTESTUTILS_API iniInputLine {
public:

	typedef enum _lineTypeData {
		BLANK,
		COMMENT,
		SECTION,
		NODE,
		GARBAGE,
		UNDEFINED
	} LINE_TYPE;

	/// @brief	Constructor.
	iniInputLine( );


	/// @brief	Constructor.
	///
	/// @param	str	The string to parse and identify.
	iniInputLine( const mr_utils::mr_string& str );


	/// @brief	Initialise the object with the string.
	///
	/// @param	str	The string to parse and identify.
	///
	/// @return	The line type as identified by parsing.
	LINE_TYPE init(  const mr_utils::mr_string& str );


	/// @brief	The first value created by parsing the line string.
	///
	/// This would be the only value for Section, the key name for
	///	a node, and the comment or garbage value for those types of lines.
	///
	/// @return	The first value.
	const mr_utils::mr_string& firstValue() const;


	/// @brief	The second value created by parsing the line string.
	///
	/// This would only apply to nodes and it would correspond to the value of
	///	the key value pair.
	///
	/// @return	The second value.
	const mr_utils::mr_string& secondValue() const;


	/// @brief	indicates the type of line that was parsed.
	///
	/// @return	Indicates the type of line that was parsed.
	LINE_TYPE type() const;

private:

	mr_utils::mr_string	m_firstValue;	///< The results of the parsing.
	mr_utils::mr_string	m_secondValue;	///< The results of the parsing.
	LINE_TYPE			m_type;			///< The parsed line type.


	void  CheckIfBlank( const mr_utils::mr_string& str );


	void  CheckIfComment( const mr_utils::mr_string& str );


	/// @brief	A static function to encapsulate the logic of determining when a valid
	///			section name is contained in a string.
	///
	/// Here are the steps to validate.											\n
	/// 1. The string is trimed	before calling.									\n
	/// 2. The first char must be '[' and the last ']'							\n
	/// 3. The brackets are removed and the contents trimmed.					\n
	/// 4. If the remainder has characters left it is returned as section name	\n
	///
	/// @param	str	The string to validate.
	void CheckIfSectionName( const mr_utils::mr_string& str );


	void CheckIfNode( const mr_utils::mr_string& str );


	void CheckIfGarbage( const mr_utils::mr_string& str );

};


}

#endif