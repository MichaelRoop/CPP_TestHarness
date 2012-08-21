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
#include "mr_testEngine.h"
#include "CppTestFixture.h"
#include "mr_pointerException.h"
#include "mr_defines.h"
#include "mr_iostream.h"

#include <time.h>
#include <algorithm>


namespace mr_test {

//---------------------------------------------------------------------------------------
class HasNamedTestFunctor
{
public:
	HasNamedTestFunctor(const mr_utils::mr_string& name) : m_name(name) {
	}

	bool operator () (CppTest::Fixture* fixture) {
		mr_utils::mr_pointerException::ptrAssert(fixture, _FL_ );
		return fixture->HasTest(this->m_name);
	}
private:
	const mr_utils::mr_string& m_name;
};


//---------------------------------------------------------------------------------------
/// @brief	Dummy testCase to carry the not found designation if lookup fails.
//class NonExistantTest : public CppTest::Fixture
//{
//public:
//
//	/// @brief	Constructor.
//	///
//	/// @param	testName	Unique name for the test.
//	NonExistantTest( const mr_utils::mr_string& testName ) 
//		: CppTest::Fixture( testName, L( "Test not found" ) )
//	{
//		m_status = ST_NOT_EXISTS;
//	}
//
//	/// @brief	Override of test method to return true.
//	///
//	/// @return	Always returns true.
//	bool test()		{ return true; }
//};


class NonExistantTestData : public CppTest::Case
{
public:
	/// @brief	Constructor.
	/// @param	testName	Unique name for the test.
	NonExistantTestData(const mr_utils::mr_string& name) 
		: CppTest::Case(name, L("Test not found") ) {
		this->Status = ST_NOT_EXISTS;
	}
};




// End of functors
//---------------------------------------------------------------------------------------


// Declaration of static instance
engine* engine::m_instance = 0;


engine& engine::getInstance()
{
	if (m_instance == 0)
	{
		m_instance = new engine();
	}
	return *m_instance;
}


void engine::regCase(CppTest::Fixture* fixture) {
	mr_utils::mr_pointerException::ptrAssert( fixture, _FL_ );
	this->m_fixtures.push_back(fixture);
}


void engine::processScript( scriptReader& theReader )
{
	m_logEngine.writeHeaders();

	testInfoObject info = theReader.getNextTest();
	while (!info.isNull()) {
		bool infoUnused = false;
		if (info.isActive()) {
			// search vector for right test case per name.
			std::vector<CppTest::Fixture*>::iterator it = 
				std::find_if(
					this->m_fixtures.begin(), 
					this->m_fixtures.end(), 
					HasNamedTestFunctor(info.getName()));

			// check if exists
			if (it == this->m_fixtures.end())
			{
				NonExistantTestData test( info.getName() );
				this->logResults(test);
			}
			else
			{
				while (!info.isNull()) {
					if (info.isActive()) {
						(*it)->RunTest(info.getName(), info.getArguments());
						this->logResults((*it)->CurrentTestCase());
					}
					info = theReader.getNextTest();
					if (info.isNull()) {
						(*it)->ResetFixture();
						break;
					}

					if (!(*it)->HasTest(info.getName())) {
						infoUnused = true;
						(*it)->ResetFixture();
						break;
					}
				}
			}
		}

		// Only get next if not already hit end. Another case is when the info is valid but unused
		if (!info.isNull() && !infoUnused) {
			info = theReader.getNextTest();
		}
	}
	m_logEngine.writeSummaries();
}


void engine::logResults(CppTest::Case& testCase) {
	m_logEngine.log(testCase);
}


testLogEngine& engine::getLogEngine()
{
	return m_logEngine;
}


mr_utils::mr_string engine::getRunId()
{
	if (m_runId.empty())
	{
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


}