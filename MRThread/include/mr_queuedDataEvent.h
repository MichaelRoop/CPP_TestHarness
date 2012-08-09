///--------------------------------------------------------------------------------------
/// @file	mr_queuedDataEvent.h
/// @brief	Cross platform queued event mechanism with embedded data.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_QUEUED_DATA_EVENT_H) 
#define MR_QUEUED_DATA_EVENT_H


#include "mr_dataEventBase.h"
#include "mr_queuedEvent.h"


namespace mr_threads
{

/// @brief	Queued event class with embeded data.
///
/// @param	T	The data type present with each event.
template <class T> 
class mr_queuedDataEvent : public mr_dataEventBase<mr_queuedEvent,T>
{
public:

	/// @brief	Default constructor.
	mr_queuedDataEvent() : mr_dataEventBase<mr_queuedEvent, T> ()
	{
	}


	/// @brief	Destructor.
	virtual ~mr_queuedDataEvent()
	{
	}
};


} // end mr_threads namespace


#endif
