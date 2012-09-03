///--------------------------------------------------------------------------------------
/// @file	MRTestEngineImplementation.h
/// @brief	Class that hides the implementation of the test engine
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_ENGINE_IMPLEMENTATION_H)
#define MR_TEST_ENGINE_IMPLEMENTATION_H

#include "IMrTestEngineImplementation.h"
#include "CppTestLogEngine.h"
#include "CppTestCaseCounter.h"
#include "ICppTestDllManager.h"
#include "mr_SharedPtr.h"

namespace MrTest {
			
class IFixture;					///< Forward declaration of fixture interface pointer
class IFixutureTestCaseNames;	///< Forward declaration of test case name object
class ITestFixtureInfoObject;	///< Forward declaration of Info objects to launch tests
class TestInfoObject;			///< Forward declaration of Info objects to launch a test

///--------------------------------------------------------------------------------------
/// 
/// @brief	Class that hides the implementation of the test engine
///
///--------------------------------------------------------------------------------------
class EngineImplementation : public MrTest::IEngineImplementation {
public:

	/// @brief	Default constructor
	EngineImplementation();


	/// @brief	Load a DLL of test cases
	/// @param	dllName	Name of the DLL containing the test cases
	virtual void LoadTests(const mr_utils::mr_string& dllName);


	/// @brief 	Unload current DLL of test cases
	virtual void UnloadTests();


	/// @brief	Register a test case to the system for later recall.
	/// It is easier to use the macros to create and register the test case. The engine
	/// takes ownership of the created test case.
	///
	/// @exception	Throws a mr_utils::mr_pointerException if the test case fixture pointer is invalid.
	virtual void RegisterCase(MrTest::IFixture* fixture);


	/// @brief Method to register a callback handler on the logged event
	virtual void RegisterLoggedEvent(MrTest::DataLoggedEvent loggedCallbackEvent);


	/// @brief Method to register a callback handler on the summary event
	virtual void RegisterSummaryEvent(MrTest::TestRunSummaryData summrayCallbackEvent);


	// TODO - unregister functionality on events


	/// TODO - load loggers from text xml passed in
	/// @brief	Load loggers from an init file.
	/// @exception	throws a mr_utils::mr_exception if the load fails.
	/// @param	fileName	Name of the int file.
	/// @param	fileType	Type of file loading.  Presently INI or XML
	virtual void LoadLoggersByFileDefinition(const std::string& fileName, const mr_utils::mr_string& fileType);


	/// @brief	Process the test cases using the vector of info objects that were assembled
	/// @param	list	The test fixture info objects and their tests
	virtual void ProcessTestList(std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> >& list);


	/// @brief	Returns the unique id for the test run.
	virtual mr_utils::mr_string GetRunId();

	/// @brief Get all the test case names that have been registered
	virtual std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> > GetTestNames();

private:
	std::vector<MrTest::IFixture*>			m_fixtures;		///< The vector of registered test case fixtures.
	mr_utils::mr_string						m_runId;		///< Unique ID for the run used in log files.
	MrTest::LogEngine						m_logEngine;	///< The logging engine.
	std::vector<MrTest::DataLoggedEvent>	m_logEvents;	///< Vector of registered log events
	std::vector<MrTest::TestRunSummaryData> m_summaryEvents;///< Vector of registered log events
	MrTest::CaseCounter						m_caseCounter;	///< track test case summary data
	mr_utils::SharedPtr<MrTest::IDllManager>m_testDllManger;///< Manages the test case DLLs


	/// @brief	Process one test case fixture based on information contained in the testInfoObject.
	///			The testInfoObject has the test name for lookup as well as the arguments needed to 
	///			feed to the test case.
	/// @param	testInfo	The data necessary to look up and run the test case.
	void ProcessCase(const MrTest::TestInfoObject& testInfo);


	/// @brief	Log the results of one test case across log outputs.
	/// @exception	Throws a mr_utils::mr_pointerException if the testCase pointer is invalid.
	/// @param	fixture	The test case fixture whose results are to be logged.
	void LogResults(MrTest::ICase& caseData);

};

} // end namespace

#endif
