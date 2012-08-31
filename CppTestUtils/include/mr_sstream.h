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

#include "CppTestUtilsDefine.h"

#include <sstream>

#if defined(WIN32) 

	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_stringstream<char, std::char_traits<char>, std::allocator<char> >;
	//EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator< std::basic_stringstream<char, std::char_traits<char>, std::allocator<char> > >;
	//EXP_TEMPLATE template class CPPTESTUTILS_API std::vector< std::basic_stringstream<char, std::char_traits<char>, std::allocator<char> > >;

	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_stringstream<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >;
	//EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator< std::basic_stringstream<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > >;
	//EXP_TEMPLATE template class CPPTESTUTILS_API std::vector< std::basic_stringstream<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > , std::allocator< std::basic_stringstream<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > > > ;
#endif

namespace mr_utils {


#if defined(MR_USE_WIDE_STR)
	typedef std::wstringstream	mr_stringstream;
	typedef std::wistringstream	mr_istringstream;
	typedef std::wostringstream	mr_ostringstream;
#else
	typedef std::stringstream	mr_stringstream;
	typedef std::istringstream	mr_istringstream;
	typedef std::ostringstream	mr_ostringstream;
#endif


#if defined(WIN32) 

#endif

/// @brief	Rest the mr_stringstream so it can be reused
///
/// @param	ss	The mr_stringstream to reset
CPPTESTUTILS_API void ResetStringStream(mr_stringstream& ss); 


} // end namespace


#endif
