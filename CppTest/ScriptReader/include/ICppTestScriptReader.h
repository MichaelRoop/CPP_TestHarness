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

#include "CppTestDefines.h"
#include "CppTestInfoObject.h"
#include "mr_exception.h"


namespace MrTest {

///--------------------------------------------------------------------------------------
///
/// @brief	Pure virtual class to abstract the reading of a test script.
///
/// The derived classes can read a script file of any format from any source as long
/// as they satisfy the interface.  In this case you could have a custom format of script
/// file or one that used known formats such as ini or XML.
///--------------------------------------------------------------------------------------
class CPPTESCASE_API IScriptReader {
public:

	/// @brief	Opens the script.
	virtual void Open()  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}


	/// @brief	Extracts the test information from the current test script line.
	/// @param	fixtureName	Name of the fixture for the test case.
	/// @return	The populated testInfoObject for the test.  If the object has no more
	///			script lines the testInfoObject.isValid() will return false.
	virtual MrTest::TestInfoObject getNextTest(mr_utils::mr_string& fixtureName)  {
		// Should be pure virtual but cannot export the class
		throw mr_utils::mr_exception(_FL_, _L_("Do not use base directly - public only for forced export"));
	}
};

CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<MrTest::IScriptReader>;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<MrTest::IScriptReader>;


} // end namespace

#endif
