
#include "CppTestListBuilder.h"

namespace CppTest {


std::vector< mr_utils::SharedPtr<CppTest::ITestFixtureInfoObject> > 
	ListBuilder::Build(CppTest::IScriptReader& theReader) {

	std::vector< mr_utils::SharedPtr<CppTest::ITestFixtureInfoObject> > list;


	//CppTest::TestInfoObject info = theReader.getNextTest();

	// TODO - modify the reader to access the test fixture part of the name

	//while (!info.IsNull()) {
	//	bool infoUnused = false;
	//	if (info.IsActive()) {
	//		// search vector for right test case per name.
	//		std::vector<CppTest::IFixture*>::iterator it = 
	//			std::find_if(
	//				this->m_fixtures.begin(), 
	//				this->m_fixtures.end(), 
	//				HasNamedTestFunctor(info.GetName()));

	//		// check if exists
	//		if (it == this->m_fixtures.end())
	//		{
	//			NonExistantTestData test( info.GetName() );
	//			this->LogResults(test);
	//		}
	//		else
	//		{
	//			while (!info.IsNull()) {
	//				if (info.IsActive()) {
	//					(*it)->RunTest(info.GetName(), info.GetArguments());
	//					this->LogResults((*it)->CurrentTestCase());
	//				}
	//				else {
	//					// TODO - Nope do not do this with script reader. It uses IsActive == false to also to indicate blank lines to skip
	//					//this->LogResults(DisabledTestData(info.GetName()));
	//				}
	//				info = theReader.getNextTest();
	//				if (info.IsNull()) {
	//					(*it)->ResetFixture();
	//					break;
	//				}

	//				if (!(*it)->HasTest(info.GetName())) {
	//					infoUnused = true;
	//					(*it)->ResetFixture();
	//					break;
	//				}
	//			}
	//		}
	//	}

	//	// Only get next if not already hit end. Another case is when the info is valid but unused
	//	if (!info.IsNull() && !infoUnused) {
	//		info = theReader.getNextTest();
	//	}
	//}

	return list;


}

} // end namesapce
