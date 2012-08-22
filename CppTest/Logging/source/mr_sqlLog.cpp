///--------------------------------------------------------------------------------------
/// @file	mr_sqlLog.cpp
/// @brief	Log to format results into SQL statements for test tool.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_sqlLog.h"
#include "mr_char.h"
#include "mr_pointerException.h"
#include "mr_defines.h"
#include "CppTestEngine.h"
#include "CppTestCase.h"

namespace mr_test
{

sqlLog::sqlLog() : testLog()
{
}


sqlLog::sqlLog( 
	mr_utils::SharedPtr<CppTest::ILogOutput>&		output, 
	mr_utils::SharedPtr<iTestLog>&			summaryLog, 
	mr_utils::SharedPtr<iLogInitialiser>&	initialiser 
)
:	testLog( output, summaryLog )
{
	this->init( initialiser );
}


sqlLog::sqlLog( 
	mr_utils::SharedPtr<CppTest::ILogOutput>&		output, 
	mr_utils::SharedPtr<iLogInitialiser>&	initialiser 
)
:	testLog( output, mr_utils::SharedPtr<iTestLog>() )
{
	this->init( initialiser );
}


sqlLog::~sqlLog()
{
}

/// @todo	Get the overwrite bool from ini

bool sqlLog::writeHeader() {
	mr_utils::mr_exception::assertCondition(this->m_output.isValid(), FL, L( "invalid output" ) );
	mr_utils::mr_exception::assertCondition(this->m_output->InitOutput(), FL, L( "output failed init" ) );

	if (this->overwriteExistingLog()) {
		this->m_output->Write( this->getDropStmt() );
	}
	return this->m_output->Write( this->getCreateStmt() );
}


bool sqlLog::writeEntry(CppTest::Case& testCase) { 
	//	mr_utils::mr_pointerException::ptrAssert(fixture, _FL_);
	mr_utils::mr_exception::assertCondition( m_output.isValid(), FL, L( "invalid output" ) );
	return this->m_output->Write(this->getInsertStmt(testCase));
}


bool sqlLog::writeSummaryEntry( iTestLog* theLog ) {
	mr_utils::mr_pointerException::ptrAssert( theLog, FL );
	mr_utils::mr_exception::assertCondition(this->m_output.isValid(), FL, L( "invalid output" ) );
	
	// Do not check return as some loggers fail if table already exists.
	this->writeHeader();
	bool ret = this->m_output->Write(this->getInsertStmt(theLog));
	this->m_output->CloseOutput();
	return ret;
}


bool sqlLog::writeFooter() {
	mr_utils::mr_exception::assertCondition(this->m_output.isValid(), FL, L("invalid output"));

	/// @todo	Figure out how to save run totals info to DB.  Is it even required since they can
	///			get it by querry or dashboard on the table itself?
	return true;
}


void sqlLog::init( mr_utils::SharedPtr<iLogInitialiser>& initialiser )
{
	mr_utils::mr_exception::assertCondition( 
		initialiser.isValid(), FL, L("Invalid intialiser") 
	);
	mr_utils::mr_exception::assertCondition( 
		initialiser->load(), FL, L("intialiser failed to load file") 
	);

	this->m_sqlData.m_tableName = initialiser->getLogName();
	if (initialiser->getUseAutoGenUniqueTableName()) {
		this->m_sqlData.m_tableName = this->m_sqlData.m_tableName + CppTest::Engine::Instance().GetRunId();
	}

	this->m_sqlData.m_strQuote = initialiser->getStringDelimiter(true);
	this->m_sqlData.m_fields = initialiser->getFields();

	sqlBuilder::buildCreateStmt(this->m_sqlData, initialiser->getSqlCreateTemplate());
	sqlBuilder::buildDropStmt(this->m_sqlData, initialiser->getSqlDropTemplate());
	sqlBuilder::buildInsertStmt(this->m_sqlData, initialiser->getSqlInsertTemplate());

	this->m_overwrite = initialiser->getOverwriteLogFlag();
}


const mr_utils::mr_string& sqlLog::getDropStmt() const {
	return this->m_sqlData.m_dropStmt;
}


const mr_utils::mr_string& sqlLog::getCreateStmt() const {
	return this->m_sqlData.m_createStmt;
}


mr_utils::mr_string sqlLog::getInsertStmt(CppTest::Case& testCase) const {
	return sqlBuilder::buildInsertStmtWithValues(this->m_sqlData, testCase);
}


mr_utils::mr_string sqlLog::getInsertStmt(iTestLog* theLog) const {
	return sqlBuilder::buildInsertStmtWithValues(this->m_sqlData, theLog );
}

} // end namespace

