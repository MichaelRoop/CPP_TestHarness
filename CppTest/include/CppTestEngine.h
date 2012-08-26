///--------------------------------------------------------------------------------------
/// @file	CppTestEngine.h
/// @brief	Class that drives the testing architecture.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_ENGINE_H)
#define CPP_TEST_ENGINE_H

#include "CppTestLogEngine.h"
#include "ICppTestScriptReader.h"
#include "ICppTestCase.h"
#include "ICppTestFixture.h"
#include "mr_singleton.h"
#include "mr_string.h"

#include <vector>

namespace CppTest {

	class Fixture;
	class Case;

///--------------------------------------------------------------------------------------
/// 
/// @brief	A Singleton class to drive the test case architecture.
///
///--------------------------------------------------------------------------------------
class Engine : public mr_utils::singleton
{
public:

	/// @brief	Static method to retrieve the unique instance of this class.
	/// The engine will be created on first call.
	/// @return	The unique instance of the test engine.
	static Engine& Instance();


	/// @brief	Register a test case to the system for later recall.
	/// It is easier to use the macros to create and register the test case. The engine
	/// takes ownership of the created test case.
	///
	/// @exception	Throws a mr_utils::mr_pointerException if the test case fixture pointer is invalid.
	void RegisterCase(CppTest::IFixture* fixture);


	/// @brief	Process the test cases using the scriptReader object.
	/// @param	theReader	The object that parses the script that drives test selection and their
	///						arguments.
	void ProcessScript(CppTest::IScriptReader& theReader );


	/// @brief	Retrieve the results logging engine.
	///
	/// @return	The results logging engine.
	CppTest::LogEngine& GetLogEngine();


	/// @brief	Returns the unique id for the test run.
	mr_utils::mr_string GetRunId();

private:

	std::vector<CppTest::IFixture*> m_fixtures;	///< The vector of registered test case fixtures.
	static Engine*					m_instance;	///< The unique instance of the testEngine.
	mr_utils::mr_string				m_runId;	///< Unique ID for the run used in log files.
	CppTest::LogEngine				m_logEngine;///< The logging engine.


	/// @brief	Process one test case fixture based on information contained in the testInfoObject.
	///
	/// The testInfoObject has the test name for lookup as well as the arguments needed to 
	/// feed to the test case.
	///
	/// @param	testInfo	The data necessary to look up and run the test case.
	void ProcessCase(const CppTest::TestInfoObject& testInfo);


	/// @brief	Log the results of one test case across log outputs.
	///
	/// @exception	Throws a mr_utils::mr_pointerException if the testCase pointer is invalid.
	///
	/// @param	fixture	The test case fixture whose results are to be logged.
	void LogResults(CppTest::ICase& caseData);

};

}


#endif