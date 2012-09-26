///--------------------------------------------------------------------------------------
/// @file	mr_pointerException.cpp
/// @brief	Functionality to verify and throw exceptions on bad pointers.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_pointerException.h"


namespace mr_utils
{


mr_pointerException::mr_pointerException( const char* file, int line ) 
: mr_exception( file, line, mr_string( L("Invalid Pointer") ) ) 
{
}


/// @brief	Destructor.
mr_pointerException::~mr_pointerException() throw()
{
}


void mr_pointerException::ptrAssert( const void* ptr, const char* file, int line )
{
	/// @todo Verify the validity of pointer, not only NULL.
	if (ptr == NULL)
	{
		throw mr_pointerException( file, line );
	}
}


} // end namespace mr_test