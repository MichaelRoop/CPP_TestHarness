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

#include <iostream>

namespace mr_utils
{

#if defined(MR_USE_WIDE_STR)
	typedef std::wostream	mr_ostream;
	#define mr_cout			std::wcout
#else
	typedef std::ostream	mr_ostream;
	#define mr_cout			std::cout
#endif


}


#endif
