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

#include "CppTestUtilsDefine.h"
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
CPPTESTUTILS_API mr_string TrimRight( const mr_string& str );


/// @brief	Function to trim white space from the left of a string.
///
/// @param	str	The string to trim.
///
/// @return	A copy of the trimmed string.
CPPTESTUTILS_API mr_string TrimLeft( const mr_string& str );


/// @brief	Function to trim white space from the left and right of a string.
///
/// @param	str	The string to trim.
///
/// @return	A copy of the trimmed string.
CPPTESTUTILS_API mr_string Trim( const mr_string& str );


/// @brief	Function to extract the file name from a string which may include the path.
///
/// @param	pathAndFile	The string which includes the fully defined file name and path.
///
/// @return	A copy of the string with only the file name.
CPPTESTUTILS_API std::string ExtractFileName(const std::string& pathAndFile);


/// @brief	Function to extract the file name from a string which may include the path.
///
/// @param	pathAndFile	The string which includes the fully defined file name and path.
///
/// @return	A copy of the string with only the file name.
CPPTESTUTILS_API std::wstring ExtractFileName(const std::wstring& pathAndFile);


/// @brief	Function to convert a wide string with only ANSII characters to narrow.
///
/// @param	str	The string to convert.
///
/// @return	A copy of the string converted to narrow char.
CPPTESTUTILS_API std::string WideToNarrowString( const std::wstring& str );


/// @brief	Function to convert a narrow string to wide.
///
/// @param	str	The string to convert.
///
/// @return	A copy of the string converted to wide char.
CPPTESTUTILS_API std::wstring NarrowToWideString( const std::string& str );


/// @brief	Function to tokenize a string by calling it repeatedly.
///
/// @param	currentPos	The current position of the parsing. This has to be initialised to 
///						0 before the first call.
/// @param	str			The complete string to tokenize.
/// @param	token		A holder to receive the extracted token.
/// @param	delimiter	The char delimiter that defines the boundry of the next token.
///
/// @return	true if a new token has been found, otherwise false.
CPPTESTUTILS_API bool MrTokenize( 
	mr_string::size_type&	currentPos, 
	const mr_string&		str, 
	mr_string&				token, 
	mr_char					delimiter 
);



/// @brief	Function to substring a string. Needed because reference to the npos causing 
///			a link failure
/// @param	pos	The start position 0 indexed.
/// @param	length	The length of the substring.
/// @return	the substring
CPPTESTUTILS_API mr_utils::mr_string SubString(
	const mr_utils::mr_string& s, 
	mr_utils::mr_string::size_type pos, 
	mr_utils::mr_string::size_type length);


/// @brief	Function to substring a string from pos to end of string. Needed because reference 
//			to the npos causing a link failure
/// @param	pos	The start position 0 indexed.
/// @return	the substring
CPPTESTUTILS_API mr_utils::mr_string SubString(const mr_utils::mr_string& s, mr_utils::mr_string::size_type pos);


/// @ replace the static npos with a function that returns the same value. The function will be exported
CPPTESTUTILS_API mr_utils::mr_string::size_type StrNPos();


/// @brief	Function to replace find. Needed because reference to the npos causing a link failure
/// @param	pos	The start position 0 indexed.
CPPTESTUTILS_API std::string::size_type Find(const std::string& s, const std::string pattern, std::string::size_type pos);


/// @brief	Contain function
CPPTESTUTILS_API bool Contains(const std::string& s, const std::string pattern);


/// @brief	Contain function
CPPTESTUTILS_API bool Contains(const std::wstring& s, const std::wstring pattern);


/// @brief	Convert a char* to mr_string. Useful for dealing with hard coded types
//			as they interact with the wide/narrow mr_string in the system
/// @param	value	The value to tranform
CPPTESTUTILS_API mr_utils::mr_string ToMrString(const char* value);


/// @brief	Convert a char* to mr_string. Useful for dealing with hard coded types
//			as they interact with the wide/narrow mr_string in the system
/// @param	value	The value to tranform
CPPTESTUTILS_API mr_utils::mr_string ToMrString(const wchar_t* value);


/// @brief	Convert a char* to mr_string. Useful for dealing with hard coded types
//			as they interact with the wide/narrow mr_string in the system
/// @param	value	The value to tranform
CPPTESTUTILS_API mr_utils::mr_string ToMrString(const std::string& value);


/// @brief	Convert a char* to mr_string. Useful for dealing with hard coded types
//			as they interact with the wide/narrow mr_string in the system
/// @param	value	The value to tranform
CPPTESTUTILS_API mr_utils::mr_string ToMrString(const std::wstring& value);


/// @brief	Convert to a char* from mr_string. Useful for dealing with returns requiring 
///			hard coded types as they interact with the wide/narrow mr_string in the system
///			The argument is hard coded to handle one possible form of the mr_string
/// @param	value	The value to tranform
CPPTESTUTILS_API std::string ToCharPtr(const std::string& value);


/// @brief	Convert to a char* from mr_string. Useful for dealing with returns requiring 
///			hard coded types as they interact with the wide/narrow mr_string in the system
///			The argument is hard coded to handle one possible form of the mr_string
/// @param	value	The value to tranform
CPPTESTUTILS_API std::string ToCharPtr(const std::wstring value);


} // end namespace.

#endif
