///--------------------------------------------------------------------------------------
/// @file	mr_string.h
/// @brief	Cross char witdh defines for string class.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_STRING_H)
#define MR_STRING_H


#include <string>
#include "mr_char.h"

namespace mr_utils
{

#if defined(MR_USE_WIDE_STR)
	typedef std::wstring	mr_string;
#else
	typedef std::string		mr_string;
#endif


/// @brief	Function to trim white space from the right of a string.
///
/// @param	str	The string to trim.
///
/// @return	A copy of the trimmed string.
mr_string TrimRight( const mr_string& str );


/// @brief	Function to trim white space from the left of a string.
///
/// @param	str	The string to trim.
///
/// @return	A copy of the trimmed string.
mr_string TrimLeft( const mr_string& str );


/// @brief	Function to trim white space from the left and right of a string.
///
/// @param	str	The string to trim.
///
/// @return	A copy of the trimmed string.
mr_string Trim( const mr_string& str );


/// @brief	Function to extract the file name from a string which may include the path.
///
/// @param	pathAndFile	The string which includes the fully defined file name and path.
///
/// @return	A copy of the string with only the file name.
std::string ExtractFileName( const std::string& pathAndFile );


/// @brief	Function to convert a wide string with only ANSII characters to narrow.
///
/// @param	str	The string to convert.
///
/// @return	A copy of the string converted to narrow char.
std::string WideToNarrowString( const std::wstring& str );


/// @brief	Function to convert a narrow string to wide.
///
/// @param	str	The string to convert.
///
/// @return	A copy of the string converted to wide char.
std::wstring NarrowToWideString( const std::string& str );


/// @brief	Function to tokenize a string by calling it repeatedly.
///
/// @param	currentPos	The current position of the parsing. This has to be initialised to 
///						0 before the first call.
/// @param	str			The complete string to tokenize.
/// @param	token		A holder to receive the extracted token.
/// @param	delimiter	The char delimiter that defines the boundry of the next token.
///
/// @return	true if a new token has been found, otherwise false.
bool MrTokenize( 
	mr_string::size_type&	currentPos, 
	const mr_string&		str, 
	mr_string&				token, 
	mr_char					delimiter 
);




} // end namespace.






#endif
