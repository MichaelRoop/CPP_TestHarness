///--------------------------------------------------------------------------------------
/// @file	mr_mutexLock.cpp
/// @brief	Cross platform auto mutex auto locking object.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_mutexLock.h"
#include "mr_mutex.h"

namespace mr_threads
{

mr_mutexLock::mr_mutexLock( mr_mutex& _mutex ) : m_mutex( _mutex )
{
	m_mutex.Aquire();
}


mr_mutexLock::~mr_mutexLock()
{
	m_mutex.Release();
}


} // end mr_threads namespace


