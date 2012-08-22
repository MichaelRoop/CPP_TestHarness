//--------------------------------------------------------------------------------------
/// @file	CppTestLogEngine.h
/// @brief	Engine to drive the logging activity.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
//--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_LOG_ENGINE_H)
#define CPP_TEST_LOG_ENGINE_H


#include "mr_SharedPtr.h"
#include "mr_string.h"
#include <vector>


namespace CppTest {

class ILog;
class Fixture;
class Case;


//--------------------------------------------------------------------------------------
/// 
/// @brief	Drives the logging of testCase information across a variable number
///			of derived Logs.
///
//--------------------------------------------------------------------------------------
class LogEngine {
public:

	/// @brief	Constructor.
	LogEngine();


	/// @brief	Destructor.
	virtual ~LogEngine();


	/// @brief	Write the header information across all loggers.
	/// @exception	throws a mr_utils::mr_pointerException on invalid loggers.
	/// @return	true if successful, otherwise false.
	bool WriteHeaders();


	/// @brief	Write the summary information across all loggers.
	/// @exception	throws a mr_utils::mr_pointerException on invalid loggers.
	/// @return	true if successful, otherwise false.
	bool WriteSummaries();


	/// @brief	Log the test case information across all loggers.
	///
	/// @exception	throws a mr_utils::mr_pointerException on invalid testCase.
	/// @exception	throws a mr_utils::mr_pointerException on invalid loggers.
	///
	/// @return	true if successful, otherwise false.
	bool Log(CppTest::Case& testCase);


	/// @brief	Add a logger object to the logger group.
	///
	/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
	///
	/// @param	theLogger	Pointer to the logger to add.
	void AddLogger(const mr_utils::SharedPtr<CppTest::ILog>& theLogger);


	/// @brief	Load loggers from an init file.
	///
	/// @exception	throws a mr_utils::mr_exception if the load fails.
	///
	/// @param	fileName	Name of the int file.
	/// @param	fileType	Type of file loading.  Presently INI or XML
	void LoadLoggers(std::string fileName, mr_utils::mr_string fileType);

protected:

	std::vector< mr_utils::SharedPtr<CppTest::ILog> >	m_logs; ///< Vector of derived logger objects.
};



}

#endif