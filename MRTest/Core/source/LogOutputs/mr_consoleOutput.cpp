///--------------------------------------------------------------------------------------
/// @file	mr_consoleOutput.h
/// @brief	Output class to output logger information to the console.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_consoleOutput.h"
#include "mr_iostream.h"

namespace mr_test
{

bool consoleOutput::initOutput()	
{ 
	return true; 
}


void consoleOutput::closeOutput()	
{ 
	; // Nothing to do.
}


bool consoleOutput::write( const mr_utils::mr_string& str )
{
	mr_cout << str.c_str() << std::endl;
	return true;
}

} // end namespace