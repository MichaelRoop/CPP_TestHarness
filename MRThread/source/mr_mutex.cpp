///--------------------------------------------------------------------------------------
/// @file	mr_mutex.cpp
/// @brief	Cross platform recursive mutex locking mechanism.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_mutex.h"

namespace mr_threads
{


mr_mutex::mr_mutex()
{
#if defined(_WIN32)  || defined(__WIN32__) || defined(WIN32) 
	InitializeCriticalSection( &m_mutex );
#else
	// Create a recursive mutex to match windows Critical Section.
	pthread_mutexattr_t attr;
	pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE );
	pthread_mutex_init( &m_mutex, attr );
#endif
}


mr_mutex::~mr_mutex()
{
#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
	DeleteCriticalSection( &m_mutex );
#else
	pthread_mutex_destroy( &m_mutex );
#endif
}


void mr_mutex::Aquire()
{
#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
	EnterCriticalSection( &m_mutex );
#else
	pthread_mutex_lock( &m_mutex );
#endif
}


void mr_mutex::Release()
{
#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
	LeaveCriticalSection( &m_mutex );
#else
	pthread_mutex_unlock( &m_mutex );
#endif
}


} // end mr_threads namespace


