///--------------------------------------------------------------------------------------
/// @file	MrTestParamParser.cpp
/// @brief	read in and parse command line arguments
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------

#include "MrTestParamParser.h"
#include "mr_sstream.h"
#include "mr_defines.h"
#include "mr_fileException.h"
#include "mr_pointerException.h"
#include <algorithm>

namespace MrTest {

/// @brief	Internal class to group command option value with enum type identifier
class ParamParserArg {
public:
	ParamParserArg(MrTest::ParamParser::ArgType	arg, mr_utils::mr_string value) :
		Arg(arg),
		Value(value) {
	  }

	MrTest::ParamParser::ArgType	Arg;
	mr_utils::mr_string				Value;
};


/// @brief	Functor to find if the vector has a command option type
class HasArgFunctor {
public:
	HasArgFunctor(const MrTest::ParamParser::ArgType& arg) : m_arg(arg) {
	}
	bool operator () (const MrTest::ParamParserArg& arg) {
		return arg.Arg == this->m_arg;
	}
	MrTest::ParamParser::ArgType m_arg;
};


///--------------------------------------------------------------------------------------
///	@brief	Read in and parse the arguments
///--------------------------------------------------------------------------------------
class ParamParserImplementation {

public:

	void Parse(int number, char* args[]) {
		mr_utils::mr_pointerException::ptrAssert(args, _FL_);
		std::vector<mr_utils::mr_string> argList;
		for (int i = 0; i < number; i++) {
			mr_utils::mr_pointerException::ptrAssert(args[i], _FL_);
			argList.push_back(mr_utils::ToMrString(args[i]));
		}
		this->ParseArgs(argList);
	}


	void Parse(int number, wchar_t* args[]) {
		mr_utils::mr_pointerException::ptrAssert(args, _FL_);
		std::vector<mr_utils::mr_string> argList;
		for (int i = 0; i < number; i++) {
			mr_utils::mr_pointerException::ptrAssert(args[i], _FL_);
			argList.push_back(mr_utils::ToMrString(args[i]));
		}
		this->ParseArgs(argList);
	}


	bool HasArg(MrTest::ParamParser::ArgType arg) const {
		return std::find_if(
			this->m_args.begin(), 
			this->m_args.end(), 
			MrTest::HasArgFunctor(arg)) != this->m_args.end();
	}


	const mr_utils::mr_string& GetArg(MrTest::ParamParser::ArgType arg) const {
		std::vector<MrTest::ParamParserArg>::const_iterator it =
			std::find_if(
				this->m_args.begin(), 
				this->m_args.end(), 
				MrTest::HasArgFunctor(arg));

		// Should always validate existence first to avoid secondary validation
		mr_utils::fileException::assertCondition(it != this->m_args.end(), _FL_, L("Arg not found"));
		return it->Value;
	}

private:
	std::vector<MrTest::ParamParserArg> m_args;

	void ParseArgs(const std::vector<mr_utils::mr_string>& argList) {
		if (argList.size() == 1 && (argList[0] == L("-h") || argList[0] == L("--help"))) {
			this->ThrowMsg(_FL_, L(""));
		}
		if (argList.size() < 3) {
			this->ThrowMsg(_FL_, L("There must be at least one valid arg"));
		}
		if (argList.size() % 2 != 1) {
			this->ThrowMsg(_FL_, L("Args must be in indicator / value pairs"));
		}

		//this->m_args.push_back(MrTest::ParamParserArg(MrTest::ParamParser::PROGRAM_NAME, argList[0]));
		for (unsigned int i = 1; i < argList.size(); i += 2) {
			this->AddArg(argList[i], argList[i+1]);
		}
		this->ValidateArgs();
	}


	void AddArg(const mr_utils::mr_string& arg, const mr_utils::mr_string& value) {
		MrTest::ParamParser::ArgType argType = MrTest::ParamParser::PROGRAM_NAME;
		if (arg == L("-d") || arg == L("--dll")) {
			argType = MrTest::ParamParser::TEST_CASE_DLL;
		}
		else if (arg == L("-c") || arg == L("--cfg")) {
			argType = MrTest::ParamParser::CONFIG_FILE;
		}
		else if (arg == L("-t") || arg == L("--test")) {
			argType = MrTest::ParamParser::TEST_CASE_LINE;
		}
		else if (arg == L("-l") || arg == L("--list")) {
			argType = MrTest::ParamParser::TEST_CASE_LIST;
		}
		else {
			mr_utils::mr_stringstream ss;
			ss << L("command option ") << arg << L(" is invalid");
			this->ThrowMsg(_FL_, ss.str());
		}
		this->m_args.push_back(MrTest::ParamParserArg(argType, value));
	}


	/// @brief	Validate combinations, missing options, and duplicates
	void ValidateArgs() {
		if (!this->HasArg(MrTest::ParamParser::TEST_CASE_DLL)) {
			this->ThrowMsg(_FL_, L("No -d|-dll option to open test case DLL"));
		}
		
		if (this->HasArg(MrTest::ParamParser::TEST_CASE_LINE) && 
			this->HasArg(MrTest::ParamParser::TEST_CASE_LIST)) {
			this->ThrowMsg(_FL_, L("-t|-test and -l|-list options are mutually exclusive"));
		}
	}
	

	mr_utils::mr_string ThrowMsg(const char*file, int line, const mr_utils::mr_string& msg) {
		throw mr_utils::mr_exception(file, line, this->GetMsg(msg));
	}


	mr_utils::mr_string GetMsg(const mr_utils::mr_string& msg) {
		mr_utils::mr_stringstream ss;
		ss	<< std::endl;
		if (!msg.empty()) {
			ss	<< msg << std::endl;
		}
		ss	<< L("-------------------") << std::endl
			<< L("programName [-d|-dll] testsuite.dll [[-c|--cfg] configFileName.ini]  [[-t|--test] fixtureName[.testCaseName]]  [[-l|--list] TestCaseListFile.txt]")  << std::endl
			<< L("-------------------") << std::endl
			<< L("-d|--dll The dll containing the test case code to be executed")  << std::endl
			<< L("-c|--cfg configFileName.ini  - Optional - configuration file for extra log outputs")  << std::endl
			<< L("-t|--test fixtureName[.testCaseName] - Optional - Execute a fixture of tests or optionaly one test case in the fixture")  << std::endl
			<< L("-l|--list TestCaseListFile.txt - - Optional - File of test case identifiers to execute")  << std::endl
			<< L("-h|--help This help message")  << std::endl
			<< L("Note: -l|--list and t|-test are mutually exclusive")  << std::endl
			<< std::endl;

		return ss.str();
	}

};



// Exposed ParamParser class wrapper

ParamParser::ParamParser() : m_implementation(0) {
	this->m_implementation = new ParamParserImplementation();
}


ParamParser::~ParamParser() {
	if (this->m_implementation != 0) {
		delete this->m_implementation;
		this->m_implementation = 0;
	}
}


void ParamParser::Parse(int number, char* args[]) {
	this->m_implementation->Parse(number, args);
}


void ParamParser::Parse(int number, wchar_t* args[]) {
	this->m_implementation->Parse(number, args);
}


bool ParamParser::HasArg(MrTest::ParamParser::ArgType arg) const {
	return this->m_implementation->HasArg(arg);
}


const mr_utils::mr_string& ParamParser::GetArg(MrTest::ParamParser::ArgType arg) const {
	return this->m_implementation->GetArg(arg);
}

} // end namespace MrTest::Case

