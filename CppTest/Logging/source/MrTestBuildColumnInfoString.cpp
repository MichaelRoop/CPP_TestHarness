///--------------------------------------------------------------------------------------
/// @file	MrTestBuildColumnInfoString.cpp
/// @brief	Builds strings with for column information.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "MrTestBuildColumnInfoString.h"
#include "mr_exception.h"
#include "mr_defines.h"


namespace MrTest {

BuildColumnInfoString::BuildColumnInfoString( 
	mr_utils::mr_stringstream&	os,
	const mr_utils::mr_string&	nameTypeDelimiter,
	const mr_utils::mr_string&	unitDelimiter,
	ColumnInfoParts				parts
) :	m_os(os), 
	m_nameTypeDelimiter(nameTypeDelimiter),
	m_unitDelimiter(unitDelimiter),
	m_parts(parts),
	m_count(0) {
}


void BuildColumnInfoString::operator () (const MrTest::FieldPair& field) {
	if ((++this->m_count) > 1) {
		m_os << this->m_unitDelimiter;
	}

	switch(this->m_parts) {
		case NAME_ONLY:
			this->m_os << field.first;
			break;
		case TYPE_ONLY:
			this->m_os << field.second;
			break;
		case NAME_TYPE:
			this->m_os << field.first << this->m_nameTypeDelimiter << field.second;
			break;
		default:
			mr_utils::mr_exception::assertCondition(false, _FL_, _L_("Unhandled case"));
		}
}


} // end namespace
