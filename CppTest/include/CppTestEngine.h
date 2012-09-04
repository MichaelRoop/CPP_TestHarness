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
#include "mr_singleton.h"
#include "mr_string.h"
#include "mr_SharedPtr.h"
#include <vector>


namespace MrTest {

class IFixture;
class ITestFixtureInfoObject;			
class IFixutureTestCaseNames;
class IEngineImplementation;

///--------------------------------------------------------------------------------------
/// 
/// @brief	A Singleton class to drive the test case architecture.
///
///--------------------------------------------------------------------------------------
class CPPTESCASE_API Engine : public mr_utils::singleton {
public:

	/// @brief	Destructor
	virtual ~Engine();


	/// @brief	Static method to retrieve the unique instance of this class.
	///			The engine will be created on first call.
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


	/// TODO - load loggers from text xml passed in
	/// @brief	Load loggers from an init file.
	/// @exception	throws a mr_utils::mr_exception if the load fails.
	/// @param	fileName	Name of the int file.
	/// @param	fileType	Type of file loading.  Presently INI or XML
	void LoadLoggersByFileDefinition(const mr_utils::mr_string& fileName, const mr_utils::mr_string& fileType);


	/// @brief	Process the test cases using the vector of info objects that were assembled
	/// @param	list	The test fixture info objects and their tests
	void ProcessTestList(std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> >& list);


	/// @brief	Returns the unique id for the test run.
	mr_utils::mr_string GetRunId();


	/// @brief Get all the test case names that have been registered
	std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> > GetTestNames();

protected:
	///@brief	Default constructor
	Engine();

private:
	MrTest::IEngineImplementation*	m_implementation;	///< The implementation object to hide details
	static Engine*					m_instance;			///< The unique instance of the testEngine.
};

} // end namespace

// Force export so it can be used in of std contained object 
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<MrTest::Engine*>;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<MrTest::Engine*>;

#endif
