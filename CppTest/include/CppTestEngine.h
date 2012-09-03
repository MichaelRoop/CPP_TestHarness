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

#include "CppTestDefines.h"
#include "MrTestTypes.h"

#include "CppTestLogEngine.h"
#include "ICppTestScriptReader.h"
#include "ICppTestCase.h"
#include "ICppTestFixture.h"
#include "ICppTestFixtureTestCaseNames.h"
#include "ICppTestRunSummary.h"
#include "ICppTestDllManager.h"
#include "CppTestFixtureInfoObject.h"
#include "CppTestCaseCounter.h"
#include "mr_singleton.h"
#include "mr_string.h"
#include "mr_SharedPtr.h"
#include <vector>


namespace MrTest {
			
///--------------------------------------------------------------------------------------
/// 
/// @brief	A Singleton class to drive the test case architecture.
///
///--------------------------------------------------------------------------------------
class CPPTESCASE_API Engine : public mr_utils::singleton {
public:

	/// @brief	Static method to retrieve the unique instance of this class.
	/// The engine will be created on first call.
	/// @return	The unique instance of the test engine.
	static Engine& Instance();
	

	/// @brief	Load a DLL of test cases
	/// @param	dllName	Name of the DLL containing the test cases
	void LoadTests(const mr_utils::mr_string& dllName);


	/// @brief 	Unload current DLL of test cases
	void UnloadTests();


	/// @brief	Register a test case to the system for later recall.
	/// It is easier to use the macros to create and register the test case. The engine
	/// takes ownership of the created test case.
	///
	/// @exception	Throws a mr_utils::mr_pointerException if the test case fixture pointer is invalid.
	void RegisterCase(MrTest::IFixture* fixture);


	/// @brief Method to register a callback handler on the logged event
	void RegisterLoggedEvent(MrTest::DataLoggedEvent loggedCallbackEvent);


	/// @brief Method to register a callback handler on the summary event
	void RegisterSummaryEvent(MrTest::TestRunSummaryData summrayCallbackEvent);


	// TODO - unregister functionality on events


#if defined(THIS_IS_REDUNDANT_NEED_TO_DELETE)
	/// @brief	Process the test cases using the scriptReader object.
	/// @param	theReader	The object that parses the script that drives test selection and their
	///						arguments.
	void ProcessScript(MrTest::IScriptReader& theReader );
#endif

	/// @brief	Process the test cases using the vector of info objects that were assembled
	/// @param	list	The test fixture info objects and their tests
	void ProcessTestList(std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> >& list);


	/// @brief	Retrieve the results logging engine.
	///
	/// @return	The results logging engine.
	MrTest::LogEngine& GetLogEngine();


	/// @brief	Returns the unique id for the test run.
	mr_utils::mr_string GetRunId();

	/// @brief Get all the test case names that have been registered
	std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> > GetTestNames();

protected:
	///@brief	Default constructor
	Engine();


private:
	std::vector<MrTest::IFixture*> m_fixtures;	///< The vector of registered test case fixtures.
	static Engine*					m_instance;	///< The unique instance of the testEngine.
	mr_utils::mr_string				m_runId;	///< Unique ID for the run used in log files.
	MrTest::LogEngine				m_logEngine;///< The logging engine.
	std::vector<MrTest::DataLoggedEvent>	m_logEvents;///< Vector of registered log events
	std::vector<MrTest::TestRunSummaryData> m_summaryEvents;///< Vector of registered log events
	MrTest::CaseCounter			m_caseCounter; ///< track test case summary data
	mr_utils::SharedPtr<MrTest::IDllManager>	m_testDllManger; // Manages the test case DLLs


	/// @brief	Process one test case fixture based on information contained in the testInfoObject.
	///
	/// The testInfoObject has the test name for lookup as well as the arguments needed to 
	/// feed to the test case.
	///
	/// @param	testInfo	The data necessary to look up and run the test case.
	void ProcessCase(const MrTest::TestInfoObject& testInfo);


	/// @brief	Log the results of one test case across log outputs.
	/// @exception	Throws a mr_utils::mr_pointerException if the testCase pointer is invalid.
	/// @param	fixture	The test case fixture whose results are to be logged.
	void LogResults(MrTest::ICase& caseData);

};

} // end namespace

// Force export so it can be used in of std contained object 
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<MrTest::Engine*>;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<MrTest::Engine*>;

#endif
