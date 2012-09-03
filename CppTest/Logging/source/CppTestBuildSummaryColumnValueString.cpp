///--------------------------------------------------------------------------------------
/// @file	CppTestBuildSummaryColumnValueString.h
/// @brief	Builds strings with for summary columns.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestBuildSummaryColumnValueString.h"
#include "ICppTestLog.h"
#include "CppTestEngine.h"
#include "mr_pointerException.h"
#include "mr_defines.h"

namespace MrTest {

BuildSummaryColumnValueString::BuildSummaryColumnValueString( 
	mr_utils::mr_stringstream&	os,
	const mr_utils::mr_string&	delimiter,
	const mr_utils::mr_string&	strQuotes,
	MrTest::ILog*				theLog 
) :	BuildColumnValueString(os, delimiter, strQuotes),
	m_log(theLog) {
		mr_utils::mr_pointerException::ptrAssert(theLog, _FL_);
}


void BuildSummaryColumnValueString::Build(const MrTest::FieldPair& field) {
	// add upper case conversion later.
	if (field.first.compare(_L_("SuccessCount")) == 0) {
		this->m_os << this->m_log->GetSuccessCount();
	}
	else if (field.first.compare(_L_("FailInitCount")) == 0) {
		this->m_os << this->m_log->GetFailInitCount();
	}
	else if (field.first.compare(_L_("FailSetupCount")) == 0) {
		this->m_os << this->m_log->GetFailSetupCount();
	}
	else if (field.first.compare(_L_("FailTestCount")) == 0) {
		this->m_os << this->m_log->GetFailTestCount();
	}
	else if (field.first.compare(_L_("FailCleanupCount")) == 0) {
		this->m_os << this->m_log->GetFailCleanupCount();
	}
	else if (field.first.compare(_L_("NotExistCount")) == 0) {
		this->m_os << this->m_log->GetNotExistCount();
	}
	else if (field.first.compare(_L_("TotalCount")) == 0) {
		this->m_os << this->m_log->GetTotalCount();
	}
	else if (field.first.compare(_L_("RunId")) == 0) {
		this->m_os << MrTest::Engine::Instance().GetRunId();
	}
	else {
		//very bad
		mr_utils::mr_stringstream os;
		os	<< field.first 
			<< _L_(": Illegal field name.  Allowed are SuccessCount, FailInitCount, FailSetupCount, FailTestCount, FailCleanupCount, NotExistCount, RunId, TotalCount.");
		mr_utils::mr_exception::assertCondition(false, _FL_, os.str());
	}
}

} // end namespace
