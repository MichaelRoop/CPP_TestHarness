///--------------------------------------------------------------------------------------
/// @file	mr_testLog.cpp
/// @brief	Log classes for test tool.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_testLog.h"
#include "mr_case.h"
#include "mr_pointerException.h"
#include "mr_defines.h"


namespace mr_test
{

testLog::testLog() 
:	m_stSuccessCount( 0 ),
	m_stFailInitCount( 0 ),
	m_stFailSetupCount( 0 ),
	m_stFailTestCount( 0 ),
	m_stFailCleanupCount( 0 ),
	m_stNotExistCount( 0 ),
	m_overwrite( false )
{
}


testLog::testLog( 
	mr_utils::SharedPtr<iLogOutput>&	output,
	mr_utils::SharedPtr<iTestLog>&		summaryLog
)
:	m_output( output ),
	m_summaryLog( summaryLog ),
	m_stSuccessCount( 0 ),
	m_stFailInitCount( 0 ),
	m_stFailSetupCount( 0 ),
	m_stFailTestCount( 0 ),
	m_stFailCleanupCount( 0 ),
	m_stNotExistCount( 0 ),
	m_overwrite( false )
{
}


testLog::~testLog()
{
	if (m_output.isValid())
	{
		m_output->closeOutput();
	}
}


bool testLog::log(  testCase* theCase )
{
	mr_utils::mr_pointerException::ptrAssert( theCase, FL );

	switch( theCase->statusEnum() )
	{
	case testCase::ST_SUCCESS:
		++m_stSuccessCount;
		break;
	case testCase::ST_FAIL_SETUP:		
		++m_stFailSetupCount;
		break;
	case testCase::ST_FAIL_TEST:		
		++m_stFailTestCount;
		break;
	case testCase::ST_FAIL_CLEANUP:	
		++m_stFailCleanupCount;
		break;
	case testCase::ST_NOT_EXISTS:		
		++m_stNotExistCount;
		break;
	default:	
		mr_utils::mr_stringstream ss;
		ss << L("Invalid testCase state:") << theCase->statusEnum();
		throw mr_utils::mr_exception( FL, ss.str() );
	}

	return this->writeEntry( theCase );
}


bool testLog::summarize()
{
	if (m_summaryLog.isValid())
	{
		return m_summaryLog->writeSummaryEntry( this );
	}
	return false;
}


bool testLog::overwriteExistingLog() const
{
	return m_overwrite;
}


int testLog::getSuccessCount() const
{
	return m_stSuccessCount;
}

int testLog::getFailInitCount() const
{
	return m_stFailInitCount;
}


int testLog::getFailSetupCount() const
{
	return m_stFailSetupCount;
}


int testLog::getFailTestCount() const
{
	return m_stFailTestCount;
}


int testLog::getFailCleanupCount() const
{
	return m_stFailCleanupCount;
}


int testLog::getNotExistCount() const
{
	return m_stNotExistCount;
}


int testLog::getTotalCount() const
{
	return	m_stSuccessCount + m_stFailInitCount + m_stFailSetupCount +
			m_stFailTestCount + m_stFailCleanupCount + m_stNotExistCount;
}


} // end namespace

