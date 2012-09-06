///--------------------------------------------------------------------------------------
/// @file	MrTestParamParser.h
/// @brief	read in and parse command line arguments
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_PARAM_PARSER_H)
#define MR_TEST_PARAM_PARSER_H

#include "CppTestDefines.h"
#include "mr_string.h"

namespace MrTest {

class ParamParserImplementation;

///--------------------------------------------------------------------------------------
///	@brief	Read in and parse the arguments
///--------------------------------------------------------------------------------------
class CPPTESCASE_API ParamParser {

public:
	/// @brief	Status indicator for the test case.
	typedef enum _ArgType {
		PROGRAM_NAME,	///< Supplied by system. Executable name
		CONFIG_FILE,	///< Configuration file name
		TEST_CASE_LINE,	///< Test fixture or fixture.testCase to execute
		TEST_CASE_LIST,	///< File name for list of test cases
		TEST_CASE_DLL,	///< The DLL containing the test cases to load
		UNKNOWN,

	} ArgType;


	/// @brief	Constructor
	ParamParser();


	/// @brief	Destructor
	virtual ~ParamParser();


	/// @brief	Parse out the narrow character command line arguments
	void Parse(int number, char* args[]);


	/// @brief	Parse out the wide character command line arguments
	void Parse(int number, wchar_t* args[]);


	/// @brief	Report if the parser found an argument of a certain type
	bool HasArg(MrTest::ParamParser::ArgType) const;


	/// @brief	Retrieve an argument of a certain type
	const mr_utils::mr_string& GetArg(MrTest::ParamParser::ArgType) const;


private:
	ParamParserImplementation* m_implementation; ///< Implementation object to hide internals

};

} // end namespace MrTest::Case

#endif
