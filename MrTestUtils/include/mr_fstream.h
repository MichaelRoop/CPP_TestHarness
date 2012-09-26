///--------------------------------------------------------------------------------------
/// @file	mr_fstream.h
/// @brief	Cross char witdh defines for file streams.
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.5
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_FSTREAM_H)
#define MR_FSTREAM_H

#include "MrTestUtilsDefine.h"
#include <fstream>

namespace mr_utils
{

// Narrow and wide type definitions
#if defined(MR_USE_WIDE_STR)
	typedef std::wifstream	mr_ifstream;
	typedef std::wofstream	mr_ofstream;
#else
	typedef std::ifstream	mr_ifstream;
	typedef std::ofstream	mr_ofstream;
#endif

}


// Force export of std file stream template classe with different char types 
#if defined(WIN32) 
	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_filebuf<wchar_t, std::char_traits<wchar_t> >;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_filebuf<char, std::char_traits<char> >;

	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_ifstream<wchar_t, std::char_traits<wchar_t> >;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_ofstream<wchar_t, std::char_traits<wchar_t> >;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_ifstream<char, std::char_traits<char> >;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_ofstream<char, std::char_traits<char> >;
#endif

#endif
