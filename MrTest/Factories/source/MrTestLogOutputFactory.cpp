///--------------------------------------------------------------------------------------
/// @file	MrTestLogOutputFactory.cpp
/// @brief	Factory to create iLogOutput objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "MrTestLogOutputFactory.h"
#include "MrTestIniLogInitialiser.h"
#include "MrTestOdbcOutput.h"
#include "MrTestFileOutput.h"
#include "MrTestConsoleOutput.h"
#include "mr_exception.h"
#include "mr_sstream.h"
#include "mr_defines.h"


namespace MrTest {

LogOutputSharedPtr LogOutputFactory::Create( 
	mr_utils::SharedPtr<MrTest::ILogInitialiser>& initialiser 
) {
	LogOutputSharedPtr output;

	if (initialiser->GetOutputType().compare(_L_("ODBC") ) == 0) {
		output = new MrTest::OdbcOutput(initialiser);
	}
	else if (initialiser->GetOutputType().compare(_L_("FILE")) == 0) {
		mr_utils::mr_exception::assertCondition( false, _FL_, _L_("FILE output not ready"));
		output = new MrTest::FileOutput("Simple log file.txt");
	}
	else if (initialiser->GetOutputType().compare(_L_("CONSOLE")) == 0) {
		output = new MrTest::ConsoleOutput();
	}
	else {
		mr_utils::mr_stringstream os;
		os << _L_("Illegal output type:") << initialiser->GetOutputType() << _L_(" Allowed types are 'ODBC', 'FILE', 'CONSOLE'");
		mr_utils::mr_exception::assertCondition(false, FL, os.str());
	}

	return output;
}

}// end namespace

