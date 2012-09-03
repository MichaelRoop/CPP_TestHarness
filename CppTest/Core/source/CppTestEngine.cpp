///--------------------------------------------------------------------------------------
/// @file	CppTestEngine.cpp
/// @brief	Class that drives the testing architecture.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestEngine.h"
#include "CppTestFixture.h"
#include "CppTestCase.h"
#include "CppTestInfoObject.h"
#include "CppTestRunSummary.h"
#include "CppTestDllManager.h"
#include "mr_pointerException.h"
#include "mr_defines.h"

#include "mr_iostream.h"

#include <time.h>
#include <algorithm>


namespace MrTest {

//---------------------------------------------------------------------------------------
/// @brief Functor to check for existence of named test case in fixture
class HasNamedTestFunctor {
public:
	HasNamedTestFunctor(const mr_utils::mr_string& name) : m_name(name) {
	}

	bool operator () (MrTest::IFixture* fixture) {
		mr_utils::mr_pointerException::ptrAssert(fixture, _FL_ );
		return fixture->HasTest(this->m_name);
	}
private:
	const mr_utils::mr_string& m_name;
};


/// @brief Functor to check for existence of named test fixture 
class HasNamedFixtureFunctor {
public:
	HasNamedFixtureFunctor(const mr_utils::mr_string& name) : m_name(name) {
	}

	bool operator () (MrTest::IFixture* fixture) {
		mr_utils::mr_pointerException::ptrAssert(fixture, _FL_ );
		return fixture->Name() == this->m_name;
	}
private:
	const mr_utils::mr_string& m_name;
};


/// @brief Populate a list of registered fixtures with their test cases
class BuildTestCaseList {
public:
	BuildTestCaseList(std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> >& names) 
		: m_names(names) {
	}

	void operator () (MrTest::IFixture* fixture) {
		mr_utils::mr_pointerException::ptrAssert(fixture, _FL_ );
		this->m_names.push_back(fixture->GetTestNames());
	}
private:
	std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> >& m_names;
};


/// @brief Fire off each log callback event
class FireLoggedEventsFunctor {
public:
	FireLoggedEventsFunctor(const MrTest::ICase& testCase) : m_case(testCase) {
	}

	void operator () (const MrTest::DataLoggedEvent logEvent) {
		mr_utils::mr_pointerException::ptrAssert(logEvent, _FL_ );
		(*logEvent)(this->m_case);
	}

	const MrTest::ICase& m_case;
};


/// @brief Fire off each summary callback event
class FireSummaryEventsFunctor {
public:
	FireSummaryEventsFunctor(const MrTest::CaseCounter& caseCounter) {
		this->m_summary = new MrTest::RunSummary(caseCounter);
	}

	void operator () (const MrTest::TestRunSummaryData summaryEvent) {
		mr_utils::mr_pointerException::ptrAssert(summaryEvent, _FL_ );
		(*summaryEvent)((*this->m_summary));
	}

	mr_utils::SharedPtr<MrTest::IRunSummary> m_summary;
};


// End of functors
//---------------------------------------------------------------------------------------

/// @brief Dummy test case to report to the loggers that the names test case was not found
class NonExistantTestData : public MrTest::Case {
public:
	/// @brief	Constructor.
	/// @param	testName	Unique name for the test.
	NonExistantTestData(const mr_utils::mr_string& fixtureName, const mr_utils::mr_string& name) 
		: MrTest::Case(fixtureName, name, L("Test not found") ) {
			this->Status = MrTest::ICase::ST_NOT_EXISTS;
	}
};


/// @brief Dummy test case to report to the loggers that the names test case was not found
class DisabledTestData : public MrTest::Case {
public:
	/// @brief	Constructor.
	/// @param	testName	Unique name for the test.
	DisabledTestData(const mr_utils::mr_string& fixtureName, const mr_utils::mr_string& name) 
		: MrTest::Case(fixtureName, name, L("Test Disabled") ) {
			this->Status = MrTest::ICase::ST_DISABLED;
	}
};


// Declaration of static instance
Engine* Engine::m_instance = 0;


Engine& Engine::Instance() {
	if (m_instance == 0) {
		m_instance = new Engine();
	}
	return *m_instance;
}


Engine::Engine() {
	mr_cout << _L_("*** Default constructor called") << std::endl;
	this->m_testDllManger = new MrTest::DllManager();
}


void Engine::RegisterCase(MrTest::IFixture* fixture) {
	mr_utils::mr_pointerException::ptrAssert( fixture, _FL_ );
	this->m_fixtures.push_back(fixture);
}

#ifdef THIS_IS_REDUNDANT_NEED_TO_DELETE
void Engine::ProcessScript(MrTest::IScriptReader& theReader ) {
	this->m_logEngine.WriteHeaders();

	mr_utils::mr_string fixtureName;


	MrTest::TestInfoObject info = theReader.getNextTest(fixtureName);
	while (!info.IsNull()) {
		bool infoUnused = false;
		if (info.IsActive()) {
			// search vector for right test case per name.
			std::vector<MrTest::IFixture*>::iterator it = 
				std::find_if(
					this->m_fixtures.begin(), 
					this->m_fixtures.end(), 
					HasNamedTestFunctor(info.GetName()));

			// check if exists
			if (it == this->m_fixtures.end())
			{
				NonExistantTestData test( info.GetName() );
				this->LogResults(test);
			}
			else
			{
				while (!info.IsNull()) {
					if (info.IsActive()) {
						(*it)->RunTest(info.GetName(), info.GetArguments());
						this->LogResults((*it)->CurrentTestCase());
					}
					else {
						this->LogResults(DisabledTestData(info.GetName()));
					}
					info = theReader.getNextTest(fixtureName);
					if (info.IsNull()) {
						(*it)->ResetFixture();
						break;
					}

					if (!(*it)->HasTest(info.GetName())) {
						infoUnused = true;
						(*it)->ResetFixture();
						break;
					}
				}
			}
		}
		else {
			this->LogResults(DisabledTestData(info.GetName()));
		}


		// Only get next if not already hit end. Another case is when the info is valid but unused
		if (!info.IsNull() && !infoUnused) {
			info = theReader.getNextTest(fixtureName);
		}
	}
	this->m_logEngine.WriteSummaries();
}
#endif


void Engine::LoadTests(const mr_utils::mr_string& dllName) {
	this->m_testDllManger->Load(dllName);
}


void Engine::UnloadTests() {
	this->m_testDllManger->Unload();
}


void Engine::ProcessTestList(std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> >& list) {
	this->m_caseCounter.Reset();
	this->m_logEngine.WriteHeaders();

	// Iterate through each Fixture info
	std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> >::iterator itFixtureInfo = list.begin();
	for (; itFixtureInfo != list.end(); itFixtureInfo++) {

		// Only look up the actual fixture if the Fixture Info has test case infos
		const std::vector<MrTest::TestInfoObject>& testInfos = (*itFixtureInfo)->GetTestInfoVector();
		if (testInfos.size() > 0) {

			// Retrieve the actual fixture pointer
			std::vector<MrTest::IFixture*>::iterator itFixture = 
				std::find_if(
					this->m_fixtures.begin(), 
					this->m_fixtures.end(), 
					HasNamedFixtureFunctor((*itFixtureInfo)->GetName()));

			// check if the fixture is registered with the engine
			if (itFixture == this->m_fixtures.end()) {
				// TODO - Log failure to find the Fixture
			}
			else {
				// iterate through each test info in the fixture info to find the tests
				std::vector<MrTest::TestInfoObject>::const_iterator itTestInfo = testInfos.begin();
				for (; itTestInfo != testInfos.end(); ++itTestInfo) {

					mr_utils::mr_string name = itTestInfo->GetName(); 
					if ((*itFixture)->HasTest(name)) {
						if (itTestInfo->IsActive()) {
							(*itFixture)->RunTest(name, itTestInfo->GetArguments());
							this->LogResults((*itFixture)->CurrentTestCase());
						}
						else {
							// Test found but marked disabled
							this->LogResults(DisabledTestData((*itFixture)->Name(), name));
						}
					}
					else {
						// test not found by name
						this->LogResults(NonExistantTestData((*itFixture)->Name(), name));
					}
				}
				// Last test in fixture. Need to close off the fixture
				(*itFixture)->ResetFixture();
			}
		}
		else {
			// No test case infos in fixture info - log this
		}
	}

	std::for_each(
		this->m_summaryEvents.begin(), 
		this->m_summaryEvents.end(), 
		FireSummaryEventsFunctor(this->m_caseCounter));

	this->m_logEngine.WriteSummaries();
}


void Engine::LogResults(MrTest::ICase& testCase) {
	this->m_logEngine.Log(testCase);
	this->m_caseCounter.Count(testCase);

	std::for_each(
		this->m_logEvents.begin(), 
		this->m_logEvents.end(), 
		FireLoggedEventsFunctor(testCase));
}


MrTest::LogEngine& Engine::GetLogEngine() {
	return this->m_logEngine;
}


mr_utils::mr_string Engine::GetRunId() {
	if (m_runId.empty()) {
		time_t		rawtime;
		struct tm*	t;
		char		buff[200];

		time( &rawtime );
		t = localtime( &rawtime );
		strftime( buff, 200, "%Y%m%d%H%M%S", t );

		mr_utils::mr_stringstream os;
		os << buff;
		m_runId = os.str();
	}
	return m_runId;
}


std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> > Engine::GetTestNames() {
	std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> > testNames;
	std::for_each(this->m_fixtures.begin(), this->m_fixtures.end(), BuildTestCaseList(testNames));
	return testNames;
}


void Engine::RegisterLoggedEvent(MrTest::DataLoggedEvent loggedCallbackEvent) {
	mr_utils::mr_pointerException::ptrAssert(loggedCallbackEvent, _FL_);
	this->m_logEvents.push_back(loggedCallbackEvent);
}


void Engine::RegisterSummaryEvent(MrTest::TestRunSummaryData summrayCallbackEvent) {
	mr_utils::mr_pointerException::ptrAssert(summrayCallbackEvent, _FL_);
	this->m_summaryEvents.push_back(summrayCallbackEvent);
}


}

