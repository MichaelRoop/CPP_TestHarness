///--------------------------------------------------------------------------------------
/// @file	mr_BuildConsoleSummaryString.h
/// @brief	Builds strings with for summary specially for console.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_buildConsoleSummaryString.h"


namespace mr_test
{

buildConsoleSummaryString::buildConsoleSummaryString( 
	mr_utils::mr_stringstream&	os,
	const mr_utils::mr_string&	delimiter,
	const mr_utils::mr_string&	strQuotes,
	iTestLog*					theLog 
) 
:	buildSummaryColumnValueString( os, delimiter, strQuotes, theLog )
{
}


void buildConsoleSummaryString::operator () ( const FieldPair& field )
{
	if ((++m_count) > 1)
	{
		m_os << std::endl;
	}

	/// @todo We will eventually left pad to create an allignment
	m_os << field.first << L(":");

	this->build( field );
}

} // end namespace
