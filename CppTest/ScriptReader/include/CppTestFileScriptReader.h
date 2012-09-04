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

#include "MrTestScriptReaderBase.h"
#include "mr_fstream.h"
#include "mr_char.h" 


namespace MrTest {

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
class CPPTESCASE_API FileScriptReader : public MrTest::ScriptReaderBase {
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


	/// @brief	Opens the file containing the script.
	///	@throw	Throws a scriptException on empty file name or file not found.
	void Open();


	/// @brief	Extracts the test information from the current test script line.
	/// @param	fixtureName	Name of the fixture for the test case.
	///	@throw	Throws a scriptException on syntax failure.
	/// @return	The populated testInfoObject for the test.  If the object has no more
	///			script lines the testInfoObject.isValid() will return false.
	MrTest::TestInfoObject getNextTest(mr_utils::mr_string& fixtureName);

private:
	std::string				m_filename;		///< The file name of the script.
	mr_utils::mr_ifstream	m_scriptStream;	///< The file object.

};

} // end namespace

CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::allocator<MrTest::FileScriptReader*>;
CPPTESCASE_EXP_TEMPLATE template class CPPTESCASE_API std::vector<MrTest::FileScriptReader*>;

#endif
