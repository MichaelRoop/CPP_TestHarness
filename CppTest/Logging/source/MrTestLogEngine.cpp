//--------------------------------------------------------------------------------------
/// @file	MrTestLogEngine.cpp
/// @brief	Engine to drive the logging activity.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
//--------------------------------------------------------------------------------------
#include "MrTestLogEngine.h"
#include "MrTestLogInitialiserFactory.h"
#include "MrTestLogFactory.h"
#include "mr_exception.h"
#include "mr_defines.h"

#include <algorithm>


namespace MrTest {


//--------------------------------------------------------------------------------------
/// @brief	Functor to write a log header per iteration on a container of log objects.
struct WriteLogHeaders {
	/// @brief	Function operator called on each iteration.
	/// @param	theLog	The log object to call.
	void operator () (mr_utils::SharedPtr<MrTest::ILog>& log ) { 
		mr_utils::mr_exception::assertCondition(log.isValid(), _FL_, _L_("Invalid pointer"));
		log->WriteHeader();  
	}
};


//--------------------------------------------------------------------------------------
/// @brief	Functor to write a log footer per iteration on a container of log objects.
struct WriteLogSummaries {
	/// @brief	Function operator called on each iteration.
	/// @param	theLog	The log object to call.
	void operator () (mr_utils::SharedPtr<MrTest::ILog>& log) { 
		mr_utils::mr_exception::assertCondition(log.isValid(), _FL_, _L_("Invalid pointer"));
		log->Summarize();  
	}
};


//--------------------------------------------------------------------------------------
/// @brief	Functor to write a log entry per iteration on a container of log objects.
struct WriteLogEntries {

	/// @brief	Constructor.
	///
	/// @param	ptr	The testCase object that contains the information to log.
	WriteLogEntries(MrTest::ICase& testCase) : m_case(testCase) { 
	}


	/// @brief	Function operator called on each iteration.
	///
	/// @param	theLog	The log object to call.
	void operator () (mr_utils::SharedPtr<MrTest::ILog>& log) { 
		mr_utils::mr_exception::assertCondition(log.isValid(), _FL_, _L_("Invalid pointer"));
		log->LogTest(this->m_case);  
	}
private:
	MrTest::ICase& m_case; ///< The testCase information containing log information.
};


//--------------------------------------------------------------------------------------
/// @brief	Functor to load named test to testLogEngine.
struct LoadLogsFromVector {
	LoadLogsFromVector( 
		MrTest::LogEngine*			logEngine, 
		const mr_utils::mr_string&	fileName,
		const mr_utils::mr_string&	fileType
	) 
	:	m_logEngine(logEngine),
		m_fileName(fileName),
		m_fileType(fileType) {
	}

	void operator () ( const mr_utils::mr_string& str ) {
		this->m_logEngine->AddLogger(MrTest::LogFactory::Create(this->m_fileName, this->m_fileType, str));
	}

	MrTest::LogEngine*			m_logEngine;
	const mr_utils::mr_string&	m_fileName;
	const mr_utils::mr_string&	m_fileType;
};

//--------------------------------------------------------------------------------------
// End functors.
//--------------------------------------------------------------------------------------


LogEngine::LogEngine() {
}


LogEngine::~LogEngine() {
}


bool LogEngine::WriteHeaders() {
	std::for_each(this->m_logs.begin(), this->m_logs.end(), WriteLogHeaders() );
	return true;
}


bool LogEngine::Log(MrTest::ICase& testCase) {
	std::for_each(this->m_logs.begin(), this->m_logs.end(), WriteLogEntries(testCase));
	return true;
}


bool LogEngine::WriteSummaries() {
	std::for_each(this->m_logs.begin(), this->m_logs.end(), WriteLogSummaries() );
	return true;
}


void LogEngine::AddLogger(const mr_utils::SharedPtr<MrTest::ILog>& log) {
	mr_utils::mr_exception::assertCondition(log.isValid(), _FL_, _L_("Invalid testLog"));
	this->m_logs.push_back(log);
}


void LogEngine::LoadLoggers(const mr_utils::mr_string& fileName, const mr_utils::mr_string& fileType) {
	mr_utils::mr_exception::assertCondition(!fileName.empty(), _FL_, _L_("Empty file name"));
	std::vector<mr_utils::mr_string> logs = 
		MrTest::LogInitialiserFactory::Create(fileName, fileType)->GetLogList();
		
	std::for_each(logs.begin(), logs.end(), LoadLogsFromVector(this, fileName, fileType));		
}


} // end namespace
