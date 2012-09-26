///--------------------------------------------------------------------------------------
/// @file	mr_fileScriptReader.cpp
/// @brief	cross platform and char width file script reader.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_fileScriptReader.h"
#include "mr_scriptException.h"
#include "mr_fileException.h"
#include "mr_pointerException.h"
#include "mr_defines.h"


namespace mr_test
{

fileScriptReader::fileScriptReader( 
	const std::string&	filename,
	mr_utils::mr_char	nameDelimiter,
	mr_utils::mr_char	argDelimiter ) 
:	m_filename( filename ),
	m_nameDelimiter( nameDelimiter ),
	m_argDelimiter( argDelimiter )
{
}


fileScriptReader::fileScriptReader( 
	const char*			filename,
	mr_utils::mr_char	nameDelimiter,
	mr_utils::mr_char	argDelimiter ) 
	: m_filename( ( filename == NULL ? "" : filename ) ),
	m_nameDelimiter( nameDelimiter ),
	m_argDelimiter( argDelimiter )
{
}


void fileScriptReader::Open()
{
	mr_utils::mr_pointerException::ptrAssert( m_filename.c_str(), FL );
	this->fileAssert( !m_filename.empty(), FL, L( "Empty File Name") );
	m_scriptStream.open( m_filename.c_str() );
	this->fileAssert( m_scriptStream.is_open(), FL, L( "File not open") );
}


CppTest::TestInfoObject fileScriptReader::getNextTest() {
	const int			size = 2048;
	mr_utils::mr_char	buff[size];
	CppTest::TestInfoObject		testInfo;

	this->fileAssert( m_scriptStream.is_open(), FL, L( "File not open") );
	if (m_scriptStream.getline( buff, size )) {
		testInfo.SetNull( false );
		processLine(testInfo, buff);
	}
	return testInfo;
}


void fileScriptReader::processLine(CppTest::TestInfoObject& testInfo, const mr_utils::mr_char* str) {
	mr_utils::mr_string s(mr_utils::Trim(mr_utils::mr_string(str )));

	// Check for empty line or line starting with # comment indicator.
	testInfo.SetActive( !s.empty() && s[0] != L( '#' ) );

	if (testInfo.IsActive()) {
		mr_utils::mr_string name;
		mr_utils::mr_string args;
		mr_utils::mr_string::size_type pos = 0;

		if (mr_utils::MrTokenize( pos, s, name, m_nameDelimiter )) {
			testInfo.SetName( name );

			// It is possible for the test to have only a name and no arguments.
			if (mr_utils::MrTokenize( pos, s, args, m_nameDelimiter )) {
				this->processArgs( testInfo, args );
			}
		}
	}
}


void fileScriptReader::processArgs(CppTest::TestInfoObject& testInfo, const mr_utils::mr_string& args) {
	mr_utils::mr_string oneArg;
	mr_utils::mr_string::size_type pos = 0;

	while (mr_utils::MrTokenize(pos, args, oneArg, m_argDelimiter)) {
		this->processArg(testInfo, oneArg);
	}
}


void fileScriptReader::processArg(CppTest::TestInfoObject& testInfo, const mr_utils::mr_string& arg) {
	mr_utils::mr_string name;
	mr_utils::mr_string value;
	mr_utils::mr_string::size_type pos = 0;

	this->getArgComponent( pos, arg, name );
	this->getArgComponent( pos, arg, value );
	testInfo.AddArgument( name, value );
}


void fileScriptReader::getArgComponent( 
	mr_utils::mr_string::size_type&	pos, 
	const mr_utils::mr_string&		str, 
	mr_utils::mr_string&			token 
) const
{
	this->scriptAssert( 
		mr_utils::MrTokenize( pos, str, token, L('=') ), FL, L("Invalid Argument Format"), str 
	);
}

#include <assert.h>

void fileScriptReader::scriptAssert( 
	bool						condition,
	const char*					file, 
	int							line, 
	const mr_utils::mr_string&	msg,
	const mr_utils::mr_string&	scriptLine
) const
{
	if (!condition)
	{
		throw scriptException( file, line, msg, m_filename, scriptLine );
	}
}


void fileScriptReader::fileAssert( 
	bool						condition,
	const char*					file, 
	int							line, 
	const mr_utils::mr_string&	msg
) const
{
	if (!condition)
	{
		throw mr_utils::fileException( file, line, msg, m_filename );
	}
}




} // end of namespace
