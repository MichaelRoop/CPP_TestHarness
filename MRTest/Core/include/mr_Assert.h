///--------------------------------------------------------------------------------------
/// @file	mr_Assert.h
/// @brief	Compare and assert methods
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_ASSERT_H)
#define MR_ASSERT_H

#include "mr_exception.h"

namespace mr_assert 
{

	// Forward declaration
	class testCase;

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
	const char* file, int line, const T& expected, const T& actual, mr_test::testCase& theCase, const mr_utils::mr_string& msg = _L_( "" )) {

	mr_utils::mr_stringstream ss;
	ss << _L_("Expected '") << expected << _L_("' but actual is '") << actual << _L_("'  ");
	CreateMsg(ss, file, line, msg);

	if (!mr_test::CompareEqual(expected, actual, theCase, ss.str())) {
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
	const char* file, int line, const T& nonexpected, const T& actual, mr_test::testCase& theCase, const mr_utils::mr_string& msg = _L_( "" )) {

	mr_utils::mr_stringstream ss;
	ss << _L_("Did not Expected '") << nonexpected << _L_("' but actual is '") << actual << _L_("'  ");
	CreateMsg(ss, file, line, msg);

	if (!mr_test::CompareNotEqual(nonexpected, actual, theCase, ss.str())) {
		throw mr_utils::mr_exception(file, line, ss.str());				
	}																	
}


/// @brief	Create a message with file and line and possibly appending user message
///
/// @param	ss		The string stream object
/// @param	file	The file where the method was executing
/// @param	line	The line being executed
/// @param	msg		The user message. Default is empty.
void CreateMsg(mr_utils::mr_stringstream& ss, const char* file, int line, const mr_utils::mr_string& msg) {
	mr_utils::ToStream( ss, mr_utils::ExtractFileName( file ));
	ss << _L_(" line:") << line;

	if (msg.length() > 0) { 
		ss << _L_(" : ") << msg;
	}
}


} // end of namespace

#endif
