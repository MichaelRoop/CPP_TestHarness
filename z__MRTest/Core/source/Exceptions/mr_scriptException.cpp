///--------------------------------------------------------------------------------------
/// @file	mr_scriptException.cpp
/// @brief	cross platform and char width exceptions for dev test platform.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_scriptException.h"
#include "mr_sstream.h"
#include "mr_toStream.h"


namespace mr_test
{

scriptException::scriptException( 
	const char*					file, 
	int							line, 
	const mr_utils::mr_string&	msg,
	const std::string&			scriptFileName,
	const mr_utils::mr_string&	scriptLine
)
:	mr_utils::mr_exception( file, line, msg ),
	m_scriptFileName( scriptFileName ),
	m_scriptLine( scriptLine )
{
	/// @todo Track down why this is happening.  If a value of '\' or '/' is 
	///			passed in as file name then we can not init the sriptException file 
	///			name object at all.  Weirdness.
}


scriptException::~scriptException() throw()
{
}


const mr_utils::mr_string scriptException::longMsg() const
{
	mr_utils::mr_stringstream ss;
	ss << mr_utils::mr_exception::longMsg() << L(" : ") ;
	mr_utils::ToStream( ss, mr_utils::ExtractFileName( m_scriptFileName ) );

	if (!m_scriptLine.empty())
	{
		ss << L(" : ") << m_scriptLine.c_str();
	}
	return ss.str();
}



} // end namespace mr_test