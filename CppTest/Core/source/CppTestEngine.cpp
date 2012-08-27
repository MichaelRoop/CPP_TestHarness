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
#include "mr_pointerException.h"
#include "mr_defines.h"

#include <time.h>
#include <algorithm>


namespace CppTest {

//---------------------------------------------------------------------------------------
class HasNamedTestFunctor {
public:
	HasNamedTestFunctor(const mr_utils::mr_string& name) : m_name(name) {
	}

	bool operator () (CppTest::IFixture* fixture) {
		mr_utils::mr_pointerException::ptrAssert(fixture, _FL_ );
		return fixture->HasTest(this->m_name);
	}
private:
	const mr_utils::mr_string& m_name;
};

//---------------------------------------------------------------------------------------
/// @brief Populate a list of registered fixtures with their test cases
class BuildTestCaseList {
public:
	BuildTestCaseList(std::vector<mr_utils::SharedPtr<CppTest::IFixutureTestCaseNames> >& names) 
		: m_names(names) {
	}

	void operator () (CppTest::IFixture* fixture) {
		mr_utils::mr_pointerException::ptrAssert(fixture, _FL_ );
		this->m_names.push_back(fixture->GetTestNames());
	}
private:
	std::vector<mr_utils::SharedPtr<CppTest::IFixutureTestCaseNames> >& m_names;
};

// End of functors
//---------------------------------------------------------------------------------------

/// @brief Dummy test case to report to the loggers that the names test case was not found
class NonExistantTestData : public CppTest::Case {
public:
	/// @brief	Constructor.
	/// @param	testName	Unique name for the test.
	NonExistantTestData(const mr_utils::mr_string& name) 
		: CppTest::Case(name, L("Test not found") ) {
			this->Status = CppTest::ICase::ST_NOT_EXISTS;
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


void Engine::RegisterCase(CppTest::IFixture* fixture) {
	mr_utils::mr_pointerException::ptrAssert( fixture, _FL_ );
	this->m_fixtures.push_back(fixture);
}


void Engine::ProcessScript(CppTest::IScriptReader& theReader ) {
	this->m_logEngine.WriteHeaders();

	CppTest::TestInfoObject info = theReader.getNextTest();
	while (!info.IsNull()) {
		bool infoUnused = false;
		if (info.IsActive()) {
			// search vector for right test case per name.
			std::vector<CppTest::IFixture*>::iterator it = 
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
					info = theReader.getNextTest();
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

		// Only get next if not already hit end. Another case is when the info is valid but unused
		if (!info.IsNull() && !infoUnused) {
			info = theReader.getNextTest();
		}
	}
	this->m_logEngine.WriteSummaries();
}


void Engine::LogResults(CppTest::ICase& testCase) {
	this->m_logEngine.Log(testCase);
}


CppTest::LogEngine& Engine::GetLogEngine() {
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


std::vector<mr_utils::SharedPtr<CppTest::IFixutureTestCaseNames> > Engine::GetTestNames() {
	std::vector<mr_utils::SharedPtr<CppTest::IFixutureTestCaseNames> > testNames;
	std::for_each(this->m_fixtures.begin(), this->m_fixtures.end(), BuildTestCaseList(testNames));
	return testNames;
}


}