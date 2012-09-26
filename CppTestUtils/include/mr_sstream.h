///--------------------------------------------------------------------------------------
/// @file	mr_sstream.h
/// @brief	Cross char witdh defines for string stream class.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_SSTREAM_H)
#define MR_SSTREAM_H

#include "MrTestUtilsDefine.h"

#include <sstream>

namespace mr_utils {

// defines a string stream that is wide or narrow depending on MR_USE_WIDE_STR define
#if defined(MR_USE_WIDE_STR)
	typedef std::wstringstream	mr_stringstream;
	typedef std::wistringstream	mr_istringstream;
	typedef std::wostringstream	mr_ostringstream;
#else
	typedef std::stringstream	mr_stringstream;
	typedef std::istringstream	mr_istringstream;
	typedef std::ostringstream	mr_ostringstream;
#endif


/// @brief	Rest the mr_stringstream so it can be reused
///
/// @param	ss	The mr_stringstream to reset
CPPTESTUTILS_API void ResetStringStream(mr_stringstream& ss); 


// Force export of std string stream template classe with different char types 
#if defined(WIN32) 
	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_stringstream<char, std::char_traits<char>, std::allocator<char> >;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_stringstream<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >;
#endif



} // end namespace


#endif
