///--------------------------------------------------------------------------------------
/// @file	MrTestCommandLineReader.cpp
/// @brief	Converts a command line argument to a test info
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#include "MrTestCommandLineReader.h"
#include "CppTestScriptException.h"
#include "mr_defines.h"

namespace MrTest {

CommandLineReader::CommandLineReader( 
	const mr_utils::mr_string&	line,
	mr_utils::mr_char			nameDelimiter,
	mr_utils::mr_char			argDelimiter ) 
	:	ScriptReaderBase("CommandLine", nameDelimiter, argDelimiter),
		m_line(mr_utils::Trim(line)),
		m_used(false) {
}


CommandLineReader::CommandLineReader( 
	const mr_utils::mr_char*	line,   
	mr_utils::mr_char nameDelimiter,
	mr_utils::mr_char argDelimiter ) 
	:	ScriptReaderBase("CommandLine", nameDelimiter, argDelimiter),
		m_line(line == 0 ? L("") : mr_utils::Trim(line)),
		m_used(false) {
}


void CommandLineReader::Open() {
	this->m_used = false;
}


MrTest::TestInfoObject CommandLineReader::getNextTest(mr_utils::mr_string& fixtureName) {
	MrTest::TestInfoObject		testInfo;
	if (!this->m_used) {
		this->m_used = true;
		if (!this->m_line.empty() && this->m_line[0] != _L_('#')) {
			testInfo.SetNull(false);
			this->ProcessLine(fixtureName, testInfo, this->m_line);
		}
	}
	return testInfo;
}

} // end of namespace
