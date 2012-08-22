///--------------------------------------------------------------------------------------
/// @file	CppTestCompareFunctions.h
/// @brief	Compare functions.
///
/// We use template functions because they automaticaly resolve the template arguments.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_COMP_FUNC_H)
#define MR_TEST_COMP_FUNC_H

#include "mr_string.h"
#include "mr_sstream.h"
#include "mr_doCompare.h"

#include <vector>

namespace CppTest {

class testCase;


//--------------------------------------------------------------------------------------
// Write to buffer functions
//--------------------------------------------------------------------------------------


/// @brief	Tests if a condition is false and then writes to the testCase message buffer.
///
/// @param	theCase	The test case to write to.
/// @param	msg		The message to write if the condition is false.
/// @param	success	Then condition to test.
///
/// @return	The value of the success argument.
bool WriteToMsgBuff(mr_utils::mr_stringstream& buffer, const mr_utils::mr_string& msg, bool success);


/// @brief	Writes the first part of the verbose message to the testCase verbose message buffer.
///
///	Message creates the template and is ready for 'expected value'
///
/// @param	file	The code file where the call originates.
/// @param	line	The code line where the call originates.
/// @param	theCase	The test case to write to.
void WriteToVerboseBuffHead(const char* file, int line, mr_utils::mr_stringstream& buffer);


/// @brief	Writes the middle part of the verbose message to the testCase verbose message buffer.
///
///	Message creates the template and is ready for 'actual value'
///
/// @param	theCase	The test case to write to.
void WriteToVerboseBuffMid(mr_utils::mr_stringstream& buffer);


/// @brief	Template function to write to the testCase verbose buffer on a false condition.
///
/// @tparam	T			The type of the expected and actual value.
/// @param	file		The code file where the call originates.
/// @param	line		The code line where the call originates.
/// @param	expected	The expected value.
/// @param	actual		The actual value encountered.
/// @param	theCase		The testCase to received the results.
/// @param	success		The condition to check.
///
/// @return The value of the success argument.
template<class T>
bool WriteToVerboseBuff( 
	const char*					file,
	int							line,
	const T&					expected, 
	const T&					actual, 
	mr_utils::mr_stringstream&	buffer, 
	bool						success 
) {
	if (!success) {
		WriteToVerboseBuffHead(file, line, buffer);
		mr_utils::ToStream( buffer, expected);
		WriteToVerboseBuffMid(buffer);
		mr_utils::ToStream(buffer, actual);
	}
	return success;
}


/// @brief	Template function to write vectors of values to the testCase verbose buffer 
///			on a false condition.
///
/// @tparam	T			The type of the expected and actual values in the containers.
/// @param	file		The code file where the call originates.
/// @param	line		The code line where the call originates.
/// @param	expected	The expected value.
/// @param	actual		The actual value encountered.
/// @param	theCase		The testCase to received the results.
/// @param	success		The condition to check.
///
/// @return The value of the success argument.
template<class T>
bool WriteVecToVerboseBuff( 
	const char*					file,
	int							line,
	const std::vector<T>&		expected, 
	const std::vector<T>&		actual, 
	mr_utils::mr_stringstream&	buffer, 
	bool						success 
) {
	if (!success) {
		mr_utils::VecStreamLineDelimited<T> lineFormater(buffer);
		WriteToVerboseBuffHead(file, line, buffer);
		mr_utils::ToStream(buffer, expected, lineFormater);
		WriteToVerboseBuffMid(buffer);
		mr_utils::ToStream(buffer, actual, lineFormater);
	}
	return success;
}


//--------------------------------------------------------------------------------------
// Comparison functions
//--------------------------------------------------------------------------------------



/// @brief	Compares two values and write a message when values are different.
///
/// @tparam	T			The type of the expected and actual value.
/// @param	expected	The expected value.
/// @param	actual		The actual value encountered.
/// @param	theCase		The testCase to received the results.
/// @param	msg			The user message. Default is 'Value not as expected'.
///
/// @return true if the values are the same, otherwise false.
template<class T, class T2>
bool CompareEqual( 
	const T&					expected, 
	const T2&					actual, 
	mr_utils::mr_stringstream&	buffer, 
	const mr_utils::mr_string&	msg = L("Value not as expected" )) {
	return WriteToMsgBuff(buffer, msg, mr_utils::CompareEqual(expected, actual));
}


/// @brief	Compares two values and write a message when the values are the same.
///
/// @tparam	T			The type of the expected and actual value.
/// @param	expected	The expected value.
/// @param	actual		The actual value encountered.
/// @param	theCase		The testCase to received the results.
/// @param	msg			The user message. Default is 'Value not as expected'.
///
/// @return true if the values are different, otherwise false.
template<class T, class T2>
bool CompareNotEqual( 
	const T&					expected, 
	const T2&					actual, 
	mr_utils::mr_stringstream&	buffer, 
	const mr_utils::mr_string&	msg = L("Value not as expected" )) {
	return WriteToMsgBuff(buffer, msg, mr_utils::CompareNotEqual(expected, actual));
}


/// @brief	Compares two values and writes a verbose message when the values are different.
///
/// @tparam	T			The type of the expected and actual value.
/// @param	file		The code file where the call originates.
/// @param	line		The code line where the call originates.
/// @param	expected	The expected value.
/// @param	actual		The actual value encountered.
/// @param	theCase		The testCase to received the results.
/// @param	msg			The user message. Default is 'Value not as expected'.
///
/// @return true if the values are the same, otherwise false.
template<class T>
bool VerbCompareEqual( 
	const char*					file,
	int							line,
	const T&					expected, 
	const T&					actual, 
	mr_utils::mr_stringstream&	buffer, 
	const mr_utils::mr_string&	msg = L( "Value not as expected" ) 
) {
	return WriteToVerboseBuff( 
		file, line, expected, actual, buffer, CompareEqual(expected, actual, buffer, msg) 
	);
}


/// @brief	Compares two values and write a verbose message when the values are the same.
///
/// @tparam	T			The type of the expected and actual value.
/// @param	file		The code file where the call originates.
/// @param	line		The code line where the call originates.
/// @param	expected	The expected value.
/// @param	actual		The actual value encountered.
/// @param	theCase		The testCase to received the results.
/// @param	msg			The user message. Default is 'Value not as expected'.
///
/// @return true if the values are different, otherwise false.
template<class T>
bool VerbCompareNotEqual( 
	const char*					file,
	int							line,
	const T&					expected, 
	const T&					actual, 
	mr_utils::mr_stringstream&	buffer, 
	const mr_utils::mr_string&	msg = L( "Value not as expected" ) 
) {
	return WriteToVerboseBuff( 
		file, line, expected, actual, buffer, CompareNotEqual(expected, actual, buffer, msg) 
	);
}


/// @brief	Compares two vectors of values and write a message when the values 
///			do not match.
///
/// @tparam	T			The type of the expected and actual value.
/// @param	file		The code file where the call originates.
/// @param	line		The code line where the call originates.
/// @param	expected	The expected value.
/// @param	actual		The actual value encountered.
/// @param	theCase		The testCase to received the results.
/// @param	msg			The user message. Default is 'Value not as expected'.
///
/// @return true if the values are different, otherwise false.
template<class T>
bool VerbCompareVecEqual( 
	const char*					file,
	int							line,
	const std::vector<T>&		expected, 
	const std::vector<T>&		actual, 
	mr_utils::mr_stringstream&	buffer, 
	const mr_utils::mr_string&	msg = L( "Value not as expected" ) 
) {
	return WriteVecToVerboseBuff( 
		file, line, expected, actual, buffer, CompareEqual( expected, actual, buffer, msg ) 
	);
}

} // end namespace

#endif
