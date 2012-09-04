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
#include "mr_pointerException.h"
#include "mr_defines.h"
#include "mr_sstream.h"
#include "mr_toStream.h"

namespace MrTest {



FileScriptReader::FileScriptReader( 
	mr_utils::mr_string&	filename,
	mr_utils::mr_char		nameDelimiter,
	mr_utils::mr_char		argDelimiter ) 
	:	ScriptReaderBase(filename, nameDelimiter, argDelimiter),
		m_filename(filename) {
}


void FileScriptReader::Open() {
	mr_utils::mr_pointerException::ptrAssert(this->m_filename.c_str(), _FL_);
	this->FileAssert(!this->m_filename.empty(), _FL_, _L_("Empty File Name"));

	this->m_scriptStream.open(m_filename.c_str());
	this->FileAssert(this->m_scriptStream.is_open(), _FL_, _L_("File not open"));
}


MrTest::TestInfoObject FileScriptReader::getNextTest(mr_utils::mr_string& fixtureName) {
	const int			size = 2048;
	mr_utils::mr_char	buff[size];
	MrTest::TestInfoObject		testInfo;
	this->FileAssert(this->m_scriptStream.is_open(), _FL_, _L_( "File not open"));

	while (this->m_scriptStream.getline(buff, size)) {
		mr_utils::mr_string line(mr_utils::Trim(mr_utils::mr_string(buff)));
		if (!line.empty() && line[0] != _L_('#')) {
			testInfo.SetNull(false);
			this->ProcessLine(fixtureName, testInfo, buff);
			break;
		}
	}
	return testInfo;
}

} // end of namespace
