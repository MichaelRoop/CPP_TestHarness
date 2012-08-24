///--------------------------------------------------------------------------------------
/// @file	mr_singleton.h
/// @brief	Base class that defines Singleton behavior.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_SINGLETON_H)
#define MR_SINGLETON_H

#include "CrossPlatform.h"

namespace mr_utils
{

	/// @brief	Singleton base class.
	class CPPTESTUTILS_API singleton
	{

	protected:

		/// @brief	Default constructor in protected scope to prevent direct intantiation.
		singleton();


		/// @brief	Copy constructor in protected scope to prevent direct intantiation.
		///
		/// @param	obj	The Singleton object used to contruct an instance.
		singleton( const singleton& obj );
	};


}


#endif