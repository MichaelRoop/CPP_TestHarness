///--------------------------------------------------------------------------------------
/// @file	mr_fstream.h
/// @brief	Cross char witdh defines for file streams.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_FSTREAM_H)
#define MR_FSTREAM_H

#include <fstream>


namespace mr_utils
{

#if defined(MR_USE_WIDE_STR)
	typedef std::wifstream	mr_ifstream;
	typedef std::wofstream	mr_ofstream;
#else
	typedef std::ifstream	mr_ifstream;
	typedef std::ofstream	mr_ofstream;
#endif

}


#endif
