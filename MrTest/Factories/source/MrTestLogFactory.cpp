///--------------------------------------------------------------------------------------
/// @file	MrTestLogFactory.cpp
/// @brief	Factory to create iTestLog objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "MrTestLogFactory.h"
#include "MrTestLogInitialiserFactory.h"
#include "MrTestLogOutputFactory.h"
#include "MrTestSqlLog.h"
#include "MrTestSimpleLog.h"
#include "mr_exception.h"
#include "mr_sstream.h"
#include "mr_defines.h"


namespace MrTest {

LogSharedPtr LogFactory::Create( 
	const mr_utils::mr_string&	configFileName, 
	const mr_utils::mr_string&	configFileType, 
	const mr_utils::mr_string&	section 
) {
	LogInitialiserSharedPtr mainInit = 
		LogInitialiserFactory::Create(configFileName, configFileType, section);
	mainInit->Load();

	LogInitialiserSharedPtr summaryInit = 
		LogInitialiserFactory::Create(configFileName, configFileType, mainInit->GetSummaryLogId());
	summaryInit->Load();

    LogSharedPtr dummyLogSharedPtr;
    LogOutputSharedPtr mainInitOutputSharedPtr = LogOutputFactory::Create(mainInit);
    LogOutputSharedPtr summaryInitSharedPtr = LogOutputFactory::Create(summaryInit);
    LogSharedPtr summaryLogSharedPtr = LogFactory::Create(summaryInitSharedPtr, dummyLogSharedPtr, summaryInit);

    return LogFactory::Create(mainInitOutputSharedPtr, summaryLogSharedPtr, mainInit);
}


LogSharedPtr LogFactory::Create(
    mr_utils::SharedPtr<MrTest::ILogOutput>&		output,
    mr_utils::SharedPtr<MrTest::ILog>&				summaryLog,
    mr_utils::SharedPtr<MrTest::ILogInitialiser>&	initialiser
) {
    LogSharedPtr log;

    if (initialiser->GetLogType().compare(_L_("SQL"))  == 0) {
        log = new MrTest::SqlLog(output, summaryLog, initialiser);
    }
    else if (initialiser->GetLogType().compare(_L_("CSV")) == 0) {
        log = new MrTest::SimpleLog(output, summaryLog, initialiser);
    }
    else {
        mr_utils::mr_stringstream os;
        os << _L_("Illegal initialiser log type:") << initialiser->GetLogType() << _L_(" Allowed types are 'SQL', 'CSV'");
        mr_utils::mr_exception::assertCondition(false, _FL_, os.str());
    }
    return log;
}



}// end namespace
