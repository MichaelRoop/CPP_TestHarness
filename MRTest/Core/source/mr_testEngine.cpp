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
/// @brief Functor to determine if the name is a match for the test case name.
class isTestNamed
{
public:
	/// @brief	Constructor.
	///
	/// @param	name	The lookup name.
	isTestNamed( const mr_utils::mr_string& name ) : m_name( name ) {}


	/// @brief	The function operator overloaded to check for each testCase.
	///
	/// The comparisons are case sensitve.
	///
	/// @param	aCase	Pointer to the current testCase being evaluated.
	///
	/// @return	true if the name matches otherwise false.
	bool operator () ( mr_test::testCase* aCase )
	{
		mr_utils::mr_pointerException::ptrAssert( aCase, FL );
		return aCase->name() == m_name;
	}
private:

	const mr_utils::mr_string& m_name; ///< The name to compare to each testCase.
};


class HasNamedTest
{
public:
	HasNamedTest(const mr_utils::mr_string& name) : m_name(name) {
	}

	bool operator () (mr_test::testCase* test) {

	//	mr_cout << _L_("** Lookup Name:") << this->m_name << _L_(" Registered test name:") << test->name() << std::endl;

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

#define BLAHBLAH
#ifdef BLAHBLAH
void engine::processScript( scriptReader& theReader )
{
	m_logEngine.writeHeaders();

	testInfoObject info = theReader.getNextTest();
	while (!info.isNull()) {
		bool infoUnused = false;
		if (info.isActive()) {
			//this->processCase( info );
			// search vector for right test case per name.
			std::vector<mr_test::testCase*>::iterator it = 
				std::find_if( m_cases.begin(), m_cases.end(), HasNamedTest(info.getName()));

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


#else
void engine::processScript( scriptReader& theReader )
{
	m_logEngine.writeHeaders();

	testInfoObject info = theReader.getNextTest();
	while (!info.isNull())
	{
		if (info.isActive())
		{
			this->processCase( info );
		}
		info = theReader.getNextTest();
	}
	m_logEngine.writeSummaries();
}
#endif


//void engine::processCase( const mr_utils::mr_string& name, const mr_utils::mr_string& args )
void engine::processCase( const testInfoObject& info )
{
	// search vector for right test case per name.
	std::vector<mr_test::testCase*>::iterator it = 
		std::find_if( m_cases.begin(), m_cases.end(), isTestNamed( info.getName() ) );
		
	// check if exists
	if (it == m_cases.end())
	{
		NonExistantTest test( info.getName() );
		this->logResults( &test );
	}
	else
	{
		(*it)->executeInit( info.getArguments() );
		(*it)->executeSetup();
		(*it)->executeTest();
		(*it)->executeCleanup();
		this->logResults( (*it) );

		// delete it now.
		delete (*it);
		(*it) = 0;
		m_cases.erase( it );
	}
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