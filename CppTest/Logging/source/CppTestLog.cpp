///--------------------------------------------------------------------------------------
/// @file	CppTestLog.cpp
/// @brief	Log classes for test tool.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestLog.h"
#include "CppTestCase.h"
#include "mr_pointerException.h"
#include "mr_defines.h"


namespace CppTest {

Log::Log() 
:	m_stSuccessCount(0),
	m_stFailInitCount(0),
	m_stFailSetupCount(0),
	m_stFailTestCount(0),
	m_stFailCleanupCount(0),
	m_stNotExistCount(0),
	m_overwrite(false) {
}


Log::Log( 
	mr_utils::SharedPtr<CppTest::ILogOutput>&	output,
	mr_utils::SharedPtr<CppTest::ILog>&				summaryLog
)
:	m_output(output),
	m_summaryLog( summaryLog ),
	m_stSuccessCount(0),
	m_stFailInitCount(0),
	m_stFailSetupCount(0),
	m_stFailTestCount(0),
	m_stFailCleanupCount(0),
	m_stNotExistCount(0),
	m_overwrite(false) {
}


Log::~Log() {
	if (this->m_output.isValid()) {
		this->m_output->CloseOutput();
	}
}


bool Log::LogTest(CppTest::ICase& testCase) {
	switch(testCase.Status) {
		case CppTest::ICase::ST_SUCCESS:
			++this->m_stSuccessCount;
			break;
		case CppTest::ICase::ST_FAIL_SETUP:		
			++this->m_stFailSetupCount;
			break;
		case CppTest::ICase::ST_FAIL_TEST:		
			++this->m_stFailTestCount;
			break;
		case CppTest::ICase::ST_FAIL_CLEANUP:	
			++this->m_stFailCleanupCount;
			break;
		case CppTest::ICase::ST_NOT_EXISTS:		
			++this->m_stNotExistCount;
			break;

		case CppTest::ICase::ST_DISABLED:		
			//++this->m_stNotExistCount;
			// TODO - add disabled count
			break;

		// TODO - Need to modify this with fixture specific counters?
		case CppTest::ICase::ST_FAIL_FIXTURE_SETUP:
			++this->m_stFailSetupCount;
			break;
		case CppTest::ICase::ST_FAIL_FIXTURE_TEARDOWN:
			++this->m_stFailCleanupCount;
			break;

		default:	
			mr_utils::mr_stringstream ss;
			ss << _L_("Invalid testCase state:") << testCase.Status;
			throw mr_utils::mr_exception(_FL_, ss.str());
	}

	return this->WriteEntry(testCase);
}


bool Log::Summarize() {
	if (this->m_summaryLog.isValid()) {
		return this->m_summaryLog->WriteSummaryEntry(this);
	}
	return false;
}


bool Log::OverwriteExistingLog() const {
	return this->m_overwrite;
}


int Log::GetSuccessCount() const {
	return this->m_stSuccessCount;
}

int Log::GetFailInitCount() const {
	return this->m_stFailInitCount;
}


int Log::GetFailSetupCount() const {
	return this->m_stFailSetupCount;
}


int Log::GetFailTestCount() const {
	return this->m_stFailTestCount;
}


int Log::GetFailCleanupCount() const {
	return this->m_stFailCleanupCount;
}


int Log::GetNotExistCount() const {
	return this->m_stNotExistCount;
}


int Log::GetTotalCount() const {
	return	
		this->m_stSuccessCount + 
		this->m_stFailInitCount + 
		this->m_stFailSetupCount +			
		this->m_stFailTestCount + 
		this->m_stFailCleanupCount + 
		this->m_stNotExistCount;
}


} // end namespace

