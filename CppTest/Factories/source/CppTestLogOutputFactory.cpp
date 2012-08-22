///--------------------------------------------------------------------------------------
/// @file	CppTestLogOutputFactory.cpp
/// @brief	Factory to create iLogOutput objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestLogOutputFactory.h"
#include "mr_iniLogInitialiser.h"
#include "mr_odbcOutput.h"
#include "mr_fileOutput.h"
#include "mr_consoleOutput.h"
#include "mr_exception.h"
#include "mr_sstream.h"
#include "mr_defines.h"


namespace CppTest {

LogOutputSharedPtr LogOutputFactory::Create( 
	mr_utils::SharedPtr<mr_test::iLogInitialiser>& initialiser 
) {
	LogOutputSharedPtr output;

	if (initialiser->getOutputType().compare(_L_("ODBC") ) == 0) {
		output = new mr_test::odbcOutput(initialiser);
	}
	else if (initialiser->getOutputType().compare(_L_("FILE")) == 0) {
		mr_utils::mr_exception::assertCondition( false, _FL_, _L_("FILE output not ready"));
		output = new mr_test::fileOutput("Simple log file.txt");
	}
	else if (initialiser->getOutputType().compare(_L_("CONSOLE")) == 0) {
		output = new mr_test::consoleOutput();
	}
	else {
		mr_utils::mr_stringstream os;
		os << _L_("Illegal output type:") << initialiser->getOutputType() << _L_(" Allowed types are 'ODBC', 'FILE', 'CONSOLE'");
		mr_utils::mr_exception::assertCondition(false, FL, os.str());
	}

	return output;
}

}// end namespace

