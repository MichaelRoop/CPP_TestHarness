///--------------------------------------------------------------------------------------
/// @file	MrTestWinFaultHandler.h
/// @brief	Handle  
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_WIN_FAULT_HANDLER_H)
#define MR_TEST_WIN_FAULT_HANDLER_H

#if defined (_WIN32)
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <Windows.h>
#include <excpt.h>

#include "mr_string.h"

namespace MrTest {

class ITestCaseHolder;

class WinExceptionHandler {
public:

	static int Process(unsigned int code, struct _EXCEPTION_POINTERS *ep, ITestCaseHolder* currentTestCase);

private:
	static int StuffMsg(ITestCaseHolder* currentTestCase, const mr_utils::mr_string& msg);

};


}

#endif

#endif