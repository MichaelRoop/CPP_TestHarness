///--------------------------------------------------------------------------------------
/// @file	mr_lockedWriteOut.h
/// @brief	Provides system wide thread safety for writting out to a stream.
///
///	These functions should only be used to write to a stream that requires system
/// wide thread access protection. All threads will be queued behind one static 
/// mutex.  Discreet data blocks should be protected by their own scoped mutex.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_LOCKED_WRITE_OUT_H) 
#define MR_LOCKED_WRITE_OUT_H

#include "mr_mutex.h"
#include "mr_mutexLock.h"
#include "mr_iostream.h"


namespace mr_threads
{


static mr_threads::mr_mutex g_ConsoleMutex; ///< global mutex for locking writes.


/// @brief	Template function to lock writes to a stream.
///
/// @param	out	The output stream.
/// @param	s	The templatized data to stream out.
template<class T>
static void LockedWriteToStream( mr_utils::mr_ostream& out, const T& s )
{
	mr_threads::mr_mutexLock l( g_ConsoleMutex );
	out << s;
}


/// @brief	Template function to lock writes to a stream including adding an end of line.
///
/// @param	out	The output stream.
/// @param	s	The templatized data to stream out.
template<class T>
static void LockedWriteLineToStream( mr_utils::mr_ostream& out, const T& s )
{
	mr_threads::mr_mutexLock l( g_ConsoleMutex );
	LockedWriteToStream( out, s );
	out << std::endl;
}


/// @brief	Template specialization function for stringstream to lock writes to a stream.
///
/// @param	out	The output stream.
/// @param	ss	The stringstream data to stream out.
template<>
static void LockedWriteToStream( mr_utils::mr_ostream& out, const mr_utils::mr_stringstream& ss )
{
	LockedWriteToStream( out, ss.str() );
}


/// @brief	Template function for to lock writes to console.
///
/// @param	s	The stringstream data to stream out.
template<class T>
static void LockedWriteToConsole( const T& t )
{
	LockedWriteToStream( mr_cout, t );
}


/// @brief	Template specialization function for stringstream to lock writes to console.
///
/// @param	ss	The stringstream data to stream out.
template<>
static void LockedWriteToConsole( const mr_utils::mr_stringstream& ss )
{
	LockedWriteToConsole( ss.str() );
}


/// @brief	Template function to lock writes to console including adding an end of line.
///
/// @param	s	The templatized data to stream out.
template<class T>
static void LockedWriteLineToConsole( const T& t )
{
	LockedWriteLineToStream( mr_cout, t );
}


/// @brief	Template specilization function to lock writes to console including adding an end 
///			of line.
///
/// @param	ss	The stringstream data to stream out.
template<>
static void LockedWriteLineToConsole( const mr_utils::mr_stringstream& ss )
{
	LockedWriteLineToConsole( ss.str() );
}


} // end of namespace

#endif