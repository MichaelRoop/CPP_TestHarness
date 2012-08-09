///--------------------------------------------------------------------------------------
/// @file	mr_threadFunctions.h
/// @brief	Cross platform thread functions.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_threadDefines.h"

#if defined(_WIN32)  || defined(__WIN32__) || defined(WIN32) 
#else
	#include <Time.h>
#endif

#include "mr_threadFunctions.h"


namespace mr_threads
{


void MRSleep( int milliseconds )
{
#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
	::Sleep( milliseconds );
#else
	timeval t;
	t.tv_sec	= milliseconds/1000;
	t.tv_usec	= ( milliseconds * 1000 ) % 1000000;

	select( 0, (fd_set*)NULL, (fd_set*)NULL, (fd_set*)NULL, &t );
#endif
}




} // end mr_threads namespace


