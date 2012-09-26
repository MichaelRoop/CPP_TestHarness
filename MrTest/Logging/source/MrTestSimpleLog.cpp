///--------------------------------------------------------------------------------------
/// @file	MrTestSimpleLog.cpp
/// @brief	Simple Log for test tool.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "MrTestSimpleLog.h"
#include "MrTestColumnBuilder.h"
#include "mr_char.h"
#include "mr_pointerException.h"
#include "mr_defines.h"
#include "mr_sstream.h"


namespace MrTest {

SimpleLog::SimpleLog() : MrTest::Log() {
}


SimpleLog::SimpleLog( 
	mr_utils::SharedPtr<MrTest::ILogOutput>&		output, 
	mr_utils::SharedPtr<MrTest::ILog>&				summaryLog, 
	mr_utils::SharedPtr<MrTest::ILogInitialiser>&	initialiser 
) :	MrTest::Log(output, summaryLog) {
	mr_utils::mr_exception::assertCondition( 
		initialiser.isValid(), _FL_, _L_("Invalid intialiser"));
	mr_utils::mr_exception::assertCondition( 
		initialiser->Load(), _FL_, _L_("intialiser failed to load file"));

	this->m_formatData.m_strQuote	= initialiser->GetStringDelimiter(false);
	this->m_formatData.m_delimiter	= initialiser->GetFieldDelimiter();
	this->m_formatData.m_fields		= initialiser->GetFields();
	this->m_overwrite				= initialiser->GetOverwriteLogFlag();
}


SimpleLog::~SimpleLog() {
}


bool SimpleLog::WriteHeader() {
	mr_utils::mr_exception::assertCondition(this->m_output.isValid(), _FL_, _L_("invalid output"));
	mr_utils::mr_exception::assertCondition(this->m_output->InitOutput(), _FL_, _L_("output failed init"));

	mr_utils::mr_stringstream os;
	os << MrTest::ColumnBuilder::CreateColumnHeaders(this->m_formatData.m_fields, this->m_formatData.m_delimiter);
	os << std::endl;
	return this->m_output->Write(os.str());
}


bool SimpleLog::WriteEntry(MrTest::ICase& testCase) {
	mr_utils::mr_exception::assertCondition(this->m_output.isValid(), _FL_, _L_("invalid output"));

	mr_utils::mr_stringstream os;
	os << MrTest::ColumnBuilder::CreateColumnData( 
				this->m_formatData.m_fields, 
				this->m_formatData.m_delimiter, 
				this->m_formatData.m_strQuote, 
				testCase);
	os << std::endl;
	return m_output->Write(os.str());
}


bool SimpleLog::WriteSummaryEntry(MrTest::ILog* log) {
	mr_utils::mr_pointerException::ptrAssert(log, _FL_);
	mr_utils::mr_exception::assertCondition(this->m_output.isValid(), _FL_, _L_("invalid output"));

	this->WriteHeader();

	mr_utils::mr_stringstream os;
	os << MrTest::ColumnBuilder::CreateColumnData( 
				this->m_formatData.m_fields, 
				this->m_formatData.m_delimiter, 
				this->m_formatData.m_strQuote, 
				log 
			);
	os << std::endl;

	bool ret = this->m_output->Write(os.str());
	this->m_output->CloseOutput();
	return ret;
}


bool SimpleLog::WriteFooter() {
	/// @todo	Remove writeFooter methods entirely ? and use the summary call.

	mr_utils::mr_exception::assertCondition(this->m_output.isValid(), _FL_, _L_("invalid output"));

	mr_utils::mr_stringstream os;
	os << L( "----------- End of Tests -------------" ) << std::endl
		<< L( "\tSummary of test states:" ) << std::endl
		<< L( "\t------------" ) << std::endl
		<< L( "\t     Success:" ) << this->m_stSuccessCount << std::endl
		<< L( "\t   Fail Init:" ) << this->m_stFailInitCount << std::endl
		<< L( "\t  Fail Setup:" ) << this->m_stFailSetupCount << std::endl
		<< L( "\t   Fail Test:" ) << this->m_stFailTestCount << std::endl
		<< L( "\tFail Cleanup:" ) << this->m_stFailCleanupCount << std::endl
		<< L( "\t   Not Found:" ) << this->m_stNotExistCount << std::endl
		<< L( "\t--------------------" ) << std::endl
		<< L( "\t       Total:" ) << + this->m_stSuccessCount + this->m_stFailInitCount + this->m_stFailSetupCount +
					  this->m_stFailTestCount + this->m_stFailCleanupCount + this->m_stNotExistCount
					<< std::endl;
	return this->m_output->Write(os.str());
}


} // end namespace

