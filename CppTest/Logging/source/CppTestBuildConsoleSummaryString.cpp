///--------------------------------------------------------------------------------------
/// @file	CppTestBuildConsoleSummaryString.h
/// @brief	Builds strings with for summary specially for console.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestBuildConsoleSummaryString.h"


namespace CppTest {

BuildConsoleSummaryString::BuildConsoleSummaryString( 
	mr_utils::mr_stringstream&	os,
	const mr_utils::mr_string&	delimiter,
	const mr_utils::mr_string&	strQuotes,
	CppTest::ILog*				theLog 
) 
:	BuildSummaryColumnValueString(os, delimiter, strQuotes, theLog) {
}


void BuildConsoleSummaryString::operator () (const FieldPair& field) {
	if ((++this->m_count) > 1) {
		this->m_os << std::endl;
	}

	/// @todo We will eventually left pad to create an allignment
	this->m_os << field.first << _L_(":");
	this->Build(field);
}

} // end namespace
