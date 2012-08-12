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
#include "mr_case.h"
#include "mr_pointerException.h"
#include "mr_defines.h"
#include "mr_iostream.h"

#include <time.h>
#include <algorithm>


namespace mr_test
{

//---------------------------------------------------------------------------------------
class HasNamedTestFunctor
{
public:
	HasNamedTestFunctor(const mr_utils::mr_string& name) : m_name(name) {
	}

	bool operator () (mr_test::testCase* test) {
		mr_utils::mr_pointerException::ptrAssert( test, FL );
		return test->HasTest(this->m_name);
	}
private:
	const mr_utils::mr_string& m_name;
};



//---------------------------------------------------------------------------------------
/// @brief	Dummy testCase to carry the not found designation if lookup fails.
class NonExistantTest : public mr_test::testCase
{
public:

	/// @brief	Constructor.
	///
	/// @param	testName	Unique name for the test.
	NonExistantTest( const mr_utils::mr_string& testName ) 
		: mr_test::testCase( testName, L( "Test not found" ) )
	{
		m_status = ST_NOT_EXISTS;
	}

	/// @brief	Override of test method to return true.
	///
	/// @return	Always returns true.
	bool test()		{ return true; }
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


void engine::regCase( mr_test::testCase* newCase )
{
	mr_utils::mr_pointerException::ptrAssert( newCase, FL );
	m_cases.push_back( newCase );
}


void engine::processScript( scriptReader& theReader )
{
	m_logEngine.writeHeaders();

	testInfoObject info = theReader.getNextTest();
	while (!info.isNull()) {
		bool infoUnused = false;
		if (info.isActive()) {
			// search vector for right test case per name.
			std::vector<mr_test::testCase*>::iterator it = 
				std::find_if( m_cases.begin(), m_cases.end(), HasNamedTestFunctor(info.getName()));

			// check if exists
			if (it == m_cases.end())
			{
				NonExistantTest test( info.getName() );
				this->logResults( &test );
			}
			else
			{
				while (!info.isNull()) {
					if (info.isActive()) {
						(*it)->RunTest(info.getName(), info.getArguments());
						this->logResults( (*it) );
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


void engine::logResults( mr_test::testCase* theCase )
{
	m_logEngine.log( theCase );
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