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
#include "mr_pointerException.h"
#include "mr_defines.h"

//#include "mr_iostream.h"

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


class HasNamedFixtureFunctor {
public:
	HasNamedFixtureFunctor(const mr_utils::mr_string& name) : m_name(name) {
	}

	bool operator () (CppTest::IFixture* fixture) {
		mr_utils::mr_pointerException::ptrAssert(fixture, _FL_ );
		return fixture->Name() == this->m_name;
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


/// @brief Dummy test case to report to the loggers that the names test case was not found
class DisabledTestData : public CppTest::Case {
public:
	/// @brief	Constructor.
	/// @param	testName	Unique name for the test.
	DisabledTestData(const mr_utils::mr_string& name) 
		: CppTest::Case(name, L("Test Disabled") ) {
			this->Status = CppTest::ICase::ST_DISABLED;
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

#ifdef THIS_IS_REDUNDANT_NEED_TO_DELETE
void Engine::ProcessScript(CppTest::IScriptReader& theReader ) {
	this->m_logEngine.WriteHeaders();

	mr_utils::mr_string fixtureName;


	CppTest::TestInfoObject info = theReader.getNextTest(fixtureName);
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


void Engine::ProcessTestList(std::vector< mr_utils::SharedPtr<CppTest::ITestFixtureInfoObject> >& list) {

	this->m_logEngine.WriteHeaders();

	// Iterate through each Fixture info
	std::vector< mr_utils::SharedPtr<CppTest::ITestFixtureInfoObject> >::iterator itFixtureInfo = list.begin();
	for (; itFixtureInfo != list.end(); itFixtureInfo++) {

		// Only look up the actual fixture if the Fixture Info has test case infos
		const std::vector<CppTest::TestInfoObject>& testInfos = (*itFixtureInfo)->GetTestInfoVector();
		if (testInfos.size() > 0) {

			// Retrieve the actual fixture pointer
			std::vector<CppTest::IFixture*>::iterator itFixture = 
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
				std::vector<CppTest::TestInfoObject>::const_iterator itTestInfo = testInfos.begin();
				for (; itTestInfo != testInfos.end(); ++itTestInfo) {

					mr_utils::mr_string name = itTestInfo->GetName(); 
					if ((*itFixture)->HasTest(name)) {
						if (itTestInfo->IsActive()) {
							(*itFixture)->RunTest(name, itTestInfo->GetArguments());
							this->LogResults((*itFixture)->CurrentTestCase());
						}
						else {
							// Test found but marked disabled
							this->LogResults(DisabledTestData(name));
						}
					}
					else {
						// test not found by name
						this->LogResults(NonExistantTestData(name));
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