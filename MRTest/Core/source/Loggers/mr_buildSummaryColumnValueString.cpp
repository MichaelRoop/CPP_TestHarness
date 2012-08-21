///--------------------------------------------------------------------------------------
/// @file	mr_BuildSummaryColumnValueString.h
/// @brief	Builds strings with for summary columns.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_buildSummaryColumnValueString.h"
#include "mr_iTestLog.h"
#include "mr_pointerException.h"
#include "mr_defines.h"
#include "CppTestEngine.h"

namespace mr_test
{

buildSummaryColumnValueString::buildSummaryColumnValueString( 
	mr_utils::mr_stringstream&	os,
	const mr_utils::mr_string&	delimiter,
	const mr_utils::mr_string&	strQuotes,
	iTestLog*					theLog 
) 
:	buildColumnValueString(os, delimiter, strQuotes),
	m_log(theLog) {
		mr_utils::mr_pointerException::ptrAssert(theLog, FL);
}


void buildSummaryColumnValueString::build(const FieldPair& field) {
	// add upper case conversion later.
	if (field.first.compare(L("SuccessCount")) == 0) {
		this->m_os << this->m_log->getSuccessCount();
	}
	else if (field.first.compare(L("FailInitCount")) == 0) {
		this->m_os << this->m_log->getFailInitCount();
	}
	else if (field.first.compare(L("FailSetupCount")) == 0) {
		this->m_os << this->m_log->getFailSetupCount();
	}
	else if (field.first.compare(L("FailTestCount")) == 0) {
		this->m_os << this->m_log->getFailTestCount();
	}
	else if (field.first.compare(L("FailCleanupCount")) == 0) {
		this->m_os << this->m_log->getFailCleanupCount();
	}
	else if (field.first.compare(L("NotExistCount")) == 0) {
		this->m_os << this->m_log->getNotExistCount();
	}
	else if (field.first.compare(L("TotalCount")) == 0) {
		this->m_os << this->m_log->getTotalCount();
	}
	else if (field.first.compare(L("RunId")) == 0) {
		this->m_os << CppTest::Engine::Instance().GetRunId();
	}
	else {
		//very bad
		mr_utils::mr_stringstream os;
		os	<< field.first 
			<< L(": Illegal field name.  Allowed are SuccessCount, FailInitCount, FailSetupCount, FailTestCount, FailCleanupCount, NotExistCount, RunId, TotalCount.");
		mr_utils::mr_exception::assertCondition( false, FL, os.str() );
	}
}

} // end namespace
