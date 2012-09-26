///--------------------------------------------------------------------------------------
/// @file	mr_iniInputLine.cpp
/// @brief	Encapsulates the logic of parsing and identifying the type of data.
///
///	The text string will either indicate that it is a section identifier or a
/// key value pair line, or a comment line, or other.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------

#include "mr_iniInputLine.h"

namespace mr_inireader
{

iniInputLine::iniInputLine( ) : m_type( UNDEFINED )
{
}


iniInputLine::iniInputLine( const mr_utils::mr_string& str ) : m_type( UNDEFINED )
{
	this->init( str );
}


iniInputLine::LINE_TYPE iniInputLine::init(  const mr_utils::mr_string& str )
{
	// Clean out any old values
	m_firstValue	= L("");
	m_secondValue	= L("");
	m_type = UNDEFINED;
	mr_utils::mr_string line = mr_utils::Trim( str );

	// The order is important.  Once it has found a match, no other checking
	// will be done on the line.
	this->CheckIfBlank( line );
	this->CheckIfSectionName( line );
	this->CheckIfComment( line );
	this->CheckIfNode( line );
	this->CheckIfGarbage( line );
	return this->type();
}


void iniInputLine::CheckIfBlank( const mr_utils::mr_string& str )
{
	if (m_type == UNDEFINED)
	{
		if (str.empty() )
		{
			m_type = BLANK;
			m_firstValue = str;
		}
	}
}


void iniInputLine::CheckIfSectionName( const mr_utils::mr_string& str )
{
	if (m_type == UNDEFINED)
	{
		if (str.size() > 2	&& str[0] == L( '[' ) && str[str.length() - 1] == L( ']' ) )
		{
			m_type = SECTION;
			m_firstValue = mr_utils::Trim( str.substr( 1, str.length() - 2 ) );
		}
	}
}


void iniInputLine::CheckIfComment( const mr_utils::mr_string& str )
{
	if (m_type == UNDEFINED)
	{
		if (str[0] == L('#') || str[0] == L('*') )
		{
			m_type = COMMENT;
			m_firstValue = str;
		}
	}
}


void iniInputLine::CheckIfNode( const mr_utils::mr_string& str )
{
	if (m_type == UNDEFINED)
	{
		mr_utils::mr_string::size_type pos = str.find( L( "=" ) );
		if (pos > 0 && pos != mr_utils::mr_string::npos)
		{
			mr_utils::mr_string name;
			pos = 0;
			if (mr_utils::MrTokenize( pos, str, name, L('=') ))
			{
				// Check if there is any chars on left side of '='.
				name = mr_utils::Trim( name );
				if (!name.empty())
				{
					m_type = NODE;
					m_firstValue = name;

					/// @todo Probably just replace with substring of remainder of string.
					mr_utils::MrTokenize( pos, str, m_secondValue, L('=') );
					m_secondValue = mr_utils::Trim( m_secondValue );
				}
			}
		}
	}
}


void iniInputLine::CheckIfGarbage( const mr_utils::mr_string& str )
{
	if (m_type == UNDEFINED)
	{
		m_firstValue = str;
		m_type = GARBAGE;
	}
}


const mr_utils::mr_string& iniInputLine::firstValue() const
{
	return m_firstValue;
}


const mr_utils::mr_string& iniInputLine::secondValue() const
{
	return m_secondValue;
}



iniInputLine::LINE_TYPE iniInputLine::type() const
{
	return m_type;
}



}

