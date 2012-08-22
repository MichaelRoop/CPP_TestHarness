///--------------------------------------------------------------------------------------
/// @file	CppTestFileScriptReader.cpp
/// @brief	cross platform and char width file script reader.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestFileScriptReader.h"
#include "CppTestScriptException.h"
#include "mr_fileException.h"
#include "mr_pointerException.h"
#include "mr_defines.h"


namespace CppTest {

FileScriptReader::FileScriptReader( 
	const std::string&	filename,
	mr_utils::mr_char nameDelimiter,
	mr_utils::mr_char argDelimiter ) 
:	m_filename(filename),
	m_nameDelimiter(nameDelimiter),
	m_argDelimiter(argDelimiter) {
}


FileScriptReader::FileScriptReader( 
	const char*	filename,
	mr_utils::mr_char nameDelimiter,
	mr_utils::mr_char argDelimiter ) 
	: m_filename((filename == NULL ? "" : filename)),
	m_nameDelimiter(nameDelimiter),
	m_argDelimiter(argDelimiter) {
}


void FileScriptReader::Open() {
	mr_utils::mr_pointerException::ptrAssert(m_filename.c_str(), _FL_);
	this->FileAssert(!m_filename.empty(), _FL_, _L_("Empty File Name"));

	this->m_scriptStream.open(m_filename.c_str());
	this->FileAssert(m_scriptStream.is_open(), _FL_, _L_("File not open"));
}


CppTest::TestInfoObject FileScriptReader::getNextTest() {
	const int			size = 2048;
	mr_utils::mr_char	buff[size];
	CppTest::TestInfoObject		testInfo;
	this->FileAssert(m_scriptStream.is_open(), _FL_, _L_( "File not open"));

	if (m_scriptStream.getline(buff, size)) {
		testInfo.SetNull(false);
		this->ProcessLine(testInfo, buff);
	}
	return testInfo;
}


void FileScriptReader::ProcessLine(CppTest::TestInfoObject& testInfo, const mr_utils::mr_char* str) {
	mr_utils::mr_string s(mr_utils::Trim(mr_utils::mr_string(str)));

	// Check for empty line or line starting with # comment indicator.
	testInfo.SetActive(!s.empty() && s[0] != _L_('#'));

	if (testInfo.IsActive()) {
		mr_utils::mr_string name;
		mr_utils::mr_string args;
		mr_utils::mr_string::size_type pos = 0;

		if (mr_utils::MrTokenize(pos, s, name, m_nameDelimiter)) {
			testInfo.SetName(name);

			// It is possible for the test to have only a name and no arguments.
			if (mr_utils::MrTokenize(pos, s, args, m_nameDelimiter)) {
				this->ProcessArgs(testInfo, args);
			}
		}
	}
}


void FileScriptReader::ProcessArgs(CppTest::TestInfoObject& testInfo, const mr_utils::mr_string& args) {
	mr_utils::mr_string oneArg;
	mr_utils::mr_string::size_type pos = 0;

	while (mr_utils::MrTokenize(pos, args, oneArg, m_argDelimiter)) {
		this->ProcessArg(testInfo, oneArg);
	}
}


void FileScriptReader::ProcessArg(CppTest::TestInfoObject& testInfo, const mr_utils::mr_string& arg) {
	mr_utils::mr_string name;
	mr_utils::mr_string value;
	mr_utils::mr_string::size_type pos = 0;

	this->GetArgComponent(pos, arg, name);
	this->GetArgComponent(pos, arg, value);
	testInfo.AddArgument(name, value);
}


void FileScriptReader::GetArgComponent( 
	mr_utils::mr_string::size_type&	pos, 
	const mr_utils::mr_string&		str, 
	mr_utils::mr_string&			token 
) const {
	this->ScriptAssert( 
		mr_utils::MrTokenize(pos, str, token, _L_('=')), _FL_, L("Invalid Argument Format"), str 
	);
}


void FileScriptReader::ScriptAssert( 
	bool						condition,
	const char*					file, 
	int							line, 
	const mr_utils::mr_string&	msg,
	const mr_utils::mr_string&	scriptLine
) const {
	if (!condition) {
		throw ScriptException(file, line, msg, m_filename, scriptLine);
	}
}


void FileScriptReader::FileAssert( 
	bool						condition,
	const char*					file, 
	int							line, 
	const mr_utils::mr_string&	msg
) const {
	if (!condition) {
		throw mr_utils::fileException(file, line, msg, m_filename);
	}
}




} // end of namespace
