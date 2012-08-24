///--------------------------------------------------------------------------------------
/// @file	mr_staticTimer.h
/// @brief	Defines a static timer to track milliseconds between calls.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_STATIC_TIMER_H)
#define MR_STATIC_TIMER_H

#include "CrossPlatform.h"

namespace mr_utils
{

	/// @brief	Static timer that tracks how many milliseconds has expired between
	///			calls.
	///
	/// @todo	Check about date roll overs.
	class CPPTESTUTILS_API StaticTimer
	{
	public:


		/// @brief	Constructor.
		StaticTimer();


		/// @brief	Reset the millisecond count to start from now.
		void start();


		/// @brief	Take and preserve the time slice since start was called.
		void stop();


		/// @brief	Returns the time slice between start and stop.
		///
		/// @return The time in milliseconds between calls to start and stop.
		long long getMsInterval() const;

	protected:

		long long m_secTime;	///< Seconds interval.
		long long m_msTime;		///< Millisecond portion of interval.

	};


}


#endif