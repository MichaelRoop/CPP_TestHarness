///--------------------------------------------------------------------------------------
/// @file	mr_buildColumnInfoString.cpp
/// @brief	Builds strings with for column information.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_buildColumnInfoString.h"
#include "mr_exception.h"
#include "mr_defines.h"


namespace mr_test
{

BuildColumnInfoString::BuildColumnInfoString( 
	mr_utils::mr_stringstream& os,
	const mr_utils::mr_string&	nameTypeDelimiter,
	const mr_utils::mr_string&	unitDelimiter,
	ColumnInfoParts				parts
) 
:	m_os(os), 
	m_nameTypeDelimiter( nameTypeDelimiter ),
	m_unitDelimiter( unitDelimiter ),
	m_parts( parts ),
	m_count( 0 )
{
}


void BuildColumnInfoString::operator () ( const FieldPair& field )
{
	if ((++m_count) > 1)
	{
		m_os << m_unitDelimiter;
	}

	switch( m_parts )
	{
	case NAME_ONLY:
		m_os << field.first;
		break;
	case TYPE_ONLY:
		m_os << field.second;
		break;
	case NAME_TYPE:
		m_os << field.first << m_nameTypeDelimiter << field.second;
		break;
	default:
		mr_utils::mr_exception::assertCondition( false, FL, L("Unhandled case") );
	}
}


} // end namespace