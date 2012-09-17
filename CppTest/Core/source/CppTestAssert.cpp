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
#include "CppTestAsserts.h"
#include "CppTestCompareFunctions.h"
#include "mr_toStream.h"

namespace MrTest {


void CreateMsg(mr_utils::mr_stringstream& msgBuffer, const char* file, int line, mr_utils::mr_stringstream& userMsg) {
	mr_utils::ToStream( msgBuffer, mr_utils::ExtractFileName(file));
	msgBuffer << _L_(":") << line;

	if (userMsg.str().length() > 0) { 
		msgBuffer << _L_(" : ") << userMsg.str();
	}
}


void IsTrue(
	const char* file, int line, bool condition, mr_utils::mr_stringstream& buffer, mr_utils::mr_stringstream& userMsg) {

	mr_utils::mr_stringstream ss;
	ss << _L_("Did not Expected false condition ");	
	CreateMsg(ss, file, line, userMsg);

	if (!MrTest::CompareEqual(true, condition, buffer, ss.str())) {
		throw MrTest::AssertException(file, line, ss.str());				
	}		
	mr_utils::ResetStringStream(buffer);
	mr_utils::ResetStringStream(userMsg);
}


void IsFalse(
	const char* file, int line, bool condition, mr_utils::mr_stringstream& buffer, mr_utils::mr_stringstream& userMsg) {

	mr_utils::mr_stringstream ss;
	ss << _L_("Did not Expected true condition ");	
	CreateMsg(ss, file, line, userMsg);

	if (!MrTest::CompareEqual(false, condition, buffer, ss.str())) {
		throw MrTest::AssertException(file, line, ss.str());				
	}			
	mr_utils::ResetStringStream(buffer);
	mr_utils::ResetStringStream(userMsg);
}


CPPTESCASE_API void Fail(
	const char* file, int line, mr_utils::mr_stringstream& buffer, mr_utils::mr_stringstream& userMsg) {

	mr_utils::mr_stringstream ss;
	ss << _L_("User Forced Fail ");	
	CreateMsg(ss, file, line, userMsg);
	buffer << ss.str();
	throw MrTest::AssertException(file, line, ss.str());				
}


CPPTESCASE_API void FailOnNotThrow(
	const char* file, int line, mr_utils::mr_stringstream& buffer, mr_utils::mr_stringstream& userMsg) {

	mr_utils::mr_stringstream ss;
	ss << _L_("Test Expected Exception to be Thrown ");	
	CreateMsg(ss, file, line, userMsg);
	buffer << ss.str();
	throw MrTest::AssertException(file, line, ss.str());				
}

}

