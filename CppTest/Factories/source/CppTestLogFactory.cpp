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
#include "CppTestSqlLog.h"
#include "CppTestSimpleLog.h"
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
	mainInit->Load();

	LogInitialiserSharedPtr summaryInit = 
		LogInitialiserFactory::Create(configFileName, configFileType, mainInit->GetSummaryLogId());
	summaryInit->Load();

	return LogFactory::Create( 
		LogOutputFactory::Create(mainInit), 
		LogFactory::Create(LogOutputFactory::Create(summaryInit), LogSharedPtr(), summaryInit), 
		mainInit 
	);
}


LogSharedPtr LogFactory::Create(
	mr_utils::SharedPtr<CppTest::ILogOutput>&		output, 
	mr_utils::SharedPtr<CppTest::ILog>&				summaryLog, 
	mr_utils::SharedPtr<CppTest::ILogInitialiser>&	initialiser 
) {
	LogSharedPtr log;

	if (initialiser->GetLogType().compare(_L_("SQL"))  == 0) {
		log = new CppTest::SqlLog(output, summaryLog, initialiser);
	}
	else if (initialiser->GetLogType().compare(_L_("CSV")) == 0) {
		log = new CppTest::SimpleLog(output, summaryLog, initialiser);
	}
	else {
		mr_utils::mr_stringstream os;
		os << _L_("Illegal initialiser log type:") << initialiser->GetLogType() << _L_(" Allowed types are 'SQL', 'CSV'");
		mr_utils::mr_exception::assertCondition(false, _FL_, os.str());
	}
	return log;
}

}// end namespace
