///--------------------------------------------------------------------------------------
/// @file	ICppScriptReader.h
/// @brief	cross platform and char width script exception for dev test platform.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------

#if !defined(ICPP_TEST_SCRIPT_READER_H)
#define ICPP_TEST_SCRIPT_READER_H


#include "CppTestInfoObject.h"


namespace CppTest {

///--------------------------------------------------------------------------------------
///
/// @brief	Pure virtual class to abstract the reading of a test script.
///
/// The derived classes can read a script file of any format from any source as long
/// as they satisfy the interface.  In this case you could have a custom format of script
/// file or one that used known formats such as ini or XML.
///--------------------------------------------------------------------------------------
class IScriptReader {
public:

	/// @brief	Opens the script.
	virtual void Open() = 0;


	/// @brief	Extracts the test information from the current test script line.
	/// @return	The populated testInfoObject for the test.  If the object has no more
	///			script lines the testInfoObject.isValid() will return false.
	virtual CppTest::TestInfoObject getNextTest() = 0;
};


} // end namespace

#endif
