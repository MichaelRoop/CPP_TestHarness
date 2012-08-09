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


#include <sstream>


namespace mr_utils
{

#if defined(MR_USE_WIDE_STR)
	typedef std::wstringstream	mr_stringstream;
	typedef std::wistringstream	mr_istringstream;
	typedef std::wostringstream	mr_ostringstream;
#else
	typedef std::stringstream	mr_stringstream;
	typedef std::istringstream	mr_istringstream;
	typedef std::ostringstream	mr_ostringstream;
#endif

} // end namespace


#endif
