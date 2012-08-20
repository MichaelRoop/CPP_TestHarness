//--------------------------------------------------------------------------------------
/// @file	mr_testLogEngine.h
/// @brief	Engine to drive the logging activity.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
//--------------------------------------------------------------------------------------
#if !defined(MR_TEST_LOG_ENGINE_H)
#define MR_TEST_LOG_ENGINE_H


#include <vector>
#include "mr_SharedPtr.h"
#include "mr_string.h"


namespace CppTest {
	class Fixture;
	class Case;
}

namespace mr_test
{

class iTestLog;


//--------------------------------------------------------------------------------------
/// 
/// @brief	Drives the logging of testCase information across a variable number
///			of derived Logs.
///
//--------------------------------------------------------------------------------------
class testLogEngine
{
public:

	/// @brief	Constructor.
	testLogEngine();


	/// @brief	Destructor.
	virtual ~testLogEngine();


	/// @brief	Write the header information across all loggers.
	///
	/// @exception	throws a mr_utils::mr_pointerException on invalid loggers.
	///
	/// @return	true if successful, otherwise false.
	bool writeHeaders();


	/// @brief	Write the summary information across all loggers.
	///
	/// @exception	throws a mr_utils::mr_pointerException on invalid loggers.
	///
	/// @return	true if successful, otherwise false.
	bool writeSummaries();



	/// @brief	Log the test case information across all loggers.
	///
	/// @exception	throws a mr_utils::mr_pointerException on invalid testCase.
	/// @exception	throws a mr_utils::mr_pointerException on invalid loggers.
	///
	/// @return	true if successful, otherwise false.
	bool log(CppTest::Case& testCase);


	/// @brief	Add a logger object to the logger group.
	///
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	///
	/// @param	theLogger	Pointer to the logger to add.
	void addLogger( const mr_utils::SharedPtr<iTestLog>& theLogger );


	/// @brief	Load loggers from an init file.
	///
	/// @exception	throws a mr_utils::mr_exception if the load fails.
	///
	/// @param	fileName	Name of the int file.
	/// @param	fileType	Type of file loading.  Presently INI or XML
	void loadLoggers(std::string fileName, mr_utils::mr_string fileType);

protected:

	std::vector< mr_utils::SharedPtr<iTestLog> >	m_logs; ///< Vector of derived logger objects.
};



}

#endif