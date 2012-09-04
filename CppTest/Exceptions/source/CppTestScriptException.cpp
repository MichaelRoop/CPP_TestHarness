///--------------------------------------------------------------------------------------
/// @file	mr_scriptException.cpp
/// @brief	cross platform and char width exceptions for dev test platform.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestScriptException.h"
#include "mr_sstream.h"
#include "mr_toStream.h"


namespace MrTest {

ScriptException::ScriptException( 
	const char*					file, 
	int							line, 
	const mr_utils::mr_string&	msg,
	const mr_utils::mr_string&	scriptFileName,
	const mr_utils::mr_string&	scriptLine
)
:	mr_utils::mr_exception( file, line, msg ),
	m_scriptFileName( scriptFileName ),
	m_scriptLine( scriptLine )
{
	/// @todo Track down why this is happening.  If a value of '\' or '/' is 
	///			passed in as file name then we can not init the sriptException file 
	///			name object at all.  Weirdness.
}


ScriptException::~ScriptException() throw() {
}


const mr_utils::mr_string ScriptException::LongMsg() const {
	mr_utils::mr_stringstream ss;
	ss << mr_utils::mr_exception::longMsg() << L(" : ") << mr_utils::ExtractFileName(this->m_scriptFileName);

	if (!m_scriptLine.empty()) {
		ss << L(" : ") << m_scriptLine.c_str();
	}
	return ss.str();
}



} // end namespace mr_test