///--------------------------------------------------------------------------------------
/// @file	mr_event.cpp
/// @brief	Cross platform event mechanism.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_event.h"

namespace mr_threads
{

mr_event::mr_event( bool isAutomaticReset ) 
:	m_handle( NULL ),
	m_auto( isAutomaticReset ),
	m_signaled( false )

{
#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
	m_handle = ::CreateEvent( NULL, !isAutomaticReset, FALSE, NULL );
#else
	pthread_cond_init( &m_handle, (pthread_cond_attr*)NULL );
	/// @todo Check Thread attributes.
#endif
}


mr_event::~mr_event()
{
#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
	::CloseHandle( m_handle );
#else
	pthread_cond_destroy( &m_handle );
#endif
}


void mr_event::Signal()
{
#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
	::SetEvent( m_handle );
#else
	mr_mutexLock L( m_mutex );
	m_signaled = true;
	if (m_auto)
	{
		pthread_cond_signal( &m_handle );
	}
	else
	{
		pthread_cond_broadcast( &m_handle );
	}
#endif
}


void mr_event::Reset()
{
#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
	::ResetEvent( m_handle );
#else
	mr_mutexLock L( m_mutex );
	m_signaled = false;
#endif
}


void mr_event::Wait()
{
#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
	::WaitForSingleObject( m_handle, INFINITE );
#else
	mr_mutexLock L( m_mutex );

	// Signaled is false until the event is signaled so it will wait in the loop. It will
	// be set to true for auto events.  For manual ones, it requires the user to call the
	// Reset method directly.  Attempting to wait again before Reset will drop through
	// immediately.
	while (!m_signaled)
	{
		pthread_cond_wait( &m_handle, &m_mutex.m_mutex );
	}

	this->SetSignaledFlag();
#endif
}


EV_TIMED_WAIT_RETURN mr_event::Wait( int ms )
{
#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
	int ret = ::WaitForSingleObject( m_handle, static_cast<DWORD>( ms ) );
	switch( ret )
	{
	case WAIT_OBJECT_0:
		return EV_SIGNALED;
	case WAIT_TIMEOUT:
		return EV_TIMEOUT;
	default:
		return EV_ERROR;
	}
#else
	mr_mutexLock L( m_mutex );
	
	// The value is set as signaled in case it is a manual event that has not been Reset.
	int	retVal = 0;	

	// Signaled is false until the event is signaled so it will wait in the loop. It will
	// be set to true for auto events.  For manual ones, it requires the user to call the
	// Reset method directly.  Attempting to wait again before Reset will drop through
	// immediately.
	while (!m_signaled)
	{
		timeval t;
		t.tv_sec	= milliseconds/1000;
		t.tv_usec	= ( milliseconds * 1000 ) % 1000000;

		retVal = pthread_cond_timedwait( &m_handle, &m_mutex.m_mutex, &t );
	}

	this->SetSignaledFlag();

	// Return based on the timed wait or default signaled.
	switch( ret )
	{
	case 0:
		return EV_SIGNALED;
	case ETIMEDOUT:
		return EV_TIMEOUT;
	default:
		return EV_ERROR;
	}
#endif
}


bool mr_event::IsSignaled()
{
#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
	return ::WaitForSingleObject( m_handle, 0 ) != WAIT_TIMEOUT;
#else
	mr_mutexLock L( m_mutex );

	bool signaled = m_signaled;
	if (m_signaled && m_auto)
	{
		m_signaled = false;
	}
	return signaled;
#endif
}


void mr_event::SetSignaledFlag()
{
#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
#else
	// Nix only, set signaled flag for automatic events.
	if (m_auto)
	{
		m_signaled = false;
	}
#endif
}


} // end mr_threads namespace


