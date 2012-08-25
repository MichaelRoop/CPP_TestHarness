///--------------------------------------------------------------------------------------
/// @file	mr_ini_section.cpp
/// @brief	Ini file node section object.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_ini_section.h"
#include "mr_char.h"
#include "mr_functors.h"
#include "mr_toStream.h"

#include <algorithm>


namespace mr_inireader
{

/// @brief	Filter out non valid nodes to produce a good set of sections.
struct FilterNodes
{
	FilterNodes( section::NodeVector& nodeVec ) : m_nodes( nodeVec ) {}

	void operator () ( const node& theNode )
	{
		if (theNode.isDataNode())
		{
			m_nodes.push_back( theNode );
		}
	}
	section::NodeVector& m_nodes; ///< Target for sections.
};
// -------------------- end functors ----------------



section::section() : m_type( NON_DATA )
{
}


section::section( const iniInputLine& input )
{
	m_name = input.firstValue();
	m_type = ( input.type() == iniInputLine::SECTION ? VALID_DATA : NON_DATA );
}



section::section( const section& obj )
{
	this->init( obj );
}


section& section::operator = ( const section& rhs )
{
	if (this != &rhs)
	{
		this->init( rhs );
	}
	return *this;
}


const mr_utils::mr_string& section::name() const
{
	return m_name;
}


void section::addNode( const iniInputLine& input )
{
	m_nodes.push_back( node( input ) );
}


const section::NodeVector& section::nodes() const
{
	return m_nodes;
}


const mr_utils::mr_string& section::value( const mr_utils::mr_string& name ) const
{
	NodeIterator it = this->getNode( name );
	return ( it == m_nodes.end() ? m_dummyVal : it->value() );
}


void section::init( const section& obj )
{
	this->clear();
	m_name = obj.m_name;
	m_nodes = obj.m_nodes;
	m_type	= obj.m_type;
}


void section::setName( const mr_utils::mr_string& name )
{
	// Setting the name always happens before loading in lines.
	this->clear();

	m_type = VALID_DATA;
	m_name = name;
}


section::NodeIterator section::getNode(  const mr_utils::mr_string& name ) const
{
	return std::find_if( 
		m_nodes.begin(), m_nodes.end(), mr_utils::isNamed<node,mr_utils::mr_string>( name ) 
	);
}


bool section::nodeExists(  const mr_utils::mr_string& name ) const
{
	NodeIterator it = this->getNode( name );
	if (it == m_nodes.end() || !it->isDataNode())
	{
		return false;
	}
	return true;
}


void section::clear()
{
	m_name.clear();
	m_nodes.clear();
}


bool section::isDataSection() const
{
	return m_type == VALID_DATA;
}


const section::NodeVector section::getNodesCopy() const
{
	section::NodeVector nodes;
	std::for_each( m_nodes.begin(), m_nodes.end(), FilterNodes( nodes ) );
	return nodes;
}



mr_utils::mr_ostream& operator << ( mr_utils::mr_ostream& os, const section& theSection )
{
	if (theSection.isDataSection())
	{
		os << L( "[" ) << theSection.name().c_str() << L( "]" ) << std::endl;

		std::for_each( 
			theSection.nodes().begin(), 
			theSection.nodes().end(), 
			mr_utils::ToStreamClass<node,mr_utils::mr_ostream>( os )
		);
	}
	else
	{
		os <<  theSection.name().c_str() << std::endl;
	}

	return os;
}



} // end namespace

