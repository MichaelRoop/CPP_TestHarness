
#include "CppTestListBuilder.h"
#include "CppTestFixtureInfoObject.h"

namespace MrTest {


std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> > 
	ListBuilder::Build(MrTest::IScriptReader& theReader) const {

	std::vector< mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> > list;

	mr_utils::mr_string currentFixtureName = _L_("");
	mr_utils::mr_string newFixtureName = _L_("");
	MrTest::TestInfoObject info = theReader.getNextTest(newFixtureName);

	mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> fixtureInfo;

	// Create the initial fixture info object if there is any date to accumulate
	if (!info.IsNull()) {
		currentFixtureName = newFixtureName;
		fixtureInfo = new MrTest::TestFixtureInfoObject(currentFixtureName);
	}

	// Evaluate the last test which was read in from the script reader 
	while (!info.IsNull()) {
		if (currentFixtureName != newFixtureName) {
			// The fixture name has changed. Push current Fixture info to vector and start another
			list.push_back(fixtureInfo);
			currentFixtureName = newFixtureName;
			fixtureInfo = new MrTest::TestFixtureInfoObject(currentFixtureName);
		}

		// Add the test info read to the current Fixture info
		fixtureInfo->AddTestInfo(info);
		
		// get the next test info. If null push existing fixtureInfo so it is not lost
		info = theReader.getNextTest(newFixtureName);
		if (info.IsNull() && fixtureInfo.isValid()) {
			list.push_back(fixtureInfo);
		}
	}

	return list;
}

} // end namesapce

