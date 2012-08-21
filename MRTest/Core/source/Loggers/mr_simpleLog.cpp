///--------------------------------------------------------------------------------------
/// @file	mr_simpleLog.cpp
/// @brief	Simple Log for test tool.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_simpleLog.h"
#include "mr_char.h"
#include "mr_pointerException.h"
#include "mr_defines.h"
#include "mr_columnBuilder.h"
#include "mr_sstream.h"


namespace mr_test
{

simpleLog::simpleLog() : testLog()
{
}


simpleLog::simpleLog( 
	mr_utils::SharedPtr<iLogOutput>&		output, 
	mr_utils::SharedPtr<iTestLog>&			summaryLog, 
	mr_utils::SharedPtr<iLogInitialiser>&	initialiser 
) 
:	testLog( output, summaryLog )
{
	mr_utils::mr_exception::assertCondition( 
		initialiser.isValid(), FL, L("Invalid intialiser") 
	);
	mr_utils::mr_exception::assertCondition( 
		initialiser->load(), FL, L("intialiser failed to load file") 
	);

	m_formatData.m_strQuote  = initialiser->getStringDelimiter( false );
	m_formatData.m_delimiter = initialiser->getFieldDelimiter();
	m_formatData.m_fields	 = initialiser->getFields();
	m_overwrite				 = initialiser->getOverwriteLogFlag();
}


simpleLog::~simpleLog()
{
}


bool simpleLog::writeHeader()
{
	mr_utils::mr_exception::assertCondition( m_output.isValid(), FL, L( "invalid output" ) );
	mr_utils::mr_exception::assertCondition( m_output->initOutput(), FL, L( "output failed init" ) );

	mr_utils::mr_stringstream os;
	os << columnBuilder::createColumnHeaders( m_formatData.m_fields, m_formatData.m_delimiter );
	os << std::endl;
	return m_output->write( os.str() );
}


bool simpleLog::writeEntry(CppTest::Case& testCase)
{
//	mr_utils::mr_pointerException::ptrAssert(fixture, _FL_);
	mr_utils::mr_exception::assertCondition( m_output.isValid(), FL, L( "invalid output" ) );

	mr_utils::mr_stringstream os;
	os << columnBuilder::createColumnData( 
				m_formatData.m_fields, 
				m_formatData.m_delimiter, 
				m_formatData.m_strQuote, 
				testCase 
			);
	os << std::endl;
	return m_output->write( os.str() );
}


bool simpleLog::writeSummaryEntry( iTestLog* theLog )
{
	mr_utils::mr_pointerException::ptrAssert( theLog, FL );
	mr_utils::mr_exception::assertCondition( m_output.isValid(), FL, L( "invalid output" ) );

	this->writeHeader();

	mr_utils::mr_stringstream os;
	os << columnBuilder::createColumnData( 
				m_formatData.m_fields, 
				m_formatData.m_delimiter, 
				m_formatData.m_strQuote, 
				theLog 
			);
	os << std::endl;

	bool ret = m_output->write( os.str() );
	m_output->closeOutput();
	return ret;
}


bool simpleLog::writeFooter()
{
	/// @todo	Remove writeFooter methods entirely ? and use the summary call.

	mr_utils::mr_exception::assertCondition( m_output.isValid(), FL, L( "invalid output" ) );

	mr_utils::mr_stringstream os;
	os << L( "----------- End of Tests -------------" ) << std::endl
		<< L( "\tSummary of test states:" ) << std::endl
		<< L( "\t------------" ) << std::endl
		<< L( "\t     Success:" ) << m_stSuccessCount << std::endl
		<< L( "\t   Fail Init:" ) << m_stFailInitCount << std::endl
		<< L( "\t  Fail Setup:" ) << m_stFailSetupCount << std::endl
		<< L( "\t   Fail Test:" ) << m_stFailTestCount << std::endl
		<< L( "\tFail Cleanup:" ) << m_stFailCleanupCount << std::endl
		<< L( "\t   Not Found:" ) << m_stNotExistCount << std::endl
		<< L( "\t--------------------" ) << std::endl
		<< L( "\t       Total:" ) << + m_stSuccessCount + m_stFailInitCount + m_stFailSetupCount +
					  m_stFailTestCount + m_stFailCleanupCount + m_stNotExistCount
					<< std::endl;
	return m_output->write( os.str() );
}


} // end namespace

