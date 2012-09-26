///--------------------------------------------------------------------------------------
/// @file	MrTestListBuilderFactory.h
/// @brief	
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------

#include "MrTestListBuilderFactory.h"
#include "MrTestFileScriptReader.h"
#include "IMrTestScriptReader.h"
#include "MrTestCommandLineReader.h"
#include "MrTestVectorLineReader.h"
#include "MrTestVectorTestCaseNamesReader.h"
#include "MrTestListBuilder.h"
#include "IMrTestFixtureTestCaseNames.h"


namespace MrTest {

std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> > 
	ListBuilderFactory::FromFile(
		const mr_utils::mr_string&	filename, 		
		mr_utils::mr_char			nameDelimiter,
		mr_utils::mr_char			argDelimiter) {

	MrTest::FileScriptReader reader(filename, nameDelimiter, argDelimiter);
	reader.Open();
	return MrTest::ListBuilder().Build(reader);
}	


std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> > 
	ListBuilderFactory::FromLine(const mr_utils::mr_string& line) {

	MrTest::CommandLineReader reader(line);
	reader.Open();
	return MrTest::ListBuilder().Build(reader);
}


std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> > 
	ListBuilderFactory::FromLines(
		const std::vector<mr_utils::mr_string>&	lines,
		mr_utils::mr_char						nameDelimiter,
		mr_utils::mr_char						argDelimiter) {

	MrTest::VectorLineReader reader(lines, nameDelimiter, argDelimiter);
	reader.Open();
	return MrTest::ListBuilder().Build(reader);
}


std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> > 
	ListBuilderFactory::FromTestCaseNames(const std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> >& testCaseNames) {
	MrTest::VectorFixtureTestCaseNames reader(testCaseNames);
	return MrTest::ListBuilder().Build(reader);
}




} // end namesapce

