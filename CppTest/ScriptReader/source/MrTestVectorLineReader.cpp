///--------------------------------------------------------------------------------------
/// @file	MrTestVectorLineReader.h
/// @brief	Converts a vector of lines argument to test info
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#include "MrTestVectorLineReader.h"
#include "mr_defines.h"
#include <algorithm>

namespace MrTest {

VectorLineReader::VectorLineReader( 
	const std::vector<mr_utils::mr_string>&	lines,
	mr_utils::mr_char						nameDelimiter,
	mr_utils::mr_char						argDelimiter ) :
		ScriptReaderBase(L("VectorOfLines"), nameDelimiter, argDelimiter),
		m_lines(lines),
		m_index(0) 	{

		this->SortVector();
		this->Open();
}


void VectorLineReader::Open() {
	this->m_index = 0;
}


MrTest::TestInfoObject VectorLineReader::getNextTest(mr_utils::mr_string& fixtureName) {
	MrTest::TestInfoObject		testInfo;
	if ( this->m_index < this->m_lines.size()) {
		if (! this->m_lines[m_index].empty() && this->m_lines[this->m_index][0] != _L_('#')) {
			testInfo.SetNull(false);
			this->ProcessLine(fixtureName, testInfo, this->m_lines[m_index]);
		}
		this->m_index++;
	}
	return testInfo;
}


void VectorLineReader::SortVector() {
	// TODO - implement sorting by fixture and test cases within fixture

	std::sort(this->m_lines.begin(), this->m_lines.end());

}

} // end of namespace
