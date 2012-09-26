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
#include "MrTestVectorTestCaseNamesReader.h"
#include "IMrTestFixtureTestCaseNames.h"


#include "mr_defines.h"
#include "mr_sstream.h"
#include <algorithm>


#include "mr_iostream.h"

namespace MrTest {

VectorFixtureTestCaseNames::VectorFixtureTestCaseNames( 
	const std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> >& infos) :
		ScriptReaderBase(L("VectorOfFixtureTestCaseNames"), _L_('$'), _L_('I')),
		m_infos(infos),
		m_fixtureIndex(0),
		m_testCaseIndex(0) {

		this->Open();
}


void VectorFixtureTestCaseNames::Open() {
	this->m_fixtureIndex = 0;
	this->m_testCaseIndex = 0;
}


MrTest::TestInfoObject VectorFixtureTestCaseNames::getNextTest(mr_utils::mr_string& fixtureName) {

	mr_cout <<L("GetNextTest") << std::endl;

	MrTest::TestInfoObject		testInfo;
	if ( this->m_fixtureIndex < this->m_infos.size()) {
		mr_cout <<L("Got fixture:") << this->m_infos[this->m_fixtureIndex]->FixtureName() << std::endl;

		if (this->m_infos[this->m_fixtureIndex]->TestCaseNames().size() == 0) {
			mr_cout <<L("No test cases") << std::endl;

			// one iteration only for this info - fixture name only means execute all
			testInfo.SetNull(false);
			this->ProcessLine(fixtureName, testInfo, this->m_infos[this->m_fixtureIndex]->FixtureName());
			this->m_fixtureIndex++;
		}
		else {
			if (this->m_testCaseIndex < this->m_infos[this->m_fixtureIndex]->TestCaseNames().size()) {
			mr_cout <<L("Test cases:") << this->m_infos[this->m_fixtureIndex]->TestCaseNames().size() << std::endl;

				// Use current case of current fixture - Test case name has fixture.testCase already complete
				testInfo.SetNull(false);
				this->ProcessLine(fixtureName, testInfo, this->m_infos[this->m_fixtureIndex]->TestCaseNames()[this->m_testCaseIndex]);
				this->m_testCaseIndex++;
			}
			else {
				this->m_testCaseIndex = 0;
				this->m_fixtureIndex++;
				// re-entrant
				testInfo = this->getNextTest(fixtureName);
			}
		}

	}
	return testInfo;
}



} // end of namespace
