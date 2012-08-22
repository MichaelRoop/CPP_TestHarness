///--------------------------------------------------------------------------------------
/// @file	CppTestLogFactory.cpp
/// @brief	Factory to create iTestLog objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestLogFactory.h"
#include "CppTestLogInitialiserFactory.h"
#include "CppTestLogOutputFactory.h"
#include "mr_sqlLog.h"
#include "mr_simpleLog.h"
#include "mr_exception.h"
#include "mr_sstream.h"
#include "mr_defines.h"


namespace CppTest {

LogSharedPtr LogFactory::Create( 
	const std::string&			configFileName, 
	const mr_utils::mr_string&	configFileType, 
	const mr_utils::mr_string&	section 
) {
	LogInitialiserSharedPtr mainInit = 
		LogInitialiserFactory::Create(configFileName, configFileType, section);
	mainInit->load();

	LogInitialiserSharedPtr summaryInit = 
		LogInitialiserFactory::Create(configFileName, configFileType, mainInit->getSummaryLogId());
	summaryInit->load();

	return LogFactory::Create( 
		LogOutputFactory::Create(mainInit), 
		LogFactory::Create(LogOutputFactory::Create(summaryInit), LogSharedPtr(), summaryInit), 
		mainInit 
	);
}


LogSharedPtr LogFactory::Create(
	mr_utils::SharedPtr<CppTest::ILogOutput>&		output, 
	mr_utils::SharedPtr<mr_test::iTestLog>&			summaryLog, 
	mr_utils::SharedPtr<mr_test::iLogInitialiser>&	initialiser 
) {
	LogSharedPtr log;

	if (initialiser->getLogType().compare(_L_("SQL"))  == 0) {
		log = new mr_test::sqlLog(output, summaryLog, initialiser);
	}
	else if (initialiser->getLogType().compare(_L_("CSV")) == 0) {
		log = new mr_test::simpleLog(output, summaryLog, initialiser);
	}
	else {
		mr_utils::mr_stringstream os;
		os << _L_("Illegal initialiser log type:") << initialiser->getLogType() << _L_(" Allowed types are 'SQL', 'CSV'");
		mr_utils::mr_exception::assertCondition(false, _FL_, os.str());
	}
	return log;
}

}// end namespace
