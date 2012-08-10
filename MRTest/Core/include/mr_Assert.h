///--------------------------------------------------------------------------------------
/// @file	mr_testMacros.h
/// @brief	Macros useful for asserting on various conditions
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_ASSERT_H_)
#define MR_ASSERT_H_

#include "mr_exception.h"

namespace mr_assert 
{

	// Forward declaration
	class testCase;

	template<class T>
		void AreEqual(
			const char* file, int line, const T& expected, const T& actual, mr_test::testCase& theCase, const mr_utils::mr_string&	msg = _L_( "" )) {

			mr_utils::mr_stringstream ss;
			ss << _L_("Expected '") << expected << _L_("' but actual is '") << actual << _L_("'  ");
			mr_utils::ToStream( ss, mr_utils::ExtractFileName( file ));
			ss << _L_(" line:") << line;

			if (msg.length() > 0) { 
				ss << _L_(" : ") << msg;
			}

			if (!mr_test::CompareEqual(expected, actual, theCase, ss.str())) {
				throw mr_utils::mr_exception(file, line, ss.str());				
			}																	
		}

	template<class T>
		void AreNotEqual(
			const char* file, int line, const T& expected, const T& actual, mr_test::testCase& theCase, const mr_utils::mr_string&	msg = _L_( "" )) {

			mr_utils::mr_stringstream ss;
			ss << _L_("Did not Expected '") << expected << _L_("' but actual is '") << actual << _L_("'  ");
			mr_utils::ToStream( ss, mr_utils::ExtractFileName( file ));
			ss << _L_(" line:") << line;

			if (msg.length() > 0) { 
				ss << _L_(" : ") << msg;
			}

			if (!mr_test::CompareNotEqual(expected, actual, theCase, ss.str())) {
				throw mr_utils::mr_exception(file, line, ss.str());				
			}																	
		}


}

#endif
