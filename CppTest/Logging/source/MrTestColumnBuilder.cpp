///--------------------------------------------------------------------------------------
/// @file	MrTestColumnBuilder.cpp
/// @brief	Builds strings for column headers and data.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "MrTestColumnBuilder.h"
#include "MrTestBuildColumnInfoString.h"
#include "MrTestBuildTestCaseColumnValueString.h"
#include "MrTestBuildSummaryColumnValueString.h"
#include "MrTestBuildConsoleSummaryString.h"
#include "IMrTestLog.h"
#include "mr_sstream.h"
#include <algorithm>

namespace MrTest {

mr_utils::mr_string ColumnBuilder::CreateColumnHeaders( 
	const FieldVector&			fieldInfo, 
	const mr_utils::mr_string&	delimiter) {
	mr_utils::mr_stringstream os;
	std::for_each( 
		fieldInfo.begin(), 
		fieldInfo.end(), 
		BuildColumnInfoString(os, _L_(" "), delimiter, BuildColumnInfoString::NAME_ONLY) 
	);
	return os.str();
}


mr_utils::mr_string ColumnBuilder::CreateColumnNameTypeStr( 
	const FieldVector&			fieldInfo, 
	const mr_utils::mr_string&	nameTypeDelimiter, 
	const mr_utils::mr_string&	colDelimiter 
) {
	mr_utils::mr_stringstream os;
	std::for_each( 
		fieldInfo.begin(), 
		fieldInfo.end(), 
		BuildColumnInfoString(os, nameTypeDelimiter, colDelimiter, BuildColumnInfoString::NAME_TYPE) 
	);
	return os.str();
}


mr_utils::mr_string ColumnBuilder::CreateColumnData( 
	const FieldVector&			fieldInfo,
	const mr_utils::mr_string&	delimiter,
	const mr_utils::mr_string&	strQuotes,
	MrTest::ICase&				testCase 
) {
	// I cannot use a factory to create the build objects since the for_each will fail with a
	// C2893.  It cannot access a derived class through a virtual base class.
	mr_utils::mr_stringstream os;
	std::for_each( 
		fieldInfo.begin(), 
		fieldInfo.end(), 
		BuildTestCaseColumnValueString(os, delimiter, strQuotes, testCase)
	);
	return os.str();
}


mr_utils::mr_string ColumnBuilder::CreateColumnData( 
	const FieldVector&			fieldInfo,
	const mr_utils::mr_string&	delimiter,
	const mr_utils::mr_string&	strQuotes,
	MrTest::ILog*				theLog 
) {
	mr_utils::mr_stringstream os;
	std::for_each( 
		fieldInfo.begin(), 
		fieldInfo.end(), 
		BuildSummaryColumnValueString(os, delimiter, strQuotes, theLog)
	);
	return os.str();

	///// @todo we will chose this by querying the log object for its output type
	//mr_utils::mr_stringstream os;
	//std::for_each( 
	//	fieldInfo.begin(), 
	//	fieldInfo.end(), 
	//	buildConsoleSummaryString( os, delimiter, strQuotes, theLog )
	//);
	//return os.str();
}

} // end namespace
