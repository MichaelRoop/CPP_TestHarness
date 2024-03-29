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
#include "mr_string.h"
#include "mr_exception.h"
#include "mr_defines.h"
#include "mr_sstream.h"
#include "mr_toStream.h"
#include "mr_functors.h"

#include <algorithm>


namespace mr_utils {

mr_utils::mr_string TrimRight(const mr_string& str) {
	if (str.empty()) {
		return str;
	}

	mr_string::size_type end = str.find_last_not_of(  L(" \n\t\r") );

	// TODO - follow up. Seems we can use the npos within the DLL
	//if (end == mr_utils::StrNPos()) {
	if (end == mr_utils::mr_string::npos) {
		// only blanks in string.
		return str;
	}
	return str.substr( 0, end + 1 ); 
}


mr_utils::mr_string TrimLeft(const mr_string& str) {
	if (str.empty()) {
		return str;
	}

	mr_string::size_type start = str.find_first_not_of( L(" \n\t\r") );
	if (start == mr_utils::StrNPos()) {
		// only blanks in string.
		return str;
	}
	return str.substr(start); 
}



mr_utils::mr_string Trim(const mr_string& str) {
	return TrimLeft( TrimRight( str ) );
}


std::string ExtractFileName(const std::string& pathAndFile) {
	if (pathAndFile.empty()) {
		return pathAndFile;
	}

	std::string::size_type pos = pathAndFile.find_last_of( "\\/" );
	if (pos == mr_utils::StrNPos()) {
		return pathAndFile;
	}

	// If found, check that it is not the only character.
	mr_exception::assertCondition( pathAndFile.length() > 1, FL, L("Path and file only contains slashes") );
	return pathAndFile.substr( pos + 1 ); 
}


std::wstring ExtractFileName(const std::wstring& pathAndFile) {
	if (pathAndFile.empty()) {
		return pathAndFile;
	}

	std::string::size_type pos = pathAndFile.find_last_of( L"\\/" );
	if (pos == mr_utils::StrNPos()) {
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


bool MrTokenize(mr_string::size_type& currentPos, const mr_string& str, mr_string& token, mr_char delimiter) {
	if (currentPos == mr_utils::StrNPos() || currentPos > str.length() - 1 ) {
		return false;
	}

	// End case Skip leading delimiters
	mr_exception::assertCondition(currentPos < str.length(), FL, L("Exceeded receptor limits"));

	if (str[currentPos] == delimiter) {
		currentPos = str.find_first_not_of( delimiter, currentPos );
		if (currentPos == mr_utils::StrNPos()) {
			// End case - string only has delimiters.
			return false;
		}
	}

	token.clear();

	mr_string::size_type delimiterPos = str.find_first_of( &delimiter, currentPos );
	if (delimiterPos == mr_utils::StrNPos()) {
		// If the delimiter is not found then the entire remaining string is the token.
		mr_string::size_type tmp = currentPos;
		
		// Move current position passed length of string to fail on next iteration
		currentPos = str.length() ;
		token = str.substr( tmp );
	} 
	else {
		// Get token and skip to next non delimiter position.
		token = str.substr( currentPos, delimiterPos - currentPos );
		currentPos = str.find_first_not_of( delimiter, delimiterPos );
	}
	return true;
}


mr_utils::mr_string SubString(
	const mr_utils::mr_string& s, 
	mr_utils::mr_string::size_type pos, 
	mr_utils::mr_string::size_type length) {
	
	return s.substr(pos, length); // Now it is working. Go figure

	//if(pos >= s.length()) {
	//	throw mr_utils::mr_exception(_FL_, _L_("The position is passed the end of line"));
	//}

	//if (length == mr_utils::StrNPos()) {
	//	length = s.length() - pos;
	//}

	//if((pos + length) > s.length()) {
	//	throw mr_utils::mr_exception(_FL_, _L_("The start position plus length requested is passed the end of line"));
	//}

	//// bit of pointer arithmetic since we cannot use the substring
	//mr_utils::mr_string copy;
	//copy.append((s.c_str() + pos), length);
	//return copy;
}


mr_utils::mr_string SubString(const mr_utils::mr_string& s, mr_utils::mr_string::size_type pos) {
	//return mr_utils::SubString(s, pos, mr_utils::StrNPos());
	return s.substr(pos);
}


// TODO - validate this.  Seems to be enough to access the npos within the DLL and send back the value 
// via an exported function
mr_utils::mr_string::size_type StrNPos() {
	return mr_utils::mr_string::npos;
}


std::string::size_type Find(const std::string& s, const std::string pattern, std::string::size_type pos) {
	return s.find(pattern, pos);
}


bool Contains(const std::string& s, const std::string pattern) {
	return s.find(pattern) != std::string::npos;
}


bool Contains(const std::wstring& s, const std::wstring pattern) {
	return s.find(pattern) != std::wstring::npos;
}


mr_utils::mr_string ToMrString(const char* value) {
	// Convert to wide or narrow mr_string
	mr_utils::mr_stringstream ss;
	mr_utils::ToStream(ss, (value == 0 ? "" : value));
	return ss.str().c_str();
}


mr_utils::mr_string ToMrString(const wchar_t* value) {
	// Convert to wide or narrow mr_string
	mr_utils::mr_stringstream ss;
	mr_utils::ToStream(ss, (value == 0 ? L"" : value));
	return ss.str().c_str();
}


mr_utils::mr_string ToMrString(const std::string& value) {
	return mr_utils::ToMrString(value.c_str());
}


mr_utils::mr_string ToMrString(const std::wstring& value) {
	return mr_utils::ToMrString(value.c_str());
}


std::string ToCharPtr(const std::string& value) {
	return value;
}


std::string ToCharPtr(const std::wstring value) {
	return mr_utils::WideToNarrowString(value);
}





} // end namespace