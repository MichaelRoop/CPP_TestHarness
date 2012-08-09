///--------------------------------------------------------------------------------------
/// @file	mr_queuedEvent.h
/// @brief	Cross platform event mechanism that remembers all the signals.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_QUEUED_EVENT_H) 
#define MR_QUEUED_EVENT_H

#include "mr_event.h"


namespace mr_threads
{


/// @brief	Keeps track of all signals so none is lost.
/// 
class mr_queuedEvent
{
public:

	/// @brief	Default Constructor.
	mr_queuedEvent();


	/// @brief	Destructor.
	~mr_queuedEvent();


	/// @brief	Pulse the event.	
	void Signal();


	/// @brief	Reset the event. Only necessary for manual events.
	//void Reset();


	/// @brief	
	void Wait();


	/// @brief	Wait on the event for a specific amount of time.
	///
	/// @param	ms	The timeout duration.
	///
	/// @return	EV_SIGNALED if signaled before timeout, EV_TIMEOUT if timed out before
	///			signal received, otherwise EV_ERROR.  An error code can be retrieved by
	///			calling GetErrorCode immediately after.
	virtual EV_TIMED_WAIT_RETURN Wait( int ms );


	/// @brief	Returns the total of queued events.
	unsigned int QueuedCount();


	/// @brief	Test the current state of the event to see if it has been signaled.
	///
	/// The function will always return immediately rather than wait. If the event is
	/// automatic, the state will be reset to non-signaled.
	///
	/// @return	true if the event was signaled, otherwise false.
	bool IsSignaled();

protected:
	mr_mutex		m_mutex;	///< Mutex object.

private:
	mr_event		m_event;	///< The event mechanism.
	unsigned int	m_count;	///< Event counter.


	/// @brief	Determine if there is a queued signal to repost.
	void mr_queuedEvent::SignalNext();

};


} // end mr_threads namespace


#endif
