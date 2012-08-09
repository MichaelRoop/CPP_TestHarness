///--------------------------------------------------------------------------------------
/// @file	mr_testEngine.h
/// @brief	Class that drives the testing architecture.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_ENGINE_H)
#define MR_TEST_ENGINE_H

#include "mr_singleton.h"
#include "mr_testLogEngine.h"
#include "mr_string.h"
#include "mr_scriptReader.h"

#include <vector>


namespace mr_test
{

class testCase;


///--------------------------------------------------------------------------------------
/// 
/// @brief	A Singleton class to drive the test case architecture.
///
///--------------------------------------------------------------------------------------
class engine : public mr_utils::singleton
{
public:

	/// @brief	Static method to retrieve the unique instance of this class.
	///
	/// The engine will be created on first call.
	///
	/// @return	The unique instance of the test engine.
	static engine& getInstance();


	/// @brief	Register a test case to the system for later recall.
	///
	/// It is easier to use the macros to create and register the test case. The engine
	/// takes ownership of the created test case.
	///
	/// @exception	Throws a mr_utils::mr_pointerException if the testCase pointer is invalid.
	void regCase( testCase* newCase );


	/// @brief	Process the test cases using the scriptReader object.
	///
	/// @param	theReader	The object that parses the script that drives test selection and their
	///						arguments.
	void processScript( scriptReader& theReader );


	/// @brief	Retrieve the results logging engine.
	///
	/// @return	The results logging engine.
	testLogEngine& getLogEngine();


	/// @brief	Returns the unique id for the test run.
	mr_utils::mr_string getRunId();

private:

	std::vector<mr_test::testCase*> m_cases;	///< The vector of registered testCase objects.
	static engine*					m_instance;	///< The unique instance of the testEngine.
	mr_utils::mr_string				m_runId;	///< Unique ID for the run used in log files.
	testLogEngine					m_logEngine;///< The logging engine.


	/// @brief	Process one testCase based on information contained in the testInfoObject.
	///
	/// The testInfoObject has the test name for lookup as well as the arguments needed to 
	/// feed to the test case.
	///
	/// @param	testInfo	The data necessary to look up and run the test case.
	void processCase(  const testInfoObject& testInfo );


	/// @brief	Log the results of one test case across log outputs.
	///
	/// @exception	Throws a mr_utils::mr_pointerException if the testCase pointer is invalid.
	///
	/// @param	theCase	The test case whose results are to be logged.
	void logResults( mr_test::testCase* theCase );


};

}


#endif