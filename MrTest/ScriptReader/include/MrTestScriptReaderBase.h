///--------------------------------------------------------------------------------------
/// @file	MrTestScriptReaderBase.h
/// @brief	Common functionality for reading in text based test case information
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_SCRIPT_READER_BASE_H)
#define MR_TEST_SCRIPT_READER_BASE_H

#include "IMrTestScriptReader.h"

namespace MrTest {

///--------------------------------------------------------------------------------------
///
/// @brief	Pure virtual class to abstract the reading of a test script.
///
/// The derived classes can read a script file of any format from any source as long
/// as they satisfy the interface.  In this case you could have a custom format of script
/// file or one that used known formats such as ini or XML.
///--------------------------------------------------------------------------------------
class MRTESCASE_API ScriptReaderBase : public IScriptReader {
protected:

	/// @brief	Constructor.
	/// @param	origine			The origine of the script
	/// @param	nameDelimiter	Delimiter character to tokenize the name and 
	///							argument portion of the line.
	/// @param	argDelimiter	Delimiter to tokenize the argument portion of the
	///							line into separate arguments.
	ScriptReaderBase(
		const mr_utils::mr_string&	origine,
		mr_utils::mr_char			nameDelimiter = _L_('$'), 
		mr_utils::mr_char			argDelimiter = _L_('|'));


	/// @brief	Helper method to process one line of the script file.
	/// @param	fixtureName	Name of the fixture for the test case.
	///	@throw	Throws a scriptException on failure
	/// @param	testInfo	The testInfoObject to populate from the script file.
	/// @param	str			The line as read from the file.
	void ProcessLine(mr_utils::mr_string& fixtureName, MrTest::TestInfoObject& testInfo, mr_utils::mr_string str);


	/// @brief	Helper method to process the arguments portion of the script line.
	///	@throw	Throws a scriptException on failure
	/// @param	testInfo	The testInfoObject to populate from the script file.
	/// @param	args		The args portion of the script line.
	void ProcessArgs(MrTest::TestInfoObject& testInfo, const mr_utils::mr_string& args);


	/// @brief	Helper method to process one argument string token.
	/// Each argument should be in the format name=value.
	///	@throw	Throws a scriptException on failure
	/// @param	testInfo	The testInfoObject to populate from the script file.
	/// @param	args		The arg token from the script line.
	void ProcessArg(MrTest::TestInfoObject& testInfo, const mr_utils::mr_string& arg);


	/// @brief	Extracts name on first call and value on second.
	///	@throw	Throws a scriptException on failure
	/// @param	pos		The current position in the argument string.
	/// @param	str		The argument string.
	/// @param	token	The string token to be extracted from the argument string.
	void GetArgComponent( 
		mr_utils::mr_string::size_type&	pos, 
		const mr_utils::mr_string&		str, 
		mr_utils::mr_string&			token 
	) const;


	/// @brief	Wrapper to clean up checking for exception throw.
	///	@throw	Throws a scriptException on failure
	/// @param	origine			Where is this sript line originating from
	/// @param	condition		The condition to test. If false an exception is thrown.
	/// @param	file			The source code file where problem originates.
	/// @param	line			The source code line where problem originates.
	/// @param	msg				The message explaining the exception.
	/// @param	scriptFileLine	The content of the script line being processed.
	void ScriptAssert( 
		bool						condition,
		const char*					file, 
		int							line, 
		const mr_utils::mr_string&	msg,
		const mr_utils::mr_string&	scriptLine = _L_("")
	) const;


	/// @brief	Wrapper to clean up checking for exception throw.
	///	@throw	Throws a fileException on failure
	/// @param	origine			Where is this sript line originating from
	/// @param	condition		The condition to test. If false an exception is thrown.
	/// @param	file			The source code file where problem originates.
	/// @param	line			The source code line where problem originates.
	/// @param	msg				The message explaining the exception.
	void FileAssert( 
		bool						condition,
		const char*					file, 
		int							line, 
		const mr_utils::mr_string&	msg
	) const;

private:
	mr_utils::mr_char	m_nameDelimiter;///< Name delimiter.
	mr_utils::mr_char	m_argDelimiter;	///< Argument delimiter.
	mr_utils::mr_string m_origine;		///< origine of script input


	/// @brief	Default constructor
	ScriptReaderBase() {
	}

};

} // end namespace

MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::allocator<MrTest::ScriptReaderBase*>;
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::vector<MrTest::ScriptReaderBase*>;

#endif
