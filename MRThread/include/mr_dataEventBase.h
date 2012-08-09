///--------------------------------------------------------------------------------------
/// @file	mr_dataEventBase.h
/// @brief	Event data class that uses different base classes for event types.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_DATA_EVENT_BASE_H) 
#define MR_DATA_EVENT_BASE_H

#include "mr_mutex.h"
#include "mr_mutexLock.h"
#include "mr_exception.h"
#include "mr_defines.h"

#include <queue>


namespace mr_threads
{

/// @brief	Holds the data for a thread synchronisation event which is fed in 
///			as its base class through a template parameter.
/// 
///	This class manages the data for its base class event object. This can be any 
///	base class which conforms to the contract of the Base argument.  For example:
///		mr_event
///		mr_queuedEvent
///
/// The base class for data events is always constructed with the default 
///	constructor which should construct an automatic event.
///
template<class Base, class T>
class mr_dataEventBase : public Base
{
public:

	/// @brief	Default Constructor.
	mr_dataEventBase() : Base()
	{
	}


	/// @brief	Destructor.
	virtual ~mr_dataEventBase()
	{
	}


	/// @brief	Pulse the event with data.	
	///
	/// @param	data	The data embeded with the event.
	void Signal( const T& data )
	{
		mr_mutexLock l( m_mutex );
		m_data.push( data );
		this->Signal();
	}


	/// @brief	Wait on the event and retrieve the data.
	///
	/// @param	data	The data to retrieve from the event.
	void Wait( T& data )
	{
		mr_mutexLock l( m_mutex );
		this->Wait();
		this->GetQueuedData( data );
	}


	/// @brief	Wait on the event for a specific amount of time and retrieve data if
	///			the event is signaled.
	///
	/// @param	ms	The timeout duration.
	///
	/// @return	EV_SIGNALED if signaled before timeout, EV_TIMEOUT if timed out before
	///			signal received, otherwise EV_ERROR.  An error code can be retrieved by
	///			calling GetErrorCode immediately after.
	virtual EV_TIMED_WAIT_RETURN Wait( T& data, int ms )
	{
		mr_mutexLock l( m_mutex );
		EV_TIMED_WAIT_RETURN ret = this->Wait( ms );
		if (ret == EV_SIGNALED)
		{
			this->GetQueuedData( data );
		}
		return ret;
	}


	/// @brief	Test the current state of the event to see if it has been signaled.
	///
	/// The function will always return immediately rather than wait. If the event is
	/// automatic, the state will be reset to non-signaled.
	///
	/// @param	data	The data to retrieve from the event. It only contains valid
	///					data if the method returns true.
	///
	/// @return	true if the event was signaled, otherwise false. Only retrieves the data
	///			if signaled.
	bool IsSignaled( T& data )
	{
		mr_mutexLock l( m_mutex );
		if (this->IsSignaled())
		{
			this->GetQueuedData( data );
			return true;
		}
		return false;
	}


private:
	
	std::queue<T>	m_data;	///< Data queue.


	/// @brief	Pulse the event. Placed in private scope to limit access.
	virtual void Signal()
	{
		Base::Signal();
	}


	/// @brief	Wait on the event. Placed in private scope to limit access.
	virtual void Wait()
	{
		Base::Wait();
	}


	/// @brief	Wait on the event for a specific amount of time. Placed in private scope 
	///			to limit access.
	///
	/// @param	ms	The timeout duration.
	///
	/// @return	EV_SIGNALED if signaled before timeout, EV_TIMEOUT if timed out before
	///			signal received, otherwise EV_ERROR.  An error code can be retrieved by
	///			calling GetErrorCode immediately after.
	virtual EV_TIMED_WAIT_RETURN Wait( int ms )
	{	
		return Base::Wait( ms );
	}


	/// @brief	Test the current state of the event to see if it has been signaled.  Placed 
	///			in private scope to limit access.
	///
	/// The function will always return immediately rather than wait. 
	///
	/// @return	true if the event was signaled, otherwise false.
	virtual bool IsSignaled()
	{
		return Base::IsSignaled();
	}


	/// @brief	Helper method to get data associated with event.
	///
	/// @exception	mr_utils::mr_exception if there is no data with the event.
	void GetQueuedData( T& data )
	{
		mr_utils::mr_exception::assertCondition( 
			!m_data.empty(), FL, L("No data with event") 
		);

		data = m_data.front();
		m_data.pop();
	}

};


} // end namespace.


#endif
