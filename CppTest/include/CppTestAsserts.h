///--------------------------------------------------------------------------------------
/// @file	CppAssert.h
/// @brief	Assert on compare methods
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_ASSERT_H)
#define CPP_TEST_ASSERT_H

#include "CppTestCrossPlatform.h"
#include "mr_sstream.h"
#include "mr_string.h"
#include "mr_exception.h"

namespace CppTest {

/// @brief	Compares two values and asserts if different after a message is written
///
/// @tparam	T			The type of the expected and actual value.
/// @param	file		The file where the method was executing
/// @param	line		The line being executed
/// @param	expected	The expected value.
/// @param	actual		The actual value encountered.
/// @param	theCase		The testCase to received the results.
/// @param	msg			The user message. Default is empty.
template<class T>
void AreEqual(
	const char* file, int line, const T& expected, const T& actual, mr_utils::mr_stringstream& buffer, const mr_utils::mr_string& msg = _L_( "" )) {

	mr_utils::mr_stringstream ss;
	ss << _L_("Expected '") << expected << _L_("' but actual is '") << actual << _L_("'  ");
	CreateMsg(ss, file, line, msg);

	if (!CppTest::CompareEqual(expected, actual, buffer, ss.str())) {
		throw mr_utils::mr_exception(file, line, ss.str());				
	}																	
}


/// @brief	Compares two values and asserts if the same after a message is written
///
/// @tparam	T			The type of the non-expected and actual value.
/// @param	file	The file where the method was executing
/// @param	line	The line being executed
/// @param	nonexpected	The value not expected.
/// @param	actual		The actual value encountered.
/// @param	theCase		The testCase to received the results.
/// @param	msg		The user message. Default is empty.
template<class T>
void AreNotEqual(
	const char* file, int line, const T& nonexpected, const T& actual, mr_utils::mr_stringstream& buffer, const mr_utils::mr_string& msg = _L_( "" )) {

	mr_utils::mr_stringstream ss;
	ss << _L_("Did not Expected '") << nonexpected << _L_("' but actual is '") << actual << _L_("'  ");
	CreateMsg(ss, file, line, msg);

	if (!mr_test::CompareNotEqual(nonexpected, actual, buffer, ss.str())) {
		throw mr_utils::mr_exception(file, line, ss.str());				
	}																	
}


/// @brief	Create a message with file and line and possibly appending user message
///
/// @param	ss		The string stream object
/// @param	file	The file where the method was executing
/// @param	line	The line being executed
/// @param	msg		The user message. Default is empty.
CPPTESCASE_API void CreateMsg(mr_utils::mr_stringstream& ss, const char* file, int line, const mr_utils::mr_string& msg);

//{
//	mr_utils::ToStream( ss, mr_utils::ExtractFileName( file ));
//	ss << _L_(" line:") << line;
//
//	if (msg.length() > 0) { 
//		ss << _L_(" : ") << msg;
//	}
//}


CPPTESCASE_API void IsTrue(
	const char* file, int line, bool condition, mr_utils::mr_stringstream& buffer, const mr_utils::mr_string& msg = _L_( "" ));

CPPTESCASE_API void IsFalse(
	const char* file, int line, bool condition, mr_utils::mr_stringstream& buffer, const mr_utils::mr_string& msg = _L_( "" ));




//#define ASSERT_TRUE(_file_, _line_, _condition_, _buffer_, _streamMsg_)		\
//mr_utils::mr_stringstream ss;												\
//ss << (_streamMsg_);														\
//mr_assert::IsTrue(_file_, _line_, _condition_, _buffer_, ss.str().c_str());			\






//{
//
//	mr_utils::mr_stringstream ss;
//	ss << msg;
//	CreateMsg(ss, file, line, msg);
//
//	if (!mr_test::CompareEqual(true, condition, buffer, ss.str())) {
//		throw mr_utils::mr_exception(file, line, ss.str());				
//	}																	
//}




} // end of namespace

#endif
