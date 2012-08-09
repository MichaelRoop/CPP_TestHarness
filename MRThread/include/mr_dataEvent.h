///--------------------------------------------------------------------------------------
/// @file	mr_dataEvent.h
/// @brief	Cross platform event mechanism with embedded data.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_DATA_EVENT_H) 
#define MR_DATA_EVENT_H


#include "mr_dataEventBase.h"
#include "mr_event.h"


namespace mr_threads
{

/// @brief	Non queued event class with embeded data.
///
/// @param	T	The data type present with each event.
template <class T> 
class mr_dataEvent : public mr_dataEventBase<mr_event,T>
{
public:

	/// @brief	Default constructor.
	mr_dataEvent() : mr_dataEventBase<mr_event, T> ()
	{
	}


	/// @brief	Destructor.
	virtual ~mr_dataEvent()
	{
	}

};

} // end mr_threads namespace


#endif
