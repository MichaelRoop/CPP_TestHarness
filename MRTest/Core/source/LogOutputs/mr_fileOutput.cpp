///--------------------------------------------------------------------------------------
/// @file	mr_fileOutput.h
/// @brief	Output class to output logger information to a file.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_fileOutput.h"
#include "mr_sstream.h"
#include "mr_toStream.h"
#include "mr_exception.h"
#include "mr_defines.h"


namespace mr_test
{


fileOutput::fileOutput( const std::string& filename ) : iLogOutput(), m_filename( filename )
{
}


bool fileOutput::initOutput()
{
	if (m_file.is_open())
	{
		m_file.close();
	}

	mr_utils::mr_exception::assertCondition( !m_filename.empty(), FL, L("No file name") );
	m_file.open( m_filename.c_str() );

	mr_utils::mr_stringstream ss;
	mr_utils::ToStream( ss, m_filename ) << L( " cannot be opened" );
	mr_utils::mr_exception::assertCondition( m_file.is_open(), FL, ss.str() );

	return m_file.is_open();
}


void fileOutput::closeOutput()
{
	if (m_file.is_open())
	{
		m_file.close();
	}
}


bool fileOutput::write( const mr_utils::mr_string& str )
{
	if (!m_file.is_open())
	{
		mr_utils::mr_stringstream ss;
		mr_utils::ToStream( ss, m_filename ) << L( " cannot be opened" );
		mr_utils::mr_exception::assertCondition( false, FL, ss.str() );
		return false;
	}
	m_file << str.c_str() << std::endl;
	return true;
}


} // end namespace