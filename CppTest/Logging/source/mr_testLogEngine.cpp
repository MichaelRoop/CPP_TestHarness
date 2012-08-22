//--------------------------------------------------------------------------------------
/// @file	mr_testLogEngine.cpp
/// @brief	Engine to drive the logging activity.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
//--------------------------------------------------------------------------------------
#include "mr_testLogEngine.h"
#include "mr_iTestLog.h"  
#include "mr_pointerException.h"
#include "mr_exception.h"
#include "mr_defines.h"
#include "mr_functors.h"
#include "CppTestLogInitialiserFactory.h"
#include "CppTestLogFactory.h"
#include "CppTestFixture.h"

#include <algorithm>


namespace mr_test
{


//--------------------------------------------------------------------------------------
/// @brief	Functor to write a log header per iteration on a container of log objects.
struct WriteLogHeaders {
	/// @brief	Function operator called on each iteration.
	///
	/// @param	theLog	The log object to call.
	void operator () ( mr_utils::SharedPtr<iTestLog>& theLog ) { 
		mr_utils::mr_exception::assertCondition( theLog.isValid(), FL, L("Invalid pointer") );
		theLog->writeHeader();  
	}
};


//--------------------------------------------------------------------------------------
/// @brief	Functor to write a log footer per iteration on a container of log objects.
struct WriteLogSummaries {
	/// @brief	Function operator called on each iteration.
	///
	/// @param	theLog	The log object to call.
	void operator () ( mr_utils::SharedPtr<iTestLog>& theLog ) { 
		mr_utils::mr_exception::assertCondition( theLog.isValid(), FL, L("Invalid pointer") );
		theLog->summarize();  
	}
};


//--------------------------------------------------------------------------------------
/// @brief	Functor to write a log entry per iteration on a container of log objects.
struct WriteLogEntries {

	/// @brief	Constructor.
	///
	/// @param	ptr	The testCase object that contains the information to log.
	WriteLogEntries(CppTest::Case& testCase) : m_case(testCase) { 
	}


	/// @brief	Function operator called on each iteration.
	///
	/// @param	theLog	The log object to call.
	void operator () (mr_utils::SharedPtr<iTestLog>& theLog) { 
		mr_utils::mr_exception::assertCondition(theLog.isValid(), FL, L("Invalid pointer"));
		theLog->log(this->m_case);  
	}
private:
	CppTest::Case& m_case; ///< The testCase information containing log information.
};


//--------------------------------------------------------------------------------------
/// @brief	Functor to load named test to testLogEngine.
struct loadLogsFromVector {
	loadLogsFromVector( 
		testLogEngine*			logEngine, 
		std::string&			fileName,
		mr_utils::mr_string&	fileType
	) 
	:	m_logEngine(logEngine),
		m_fileName(fileName),
		m_fileType(fileType) {
	}

	void operator () ( const mr_utils::mr_string& str ) {
		m_logEngine->addLogger(CppTest::LogFactory::Create(this->m_fileName, this->m_fileType, str));
	}

	testLogEngine*			m_logEngine;
	std::string&			m_fileName;
	mr_utils::mr_string&	m_fileType;
};

//--------------------------------------------------------------------------------------
// End functors.
//--------------------------------------------------------------------------------------


testLogEngine::testLogEngine()
{
}


testLogEngine::~testLogEngine() {
}


bool testLogEngine::writeHeaders() {
	std::for_each( m_logs.begin(), m_logs.end(), WriteLogHeaders() );
	return true;
}


bool testLogEngine::log(CppTest::Case& testCase) {
	//mr_utils::mr_pointerException::ptrAssert(fixture, FL );
	std::for_each(m_logs.begin(), m_logs.end(), WriteLogEntries(testCase));
	return true;
}


bool testLogEngine::writeSummaries() {
	std::for_each( m_logs.begin(), m_logs.end(), WriteLogSummaries() );
	return true;
}


void testLogEngine::addLogger(const mr_utils::SharedPtr<iTestLog>& theLog) {
	mr_utils::mr_exception::assertCondition(theLog.isValid(), FL, L("Invalid testLog"));
	m_logs.push_back( theLog );
}


void testLogEngine::loadLoggers(std::string fileName, mr_utils::mr_string fileType) {
	mr_utils::mr_exception::assertCondition( !fileName.empty(), FL, L("Empty file name") );
	std::vector<mr_utils::mr_string> logs = 
		CppTest::LogInitialiserFactory::Create( fileName, fileType )->getLogList();
		
	std::for_each(logs.begin(), logs.end(), loadLogsFromVector(this, fileName, fileType));		
}


}
