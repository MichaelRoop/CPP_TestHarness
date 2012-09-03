///--------------------------------------------------------------------------------------
/// @file	CppTestRunSummary.h
/// @brief	Test run summary data
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------

#include "CppTestRunSummary.h"
#include "mr_exception.h"
#include "mr_defines.h"

namespace MrTest {


RunSummary::RunSummary(const MrTest::CaseCounter& counter) :
	m_Success(counter.SuccessCount()),
	m_FailFixtureSetup(counter.FailFixtureSetupCount()),
	m_FailSetup(counter.FailSetupCount()),
	m_FailTest(counter.FailTestCount()),
	m_FailTeardown(counter.FailTeardownCount()),
	m_Disabled(counter.DisabledCount()),
	m_NotFound(counter.NotFoundCount()) {
}


int RunSummary::Total(MrTest::ICase::TestCaseStatus status) const {
	switch (status) {
		case ICase::ST_SUCCESS:				return this->m_Success;
		case ICase::ST_FAIL_SETUP:			return this->m_FailSetup;
		case ICase::ST_FAIL_TEST:			return this->m_FailTest;
		case ICase::ST_FAIL_CLEANUP:		return this->m_FailTeardown;
		case ICase::ST_FAIL_FIXTURE_SETUP:	return this->m_FailFixtureSetup;
		case ICase::ST_FAIL_FIXTURE_TEARDOWN: return 0; // TODO - remove this type
		case ICase::ST_DISABLED:			return this->m_Disabled;
		case ICase::ST_NOT_EXISTS:			return this->m_NotFound;
		case ICase::ST_NONE:				return 0;	
	default:				
		throw mr_utils::mr_exception(_FL_, _L_("Unhandled test state type"));
	}
}


int RunSummary::Total() const {
	return this->m_Success +
		this->m_FailFixtureSetup +
		this->m_FailSetup +
		this->m_FailTest +
		this->m_FailTeardown +
		this->m_Disabled +
		this->m_NotFound;
}

} // end namespace
