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
#include "mr_exception.h"

namespace MrTest {


void CreateMsg(mr_utils::mr_stringstream& msgBuffer, const char* file, int line, const mr_utils::mr_stringstream& userMsg) {
	mr_utils::ToStream( msgBuffer, mr_utils::ExtractFileName(file));
	msgBuffer << _L_(":") << line;

	if (userMsg.str().length() > 0) { 
		msgBuffer << _L_(" : ") << userMsg.str();
	}
}


void IsTrue(
	const char* file, int line, bool condition, mr_utils::mr_stringstream& buffer, const mr_utils::mr_stringstream& userMsg) {

	mr_utils::mr_stringstream ss;
	ss << _L_("Did not Expected false condition ");	
	CreateMsg(ss, file, line, userMsg);

	if (!MrTest::CompareEqual(true, condition, buffer, ss.str())) {
		throw mr_utils::mr_exception(file, line, ss.str());				
	}		
}


void IsFalse(
	const char* file, int line, bool condition, mr_utils::mr_stringstream& buffer, const mr_utils::mr_stringstream& userMsg) {

	mr_utils::mr_stringstream ss;
	ss << _L_("Did not Expected true condition ");	
	CreateMsg(ss, file, line, userMsg);

	if (!MrTest::CompareEqual(false, condition, buffer, ss.str())) {
		throw mr_utils::mr_exception(file, line, ss.str());				
	}																	
}


}

