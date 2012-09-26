///--------------------------------------------------------------------------------------
/// @file	IMRTestEngineImplementation.h
/// @brief	Interface that hides the implementation of the test engine
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(IMR_TEST_ENGINE_IMPLEMENTATION_H)
#define IMR_TEST_ENGINE_IMPLEMENTATION_H

#include "MrTestTypes.h"
#include "mr_SharedPtr.h"


namespace MrTest {
			
class IFixture;					///< Forward declaration of fixture interface pointer
class IFixutureTestCaseNames;	///< Forward declaration of test case name object
class ITestFixtureInfoObject;	///< Forward declaration of Info objects to launch tests

///--------------------------------------------------------------------------------------
/// 
/// @brief	Interface that hides the implementation of the test engine
///
///--------------------------------------------------------------------------------------
class IEngineImplementation {
public:

	/// @brief	Load a DLL of test cases
	/// @param	dllName	Name of the DLL containing the test cases
	virtual void LoadTests(const mr_utils::mr_string& dllName) = 0;


	/// @brief 	Unload current DLL of test cases
	virtual void UnloadTests() = 0;


	/// @brief	Register a test case to the system for later recall. Use the macros to create
	///			and register the test case. The engine takes ownership of the created test case.
	/// @exception	mr_utils::mr_pointerException if the test case fixture pointer is invalid.
	virtual void RegisterCase(MrTest::IFixture* fixture) = 0;


	/// @brief Method to register a callback handler on the logged event
	virtual void RegisterLoggedEvent(MrTest::DataLoggedEvent loggedCallbackEvent) = 0;


	/// @brief Method to register a callback handler on the summary event
	virtual void RegisterSummaryEvent(MrTest::TestRunSummaryData summrayCallbackEvent) = 0;


	// TODO - unregister functionality on events


	/// TODO - load loggers from text xml passed in
	/// @brief	Load loggers from an init file.
	/// @exception	throws a mr_utils::mr_exception if the load fails.
	/// @param	fileName	Name of the int file.
	/// @param	fileType	Type of file loading.  Presently INI or XML
	virtual void LoadLoggersByFileDefinition(const mr_utils::mr_string& fileName, const mr_utils::mr_string& fileType) = 0;


	/// @brief	Process the test cases using the vector of info objects that were assembled
	/// @param	list	The test fixture info objects and their tests
	virtual void ProcessTestList(std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> >& list) = 0;


	/// @brief	Returns the unique id for the test run.
	virtual mr_utils::mr_string GetRunId() = 0;

	/// @brief Get all the test case names that have been registered
	virtual std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> > GetTestNames() = 0;

};

} // end namespace

#endif
