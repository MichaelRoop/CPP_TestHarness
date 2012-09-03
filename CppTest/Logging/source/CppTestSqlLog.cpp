///--------------------------------------------------------------------------------------
/// @file	CppTestSqlLog.cpp
/// @brief	Log to format results into SQL statements for test tool.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestSqlLog.h"
#include "CppTestEngine.h"
#include "CppTestCase.h"
#include "mr_char.h"
#include "mr_pointerException.h"
#include "mr_defines.h"

namespace MrTest {

SqlLog::SqlLog() : MrTest::Log()
{
}


SqlLog::SqlLog( 
	mr_utils::SharedPtr<MrTest::ILogOutput>&		output, 
	mr_utils::SharedPtr<MrTest::ILog>&				summaryLog, 
	mr_utils::SharedPtr<MrTest::ILogInitialiser>&	initialiser 
) :	MrTest::Log(output, summaryLog) {
	this->Init(initialiser);
}


SqlLog::SqlLog( 
	mr_utils::SharedPtr<MrTest::ILogOutput>&		output, 
	mr_utils::SharedPtr<MrTest::ILogInitialiser>&	initialiser 
):	MrTest::Log(output, mr_utils::SharedPtr<MrTest::ILog>()) {
	this->Init(initialiser);
}


SqlLog::~SqlLog() {
}

/// @todo	Get the overwrite bool from ini

bool SqlLog::WriteHeader() {
	mr_utils::mr_exception::assertCondition(this->m_output.isValid(), FL, L("invalid output"));
	mr_utils::mr_exception::assertCondition(this->m_output->InitOutput(), FL, L("output failed init"));

	if (this->OverwriteExistingLog()) {
		this->m_output->Write( this->GetDropStmt() );
	}
	return this->m_output->Write( this->GetCreateStmt() );
}


bool SqlLog::WriteEntry(MrTest::ICase& testCase) { 
	mr_utils::mr_exception::assertCondition(this->m_output.isValid(), FL, L("invalid output"));
	return this->m_output->Write(this->GetInsertStmt(testCase));
}


bool SqlLog::WriteSummaryEntry(MrTest::ILog* log) {
	mr_utils::mr_pointerException::ptrAssert(log, FL);
	mr_utils::mr_exception::assertCondition(this->m_output.isValid(), FL, L("invalid output"));
	
	// Do not check return as some loggers fail if table already exists.
	this->WriteHeader();
	bool ret = this->m_output->Write(this->GetInsertStmt(log));
	this->m_output->CloseOutput();
	return ret;
}


bool SqlLog::WriteFooter() {
	mr_utils::mr_exception::assertCondition(this->m_output.isValid(), FL, L("invalid output"));

	/// @todo	Figure out how to save run totals info to DB.  Is it even required since they can
	///			get it by querry or dashboard on the table itself?
	return true;
}


void SqlLog::Init(mr_utils::SharedPtr<MrTest::ILogInitialiser>& initialiser) {
	mr_utils::mr_exception::assertCondition( 
		initialiser.isValid(), _FL_, _L_("Invalid intialiser"));
	mr_utils::mr_exception::assertCondition( 
		initialiser->Load(), _FL_, _L_("intialiser failed to load file"));

	this->m_sqlData.m_tableName = initialiser->GetLogName();
	if (initialiser->GetUseAutoGenUniqueTableName()) {
		this->m_sqlData.m_tableName = this->m_sqlData.m_tableName + MrTest::Engine::Instance().GetRunId();
	}

	this->m_sqlData.m_strQuote = initialiser->GetStringDelimiter(true);
	this->m_sqlData.m_fields = initialiser->GetFields();

	SqlBuilder::BuildCreateStmt(this->m_sqlData, initialiser->GetSqlCreateTemplate());
	SqlBuilder::BuildDropStmt(this->m_sqlData, initialiser->GetSqlDropTemplate());
	SqlBuilder::BuildInsertStmt(this->m_sqlData, initialiser->GetSqlInsertTemplate());

	this->m_overwrite = initialiser->GetOverwriteLogFlag();
}


const mr_utils::mr_string& SqlLog::GetDropStmt() const {
	return this->m_sqlData.m_dropStmt;
}


const mr_utils::mr_string& SqlLog::GetCreateStmt() const {
	return this->m_sqlData.m_createStmt;
}


mr_utils::mr_string SqlLog::GetInsertStmt(MrTest::ICase& testCase) const {
	return SqlBuilder::BuildInsertStmtWithValues(this->m_sqlData, testCase);
}


mr_utils::mr_string SqlLog::GetInsertStmt(MrTest::ILog* log) const {
	return SqlBuilder::BuildInsertStmtWithValues(this->m_sqlData, log);
}

} // end namespace

