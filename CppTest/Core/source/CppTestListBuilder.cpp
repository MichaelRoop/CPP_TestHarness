
#include "CppTestListBuilder.h"
#include "CppTestFixtureInfoObject.h"

// temp
#include "mr_iostream.h"

namespace CppTest {


std::vector< mr_utils::SharedPtr<CppTest::TestFixtureInfoObject> > 
	ListBuilder::Build(CppTest::IScriptReader& theReader) const {

	std::vector< mr_utils::SharedPtr<CppTest::TestFixtureInfoObject> > list;

	mr_utils::mr_string currentFixtureName = _L_("");
	mr_utils::mr_string newFixtureName = _L_("");
	CppTest::TestInfoObject info = theReader.getNextTest(newFixtureName);


	//mr_utils::SharedPtr<CppTest::TestFixtureInfoObject> f2(new CppTest::TestFixtureInfoObject(newFixtureName));
	//mr_cout << _L_("Add") << f2->GetName() << std::endl;

	mr_utils::SharedPtr<CppTest::TestFixtureInfoObject> fixtureInfo;
	//mr_utils::SharedPtr<CppTest::TestFixtureInfoObject> fixtureInfo(new CppTest::TestFixtureInfoObject(newFixtureName));
	//mr_utils::SharedPtr<CppTest::ITestFixtureInfoObject> fixtureInfo(reinterpret_cast<CppTest::ITestFixtureInfoObject*>(new CppTest::TestFixtureInfoObject(newFixtureName))); // TODO - find if this needs to be interface template parameter

	//mr_cout << _L_("Add") << (reinterpret_cast<CppTest::TestFixtureInfoObject*>(fixtureInfo.getPtr()))->GetName() << std::endl;


	
	//mr_utils::SharedPtr<CppTest::ITestFixtureInfoObject> fixtureInfo; // TODO - find if this needs to be interface template parameter

	if (!info.IsNull()) {
		currentFixtureName = newFixtureName;

		// dynamic cast does not work due to lack of runtime libraries included

		fixtureInfo = new CppTest::TestFixtureInfoObject(currentFixtureName);
		//fixtureInfo = (CppTest::ITestFixtureInfoObject*)(new CppTest::TestFixtureInfoObject(currentFixtureName));
	//	fixtureInfo = reinterpret_cast<CppTest::ITestFixtureInfoObject*>(new CppTest::TestFixtureInfoObject(currentFixtureName));
		//fixtureInfo = dynamic_cast<CppTest::ITestFixtureInfoObject*>(new CppTest::TestFixtureInfoObject(currentFixtureName));
		mr_cout << _L_("First creation - is valid:") << fixtureInfo.isValid() << std::endl;
	}


	while (!info.IsNull()) {
		mr_cout << _L_("Iteration CurrentName:") << currentFixtureName << _L_("NewName:") << newFixtureName << std::endl;

		if (currentFixtureName != newFixtureName) {
			mr_cout << _L_("%%%%%Push on Fixture Info") << std::endl;
			list.push_back(fixtureInfo);
			currentFixtureName = newFixtureName;

			fixtureInfo = new CppTest::TestFixtureInfoObject(currentFixtureName);
			// dynamic does not work
	//		fixtureInfo = reinterpret_cast<CppTest::ITestFixtureInfoObject*>(new CppTest::TestFixtureInfoObject(currentFixtureName));
			//fixtureInfo = reinterpret_cast<CppTest::ITestFixtureInfoObject*>(new CppTest::TestFixtureInfoObject(currentFixtureName));
			//fixtureInfo = dynamic_cast<CppTest::ITestFixtureInfoObject*>(new CppTest::TestFixtureInfoObject(currentFixtureName));
		}
		//mr_cout << _L_("Add") << fixtureInfo->GetName() << std::endl;


		mr_cout << _L_("++++Push on Test Info") << std::endl;
		fixtureInfo->AddTestInfo(info);
		//(reinterpret_cast<CppTest::TestFixtureInfoObject*>(fixtureInfo.getPtr()))->AddTestInfo(info);


		int i =11;

		//if (currentFixtureName != newFixtureName) {
		//	if (fixtureInfo.isValid()) {
		//		list.push_back(fixtureInfo);
		//		currentFixtureName = newFixtureName;
		//		fixtureInfo = dynamic_cast<CppTest::ITestFixtureInfoObject*>(new CppTest::TestFixtureInfoObject(currentFixtureName));
		//	}
		//	else {
		//		currentFixtureName = newFixtureName;
		//		fixtureInfo = dynamic_cast<CppTest::ITestFixtureInfoObject*>(new CppTest::TestFixtureInfoObject(currentFixtureName));
		//		list.push_back(fixtureInfo);
		//	}
		//}
		//fixtureInfo->AddTestInfo(info);
		
		// get the next test info. If null push existing fixtureInfo so it is not lost
		info = theReader.getNextTest(newFixtureName);
		if (info.IsNull() && fixtureInfo.isValid()) {
			list.push_back(fixtureInfo);
		}





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
	}

	mr_cout << _L_("&&&&&& Builder list - size:") << list.size() <<  std::endl;

	return list;


}

} // end namesapce
