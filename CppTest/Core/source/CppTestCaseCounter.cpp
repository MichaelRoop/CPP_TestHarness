///--------------------------------------------------------------------------------------
/// @file	CppTestCaseCounter.h
/// @brief	To keep a summary count of the test run
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------

#include "CppTestCaseCounter.h"
#include "ICppTestCase.h"
#include "CppTestRunSummary.h"
#include "mr_exception.h"
#include "mr_defines.h"

namespace MrTest {


CaseCounter::CaseCounter() {
	this->Reset();
}


void CaseCounter::Count(const MrTest::ICase& testCase) {
	switch(testCase.Status) {
		case MrTest::ICase::ST_SUCCESS:
			++this->m_success;
			break;
		case MrTest::ICase::ST_FAIL_TEST:		
			++this->m_failTest;
			break;
		case MrTest::ICase::ST_FAIL_SETUP:		
			++this->m_failSetup;
			break;
		case MrTest::ICase::ST_FAIL_CLEANUP:	
			++this->m_failTeardown;
			break;
		case MrTest::ICase::ST_FAIL_FIXTURE_SETUP:
			++this->m_failFixtureSetup;
			break;
		case MrTest::ICase::ST_DISABLED:
			++this->m_disabled;
			break;
		case MrTest::ICase::ST_NOT_EXISTS:		
			++this->m_notFound;
			break;
		// TODO - REMOVE - fixture teardown never counted - no test case to save it to
		case MrTest::ICase::ST_FAIL_FIXTURE_TEARDOWN:
		//	++this->m_stFailCleanupCount;
			break;
		default:	
			mr_utils::mr_stringstream ss;
			ss << _L_("Invalid testCase state:") << testCase.Status;
			throw mr_utils::mr_exception(_FL_, ss.str());
	}
}


	/// @brief	Called to reset internal state
void CaseCounter::Reset() {
	this->m_success = 0;
	this->m_failFixtureSetup = 0;
	this->m_failSetup = 0;
	this->m_failTest = 0;
	this->m_failTeardown = 0; // TODO - remove since we are not tracking it
	this->m_notFound = 0;
	this->m_disabled = 0;
}


mr_utils::SharedPtr<MrTest::IRunSummary> CaseCounter::Summary(const mr_utils::mr_string& runId) const {
	return mr_utils::SharedPtr<MrTest::IRunSummary>(new MrTest::RunSummary(*this));
}


int CaseCounter::SuccessCount() const {
	return this->m_success;
}


int CaseCounter::FailFixtureSetupCount() const {
	return this->m_failFixtureSetup;
}


int CaseCounter::FailSetupCount() const {
	return this->m_failSetup;
}


int CaseCounter::FailTestCount() const {
	return this->m_failTest;
}


int CaseCounter::FailTeardownCount() const {
	return this->m_failTeardown;
}
	

int CaseCounter::NotFoundCount() const {
	return this->m_notFound;
}


int CaseCounter::DisabledCount() const {
	return this->m_disabled;
}


} // end namespace 
