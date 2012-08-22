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
#include "CppTestIniLogInitialiser.h"
#include "CppTestOdbcOutput.h"
#include "CppTestFileOutput.h"
#include "CppTestConsoleOutput.h"
#include "mr_exception.h"
#include "mr_sstream.h"
#include "mr_defines.h"


namespace CppTest {

LogOutputSharedPtr LogOutputFactory::Create( 
	mr_utils::SharedPtr<CppTest::ILogInitialiser>& initialiser 
) {
	LogOutputSharedPtr output;

	if (initialiser->GetOutputType().compare(_L_("ODBC") ) == 0) {
		output = new CppTest::OdbcOutput(initialiser);
	}
	else if (initialiser->GetOutputType().compare(_L_("FILE")) == 0) {
		mr_utils::mr_exception::assertCondition( false, _FL_, _L_("FILE output not ready"));
		output = new CppTest::FileOutput("Simple log file.txt");
	}
	else if (initialiser->GetOutputType().compare(_L_("CONSOLE")) == 0) {
		output = new CppTest::ConsoleOutput();
	}
	else {
		mr_utils::mr_stringstream os;
		os << _L_("Illegal output type:") << initialiser->GetOutputType() << _L_(" Allowed types are 'ODBC', 'FILE', 'CONSOLE'");
		mr_utils::mr_exception::assertCondition(false, FL, os.str());
	}

	return output;
}

}// end namespace

