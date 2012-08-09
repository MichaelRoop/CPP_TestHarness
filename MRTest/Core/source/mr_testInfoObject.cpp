///--------------------------------------------------------------------------------------
/// @file	mr_testInfoObject.cpp
/// @brief	cross platform and char width holder for test information.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_testInfoObject.h"


namespace mr_test
{

testInfoObject::testInfoObject() 
:	m_isActive( false ),
	m_isNull( true )
{
}


bool testInfoObject::isActive() const
{
	return m_isActive;
}


void testInfoObject::setActive( bool active )
{
	m_isActive = active;
}


bool testInfoObject::isNull() const
{
	return this->m_isNull;
}


void testInfoObject::setNull( bool isNull )
{
	m_isNull = isNull;
}


const mr_utils::mr_string& testInfoObject::getName() const
{
	return m_name;
}


void testInfoObject::setName( const mr_utils::mr_string& name )
{
	m_name = name;
}


const std::vector<TestInfoArgument>& testInfoObject::getArguments() const
{
	return m_arguments;
}


void testInfoObject::AddArgument( 
	const mr_utils::mr_string& name, 
	const mr_utils::mr_string& value 
)
{
	this->m_arguments.push_back( TestInfoArgument( name, value ) );
}


}