///--------------------------------------------------------------------------------------
/// @file	MrTestSegfaultHandler.h
/// @brief	Handle the cross platform selection of segfault capture 
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_SEGFAULT_HANDLER_H)
#define MR_TEST_SEGFAULT_HANDLER_H

#if defined (_WIN32)
#	include "MrTestWinFaultHandler.h"
#else
#endif

namespace MrTest {


#if defined (_WIN32)
#	define START_SEGFAULT_CATCH_BLOCK			__try {	
#else
#	define START_SEGFAULT_CATCH_BLOCK			try {	
#endif


#if defined (_WIN32)
#	define END_SEGFAULT_CATCH_BLOCK	} __except(WinExceptionHandler::Process(GetExceptionCode(), GetExceptionInformation(), this->m_currentTestCase)) {}
#else
#	define END_SEGFAULT_CATCH_BLOCK	} catch (...) {}
#endif


} // end namespace

#endif
