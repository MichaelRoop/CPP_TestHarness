///--------------------------------------------------------------------------------------
/// @file	mr_ini_node.cpp
/// @brief	Ini file node which is the key value pair unit in a section.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_ini_node.h"
#include "mr_char.h"

namespace mr_inireader
{

node::node( const iniInputLine& inLine )
{
	// Always safe to copy over second value.
	m_name = inLine.firstValue();
	m_value = inLine.secondValue();
	m_type = ( inLine.type() == iniInputLine::NODE ? VALID_DATA : NON_DATA );
}


node::node( const node& obj )
{
	this->init( obj );
}


node& node::operator = ( const node& rhs )
{
	if (this != &rhs)
	{
		this->init( rhs );
	}
	return *this;
}


const mr_utils::mr_string& node::value() const
{
	return m_value;
}


const mr_utils::mr_string& node::name() const
{
	return m_name;
}


bool node::isDataNode() const
{
	return m_type == VALID_DATA;
}


node::node()
{
}


void node::init( const node& obj )
{
	m_name	= obj.m_name;
	m_value = obj.m_value;
	m_type	= obj.m_type;
}


mr_utils::mr_ostream& operator << ( mr_utils::mr_ostream& os, const node& theNode )
{
	os << theNode.name().c_str();
	if (theNode.isDataNode())
	{
		os << L( "=" ) << theNode.value().c_str(); 
	}
	os << std::endl;
	return os;
}


} // end of namespace

