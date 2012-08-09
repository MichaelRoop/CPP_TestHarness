///--------------------------------------------------------------------------------------
/// @file	mr_threadObj.h
/// @brief	Cross platform thread object.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_THREAD_OBJ_H) 
#define MR_THREAD_OBJ_H

#include "mr_threadDefines.h"

namespace mr_threads
{


/// @brief	Cross platform Threaded ojects
/// 
class mr_threadObj
{
public:

	/// @brief	Default Constructor.
	///
	/// @param	priority	Thread priority.
	mr_threadObj( int priority = MR_DEFAULT_THREAD_PRIORITY );


	/// @brief	Destructor.
	virtual ~mr_threadObj();


	/// @brief	Put the run loop to sleep.
	///
	/// @param	ms	sleep duration in milleseconds.
	void Sleep( int ms );


	/// @brief	Thread Id.
	unsigned int Id() const;

	
	/// @brief	Block until the run loop has terminated.
	void Join();


	/// @brief	Execute the Break method and wait on the run.
	void BreakAndJoin();


	/// @brief	Override to execute a command that will cause the run to end.
	///
	/// The ususal implementation is to signal an event that the Run is blocked
	/// on internaly.  This allows a very clean exit at a known point in the Run
	/// code.
	virtual void Break();


	/// @brief	Launch the internal thread with executes the Run.
	void Start();


	/// @brief	Sets the thread priority before calling Start.
	///
	/// @param	priority	The new priority for the thread.
	void SetNewPriority( int priority );


	/// @brief	Gets the current thread priority.
	///
	/// @return	The current priority for the thread.
	int GetCurrentPriority() const;


protected:

	/// @brief	The code that is executed by the thread.  It must be overriden to 
	///			provide functionality.
	virtual void Run() = 0;

private:

	MR_THREAD_HANDLE	m_handle;	///< Thread handle.
	unsigned int		m_id;		///< Thread id.
	bool				m_started;	///< Started flag.
	int					m_priority;	///< Thread priority.


	/// @brief	Static entry point for thread launch.
	///
	///	The thread functions require a static function to lauch. By passing in 
	/// instance of the class the various instances can be launched.
	///
	/// The entry will execute the Run() method of the instance of the mr_thread
	///	class that is passed in.
	///
	/// @param	pInstance	The instance of the object to launch.
	static unsigned int MR_THREAD_CALL_TYPE ThreadEntry( void* pInstance );

};


} // end mr_threads namespace


#endif
