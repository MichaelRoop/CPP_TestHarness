///--------------------------------------------------------------------------------------
/// @file	MrTestScriptReader.h
/// @brief	cross platform and char width file script reader.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_FILE_SCRIPT_READER_H)
#define MR_TEST_FILE_SCRIPT_READER_H

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
/// 1.	If there is only one word then it assumes it is a test fixture. The engine will
///		then try to execute all tests in the fixture. Example:  #TokenizerTests1
/// 2.	Two words separated by a '.' is presumed to be fixture and test case names. The
///		Engine will attempt to run the named test case in the names fixture.
///		Example: TokenizerTests1.UTL_TOK_1_1
///	3.	The Fixture and Test case name followd by optional arguments.
///		Example: TokenizerTests1.UTL_TOK_1_3$arg1=3434||arg2=jjf
///
/// The delimiter between name and argument sections is configurable.  The default is
/// the '$' character.
///
/// The arguments portion will be further broken down into name and value pairs.
///
/// The delimiters are configurable between arguments is configurable. The default is 
/// the '|' character.
///
///	Each argument will follow this format:
///		ArgName=ArgValue.
///
/// If the first non whitespace on a line is '#' it will be considered as a comment  
/// and be discarded.
///
/// If the first non whitespace on a line is '@' it will be considered as an inactive 
/// inactive test case. It will not be run but an output entry marked 'DISABLED' will
/// appear in the logs
///
///--------------------------------------------------------------------------------------
class MRTESCASE_API FileScriptReader : public MrTest::ScriptReaderBase {
public:

	/// @brief	Constructor.
	/// @param	filename	The file to load the script from.
	/// @param	nameDelimiter	Delimiter character to tokenize the name and 
	///							argument portion of the line.
	/// @param	argDelimiter	Delimiter to tokenize the argument portion of the
	///							line into separate arguments.
	FileScriptReader( 
		const mr_utils::mr_string&	filename,
		mr_utils::mr_char			nameDelimiter = _L_('$'),
		mr_utils::mr_char			argDelimiter = _L_('|')
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
	mr_utils::mr_string		m_filename;		///< The file name of the script.
	mr_utils::mr_ifstream	m_scriptStream;	///< The file object.

};

} // end namespace

MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::allocator<MrTest::FileScriptReader*>;
MRTESCASE_EXP_TEMPLATE template class MRTESCASE_API std::vector<MrTest::FileScriptReader*>;

#endif
