///--------------------------------------------------------------------------------------
/// @file	MrTestConsoleOutput.h
/// @brief	Output class to output logger information to the console.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "MrTestConsoleOutput.h"
#include "mr_iostream.h"

namespace MrTest {

bool ConsoleOutput::InitOutput() { 
	return true; 
}


void ConsoleOutput::CloseOutput() { 
	; // Nothing to do.
}


bool ConsoleOutput::Write(const mr_utils::mr_string& str) {
	mr_cout << str.c_str() << std::endl;
	return true;
}

} // end namespace
