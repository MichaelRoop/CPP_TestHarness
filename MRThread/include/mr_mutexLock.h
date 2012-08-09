///--------------------------------------------------------------------------------------
/// @file	mr_mutexLock.h
/// @brief	Cross platform auto mutex auto locking object.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_MUTEX_LOCK_H) 
#define MR_MUTEX_LOCK_H


namespace mr_threads
{

class mr_mutex;	///< Forward declaration of mr_mutex object.


/// @brief	Auto locking mutex object using constructor and destructor.
///
/// The user constructs an mr_mutexLock object with existing mr_mutex object. On 
/// construction it automatically aquires the lock. When the object goes out of
/// scope its destructor releases the lock.
///
/// Example:
///
/// class foo
/// {
///  public:
///		void DoSomething()
///		{
///			mr_mutexLock L( m_mutex );
///			... do stuff
///			... the lock is release on leaving function scope
///		}
///	private:
///		mr_mutex m_mutex;
///
class mr_mutexLock
{
public:

	/// @brief	Constructor.
	///
	/// @param	_mutex	Mutex to auto lock on construction.
	///
	/// @return	A copy of the trimmed string.
	mr_mutexLock( mr_mutex& _mutex );


	/// @brief	Destructor to auto unlock on destruction.
	~mr_mutexLock();

private:

	/// @brief	Default constructor in private scope.
	mr_mutexLock();


	mr_mutex& m_mutex;	///< Mutex to lock and unlock.


	/// @brief	Protected assignement operator.
	mr_mutexLock& operator = ( const mr_mutexLock& ) { return *this; }
};


} // end mr_threads namespace


#endif
