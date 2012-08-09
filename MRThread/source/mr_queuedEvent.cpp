///--------------------------------------------------------------------------------------
/// @file	mr_queuedEvent.cpp
/// @brief	Cross platform event mechanism that remembers all its signals.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_queuedEvent.h"
#include "mr_mutexLock.h"

namespace mr_threads
{


mr_queuedEvent::mr_queuedEvent() 
:	m_event( true ),
	m_count( 0 )
{
}


mr_queuedEvent::~mr_queuedEvent()
{
}


void mr_queuedEvent::Signal()
{
	mr_mutexLock L( m_mutex );
	if (++m_count == 1)
	{
		m_event.Signal();
	}
}


void mr_queuedEvent::SignalNext()
{
	if (--m_count > 0)
	{
		// If queued signals left pulse event so that next wait will fall through.
		m_event.Signal();
	}
}


void mr_queuedEvent::Wait()
{
	mr_mutexLock L( m_mutex );
	m_event.Wait();
	this->SignalNext();
}


EV_TIMED_WAIT_RETURN mr_queuedEvent::Wait( int ms )
{
	mr_mutexLock L( m_mutex );
	EV_TIMED_WAIT_RETURN ret = m_event.Wait( ms );
	if (ret == EV_SIGNALED)
	{
		this->SignalNext();
	}
	return ret;
}


bool mr_queuedEvent::IsSignaled()
{
	mr_mutexLock L( m_mutex );
	if (m_event.IsSignaled())
	{
		this->SignalNext();
		return true;
	}
	return false;
}


unsigned int mr_queuedEvent::QueuedCount()
{
	mr_mutexLock L( m_mutex );
	return m_count;
}


} // end mr_threads namespace


