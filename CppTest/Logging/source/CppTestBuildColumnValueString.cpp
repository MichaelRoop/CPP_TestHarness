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
#include "CppTestBuildColumnValueString.h"
#include "mr_exception.h"
#include "mr_defines.h"


namespace MrTest {

BuildColumnValueString::BuildColumnValueString( 
	mr_utils::mr_stringstream&	os,
	const mr_utils::mr_string&	delimiter,
	const mr_utils::mr_string&	strQuotes
) :	m_os(os), 
	m_delimiter(delimiter),
	m_strQuotes(strQuotes),
	m_count(0) {
}


void BuildColumnValueString::operator () (const FieldPair& field) {
	if ((++this->m_count) > 1) {
		this->m_os << _L_(",");
	}
	this->Build(field);
}


void BuildColumnValueString::ConcatenateStr(const mr_utils::mr_string& str) {
	this->m_os << this->m_strQuotes.c_str() << str.c_str() << this->m_strQuotes.c_str();
}

} // end namespace

