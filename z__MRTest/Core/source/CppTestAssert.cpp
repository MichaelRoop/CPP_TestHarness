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

namespace CppTest {


void CreateMsg(mr_utils::mr_stringstream& ss, const char* file, int line, const mr_utils::mr_string& msg) {
	mr_utils::ToStream( ss, mr_utils::ExtractFileName( file ));
	ss << _L_(" line:") << line;

	if (msg.length() > 0) { 
		ss << _L_(" : ") << msg;
	}
}


void IsTrue(
	const char* file, int line, bool condition, mr_utils::mr_stringstream& buffer, const mr_utils::mr_string& msg) {

	mr_utils::mr_stringstream ss;
	//ss << msg;
	ss << _L_("Did not Expected false condition ");	
	CreateMsg(ss, file, line, msg);

	if (!CppTest::CompareEqual(true, condition, buffer, ss.str())) {
		throw mr_utils::mr_exception(file, line, ss.str());				
	}																	
}

void IsFalse(
	const char* file, int line, bool condition, mr_utils::mr_stringstream& buffer, const mr_utils::mr_string& msg) {

	mr_utils::mr_stringstream ss;
	ss << _L_("Did not Expected true condition ");	
	CreateMsg(ss, file, line, msg);

	if (!CppTest::CompareEqual(false, condition, buffer, ss.str())) {
		throw mr_utils::mr_exception(file, line, ss.str());				
	}																	
}


}

