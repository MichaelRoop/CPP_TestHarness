///--------------------------------------------------------------------------------------
/// @file	mr_event.h
/// @brief	Cross platform event mechanism.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_EVENT_H) 
#define MR_EVENT_H

#include "mr_mutex.h"


namespace mr_threads
{


/// @brief	Cross platform event class for thread synchronisation.
/// 
/// Only one thread can be handled at a time with the event.
class mr_event
{
public:

	/// @brief	Default Constructor.
	///
	/// @param	isAutomaticReset	indicates if the event will automaticaly reset itself to 
	///								non signaled when it is picked up on Wait. Default true.
	mr_event( bool isAutomaticReset = true );


	/// @brief	Destructor.
	~mr_event();


	/// @brief	Pulse the event.	
	virtual void Signal();


	/// @brief	Reset the event. Only necessary for manual events.
	void Reset();


	/// @brief	Wait indefinitely on the event.
	virtual void Wait();


	/// @brief	Wait on the event for a specific amount of time.
	///
	/// @param	ms	The timeout duration.
	///
	/// @return	EV_SIGNALED if signaled before timeout, EV_TIMEOUT if timed out before
	///			signal received, otherwise EV_ERROR.  An error code can be retrieved by
	///			calling GetErrorCode immediately after.
	virtual EV_TIMED_WAIT_RETURN Wait( int ms );


	/// @brief	Test the current state of the event to see if it has been signaled.
	///
	/// The function will always return immediately rather than wait. If the event is
	/// automatic, the state will be reset to non-signaled.
	///
	/// @return	true if the event was signaled, otherwise false.
	virtual bool IsSignaled();


	/// @brief	Return OS specific error code from last error.
	///
	/// @todo	Work out scheme for NIX/WIN
	//unsigned long GetLastErrorCode();

protected:

	mr_mutex		m_mutex;	///< Mutex object.

private:

	MR_EVENT_HANDLE	m_handle;	///< Event handle.
	bool			m_auto;		///< Automatic flag.
	bool			m_signaled;	///< Signaled state flag.


	/// @brief	Helper method to set internal signaled flag.
	void SetSignaledFlag();

};


} // end mr_threads namespace


#endif
