///--------------------------------------------------------------------------------------
/// @file	mr_threadDefines.h
/// @brief	Cross platform defines for thread library.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_THREAD_DEFINES_H)
#define MR_THREAD_DEFINES_H

#if defined(_WIN32)  || defined(__WIN32__) || defined(WIN32) 
	#pragma message("Compiling under Win 32")

	#if !defined(WINDOWS_LEAN_AND_MEAN)
		#define WINDOWS_LEAN_AND_MEAN
	#endif
	#include <windows.h>
	#include <process.h>
	#undef WINDOWS_LEAN_AND_MEAN
#else
	#pragma message("Compiling under non windows platform")
	#include <unix.h>
	#include <pthread.h>
#endif



namespace mr_threads
{

#if defined(_WIN32)  || defined(__WIN32__) || defined(WIN32) 
	#define MR_MUTEX_OBJ CRITICAL_SECTION
	#define MR_THREAD_HANDLE HANDLE
	#define MR_EVENT_HANDLE HANDLE
	#define MR_THREAD_CALL_TYPE __stdcall
	#define MR_DEFAULT_THREAD_PRIORITY	THREAD_PRIORITY_NORMAL
#else
	#pragma message("Compiling under non windows platform")
	#define MR_MUTEX_OBJ pthread_mutex_t
	#define MR_EVENT_HANDLE pthread_cond_t
	#define MR_THREAD_HANDLE pthread_t
	#define MR_STD_CALL 

	/// @todo	Determine a good general normal thread priority number for NIX
	#define MR_DEFAULT_THREAD_PRIORITY	20
#endif


	/// @brief	Possible returns for timed wait.
	typedef enum
	{
		EV_SIGNALED,		///< The event was signaled.
		EV_TIMEOUT,			///< The event timed out.
		EV_ERROR			///< The event encountered an error.
	} EV_TIMED_WAIT_RETURN;



	/// @todo	Define for common cross platform normal thread priority.
	// These are the win priorities
	// THREAD_PRIORITY_TIME_CRITICAL	15
	// THREAD_PRIORITY_HIGHEST			2
	// THREAD_PRIORITY_ABOVE_NORMAL		1
	// THREAD_PRIORITY_NORMAL			0
	// THREAD_PRIORITY_BELOW_NORMAL		-1
	// THREAD_PRIORITY LOWEST			-2
	// THREAD_PRIORITY_IDLE				-15




} // end mr_threads namespace


#endif
