///--------------------------------------------------------------------------------------
/// @file	mr_logOutputFactory.cpp
/// @brief	Factory to create iLogOutput objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_logOutputFactory.h"
#include "mr_iniLogInitialiser.h"
#include "mr_odbcOutput.h"
#include "mr_fileOutput.h"
#include "mr_consoleOutput.h"
#include "mr_exception.h"
#include "mr_sstream.h"
#include "mr_defines.h"


namespace mr_test
{

logOutputSharedPtr logOutputFactory::create( 
	mr_utils::SharedPtr<mr_test::iLogInitialiser>& initialiser 
)
{
	logOutputSharedPtr output;

	if (initialiser->getOutputType().compare( L("ODBC") ) == 0)
	{
		output = new mr_test::odbcOutput( initialiser );
	}
	else if (initialiser->getOutputType().compare( L("FILE") ) == 0)
	{
		mr_utils::mr_exception::assertCondition( false, FL, L("FILE output not ready") );
		output = new mr_test::fileOutput( "Simple log file.txt" );
	}
	else if (initialiser->getOutputType().compare( L("CONSOLE") ) == 0)
	{
		output = new mr_test::consoleOutput();
	}
	else
	{
		mr_utils::mr_stringstream os;
		os << L("Illegal output type:") << initialiser->getOutputType() << L(" Allowed types are 'ODBC', 'FILE', 'CONSOLE'");
		mr_utils::mr_exception::assertCondition( false, FL, os.str() );
	}

	return output;
}



}// end namespace

