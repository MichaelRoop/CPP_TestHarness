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
#include "mr_case.h"
#include "mr_char.h"
#include "mr_pointerException.h"
#include "mr_defines.h"
#include "mr_testEngine.h"


namespace mr_test
{

sqlLog::sqlLog() : testLog()
{
}


sqlLog::sqlLog( 
	mr_utils::SharedPtr<iLogOutput>&		output, 
	mr_utils::SharedPtr<iTestLog>&			summaryLog, 
	mr_utils::SharedPtr<iLogInitialiser>&	initialiser 
)
:	testLog( output, summaryLog )
{
	this->init( initialiser );
}


sqlLog::sqlLog( 
	mr_utils::SharedPtr<iLogOutput>&		output, 
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

bool sqlLog::writeHeader()
{
	mr_utils::mr_exception::assertCondition( m_output.isValid(), FL, L( "invalid output" ) );
	mr_utils::mr_exception::assertCondition( m_output->initOutput(), FL, L( "output failed init" ) );

	if (this->overwriteExistingLog())
	{
		m_output->write( this->getDropStmt() );
	}
	return m_output->write( this->getCreateStmt() );
}


bool sqlLog::writeEntry( testCase* theCase )
{
	mr_utils::mr_pointerException::ptrAssert( theCase, FL );
	mr_utils::mr_exception::assertCondition( m_output.isValid(), FL, L( "invalid output" ) );
	return m_output->write( this->getInsertStmt( theCase ) );
}


bool sqlLog::writeSummaryEntry( iTestLog* theLog )
{
	mr_utils::mr_pointerException::ptrAssert( theLog, FL );
	mr_utils::mr_exception::assertCondition( m_output.isValid(), FL, L( "invalid output" ) );
	
	// Do not check return as some loggers fail if table already exists.
	this->writeHeader();
	bool ret = m_output->write( this->getInsertStmt( theLog ) );
	m_output->closeOutput();
	return ret;
}


bool sqlLog::writeFooter()
{
	mr_utils::mr_exception::assertCondition( m_output.isValid(), FL, L( "invalid output" ) );

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

	m_sqlData.m_tableName = initialiser->getLogName();
	if (initialiser->getUseAutoGenUniqueTableName())
	{
		m_sqlData.m_tableName = m_sqlData.m_tableName + mr_test::engine::getInstance().getRunId();
	}

	m_sqlData.m_strQuote  = initialiser->getStringDelimiter( true );
	m_sqlData.m_fields	  = initialiser->getFields();

	sqlBuilder::buildCreateStmt( m_sqlData, initialiser->getSqlCreateTemplate() );
	sqlBuilder::buildDropStmt( m_sqlData, initialiser->getSqlDropTemplate() );
	sqlBuilder::buildInsertStmt( m_sqlData, initialiser->getSqlInsertTemplate() );

	m_overwrite = initialiser->getOverwriteLogFlag();
}


const mr_utils::mr_string& sqlLog::getDropStmt() const
{
	return m_sqlData.m_dropStmt;
}


const mr_utils::mr_string& sqlLog::getCreateStmt() const
{
	return m_sqlData.m_createStmt;
}


mr_utils::mr_string sqlLog::getInsertStmt(  testCase* theCase ) const
{
	return sqlBuilder::buildInsertStmtWithValues( m_sqlData, theCase );
}


mr_utils::mr_string sqlLog::getInsertStmt(  iTestLog* theLog ) const
{
	return sqlBuilder::buildInsertStmtWithValues( m_sqlData, theLog );
}

} // end namespace

