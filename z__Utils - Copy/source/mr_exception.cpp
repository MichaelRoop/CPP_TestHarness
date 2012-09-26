///--------------------------------------------------------------------------------------
/// @file	mr_exception.cpp
/// @brief	A common cross platform and char width base for exceptions.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_exception.h"
#include "mr_sstream.h"
#include "mr_toStream.h" 

#include <assert.h>

namespace mr_utils
{


mr_exception::mr_exception( const char* file, int line, const mr_string& msg ) 
	: exception(),
	m_fileName( ( file == NULL ? "" : file ) ),
	m_line( line ),
	m_msg( msg )
{
	assert( file );
}


mr_exception::~mr_exception() throw()
{
}


const mr_string& mr_exception::msg() const
{
	return m_msg;
}


const mr_string mr_exception::fileName() const
{
	// We never use this value to open a file so we are safe to always convert its width.
	mr_stringstream ss;
	ToStream( ss, ExtractFileName( m_fileName ) );
	return ss.str();
}


int mr_exception::fileLine() const
{
	return m_line;
}


const mr_string mr_exception::longMsg() const
{
	mr_stringstream ss;
	ss	<< L( "Exception:" ) 
		<< this->fileName().c_str() << L(":") << m_line << L(" " ) << m_msg.c_str();
	return ss.str();
}


void mr_exception::assertCondition( 
	bool				condition,
	const char*			file, 
	int					line, 
	const mr_string&	msg
)
{
	if (!condition)
	{
		throw mr_exception( file, line, msg );
	}
}



} // end namespace mr_test