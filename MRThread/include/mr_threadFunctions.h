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
#if !defined(MR_THREAD_FUNCTIONS_H)
#define MR_THREAD_FUNCTIONS_H


namespace mr_threads
{

/// @brief	Cross platform sleep function.
///
/// @param	millisecond	Duration of sleep.
void MRSleep( int milliseconds );


} // end mr_threads namespace


#endif
