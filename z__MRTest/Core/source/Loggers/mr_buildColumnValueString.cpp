///--------------------------------------------------------------------------------------
/// @file	mr_buildColumnValueString.cpp
/// @brief	Builds strings with for column information.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_buildColumnValueString.h"
#include "mr_exception.h"
#include "mr_defines.h"


namespace mr_test
{

buildColumnValueString::buildColumnValueString( 
	mr_utils::mr_stringstream&	os,
	const mr_utils::mr_string&	delimiter,
	const mr_utils::mr_string&	strQuotes
) 
:	m_os(os), 
	m_delimiter( delimiter ),
	m_strQuotes( strQuotes ),
	m_count( 0 )
{
}


void buildColumnValueString::operator () ( const FieldPair& field )
{
	if ((++m_count) > 1)
	{
		m_os << L(",");
	}
	this->build( field );
}


void buildColumnValueString::concatenateStr( const mr_utils::mr_string& str )
{
	m_os << m_strQuotes.c_str() << str.c_str() << m_strQuotes.c_str();
}

} // end namespace

