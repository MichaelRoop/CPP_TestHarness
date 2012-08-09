///--------------------------------------------------------------------------------------
/// @file	mr_mutex.h
/// @brief	Cross platform recursive mutex locking mechanism.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_MUTEX_H) 
#define MR_MUTEX_H

#include "mr_threadDefines.h"

namespace mr_threads
{


/// @brief	Simple mutex class to provide thread locking.
/// 
///	The mutex for both Windows and Nix is recursive.
///
class mr_mutex
{
public:

	/// @brief	Default Constructor.
	mr_mutex();


	/// @brief	Destructor.
	~mr_mutex();


	/// @brief	Aquire the mutex lock.
	void Aquire();


	/// @brief	Release the mutex lock.
	void Release();

private:
	/// @todo	Remember why I did this. One of the pthread event calls must access
	///			the internals of the mutex directly, or so I thought.
	//friend class	mr_event;	///< Allows mr_event to access mutex directly.
	MR_MUTEX_OBJ	m_mutex;	///< Mutex object.

};


} // end mr_threads namespace


#endif
