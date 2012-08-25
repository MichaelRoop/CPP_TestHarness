///--------------------------------------------------------------------------------------
/// @file	mr_string.cpp
/// @brief	Cross char witdh defines for string class.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_char.h"
#include "mr_string.h"
#include "mr_exception.h"
#include "mr_defines.h"
#include "mr_functors.h"

#include <algorithm>


	//EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> >;
	//EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_string<char, struct std::char_traits<char>, std::allocator<char> >;


//static size_t posWToForceExport = std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> >::npos;
//static size_t posNToForceExport = std::basic_string<char, struct std::char_traits<char>, std::allocator<char> >::npos;


//CPPTESTUTILS_API 
//	std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> >::size_type ziffle;
//	//std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> >::npos;


namespace mr_utils
{

	//static std::string::size_type std::string::npos nposNarrow;
	//template std::wstring::size_type std::wstring::npos;


mr_utils::mr_string TrimRight( const mr_string& str )
{
	if (str.empty())
	{
		return str;
	}

	mr_string::size_type end = str.find_last_not_of(  L(" \n\t\r") );
	if (end == mr_string::npos)
	{
		// only blanks in string.
		return str;
	}
	return str.substr( 0, end + 1 ); 
}


mr_utils::mr_string TrimLeft( const mr_string& str )
{
	if (str.empty())
	{
		return str;
	}

	mr_string::size_type start = str.find_first_not_of( L(" \n\t\r") );
	if (start == mr_string::npos)
	{
		// only blanks in string.
		return str;
	}
	return str.substr( start ); 
}



mr_utils::mr_string Trim( const mr_string& str )
{
	return TrimLeft( TrimRight( str ) );
}


std::string ExtractFileName( const std::string& pathAndFile )
{
	if (pathAndFile.empty())
	{
		return pathAndFile;
	}

	std::string::size_type pos = pathAndFile.find_last_of( "\\/" );
	if (pos == mr_string::npos )
	{
		return pathAndFile;
	}

	// If found, check that it is not the only character.
	mr_exception::assertCondition( pathAndFile.length() > 1, FL, L("Path and file only contains slashes") );
	return pathAndFile.substr( pos + 1 ); 
}


// But simple wide to narrow conversion.  No Unicode considered.  Will only 
// work with normal range of ANSII characters in wide format.
std::string WideToNarrowString( const std::wstring& str )
{
	// Create matching buffers and add null terminator char to end.
	std::vector<wchar_t> wideChars( str.length() + 1, L'\0' );
	std::vector<char> narrowChars( str.length() + 1, '\0' );
	memcpy( &wideChars[0], str.c_str(), str.length() * sizeof( wchar_t ) );

	std::for_each( wideChars.begin(), wideChars.end(), AnsiiWideCharToNarrow( narrowChars ) );
	return std::string( &narrowChars[0] );
}


// But simple narrow to wide conversion.  No Unicode considered.  Will only 
// work with normal range of ANSII characters in wide format.
std::wstring NarrowToWideString( const std::string& str )
{
	// Create matching buffers and add null terminator char to end.
	std::vector<wchar_t> wideChars( str.length() + 1, L'\0' );
	std::vector<char>	 narrowChars( str.length() + 1, '\0' );
	memcpy( &narrowChars[0], str.c_str(), str.length() );

	std::for_each( narrowChars.begin(), narrowChars.end(), NarrowCharToWide( wideChars ) );
	return std::wstring( &wideChars[0] );
}


bool MrTokenize( mr_string::size_type& currentPos, const mr_string& str, mr_string& token, mr_char delimiter )
{
	if (currentPos == mr_string::npos || currentPos > str.length() - 1 )
	{
		return false;
	}

	// End case Skip leading delimiters
	mr_exception::assertCondition( currentPos < str.length(), FL, L("Exceeded receptor limits") );

	if (str[currentPos] == delimiter)
	{
		currentPos = str.find_first_not_of( delimiter, currentPos );
		if (currentPos == mr_string::npos)
		{
			// End case - string only has delimiters.
			return false;
		}
	}

	token.clear();

	mr_string::size_type delimiterPos = str.find_first_of( &delimiter, currentPos );
	if (delimiterPos == mr_string::npos)
	{
		// If the delimiter is not found then the entire remaining string is the token.
		mr_string::size_type tmp = currentPos;
		
		// Move current position passed length of string to fail on next iteration
		currentPos = str.length() ;
		token = str.substr( tmp );
	}
	else
	{
		// Get token and skip to next non delimiter position.
		token = str.substr( currentPos, delimiterPos - currentPos );
		currentPos = str.find_first_not_of( delimiter, delimiterPos );
	}
	return true;
}




} // end namespace