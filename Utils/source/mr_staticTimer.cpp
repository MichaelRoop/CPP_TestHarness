///--------------------------------------------------------------------------------------
/// @file	mr_staticTimer.cpp
/// @brief	Defines a static timer to track milliseconds between calls.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_staticTimer.h"
#include "mr_exception.h"
#include "mr_defines.h"

#include <sys/timeb.h>
#include <time.h>


namespace mr_utils
{


StaticTimer::StaticTimer() : m_secTime( 0 ), m_msTime( 0 )
{
}


void StaticTimer::start()
{
	// WARNING:  This will wrap after Dec 2038.
	/// @todo	Determine a way around the wrapping.  This will happen in 2038 
	///			if the application is still compiled in 32 bits.
	timeb t;
	ftime( &t );
	m_secTime = t.time;
	m_msTime = t.millitm;
}


void StaticTimer::stop()
{
	timeb t;
	ftime( &t );

	long long newSec  = t.time;
	long long newMSec = t.millitm;

	m_secTime = newSec - m_secTime;
	
	if (t.millitm < m_msTime)
	{
		mr_exception::assertCondition( 
			m_secTime > 0 , FL, L("logic error with time calculation") );
		--m_secTime;
		t.millitm += 1000;
	}
	m_msTime = t.millitm - m_msTime;
}


long long StaticTimer::getMsInterval() const
{
	return ( m_secTime * 1000 ) + m_msTime;
}


}