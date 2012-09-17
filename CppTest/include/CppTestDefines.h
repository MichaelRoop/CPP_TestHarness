///--------------------------------------------------------------------------------------
/// @file	CppTestDefines.h
/// @brief	To export types and typedefs used by CppTest classes
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_DEFINES_H)
#define CPP_TEST_DEFINES_H

#if defined(WIN32)
#	if defined(CPPTESTCASE_EXPORTS)
#		pragma message("Exporting CppTestCase DLL Classes")
#		define CPPTESCASE_API __declspec(dllexport)
#		define CPPTESCASE_EXP_TEMPLATE
#	else
#		pragma message("Importing CppTestCase DLL Classes")
#		define CPPTESCASE_API __declspec(dllimport)
#		define CPPTESCASE_EXP_TEMPLATE extern
#	endif
#elif defined(__linux) || defined(_linux_)
#	if defined(CPPTESTCASE_EXPORTS)
#		pragma message("Exporting CppTestCase DLL Classes")
#		define CPPTESCASE_API
#		define CPPTESCASE_EXP_TEMPLATE
#	else
#		pragma message("Importing CppTestCase DLL Classes")
#		define CPPTESCASE_API __declspec(dllimport)
#		define CPPTESCASE_EXP_TEMPLATE extern
#	endif
#else
#   pragma message("*** Neither WIN32 or Linux defined ***")
#endif



   //disable warnings on 255 char debug symbols
#	pragma warning (disable : 4786)
   //disable warnings on extern before template instantiation
#	pragma warning (disable : 4231)
//#else
//#	pragma message("*** WIN32 Not defined ***")
//#	define CPPTESCASE_API
//#	define CPPTESCASE_EXP_TEMPLATE
//#endif




#endif
