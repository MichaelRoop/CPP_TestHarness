///--------------------------------------------------------------------------------------
/// @file	mr_threadObj.cpp
/// @brief	Cross platform thread object.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_threadObj.h"
#include "mr_threadFunctions.h"

//#include <Aclapi.h>
//#include <assert.h>


namespace mr_threads
{

mr_threadObj::mr_threadObj( int priority )
: 	m_handle( NULL ),
	m_id( 0 ),
	m_started( false ),
	m_priority( priority )
{
}


mr_threadObj::~mr_threadObj()
{
	this->BreakAndJoin();
}


void mr_threadObj::Sleep( int ms )
{
	mr_threads::MRSleep( ms );
}


unsigned int mr_threadObj::Id() const
{
	return m_id;
}


unsigned int mr_threadObj::ThreadEntry( void* instance )
{
	static_cast<mr_threadObj*>( instance )->Run();
	return 1;
}


void mr_threadObj::Start()
{
	if (!m_started)
	{
#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 

		m_handle = (HANDLE)_beginthreadex( 
			NULL, 
			0, 
			mr_threadObj::ThreadEntry, 
			this, 
			0, // Created running. For suspended see CREATE_SUSPENDED, 
			&m_id );


		////SE_OBJECT_TYPE se;
		//SECURITY_ATTRIBUTES sa;
		//memset( &sa, 0, sizeof( sa ) );

		//::GetSecurityInfo(
		//	m_handle,
		//	SE_KERNEL_OBJECT,
		//	DACL_SECURITY_INFORMATION,
		//	NULL,
		//	NULL,
		//	NULL,
		//	NULL,
		//	&(sa.lpSecurityDescriptor) 
		//);

		//assert( sa.lpSecurityDescriptor );
		//sa.lpSecurityDescriptor->


		m_started = ( m_handle != NULL );
		if (m_started)
		{
			/// @todo	Figure out some way to test this to see if it is operating
			///			according to priorities.  Does not seem to pay any attention
			///			to the levels.

			// This is only experimental.  I do not think it is necessary to boost classes
			//if (m_priority > 0)
			//{
			//	::SetPriorityClass( GetCurrentProcess(), REALTIME_PRIORITY_CLASS );
			//}
			//else
			//{
			//	::SetPriorityClass( GetCurrentProcess(), IDLE_PRIORITY_CLASS );
			//}


			::SetThreadPriorityBoost( m_handle, true );
			::SetThreadPriority( m_handle, m_priority );
		}

#else
		/// @todo Determine if need to set the scheduling policy SCHED_RR, or
		// SCHED_FIFO, SCHED_LIFO

		pthread_attr_t attr;
		pthread_attr_init( &attr );

		sched_param p;
		pthread_attr_getschedparam ( &attr, &p );
		p.sched_priority = m_priority;
		pthread_attr_setschedparam ( &attr, &p );

		m_started = pthread_create(
			&m_handle,
			&attr,
			mr_threadObj::ThreadEntry,
			this ) == 0;
		pthread_attr_destroy( &attr );
#endif
	}
}


void mr_threadObj::Join()
{
	if (m_started)
	{
#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
		::WaitForSingleObject( m_handle, INFINITE );
		// We can get the status here.
		//::GetExitCodeThread( m_handle, LPDWORD param )
		::CloseHandle( m_handle );
#else
		void* status = NULL;
		pthread_join( m_handle, &status );
#endif
		m_started = false;
	}
}



void mr_threadObj::Break()
{
	// override to post events recognized in derived Run method.
}


void mr_threadObj::BreakAndJoin()
{
	this->Break();
	this->Join();
}


void mr_threadObj::SetNewPriority( int priority )
{
	m_priority = priority;
}


int mr_threadObj::GetCurrentPriority() const
{
	if (!m_started)
	{
		return m_priority;
	}

#if defined(_WIN32)|| defined(__WIN32__)|| defined(WIN32) 
	return ::GetThreadPriority( m_handle );
#else
		pthread_attr_t attr;
		pthread_attr_init( &attr );

		sched_param p;
		pthread_attr_getschedparam ( &attr, &p );
		int priority = p.sched_priority ;
		pthread_attr_destroy( &attr );
		return priority;
#endif
}


} // end mr_threads namespace


