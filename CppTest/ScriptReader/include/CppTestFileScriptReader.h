///--------------------------------------------------------------------------------------
/// @file	CppTestScriptReader.h
/// @brief	cross platform and char width file script reader.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_FILE_SCRIPT_READER_H)
#define CPP_TEST_FILE_SCRIPT_READER_H

#include "CppTestDefines.h"
#include "ICppTestScriptReader.h"
#include "mr_fstream.h"
#include "mr_char.h" 


namespace CppTest {

///--------------------------------------------------------------------------------------
///
/// @brief	Class to abstract the reading of a test script from a file.
///
/// Each line in the file represents one test case. As the lines are read in, a 
/// testInfoObject is created that holds the name and arguments of the test case.
///
/// Each line will be broken in two parts, the test name and the arguments string.
/// The delimiter between name and argument sections is configurable.  The default is
/// the '$' character.
///
/// The name section is obligatory.  The argument section is optional.
///
/// The arguments portion will be further broken down into name and value pairs.
///
/// The delimiters are configurable between arguments is configurable. The default is 
/// the '|' character.
///
///	Each argument will follow this format:
///		ArgName=ArgValue.
///
/// If there is no name/arguments delimiter or it is not found then the entire line will 
/// be taken as the test name.
///
/// If the first non whitespace on a line is '#' it will be considered as a comment or 
/// inactive test case and be discarded.
///--------------------------------------------------------------------------------------
class CPPTESCASE_API FileScriptReader : public CppTest::IScriptReader {
public:

	/// @brief	Constructor.
	/// @param	filename	The file to load the script from.
	/// @param	nameDelimiter	Delimiter character to tokenize the name and 
	///							argument portion of the line.
	/// @param	argDelimiter	Delimiter to tokenize the argument portion of the
	///							line into separate arguments.
	FileScriptReader( 
		const std::string&	filename,
		mr_utils::mr_char	nameDelimiter = _L_('$'),
		mr_utils::mr_char	argDelimiter = _L_('|')
	);


	/// @brief	Constructor.
	/// @param	filename	The file to load the script from.
	/// @param	nameDelimiter	Delimiter character to tokenize the name and 
	///							argument portion of the line.
	/// @param	argDelimiter	Delimiter to tokenize the argument portion of the
	///							line into separate arguments.
	FileScriptReader( 
		const char*			filename,
		mr_utils::mr_char	nameDelimiter = _L_('$'),
		mr_utils::mr_char	argDelimiter = _L_('|')
	);


	/// @brief	Default constructor in private scope to avoid construction.
	FileScriptReader() {
		// put public to force export of class
	};


	/// @brief	Default constructor in private scope to avoid construction.
	FileScriptReader(const FileScriptReader& obj) {
		// TODO - check effect  put public to force export of class
	};


	FileScriptReader FileScriptReader::operator=(class CppTest::FileScriptReader const &) {
		// TODO - check effect  put public to force export of class
		return *this;
	}


	/// @brief	Opens the file containing the script.
	///	@throw	Throws a scriptException on empty file name or file not found.
	void Open();


	/// @brief	Extracts the test information from the current test script line.
	/// @param	fixtureName	Name of the fixture for the test case.
	///	@throw	Throws a scriptException on syntax failure.
	/// @return	The populated testInfoObject for the test.  If the object has no more
	///			script lines the testInfoObject.isValid() will return false.
	CppTest::TestInfoObject getNextTest(mr_utils::mr_string& fixtureName);

private:
	std::string				m_filename;		///< The file name of the script.
	mr_utils::mr_ifstream	m_scriptStream;	///< The file object.
	mr_utils::mr_char		m_nameDelimiter;///< Name delimiter.
	mr_utils::mr_char		m_argDelimiter;	///< Argument delimiter.


	/// @brief	Helper method to process one line of the script file.
	/// @param	fixtureName	Name of the fixture for the test case.
	///	@throw	Throws a scriptException on failure
	/// @param	testInfo	The testInfoObject to populate from the script file.
	/// @param	str			The line as read from the file.
	void ProcessLine(mr_utils::mr_string& fixtureName, CppTest::TestInfoObject& testInfo, mr_utils::mr_string str);


	/// @brief	Helper method to process the arguments portion of the script line.
	///	@throw	Throws a scriptException on failure
	/// @param	testInfo	The testInfoObject to populate from the script file.
	/// @param	args		The args portion of the script line.
	void ProcessArgs(CppTest::TestInfoObject& testInfo, const mr_utils::mr_string& args);


	/// @brief	Helper method to process one argument string token.
	/// Each argument should be in the format name=value.
	///	@throw	Throws a scriptException on failure
	/// @param	testInfo	The testInfoObject to populate from the script file.
	/// @param	args		The arg token from the script line.
	void ProcessArg(CppTest::TestInfoObject& testInfo, const mr_utils::mr_string& arg);


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

};

} // end namespace


CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<CppTest::FileScriptReader>;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<CppTest::FileScriptReader>;


#endif
