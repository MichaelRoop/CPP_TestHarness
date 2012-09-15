///--------------------------------------------------------------------------------------
/// @file	MrTestAssertException.cpp
/// @brief	Exception exclusively for use in test assert methods
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------

#include "MrTestAssertException.h"


namespace MrTest {


AssertException::AssertException(const char* file, int line, const mr_utils::mr_string&	msg)
	: mr_utils::mr_exception(file, line, msg)  {
}


AssertException::~AssertException() throw() {
}


} // end of namespace

