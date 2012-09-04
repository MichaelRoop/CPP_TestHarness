///--------------------------------------------------------------------------------------
/// @file	MrTestScriptReaderBase.cpp
/// @brief	Common functionality for reading in text based test case information
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#include "MrTestScriptReaderBase.h"
#include "CppTestScriptException.h"
#include "mr_defines.h"
#include "mr_fileException.h"


namespace MrTest {


ScriptReaderBase::ScriptReaderBase(
	const std::string& origine,
	mr_utils::mr_char nameDelimiter, 
	mr_utils::mr_char argDelimiter) :
	m_origine(origine),
	m_nameDelimiter(nameDelimiter),
	m_argDelimiter(argDelimiter) {
}


void ScriptReaderBase::ProcessLine(mr_utils::mr_string& fixtureName, MrTest::TestInfoObject& testInfo, mr_utils::mr_string line) {

	// Check for Disabled indicator
	testInfo.SetActive(line[0] != _L_('@'));
	// TODO - make more robust
	if (!testInfo.IsActive()) {
		line = mr_utils::SubString(line, 1);
	}

	mr_utils::mr_string name;
	mr_utils::mr_string args;
	mr_utils::mr_string::size_type pos = 0;

	// If no '.' then assume it is the fixture name only. This means execute all tests on that fixture
	if (line.find(_L_('.')) == mr_utils::StrNPos()) {
		if (mr_utils::MrTokenize(pos, line, fixtureName, m_nameDelimiter)) {
			return;
		}
		this->ScriptAssert(false, _FL_, L("Invalid script line format"), line); 
	}
	else {
		mr_utils::MrTokenize(pos, line, fixtureName, _L_('.'));

		if (mr_utils::MrTokenize(pos, line, name, m_nameDelimiter)) {
			testInfo.SetName(name);

			// It is possible for the test to have only a name and no arguments.
			if (mr_utils::MrTokenize(pos, line, args, m_nameDelimiter)) {
				this->ProcessArgs(testInfo, args);
			}
		}
	}
}


void ScriptReaderBase::ProcessArgs(MrTest::TestInfoObject& testInfo, const mr_utils::mr_string& args) {
	mr_utils::mr_string oneArg;
	mr_utils::mr_string::size_type pos = 0;

	while (mr_utils::MrTokenize(pos, args, oneArg, m_argDelimiter)) {
		this->ProcessArg(testInfo, oneArg);
	}
}


void ScriptReaderBase::ProcessArg(MrTest::TestInfoObject& testInfo, const mr_utils::mr_string& arg) {
	mr_utils::mr_string name;
	mr_utils::mr_string value;
	mr_utils::mr_string::size_type pos = 0;

	this->GetArgComponent(pos, arg, name);
	this->GetArgComponent(pos, arg, value);
	testInfo.AddArgument(name, value);
}


void ScriptReaderBase::GetArgComponent( 
	mr_utils::mr_string::size_type&	pos, 
	const mr_utils::mr_string&		str, 
	mr_utils::mr_string&			token) const {

	this->ScriptAssert( 
		mr_utils::MrTokenize(pos, str, token, _L_('=')), _FL_, L("Invalid Argument Format"), str 
	);
}


void ScriptReaderBase::ScriptAssert( 
	bool						condition,
	const char*					file, 
	int							line, 
	const mr_utils::mr_string&	msg,
	const mr_utils::mr_string&	scriptLine
) const {
	if (!condition) {
		throw MrTest::ScriptException(file, line, msg, this->m_origine, scriptLine);
	}
}


void ScriptReaderBase::FileAssert( 
	bool						condition,
	const char*					file, 
	int							line, 
	const mr_utils::mr_string&	msg
) const {
	if (!condition) {
		throw mr_utils::fileException(file, line, msg, this->m_origine);
	}
}



} // end namespace