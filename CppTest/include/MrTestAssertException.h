///--------------------------------------------------------------------------------------
/// @file	MrTestAssertException.h
/// @brief	Exception exclusively for use in test assert methods
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_ASSERT_EXCEPTION_H)
#define MR_TEST_ASSERT_EXCEPTION_H

#include "MrTestDefines.h"
#include "mr_exception.h"


namespace MrTest {

///--------------------------------------------------------------------------------------
///
///	@brief	Class to throw exceptions on test assert failures
///
/// Use the FL macro to insert the file name and line from the system.
/// Use the L() macro to provide cross char width portability.
/// Use the cross char width streaming so that the message can be displayed on both
/// both narrow and wide char compilation mode.
///
///--------------------------------------------------------------------------------------
class MRTESCASE_API AssertException : public mr_utils::mr_exception {
public:

	/// @brief	Constructor.
	///
	/// @param	file			The source code file where problem originates.
	/// @param	line			The source code line where problem originates.
	/// @param	msg				The message explaining the exception.
	AssertException(const char*	file, int line, const mr_utils::mr_string&	msg);


    /// @brief	Copy Constructor.
    ///
    /// @param	msg				The message explaining the exception.
    AssertException(const AssertException& obj);


	/// @brief	Destructor.
	virtual ~AssertException() throw();


};

} // end of namespace

#endif
