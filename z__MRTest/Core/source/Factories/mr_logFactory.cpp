///--------------------------------------------------------------------------------------
/// @file	mr_logFactory.cpp
/// @brief	Factory to create iTestLog objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_logFactory.h"
#include "mr_logInitialiserFactory.h"
#include "mr_logOutputFactory.h"
#include "mr_sqlLog.h"
#include "mr_simpleLog.h"
#include "mr_exception.h"
#include "mr_sstream.h"
#include "mr_defines.h"


namespace mr_test
{

logSharedPtr logFactory::create( 
	const std::string&			configFileName, 
	const mr_utils::mr_string&	configFileType, 
	const mr_utils::mr_string&	section 
)
{
	logInitialiserSharedPtr mainInit = 
		logInitialiserFactory::create( configFileName, configFileType, section );
	mainInit->load();

	logInitialiserSharedPtr summaryInit = 
		logInitialiserFactory::create( configFileName, configFileType, mainInit->getSummaryLogId() );
	summaryInit->load();

	return logFactory::create( 
		logOutputFactory::create( mainInit ), 
		logFactory::create( logOutputFactory::create( summaryInit ), logSharedPtr(), summaryInit ), 
		mainInit 
	);
}


logSharedPtr logFactory::create(
	mr_utils::SharedPtr<iLogOutput>&		output, 
	mr_utils::SharedPtr<iTestLog>&			summaryLog, 
	mr_utils::SharedPtr<iLogInitialiser>&	initialiser 
)
{
	logSharedPtr log;

	if (initialiser->getLogType().compare( L("SQL") )  == 0)
	{
		log = new mr_test::sqlLog( output, summaryLog, initialiser );
	}
	else if (initialiser->getLogType().compare( L("CSV") ) == 0 )
	{
		log = new mr_test::simpleLog( output, summaryLog, initialiser );
	}
	else
	{
		mr_utils::mr_stringstream os;
		os << L("Illegal initialiser log type:") << initialiser->getLogType() << L(" Allowed types are 'SQL', 'CSV'");
		mr_utils::mr_exception::assertCondition( false, FL, os.str() );
	}
	return log;
}

}// end namespace
