///--------------------------------------------------------------------------------------
/// @file	mr_pointerException.h
/// @brief	Functionality to verify and throw exceptions on bad pointers.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR__POINTER_EXCEPTION_H)
#define MR__POINTER_EXCEPTION_H

#include "mr_exception.h"


namespace mr_utils
{

///--------------------------------------------------------------------------------------
///
///@brief	Pointer exception class
///
/// Provides source code name and line and a user defined message.
///
/// Use the FL macro to insert the file name and line from the system.
/// Use the L() macro to provide cross char width portability.
///
/// You can use the static method ptrAssert to check a pointer and throw the exception.
///
/// On the catch you can either access the different parts of the message or use the formatted
/// message.
///
///		catch( const mr_utils::mr_exception& e )	\n
///		{											\n
///			mr_cout << e.longMsg() << std::endl;	\n
///		}											\n
///
///--------------------------------------------------------------------------------------
class mr_pointerException : public mr_exception
{
public:

	/// @brief	Constructor.
	///
	/// @param	file	The source code file where problem originates.
	/// @param	line	The source code line where problem originates.
	mr_pointerException( const char* file, int line );


	/// @brief	Destructor.
	~mr_pointerException() throw();


	/// @brief	Wrapper to clean up checking for exception throw on bad pointers.
	///
	///	@throw	Throws a mr_pointerException on failure
	///
	/// @param	ptr		The pointer to test. If NULL, an exception is thrown.
	/// @param	file	The source code file where problem originates.
	/// @param	line	The source code line where problem originates.
	static void ptrAssert( const void* ptr, const char* file, int line );

};


}

#endif