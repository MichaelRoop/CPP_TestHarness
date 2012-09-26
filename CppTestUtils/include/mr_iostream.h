///--------------------------------------------------------------------------------------
/// @file	mr_iostream.h
/// @brief	Cross char witdh defines for io streams.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_IOSTREAM_H)
#define MR_IOSTREAM_H

#include "MrTestUtilsDefine.h"
#include <iostream>
#include <ostream>

namespace mr_utils {

#if defined(MR_USE_WIDE_STR)
	typedef std::wostream	mr_ostream;
	#define mr_cout			std::wcout
#else
	typedef std::ostream	mr_ostream;
	#define mr_cout			std::cout
#endif

}

// Force export of i and o stream template class with different char types
//#if defined(WIN32) 
//	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_ostream<wchar_t, std::char_traits<wchar_t> >;
//	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_ostream<wchar_t, std::char_traits<wchar_t> >;
//	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_istream<char, std::char_traits<char> >;
//	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_ostream<char, std::char_traits<char> >;
//#endif


#endif
